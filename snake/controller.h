#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include "snake.h"

namespace s21 {

class SnakeController {
public:
    SnakeController(Snake* model);
    void handleInput(int key);

private:
    Snake* model_;
};

} // namespace s21

#endif
