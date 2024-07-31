#include "mainwindow.h"
Figure figures[] = {
    {{{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}, 3},
    {{{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}, 3},
    {{{1, 1, 0}, {1, 1, 0}, {0, 0, 0}}, 3},
    {{{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}, 3},
    {{{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}, 3},
    {{{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}, 3},
    {{{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 4},
};
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  m_QTimer = new QTimer();
  InitGameInfo(&m_info, &m_figure, &m_nextFigure, figures);
  AllocateMemory(&m_info);
  InitField(m_info);
  m_tetrisView = new tetrisView(&m_info, &m_figure, &m_nextFigure);
  connect(m_QTimer, &QTimer::timeout, this, &MainWindow::UpdateGameState);
  m_QTimer->start(m_info.speed);
  setCentralWidget(m_tetrisView);
}

MainWindow::~MainWindow() { FreeMemory(&m_info); }

void MainWindow::UpdateGameState() {
  if (m_info.startGame == Start) {
    m_QTimer->start(m_info.speed);
    if (!FigureCollision(m_info, m_figure))
      m_info.y++;
    else {
      GameOver(&m_info);
      if (m_info.gameOver) QCoreApplication::quit();
      UpdateCurrentState(&m_info, &m_figure, &m_nextFigure, figures);
    }
    GetScore(&m_info);
    ChangeLevel(&m_info);
    repaint();
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  m_info.inputChar = event->key();
  if (event->key() == TerminateKey) QCoreApplication::quit();
  UserInput(&m_info, &m_figure);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  Q_UNUSED(event);
  m_info.hold = 0;
}
