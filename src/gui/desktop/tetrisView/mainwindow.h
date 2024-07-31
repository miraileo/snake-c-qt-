#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>

#include "tetrisview.h"
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  tetrisView *m_tetrisView;
  Figure m_figure;
  Figure m_nextFigure;
  GameInfo m_info;
  QTimer *m_QTimer;
 private slots:
  void UpdateGameState();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
};
#endif  // MAINWINDOW_H
