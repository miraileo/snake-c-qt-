#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>

#include "../../../brick_game/snake/snakeController/snakecontroller.h"
#include "snakeview.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  QTimer *m_QTimer;
  s21::SnakeView *m_snakeView;
  s21::SnakeModel *m_snakeModel;
  s21::Apple *m_apple;
  s21::Level *m_level;
  s21::SnakeController *m_snakeController;
  void updateGameState();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
 private slots:
  void MoveSnakeSlot();
};
#endif  // MAINWINDOW_H
