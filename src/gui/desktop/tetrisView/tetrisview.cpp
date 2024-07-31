#include "tetrisview.h"
tetrisView::tetrisView(GameInfo *info, Figure *figure, Figure *nextFigure)
    : m_figure(figure), m_nextFigure(nextFigure), m_info(info) {
  setFixedSize(SNAKEPARTSSIZE * WIDTH + 150, SNAKEPARTSSIZE * HEIGHT);
}

void tetrisView::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  DrawGreed(painter);
  DrawBorders(painter);
  DrawField(painter);
  DrawFigure(painter);
  DrawScoreAndLevel(painter);
  DrawNextFigure(painter);
}

void tetrisView::DrawBorders(QPainter &painter) {
  painter.setBrush(Qt::black);
  for (int i = 0; i < HEIGHT; i++) {
    painter.drawRect((WIDTH - 1) * SNAKEPARTSSIZE, i * SNAKEPARTSSIZE,
                     SNAKEPARTSSIZE, SNAKEPARTSSIZE);
  }
  for (int i = 0; i < HEIGHT; i++) {
    painter.drawRect(0, i * SNAKEPARTSSIZE, SNAKEPARTSSIZE, SNAKEPARTSSIZE);
  }
  for (int i = 0; i < WIDTH; i++) {
    painter.drawRect(i * SNAKEPARTSSIZE, (HEIGHT - 1) * SNAKEPARTSSIZE,
                     SNAKEPARTSSIZE, SNAKEPARTSSIZE);
  }
}
void tetrisView::DrawGreed(QPainter &painter) {
  painter.setPen(Qt::black);
  for (int x = 0; x < WIDTH; ++x) {
    painter.drawLine(x * SNAKEPARTSSIZE, 0, x * SNAKEPARTSSIZE,
                     SNAKEPARTSSIZE * HEIGHT);
  }
  for (int y = 0; y < HEIGHT; ++y) {
    painter.drawLine(0, y * SNAKEPARTSSIZE, SNAKEPARTSSIZE * WIDTH,
                     y * SNAKEPARTSSIZE);
  }
}
void tetrisView::DrawFigure(QPainter &painter) {
  painter.setBrush(Qt::yellow);
  for (int i = 0; i < m_figure->size; i++) {
    for (int j = 0; j < m_figure->size; j++) {
      if (m_figure->matrix[i][j] == 1) {
        painter.drawRect((m_info->x + j) * SNAKEPARTSSIZE,
                         (m_info->y + i) * SNAKEPARTSSIZE, SNAKEPARTSSIZE,
                         SNAKEPARTSSIZE);
      }
    }
  }
}
void tetrisView::DrawField(QPainter &painter) {
  painter.setBrush(Qt::blue);
  for (int i = 0; i < HEIGHT - 1; i++) {
    for (int j = 1; j < WIDTH - 1; j++) {
      if (m_info->array[i][j] == 1) {
        painter.drawRect(j * SNAKEPARTSSIZE, i * SNAKEPARTSSIZE, SNAKEPARTSSIZE,
                         SNAKEPARTSSIZE);
      }
    }
  }
}

void tetrisView::DrawScoreAndLevel(QPainter &painter) {
  QString scoreText = QString("Score: %1").arg(m_info->score);
  QString levelText = QString("Level: %1").arg(m_info->level);
  QString maxScoreText = QString("MaxScore: %1").arg(m_info->highScore);
  painter.drawText(SNAKEPARTSSIZE * WIDTH, 0, width(), height(), Qt::AlignTop,
                   scoreText);
  painter.drawText(SNAKEPARTSSIZE * WIDTH, SNAKEPARTSSIZE, width(), height(),
                   Qt::AlignTop, levelText);
  painter.drawText(SNAKEPARTSSIZE * WIDTH, SNAKEPARTSSIZE * 2, width(),
                   height(), Qt::AlignTop, maxScoreText);
}

void tetrisView::DrawNextFigure(QPainter &painter) {
  painter.setBrush(Qt::yellow);
  for (int i = 0; i < m_nextFigure->size; i++) {
    for (int j = 0; j < m_nextFigure->size; j++) {
      if (m_nextFigure->matrix[i][j] == 1) {
        painter.drawRect((j + WIDTH) * SNAKEPARTSSIZE, (i + 3) * SNAKEPARTSSIZE,
                         SNAKEPARTSSIZE, SNAKEPARTSSIZE);
      }
    }
  }
}
