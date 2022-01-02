package com.example.lab3.checkers;

public class Checker {
    private final CheckerColour checkerColour;
    private boolean isQueen = false;

    public Checker(CheckerColour checkerColour) {
        this.checkerColour = checkerColour;
    }

    public boolean isQueen() {
        return isQueen;
    }

    public void setQueen(boolean queen) {
        isQueen = queen;
    }

    public CheckerColour getCheckerColour() {
        return checkerColour;
    }
}
