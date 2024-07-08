#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    snake_(10, 20, this),
    snakeController(&snake_, this),
    snakeview(&snake_, this)
{
    snakeController.setFocus();
    ui->setupUi(this);
    setFixedSize(200, 400);
    snake_.start();
}

MainWindow::~MainWindow() {
    delete ui;
}
