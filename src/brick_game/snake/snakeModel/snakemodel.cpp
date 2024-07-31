#include "snakemodel.h"
namespace s21 {
/**
 * @brief конструктор
 * устанавливается поля для старта игры в положение старт
 * инициализируется змейка и устанавливается направление движения
 */
SnakeModel::SnakeModel() {
  startGame = START;
  for (int i = 0; i < SNAKEBEGINSIZE; i++) {
    m_snakeBody.push_front(new SnakePart(i, 0));
  }
  m_snakeDirection = SnakeDirection::right;
}
/**
 * @brief движение змейки
 * проверяется направление движения змейки после чего изменяются координаты
 */
void SnakeModel::snakeMove() {
  SnakePart *newSnakePart;
  if (m_snakeDirection == SnakeDirection::right) {
    newSnakePart = new SnakePart(m_snakeBody.front()->getX() + 1,
                                 m_snakeBody.front()->getY());
  } else if (m_snakeDirection == SnakeDirection::left) {
    newSnakePart = new SnakePart(m_snakeBody.front()->getX() - 1,
                                 m_snakeBody.front()->getY());
  } else if (m_snakeDirection == SnakeDirection::up) {
    newSnakePart = new SnakePart(m_snakeBody.front()->getX(),
                                 m_snakeBody.front()->getY() - 1);
  } else {
    newSnakePart = new SnakePart(m_snakeBody.front()->getX(),
                                 m_snakeBody.front()->getY() + 1);
  }

  m_snakeBody.push_front(newSnakePart);
  m_snakeBody.pop_back();
}
/**
 * @brief коллизия с стенами и самой змейкой
 * проверяется коллизия змейки посредством сравнения координат головы змейки с
 * границами и соб. телом змейки
 */
bool SnakeModel::SnakeCollision() {
  bool result = false;
  if (this->m_snakeBody.front()->getX() >= 10 ||
      this->m_snakeBody.front()->getX() <= -1 ||
      this->m_snakeBody.front()->getY() >= 20 ||
      this->m_snakeBody.front()->getY() <= -1) {
    result = true;
  }
  for (auto it = std::next(m_snakeBody.begin()); it != m_snakeBody.end();
       ++it) {
    if (m_snakeBody.front()->getX() == (*it)->getX() &&
        m_snakeBody.front()->getY() == (*it)->getY()) {
      result = true;
    }
  }
  return result;
}
/**
 * @brief коллизия с яблоком
 * проверяется коллизия яблока и головы змейки
 * так же прибаление длинны змейкм и спавн нового яблока
 */
void SnakeModel::eatApple(Apple *apple) {
  if (m_snakeBody.front()->getX() == apple->getX() &&
      m_snakeBody.front()->getY() == apple->getY()) {
    apple->SpawnApple();
    SnakePart *newSnakePart =
        new SnakePart(m_snakeBody.back()->getX(), m_snakeBody.back()->getY());
    setNewPart2SnakeBody(newSnakePart);
    apple->setNumOfApples(apple->getNumOfApples() + 1);
  }
}

std::list<SnakePart *> SnakeModel::getSnakeBody() { return m_snakeBody; }

void SnakeModel::setNewPart2SnakeBody(SnakePart *newSnakePart) {
  m_snakeBody.push_back(newSnakePart);
}

SnakePart::SnakePart(int x, int y) {
  m_x = x;
  m_y = y;
}

int SnakePart::getX() { return m_x; }
int SnakePart::getY() { return m_y; }
/**
 * @brief яблоко
 * рандомный спавн яблока
 */
void Apple::SpawnApple() {
  srand((unsigned)time(NULL));
  m_x = rand() % FIELDWIDTH;
  m_y = rand() % FIELDHEIGTH;
}
Apple::Apple(int x, int y) {
  m_x = x;
  m_y = y;
  m_numOfApples = 0;
}
int Apple::getX() { return m_x; }
int Apple::getNumOfApples() { return m_numOfApples; }
void Apple::setNumOfApples(int num) { m_numOfApples = num; }
int Apple::getY() { return m_y; }
/**
 * @brief конструктор
 * конструктор уровней и скорости
 */
Level::Level() {
  m_level = 0;
  setScore(0);
  speed = STARTSPEED;
  filename = "maxScore.txt";
  maxScore = getMaxScore();
}
int Level::getLevel() { return m_level; }
int Level::getScore() { return m_score; }
void Level::setScore(int score) { m_score = score; }

int Level::getMaxScore() {
  int score = 0;
  std::ifstream inFile(filename);
  inFile >> score;
  inFile.close();
  return score;
}
/**
 * @brief макс. кол. очков
 * запись макс скорости
 */
void Level::setMaxScore(int score) {
  std::ofstream outFile(filename);
  outFile << score;
  outFile.close();
}

int Level::getSpeed() { return speed; }
void Level::setSpeed(int m_speed) { speed = m_speed; }
/**
 * @brief очки
 * подсчет очков
 */
void Level::countScore(Apple *apple) { m_score = apple->getNumOfApples(); }
/**
 * @brief уровень
 * подсчет уровня и скорости
 */
bool Level::countLevel() {
  if (m_score % 5 == 0 && m_level <= 9 && m_score != 0) {
    if (m_score / 5 != m_level) {
      speed -= SPEEDADDITION;
      m_level = m_score / 5;
      return true;
    }
  }
  return false;
}
bool Level::winGame() {
  if (m_score >= 196) return true;
  return false;
}
}  // namespace s21