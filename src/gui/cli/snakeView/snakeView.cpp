#include "snakeView.h"
namespace s21 {
snakeView::snakeView(SnakeModel *m_snake, Apple *m_apple, Level *level)
    : m_snake(m_snake), m_apple(m_apple), level(level) {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
}
void snakeView::DrawSnake(s21::SnakeModel *m_snake) {
  int partIndex = 0;
  for (const auto &part : m_snake->getSnakeBody()) {
    mvaddch(part->getY(), part->getX(), ACS_CKBOARD);
    partIndex++;
  }
}

void snakeView::DrawApple(s21::Apple *m_apple) {
  mvaddch(m_apple->getY(), m_apple->getX(), ACS_CKBOARD);
}

void snakeView::DrawBorders() {
  for (int i = 0; i < 21; i++) {
    mvaddch(i, 10, ACS_CKBOARD);
  }
  for (int i = 0; i < 11; i++) {
    mvaddch(20, i, ACS_CKBOARD);
  }
}
void snakeView::DrawStatistics(s21::Level *level) {
  mvprintw(0, 22, "Score: %d", level->getScore());
  mvprintw(1, 22, "Level: %d", level->getLevel() + 1);
  mvprintw(2, 22, "MaxScore: %d", level->getMaxScore());
}
}  // namespace s21