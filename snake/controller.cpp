#include "controller.h"
#include <QKeyEvent>
namespace s21 {

SnakeController::SnakeController(Snake* model) : model_(model) {}

void SnakeController::handleInput(int key) {
    switch (key) {
        case Qt::Key_Left:
            model_->changeDirection(Direction::LEFT);
            break;
        case Qt::Key_Right:
            model_->changeDirection(Direction::RIGHT);
            break;
        case Qt::Key_Up:
            model_->changeDirection(Direction::UP);
            break;
        case Qt::Key_Down:
            model_->changeDirection(Direction::DOWN);
            break;
    }
}
}
