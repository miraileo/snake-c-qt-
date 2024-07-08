#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snake.h"
#include "snakecontroller.h"
#include "snakeview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    s21::Snake snake_;
    s21::snakeController snakeController;
    s21::SnakeView snakeview;
};

#endif // MAINWINDOW_H
