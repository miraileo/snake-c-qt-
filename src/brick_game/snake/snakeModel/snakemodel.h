#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H
#include <fstream>
#include <iostream>
#include <list>

#include "../../constants.h"
namespace s21 {
class SnakePart;
class Apple;
class SnakeModel {
  friend class SnakeController;

 public:
  int startGame;
  SnakeModel();
  void snakeMove();
  bool SnakeCollision();
  void eatApple(Apple *apple);
  std::list<SnakePart *> getSnakeBody();
  void setNewPart2SnakeBody(SnakePart *newSnakePart);

 private:
  std::list<SnakePart *> m_snakeBody;
  enum SnakeDirection { up, down, left, right };
  SnakeDirection m_snakeDirection;
};

class SnakePart {
 public:
  SnakePart(int x, int y);
  int getX();
  int getY();

 private:
  int m_x;
  int m_y;
};

class Apple {
 private:
  int m_numOfApples;
  int m_x;
  int m_y;

 public:
  Apple(int x, int y);
  int getX();
  int getY();
  int getNumOfApples();
  void setNumOfApples(int num);
  void SpawnApple();
};

class Level {
 private:
  int m_score;
  int m_level;
  int speed;
  int maxScore;
  std::string filename;

 public:
  Level();
  int getLevel();
  int getScore();
  void setScore(int score);
  int getMaxScore();
  void setMaxScore(int score);
  int getSpeed();
  void setSpeed(int m_speed);
  void countScore(Apple *apple);
  bool countLevel();
  bool winGame();
};
}  // namespace s21
#endif  // SNAKEMODEL_H
