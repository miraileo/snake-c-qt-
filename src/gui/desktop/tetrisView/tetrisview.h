#ifndef TETRISVIEW_H
#define TETRISVIEW_H
#include <QPainter>
#include <QWidget>

#include "../../../brick_game/constants.h"
#include "../../../brick_game/tetris/tetris.h"
class tetrisView : public QWidget {
  Q_OBJECT
 public:
  tetrisView(GameInfo *info, Figure *figure, Figure *nextFigure);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  Figure *m_figure;
  Figure *m_nextFigure;
  GameInfo *m_info;
  void DrawBorders(QPainter &painter);
  void DrawFigure(QPainter &painter);
  void DrawNextFigure(QPainter &painter);
  void DrawGreed(QPainter &painter);
  void DrawField(QPainter &painter);
  void DrawScoreAndLevel(QPainter &painter);
};

#endif  // TETRISVIEW_H
