#ifndef PLOTVIEW_HH
#define PLOTVIEW_HH

#include <QWidget>
#include "plot.hh"

class PlotView : public QWidget
{
  Q_OBJECT
public:
  explicit PlotView(Plot *plot, QWidget *parent = 0);

public slots:
  bool save(const QString &filename);

protected:
  void paintEvent(QPaintEvent *evt);
  void _draw(QPainter &painter);
  void _drawAxes(QPainter &painter);
  void _drawGraphs(QPainter &painter);
  void _drawGraph(const Graph &graph, QPainter &painter);

protected:
  Plot *_plot;
  QVector<QColor> _palette;
};

#endif // PLOTVIEW_HH
