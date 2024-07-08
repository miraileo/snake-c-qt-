#include "snake.h"
#include "mainwindow.h"
#include <cstdlib>
#include <ctime>

namespace s21 {

Snake::Snake(int width, int height, MainWindow *parent)
    : width_(width), height_(height), direction_(Direction::RIGHT), state_(GameState::RUNNING), parent_(parent) {
    srand(time(0));
    snake_.emplace_back(height / 2, width / 2);
    for (int i = 1; i < 4; ++i) {
        snake_.emplace_back(height / 2, (width / 2) - i);
    }
    generateApple();
    connect(&timer_, &QTimer::timeout, this, &Snake::updateGame);
}

void Snake::start() {
    timer_.start(200);
}

void Snake::move() {
    if (state_ != GameState::RUNNING) return;

    std::pair<int, int> newHead = snake_.front();
    switch (direction_) {
        case Direction::UP: newHead.first--; break;
        case Direction::DOWN: newHead.first++; break;
        case Direction::LEFT: newHead.second--; break;
        case Direction::RIGHT: newHead.second++; break;
    }
    snake_.push_front(newHead);
    if (isAppleEaten()) {
        grow();
        generateApple();
    } else {
        snake_.pop_back();
    }
    checkCollision();
}

void Snake::updateGame() {
    move();
    if (parent_) {
        parent_->update(); // Вызов обновления интерфейса у MainWindow
    }
    if (state_ != GameState::RUNNING) {
        timer_.stop();
    }
}

void Snake::changeDirection(Direction newDirection) {
    if ((direction_ == Direction::UP && newDirection != Direction::DOWN) ||
        (direction_ == Direction::DOWN && newDirection != Direction::UP) ||
        (direction_ == Direction::LEFT && newDirection != Direction::RIGHT) ||
        (direction_ == Direction::RIGHT && newDirection != Direction::LEFT)) {
        direction_ = newDirection;
    }
}

void Snake::generateApple() {
    bool onSnake;
    do {
        onSnake = false;
        apple_.first = rand() % height_;
        apple_.second = rand() % width_;
        for (auto &part : snake_) {
            if (part == apple_) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

GameState Snake::getState() const {
    return state_;
}

std::vector<std::vector<int>> Snake::getBoard() const {
    std::vector<std::vector<int>> board(height_, std::vector<int>(width_, 0));
    for (auto &part : snake_) {
        board[part.first][part.second] = 1;
    }
    board[apple_.first][apple_.second] = 2;
    return board;
}

void Snake::checkCollision() {
    auto &head = snake_.front();
    if (head.first < 0 || head.first >= height_ || head.second < 0 || head.second >= width_) {
        state_ = GameState::LOST;
        return;
    }
    for (size_t i = 1; i < snake_.size(); ++i) {
        if (snake_[i] == head) {
            state_ = GameState::LOST;
            return;
        }
    }
    if (snake_.size() >= 200) {
        state_ = GameState::WON;
    }
}

bool Snake::isAppleEaten() {
    return snake_.front() == apple_;
}

void Snake::grow() {
    snake_.push_back(snake_.back());
}

} // namespace s21
