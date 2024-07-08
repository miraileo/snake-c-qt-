#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <deque>
#include <utility>
#include <QObject>
#include <QTimer>

class MainWindow;

namespace s21 {

enum class Direction { UP, DOWN, LEFT, RIGHT };
enum class GameState { RUNNING, WON, LOST };

class Snake : public QObject {
    Q_OBJECT

public:
    Snake(int width, int height, MainWindow *parent);
    void move();
    void changeDirection(Direction newDirection);
    void generateApple();
    GameState getState() const;
    std::vector<std::vector<int>> getBoard() const;
    void start();

private slots:
    void updateGame();

private:
    int width_;
    int height_;
    std::deque<std::pair<int, int>> snake_;
    std::pair<int, int> apple_;
    Direction direction_;
    GameState state_;
    QTimer timer_;
    MainWindow *parent_;
    void checkCollision();
    bool isAppleEaten();
    void grow();
};

} // namespace s21

#endif // SNAKE_H
