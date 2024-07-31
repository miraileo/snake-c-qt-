#include "snakecontroller.h"
namespace s21 {
SnakeController::SnakeController(SnakeModel *m_model, Level *m_level)
    : m_model(m_model), m_level(m_level) {}

void SnakeController::SnakeControl(int key) {
  if ((key == QtKeys::QtLeft || key == NcursesKeys::NLeft) &&
      m_model->m_snakeDirection != m_model->SnakeDirection::right) {
    m_model->m_snakeDirection = m_model->SnakeDirection::left;
  } else if ((key == QtKeys::QtUp || key == NcursesKeys::NUp) &&
             m_model->m_snakeDirection != m_model->SnakeDirection::down) {
    m_model->m_snakeDirection = m_model->SnakeDirection::up;
  } else if ((key == QtKeys::QtDown || key == NcursesKeys::NDown) &&
             m_model->m_snakeDirection != m_model->SnakeDirection::up) {
    m_model->m_snakeDirection = m_model->SnakeDirection::down;
  } else if ((key == QtKeys::QtRight || key == NcursesKeys::NRight) &&
             m_model->m_snakeDirection != m_model->SnakeDirection::left) {
    m_model->m_snakeDirection = m_model->SnakeDirection::right;
  } else if (key == QtKeys::QtStartKey || key == NcursesKeys::NStartKey) {
    m_model->startGame = START;
  } else if (key == QtKeys::QtPauseKey || key == NcursesKeys::NPauseKey) {
    m_model->startGame = PAUSE;
  } else if (key == QtKeys::QtSpeedUp) {
    m_level->setSpeed(100);
  } else if (key == QtKeys::QtTerminateKey ||
             key == NcursesKeys::NTerminateKey) {
    m_level->setSpeed(404);
  }
}
}  // namespace s21
