package com.example.lab3;

public class Coordinates {
    public int x;
    public int y;

    public Coordinates(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public static Coordinates toCoordinates(float x, float y, int fieldSize, int cellSize) {
        Coordinates res = new Coordinates((int) (x / cellSize), (int) (y / cellSize));
        if (res.x >= fieldSize || res.y >= fieldSize)
            return null;
        return res;
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof Coordinates))
            return false;

        Coordinates coords = (Coordinates) (o);
        return coords.x == x && coords.y == y;
    }
}
