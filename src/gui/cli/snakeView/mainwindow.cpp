#include "mainwindow.h"
mainwindow::mainwindow() {
  snake = new s21::SnakeModel();
  level = new s21::Level();
  snakeController = new s21::SnakeController(snake, level);
  apple = new s21::Apple(5, 10);
  snakeview = new s21::snakeView(snake, apple, level);
}
void mainwindow::show() {
  int ch;
  while (!snake->SnakeCollision()) {
    if (level->getSpeed() == 404 || level->winGame()) break;
    snakeController->SnakeControl(ch);
    if (snake->startGame) {
      timeout(level->getSpeed());
      clear();
      snake->snakeMove();
      snake->eatApple(apple);
      if (level->getScore() > level->getMaxScore()) {
        level->setMaxScore(level->getScore());
      }
      level->countLevel();
      level->countScore(apple);
      snakeview->DrawSnake(snake);
      snakeview->DrawApple(apple);
      snakeview->DrawBorders();
      snakeview->DrawStatistics(level);
      refresh();
    }
    ch = getch();
  }
  getch();
  endwin();
}