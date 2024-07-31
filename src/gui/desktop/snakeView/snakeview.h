#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H
#include <QCoreApplication>
#include <QPainter>
#include <QWidget>

#include "../../../brick_game/constants.h"
#include "../../../brick_game/snake/snakeModel/snakemodel.h"
namespace s21 {
class SnakeView : public QWidget {
  Q_OBJECT
 public:
  SnakeView(SnakeModel *snakeModel, Apple *appleModel, Level *levelModel);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  SnakeModel *m_snake;
  Apple *m_apple;
  Level *m_level;
};
}  // namespace s21
#endif  // SNAKEVIEW_H
