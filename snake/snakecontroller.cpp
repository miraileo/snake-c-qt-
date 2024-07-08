#include "snakecontroller.h"
namespace s21 {

snakeController::snakeController(Snake* snake, QWidget *parent) : QWidget(parent), snake(snake) {}

void snakeController::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Left:
            snake->changeDirection(s21::Direction::LEFT);
            break;
        case Qt::Key_Right:
            snake->changeDirection(s21::Direction::RIGHT);
            break;
        case Qt::Key_Up:
            snake->changeDirection(s21::Direction::UP);
            break;
        case Qt::Key_Down:
            snake->changeDirection(s21::Direction::DOWN);
            break;
        }
    }
}

