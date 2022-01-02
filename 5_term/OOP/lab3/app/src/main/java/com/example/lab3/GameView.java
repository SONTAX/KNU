package com.example.lab3;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Canvas;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

import static java.util.concurrent.Executors.newFixedThreadPool;

public class GameView extends View {
    private final ExecutorService executor = newFixedThreadPool(5);

    private final FieldController fieldController;
    private Future<?> botFuture;


    public GameView(Context context) {
        super(context);
        fieldController = new FieldController(this);

        assignTouchListener();
        startBotThread();
    }

    private void startBotThread() {
        botFuture = executor.submit(() -> {
            try {
                fieldController.startBotCycle();
            } catch (Exception e) {
                Thread.currentThread().interrupt();
            }
        });
    }

    @SuppressLint("ClickableViewAccessibility")
    private void assignTouchListener() {
        setOnTouchListener((v, event) -> {
            Future<?> touchFuture = executor.submit(new OnTouchTask(event, fieldController));
            try {
                touchFuture.get();
            } catch (Exception e) {
                Log.e("Touch exception", Arrays.toString(e.getStackTrace()));
                Thread.currentThread().interrupt();
            }
            return true;
        });
    }

    public void updateView() {
        invalidate();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        fieldController.draw(canvas);
    }

    public Future<?> getBotFuture() {
        return botFuture;
    }

    public FieldController getFieldController() {
        return fieldController;
    }
}

class OnTouchTask implements Runnable {
    private final MotionEvent event;
    private final FieldController fieldController;

    OnTouchTask(MotionEvent event, FieldController fieldController) {
        this.event = event;
        this.fieldController = fieldController;
    }

    @Override
    public void run() {
        if (event == null)
            return;
        if (event.getAction() == MotionEvent.ACTION_UP) {
            fieldController.activatePlayer(event.getX(), event.getY());
        }
    }
}
