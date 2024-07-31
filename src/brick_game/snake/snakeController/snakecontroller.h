#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include "../snakeModel/snakemodel.h"
namespace s21 {
class SnakeController {
 public:
  SnakeController(SnakeModel *m_model, Level *m_level);
  void SnakeControl(int key);

 private:
  SnakeModel *m_model;
  Level *m_level;
};
}  // namespace s21
#endif  // SNAKECONTROLLER_H
