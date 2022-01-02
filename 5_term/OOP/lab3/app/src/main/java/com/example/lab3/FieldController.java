package com.example.lab3;

import android.graphics.Canvas;
import com.example.lab3.cell.Cell;
import com.example.lab3.cell.CellColour;
import com.example.lab3.cell.CellState;
import com.example.lab3.checkers.Checker;
import com.example.lab3.checkers.CheckerColour;
import com.example.lab3.checkersfield.CheckersField;
import com.example.lab3.computer.Computer;
import com.example.lab3.desk.Desk;

import java.util.ArrayList;
import java.util.List;

public class FieldController implements Drawable {
    public static final CheckerColour playerSide = CheckerColour.BLACK;
    private final GameView caller;
    private final Desk desk;
    private int fieldSize;
    private CheckersField checkers;

    private Checker selected;
    private CheckerColour gameState = CheckerColour.BLACK;
    private volatile boolean playerBeatRow = false;
    private List<Coordinates> availableCoords = new ArrayList<>();

    public FieldController(GameView caller) {
        this.caller = caller;
        desk = new Desk();
        checkers = new CheckersField();
    }

    public static CheckerColour other(CheckerColour color) {
        if (color == CheckerColour.BLACK) return CheckerColour.WHITE;
        else return CheckerColour.BLACK;
    }

    @Override
    public void draw(Canvas canvas) {
        desk.draw(canvas);
        checkers.draw(canvas);
    }

    public void startBotCycle() {
        while (!Thread.currentThread().isInterrupted()) {
            if (gameState == other(playerSide)) {
                if (!playerBeatRow) {
                    startBotTurn();
                    reverseState();
                }
            }
        }
    }

    public void activatePlayer(float x, float y) {
        if (gameState == playerSide) {
            Coordinates tapCoords = Coordinates.toCoordinates(x, y, fieldSize, desk.getCellSize());

            if (selected == null) {
                trySelect(tapCoords);
                callUpdate();
            } else {

                if (coordinatesInAvailableCells(tapCoords)) {
                    playerBeatRow = doPlayerStep(tapCoords);
                    Coordinates lastPosition = checkers.find(selected);

                    if (playerBeatRow && canBeatMore(tapCoords)) {
                        playerBeatRow = true;
                        trySelectBeatable(lastPosition);
                    } else {
                        playerBeatRow = false;
                        unselectAll();
                    }
                } else {
                    unselectAll();
                    callUpdate();
                    return;
                }
                callUpdate();

                if (!playerBeatRow) {
                    unselectAll();
                    reverseState();
                }
            }


        }
    }

    public void startBotTurn() {
        boolean botBeatRow;
        Coordinates checkerCoords = Computer.chooseChecker(checkers, other(playerSide), 300);
        if (checkerCoords == null) return;
        Checker checkerBot = checkers.getChecker(checkerCoords);
        trySelect(checkerCoords);
        callUpdate();
        Coordinates moveCoords = Computer.chooseMove(checkers, checkerBot, 300);
        if (moveCoords == null) return;
        botBeatRow = checkers.move(checkerBot, moveCoords.x, moveCoords.y);
        unselectAll();
        callUpdate();

        while (botBeatRow && canBeatMore(moveCoords)) {
            unselectAll();
            trySelectBeatable(moveCoords);
            callUpdate();
            moveCoords = Computer.chooseMove(checkers, checkerBot, 300);
            if (moveCoords != null) botBeatRow = checkers.move(checkerBot, moveCoords.x, moveCoords.y);
            else botBeatRow = false;
            callUpdate();
        }
        unselectAll();
    }

    public void callUpdate() {
        if (caller != null) caller.invalidate();
    }

    private boolean doPlayerStep(Coordinates tapCoords) {
        Coordinates oldCoords = checkers.find(selected);
        if (oldCoords.equals(tapCoords)) return false;
        return checkers.move(selected, tapCoords.x, tapCoords.y);
    }

    public boolean canBeatMore(Coordinates lastPosition) {
        if (lastPosition == null) return false;
        Checker checker = checkers.getChecker(lastPosition);
        List<Coordinates> beatable = checkers.canBeat(checker);
        return !beatable.isEmpty();
    }

    private boolean coordinatesInAvailableCells(Coordinates tapCoordinates) {
        if (tapCoordinates == null) return false;
        for (Coordinates coords : availableCoords) {
            if (tapCoordinates.equals(coords)) return true;
        }
        return false;
    }

    private void trySelect(Coordinates coordinates) {
        if (coordinates == null) return;
        unselectAll();
        Cell cell = desk.getCell(coordinates);
        Checker checker = checkers.getChecker(coordinates);

        if (cell != null && checker != null && cell.getCellColor() == CellColour.BLACK && checker.getCheckerColour().equals(gameState)) {
            cell.setCurrentState(CellState.ACTIVE);
            selected = checker;

            activateAvailable(checker);
        }
    }

    private void trySelectBeatable(Coordinates coords) {
        if (coords == null) return;
        Cell cell = desk.getCell(coords);
        Checker checker = checkers.getChecker(coords);

        if (cell != null && checker != null && cell.getCellColor() == CellColour.BLACK && checker.getCheckerColour().equals(gameState)) {
            cell.setCurrentState(CellState.ACTIVE);
            selected = checker;

            activateAvailableBeatable(checker);
        }
    }

    public void reverseState() {
        gameState = other(gameState);
    }

    private void unselectAll() {
        selected = null;
        availableCoords.clear();
        desk.unselectAll();
    }

    private void activateAvailable(Checker checker) {
        if (activationPreparation(checker)) return;
        availableCoords = checkers.buildAvailable(checker);
        setActiveToAvailable();
    }

    private void activateAvailableBeatable(Checker checker) {
        if (activationPreparation(checker)) return;
        availableCoords = checkers.canBeat(checker);
        setActiveToAvailable();
    }

    private boolean activationPreparation(Checker checker) {
        if (checker == null) return true;
        availableCoords.clear();
        desk.unselectAll();
        return false;
    }

    private void setActiveToAvailable() {
        for (Coordinates coords : availableCoords) {
            desk.getCell(coords).setCurrentState(CellState.ACTIVE);
        }
    }

    public CheckersField getCheckers() {
        return checkers;
    }

    public void setCheckers(CheckersField checkers) {
        this.checkers = checkers;
    }
}
