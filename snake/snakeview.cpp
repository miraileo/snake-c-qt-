#include "snakeview.h"
#include <QPainter>

namespace s21 {

SnakeView::SnakeView(Snake* model, QWidget* parent)
    : QWidget(parent), model_(model) {
    setFixedSize(model_->getBoard()[0].size() * 20, model_->getBoard().size() * 20);
}

void SnakeView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    auto board = model_->getBoard();
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 1) {
                painter.setBrush(Qt::black);
            } else if (board[i][j] == 2) {
                painter.setBrush(Qt::red);
            } else {
                painter.setBrush(Qt::white);
            }
            painter.drawRect(j * 20, i * 20, 20, 20);
        }
    }
}

} // namespace s21
