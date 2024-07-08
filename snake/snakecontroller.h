#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H
#include <QKeyEvent>
#include <QWidget>
#include "snake.h"
namespace s21 {
class snakeController: public QWidget
{
    Q_OBJECT
public:
    snakeController(Snake* snake, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Snake *snake;

};
}

#endif // SNAKECONTROLLER_H
