#include "plotview.hh"
#include <QPainter>
#include <QPaintEvent>

PlotView::PlotView(Plot *plot, QWidget *parent) :
  QWidget(parent), _plot(plot)
{
  // Destroy view if plot gets destroyed
  QObject::connect(plot, SIGNAL(destroyed()), this, SLOT(deleteLater()));
  // Update plot if data changed
  QObject::connect(plot, SIGNAL(update()), this, SLOT(update()));
  // Requires minimum size
  this->setMinimumSize(800,600);

  // Assemble color-palette
  _palette << QColor(0, 0, 125) << QColor(125, 0, 0) << QColor(0, 125, 0) << QColor(125, 125, 0)
           << QColor(0, 125, 125) << QColor(125, 0, 125) << QColor(205, 79, 18)
           << QColor(255, 185, 24) << QColor(243, 250, 146) << QColor(105, 151, 102)
           << QColor(69, 47, 96) << QColor(224, 26, 53) << QColor(204, 15, 19)
           << QColor(63, 61, 153) << QColor(153, 61, 113) << QColor(61, 153, 86)
           << QColor(61, 90, 153) << QColor(153, 61, 144) << QColor(61, 121, 153)
           << QColor(132, 61, 153) << QColor(153, 78, 61) << QColor(98, 153, 61)
           << QColor(61, 151, 153) << QColor(101, 61, 153) << QColor(153, 61, 75);
}


void
PlotView::paintEvent(QPaintEvent *evt) {
  // First, paint widget background
  QWidget::paintEvent(evt);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setClipRect(evt->rect());
  painter.save();

  painter.fillRect(evt->rect(), Qt::white);

  _drawGraphs(painter);
  _drawAxes(painter);

  painter.restore();
}


void
PlotView::_drawGraphs(QPainter &painter) {
  Plot::iterator graph = _plot->begin();
  QVector<QColor>::iterator color = _palette.begin();
  for (; graph != _plot->end(); graph++, color++) {
    painter.setPen(*color);
    _drawGraph(*graph, painter);
  }
}

void
PlotView::_drawGraph(const Graph &graph, QPainter &painter) {
  double tscale = width()/_plot->maxT();
  double minY = _plot->minY();
  double yscale = height()/(_plot->maxY() - minY);

  if (1 < graph.numValues()) {
    int x1 = tscale*graph.time(0);
    int y1 = height()-yscale*(graph.value(0)-minY);
    for (size_t i=1; i<graph.numValues(); i++) {
      int x2 = tscale*graph.time(i);
      int y2 = height()-yscale*(graph.value(i)-minY);
      painter.drawLine(x1,y1, x2,y2);
      x1 = x2; y1 = y2;
    }
  }
}

void
PlotView::_drawAxes(QPainter &painter) {
  // pass...
}
