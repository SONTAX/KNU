package com.example.lab3.checkersfield;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import com.example.lab3.Coordinates;
import com.example.lab3.Drawable;
import com.example.lab3.checkers.Checker;
import com.example.lab3.checkers.CheckerColour;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CheckersField implements Drawable {
    private Checker[][] checkersField;
    private final Paint paint;
    private int cellSize;
    private int checkerSize;

    public CheckersField() {
        this.checkersField = new Checker[8][8];
        initializeCheckers();
        paint = new Paint();
    }

    public void initializeCheckers() {
        checkersField[0][1] = new Checker(CheckerColour.WHITE);
        checkersField[0][3] = new Checker(CheckerColour.WHITE);
        checkersField[0][5] = new Checker(CheckerColour.WHITE);
        checkersField[0][7] = new Checker(CheckerColour.WHITE);
        checkersField[1][0] = new Checker(CheckerColour.WHITE);
        checkersField[1][2] = new Checker(CheckerColour.WHITE);
        checkersField[1][4] = new Checker(CheckerColour.WHITE);
        checkersField[1][6] = new Checker(CheckerColour.WHITE);
        checkersField[2][1] = new Checker(CheckerColour.WHITE);
        checkersField[2][3] = new Checker(CheckerColour.WHITE);
        checkersField[2][5] = new Checker(CheckerColour.WHITE);
        checkersField[2][7] = new Checker(CheckerColour.WHITE);
        checkersField[5][0] = new Checker(CheckerColour.BLACK);
        checkersField[5][2] = new Checker(CheckerColour.BLACK);
        checkersField[5][4] = new Checker(CheckerColour.BLACK);
        checkersField[5][6] = new Checker(CheckerColour.BLACK);
        checkersField[6][1] = new Checker(CheckerColour.BLACK);
        checkersField[6][3] = new Checker(CheckerColour.BLACK);
        checkersField[6][5] = new Checker(CheckerColour.BLACK);
        checkersField[6][7] = new Checker(CheckerColour.BLACK);
        checkersField[7][0] = new Checker(CheckerColour.BLACK);
        checkersField[7][2] = new Checker(CheckerColour.BLACK);
        checkersField[7][4] = new Checker(CheckerColour.BLACK);
        checkersField[7][6] = new Checker(CheckerColour.BLACK);

    }

    @Override
    public void draw(Canvas canvas) {
        cellSize = canvas.getWidth() / 8;
        checkerSize = cellSize / 3;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (checkersField[i][j] != null) {
                    if (checkersField[i][j].getCheckerColour() == CheckerColour.BLACK) {
                        paint.setColor(Color.rgb(255, 0, 0));
                    } else {
                        paint.setColor(Color.rgb(255, 255, 255));
                    }
                    canvas.drawCircle(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2, checkerSize, paint);
                    if (checkersField[i][j].isQueen()) {
                        canvas.drawCircle(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2, checkerSize * 0.66f, paint);
                    }
                }
            }
        }
    }

    public Checker getChecker(int row, int col) {
        if (border(row) && border(col))
            return checkersField[col][row];
        return null;
    }

    public Checker getChecker(Coordinates coords) {
        return checkersField[coords.y][coords.x];
    }

    public Coordinates find(Checker checker) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (checkersField[i][j] == null)
                    continue;
                if (checkersField[i][j].equals(checker))
                    return new Coordinates(j, i);
            }
        }
        return null;
    }

    public void remove(int col, int row) {
        checkersField[row][col] = null;
    }

    public boolean move(Checker checker, int x, int y) {
        boolean haveBeaten = false;
        Coordinates found = find(checker);
        if (found != null && !(found.x == x && found.y == y))
            haveBeaten = beat(found.x, found.y, x, y);
        checkersField[y][x] = checker;
        if (found != null) {
            remove(found.x, found.y);
        }
        return haveBeaten;
    }

    private boolean beat(int xStart, int yStart,
                         int xEnd, int yEnd) {
        boolean haveBeaten = false;
        int xDir = xEnd - xStart;
        int yDir = yEnd - yStart;
        if (xDir == 0 || yDir == 0)
            return false;
        xDir = xDir / Math.abs(xDir);
        yDir = yDir / Math.abs(yDir);
        int xCurr = xStart;
        int yCurr = yStart;
        while (xEnd - xCurr != 0) {
            xCurr += xDir;
            yCurr += yDir;
            if (checkersField[yCurr][xCurr] != null)
                haveBeaten = true;
            checkersField[yCurr][xCurr] = null;
        }
        return haveBeaten;
    }
    public List<Coordinates> buildAvailable(Checker checker) {
        Coordinates coords = find(checker);
        int x = coords.x;
        int y = coords.y;
        List<Coordinates> result = new ArrayList<>();
        if (!checker.isQueen()) {
            if (checker.getCheckerColour() == CheckerColour.BLACK) {
                tryMove(x, y, -1, -1, checker, result);
                tryMove(x, y, 1, -1, checker, result);

                tryBeat(x, y, -1, 1, checker, result);
                tryBeat(x, y, 1, 1, checker, result);
            } else {
                tryBeat(x, y, -1, -1, checker, result);
                tryBeat(x, y, 1, -1, checker, result);

                tryMove(x, y, -1, 1, checker, result);
                tryMove(x, y, 1, 1, checker, result);
            }

        } else if (checker.isQueen()) {
            moveInVector(x, y, 1, 1, checker, result);
            moveInVector(x, y, 1, -1, checker, result);
            moveInVector(x, y, -1, 1, checker, result);
            moveInVector(x, y, -1, -1, checker, result);
        }
        return result;
    }

    private void moveInVector(int x, int y, int vx, int vy, Checker current, List<Coordinates> result) {
        while (border(x + vx) && border(y + vy)) {
            x = x + vx;
            y = y + vy;
            Checker other = getChecker(x, y);
            if (other != null) {
                if (other.getCheckerColour() == current.getCheckerColour())
                    return;
                if (border(x + vx) && border(y + vy)) {
                    other = getChecker(x + vx, y + vy);
                    if (other == null) {
                        result.add(new Coordinates(x + vx, y + vy));
                    }
                    return;
                }
            } else {
                result.add(new Coordinates(x, y));
            }
        }
    }

    private void beatInVector(int x, int y, int vx, int vy, Checker current, List<Coordinates> result) {
        while (border(x + vx) && border(y + vy)) {
            x = x + vx;
            y = y + vy;
            Checker other = getChecker(x, y);
            if (other != null) {
                if (other.getCheckerColour() == current.getCheckerColour())
                    return;
                if (border(x + vx) && border(y + vy)) {
                    other = getChecker(x + vx, y + vy);
                    if (other == null) {
                        result.add(new Coordinates(x + vx, y + vy));
                    }
                    return;
                }
            }
        }
    }

    private void tryMove(int x, int y, int dx, int dy, Checker current, List<Coordinates> res) {
        if (border(x, dx) && border(y, dy)) {
            Checker checkerOther = getChecker(x + dx, y + dy);
            if (checkerOther == null) {
                res.add(new Coordinates(x + dx, y + dy));
            } else if (checkerOther.getCheckerColour() != current.getCheckerColour()
                    && border(x, 2 * dx)
                    && border(y, 2 * dy)) {
                checkerOther = getChecker(x + 2 * dx, y + 2 * dy);
                if (checkerOther == null) {
                    res.add(new Coordinates(x + 2 * dx, y + 2 * dy));
                }
            }
        }
    }

    public Map<Checker, List<Coordinates>> getAvailableListByColor(CheckerColour color) {
        Map<Checker, List<Coordinates>> result = new HashMap<>();
        for (Checker[] row : checkersField) {
            for (Checker checker : row) {
                if (checker == null)
                    continue;
                if (checker.getCheckerColour() == color) {
                    List<Coordinates> availableForThisChecker = buildAvailable(checker);
                    result.put(checker, availableForThisChecker);
                }
            }
        }
        return result;
    }

    private void tryBeat(int x, int y, int dx, int dy, Checker current, List<Coordinates> result) {
        if (border(x, dx) && border(y, dy)) {
            Checker checkerOther = getChecker(x + dx, y + dy);
            if (checkerOther != null && checkerOther.getCheckerColour() != current.getCheckerColour()
                    && border(x, 2 * dx)
                    && border(y, 2 * dy)) {
                checkerOther = getChecker(x + 2 * dx, y + 2 * dy);
                if (checkerOther == null) {
                    result.add(new Coordinates(x + 2 * dx, y + 2 * dy));
                }
            }
        }
    }

    public List<Coordinates> canBeat(Checker checker) {
        List<Coordinates> result = new ArrayList<>();
        Coordinates coords = find(checker);
        int x = coords.x;
        int y = coords.y;
        if (!checker.isQueen()) {
            tryBeat(x, y, -1, 1, checker, result);
            tryBeat(x, y, 1, 1, checker, result);
            tryBeat(x, y, -1, -1, checker, result);
            tryBeat(x, y, 1, -1, checker, result);
        } else {
            beatInVector(x, y, 1, 1, checker, result);
            beatInVector(x, y, 1, -1, checker, result);
            beatInVector(x, y, -1, 1, checker, result);
            beatInVector(x, y, -1, -1, checker, result);
        }
        return result;
    }

    public int count(CheckerColour color) {
        int counter = 0;
        for (Checker[] row : checkersField) {
            for (Checker checker : row) {
                if (checker != null && checker.getCheckerColour() == color)
                    counter++;
            }
        }
        return counter;
    }

    private boolean border(int a, int da) {
        return border(a + da);
    }

    private boolean border(int a) {
        return (a >= 0) && a < 8;
    }
}
