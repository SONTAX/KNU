package com.example.lab3.cell;

import android.graphics.Color;
import android.graphics.Paint;

public class Cell {
    private CellColour cellColor;
    private int colorIdle;

    private Paint paint;
    private CellState currentState = CellState.IDLE;

    public Cell(CellColour color) {
        cellColor = color;
        this.paint = new Paint();

        if (color == CellColour.BLACK) {
            setColorIdle(Color.rgb(50, 50, 50));
        } else if (color == CellColour.WHITE) {
            setColorIdle(Color.rgb(255, 255, 255));
        }
    }

    public int getColorIdle() {
        return colorIdle;
    }

    public void setColorIdle(int colorIdle) {
        this.colorIdle = colorIdle;
        this.paint.setColor(colorIdle);
    }

    public Paint getPaint() {
        return paint;
    }

    public CellState getCurrentState() {
        return currentState;
    }

    public void setCurrentState(CellState currentState) {
        this.currentState = currentState;
        if (currentState == CellState.IDLE) {
            paint.setColor(colorIdle);
        } else if (currentState == CellState.ACTIVE) {
            paint.setColor(Color.rgb(171, 47, 188));
        }
    }

    public CellColour getCellColor() {
        return cellColor;
    }

    public void setCellColor(CellColour cellColor) {
        this.cellColor = cellColor;
    }
}

