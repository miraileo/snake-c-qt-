#include "snakeview.h"
namespace s21 {
SnakeView::SnakeView(SnakeModel *snakeModel, Apple *appleModel,
                     Level *levelModel)
    : m_snake(snakeModel), m_apple(appleModel), m_level(levelModel) {
  setFixedSize(SNAKEPARTSSIZE * FIELDWIDTH + 150, SNAKEPARTSSIZE * FIELDHEIGTH);
}

void SnakeView::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setPen(Qt::lightGray);
  for (int x = 0; x < FIELDWIDTH; ++x) {
    painter.drawLine(x * SNAKEPARTSSIZE, 0, x * SNAKEPARTSSIZE,
                     SNAKEPARTSSIZE * FIELDHEIGTH);
  }
  for (int y = 0; y < FIELDHEIGTH; ++y) {
    painter.drawLine(0, y * SNAKEPARTSSIZE, SNAKEPARTSSIZE * FIELDWIDTH,
                     y * SNAKEPARTSSIZE);
  }
  int partIndex = 0;
  for (const auto &part : m_snake->getSnakeBody()) {
    if (partIndex == 0) {
      painter.setBrush(Qt::blue);
    } else {
      painter.setBrush(Qt::green);
    }
    painter.drawRect(part->getX() * SNAKEPARTSSIZE,
                     part->getY() * SNAKEPARTSSIZE, SNAKEPARTSSIZE,
                     SNAKEPARTSSIZE);
    partIndex++;
  }
  painter.setBrush(Qt::red);
  painter.drawRect(m_apple->getX() * SNAKEPARTSSIZE,
                   m_apple->getY() * SNAKEPARTSSIZE, SNAKEPARTSSIZE,
                   SNAKEPARTSSIZE);
  painter.setPen(Qt::black);
  painter.setFont(QFont("Arial", 15, QFont::Bold));
  QString scoreText = QString("Score: %1").arg(m_level->getScore());
  QString maxScoreText = QString("MaxScore: %1").arg(m_level->getMaxScore());
  QString levelText = QString("Level: %1").arg(m_level->getLevel() + 1);
  painter.drawText(SNAKEPARTSSIZE * FIELDWIDTH, 0, width(), height(),
                   Qt::AlignTop, scoreText);
  painter.drawText(SNAKEPARTSSIZE * FIELDWIDTH, SNAKEPARTSSIZE, width(),
                   height(), Qt::AlignTop, levelText);
  painter.drawText(SNAKEPARTSSIZE * FIELDWIDTH, 2 * SNAKEPARTSSIZE, width(),
                   height(), Qt::AlignTop, maxScoreText);
}
}  // namespace s21
