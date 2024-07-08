#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H

#include <QWidget>
#include "snake.h"

namespace s21 {

class SnakeView : public QWidget {
    Q_OBJECT

public:
    explicit SnakeView(Snake* model, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Snake* model_;
};

} // namespace s21

#endif // SNAKE_VIEW_H
