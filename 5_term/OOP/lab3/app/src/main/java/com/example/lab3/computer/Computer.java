package com.example.lab3.computer;

import com.example.lab3.Coordinates;
import com.example.lab3.checkers.Checker;
import com.example.lab3.checkers.CheckerColour;
import com.example.lab3.checkersfield.CheckersField;

import java.util.List;
import java.util.Map;
import java.util.Random;

public class Computer {
    private static Random random = new Random();

    public static Coordinates chooseChecker(CheckersField checkers, CheckerColour botColor, long delay) {
        waitFor(delay);
        Map<Checker, List<Coordinates>> available = checkers.getAvailableListByColor(botColor);
        Coordinates result = null;
        for (Map.Entry<Checker, List<Coordinates>> entry : available.entrySet()) {
            if (!entry.getValue().isEmpty()) {
                result = checkers.find(entry.getKey());
                break;
            }
        }
        return result;
    }

    public static Coordinates chooseMove(CheckersField checkers, Checker checker, long delay) {
        List<Coordinates> available = checkers.buildAvailable(checker);
        if (available.isEmpty())
            return null;
        List<Coordinates> canBeat = checkers.canBeat(checker);
        if (canBeat.size() == 0) {
            return available.get(random.nextInt(available.size()));
        } else {
            return canBeat.get(random.nextInt(canBeat.size()));
        }
    }

    private static void waitFor(long delay) {
        try {
            Thread.sleep(delay);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
