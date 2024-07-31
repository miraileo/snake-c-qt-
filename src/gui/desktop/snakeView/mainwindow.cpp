#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  m_snakeModel = new s21::SnakeModel();
  m_apple = new s21::Apple(5, 10);
  m_level = new s21::Level();
  m_snakeView = new s21::SnakeView(m_snakeModel, m_apple, m_level);
  m_snakeController = new s21::SnakeController(m_snakeModel, m_level);
  m_QTimer = new QTimer();
  connect(m_QTimer, &QTimer::timeout, this, &MainWindow::MoveSnakeSlot);
  m_QTimer->start(STARTSPEED);
  setCentralWidget(m_snakeView);
}

MainWindow::~MainWindow() {}

void MainWindow::updateGameState() {
  if (m_level->getSpeed() == 404 || m_level->winGame())
    QCoreApplication::quit();
  if (m_snakeModel->startGame) {
    m_snakeModel->snakeMove();
    m_level->countScore(m_apple);
    m_snakeModel->eatApple(m_apple);
    m_level->countLevel();
    m_QTimer->start(m_level->getSpeed());
    if (m_snakeModel->SnakeCollision()) {
      QCoreApplication::quit();
    }
    if (m_level->getScore() > m_level->getMaxScore()) {
      m_level->setMaxScore(m_level->getScore());
    }
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  m_snakeController->SnakeControl(event->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  Q_UNUSED(event);
  m_level->setSpeed(STARTSPEED - (m_level->getLevel() * SPEEDADDITION));
}

void MainWindow::MoveSnakeSlot() {
  updateGameState();
  repaint();
}
