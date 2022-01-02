package com.example.lab3.desk;

import android.graphics.Canvas;
import com.example.lab3.Coordinates;
import com.example.lab3.Drawable;
import com.example.lab3.cell.Cell;
import com.example.lab3.cell.CellColour;
import com.example.lab3.cell.CellState;

public class Desk implements Drawable {
    private int cellSize;
    private Cell[][] cells;

    public Desk() {
        cells = new Cell[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    cells[j][i] = new Cell(CellColour.WHITE);
                } else
                    cells[j][i] = new Cell(CellColour.BLACK);
            }
        }
    }

    private void initCells(int columns, int rows) {
    }

    @Override
    public void draw(Canvas canvas) {
        cellSize = canvas.getWidth() / 8;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                canvas.drawRect(j * cellSize, i * cellSize,
                        j * cellSize + cellSize, i * cellSize + cellSize,
                        cells[j][i].getPaint());
            }
        }
    }

    public Cell getCell(Coordinates coordinates) {
        if (!border(coordinates))
            return null;
        return cells[coordinates.x][coordinates.y];
    }

    public int getCellSize() {
        return cellSize;
    }

    public void setCellSize(int size) {
        cellSize = size;
    }

    public void unselectAll() {
        for (Cell[] cellRow : cells) {
            for (Cell cell : cellRow) {
                cell.setCurrentState(CellState.IDLE);
            }
        }
    }

    private boolean border(Coordinates coordinates) {
        return border(coordinates.x) && border(coordinates.y);
    }

    private boolean border(int a, int da) {
        return border(a + da);
    }

    private boolean border(int a) {
        return (a >= 0) && a < 8;
    }
}
