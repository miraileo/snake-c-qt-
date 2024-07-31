#include <unistd.h>

#include "snakeView.h"
class mainwindow {
 public:
  mainwindow();
  void show();

 private:
  s21::snakeView *snakeview;
  s21::SnakeModel *snake;
  s21::Level *level;
  s21::SnakeController *snakeController;
  s21::Apple *apple;
};