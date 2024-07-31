#include <ncurses.h>

#include <iostream>

#include "../../../brick_game/snake/snakeController/snakecontroller.h"
#include "../../../brick_game/snake/snakeModel/snakemodel.h"

namespace s21 {
class snakeView {
 public:
  snakeView(SnakeModel *m_snake, Apple *m_apple, Level *level);
  void DrawSnake(SnakeModel *m_snake);
  void DrawApple(Apple *m_apple);
  void DrawBorders();
  void DrawStatistics(Level *level);

 private:
  SnakeModel *m_snake;
  Apple *m_apple;
  Level *level;
};
}  // namespace s21