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
  QPen pen = painter.pen();
  pen.setWidth(2);

  Plot::iterator graph = _plot->begin();
  QVector<QColor>::iterator color = _palette.begin();
  for (; graph != _plot->end(); graph++, color++) {
    pen.setColor(*color); painter.setPen(pen);
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
  int32_t height = this->size().height();
  int32_t width = this->size().width();

  QPen pen(Qt::black);
  pen.setWidth(1); pen.setCosmetic(true);
  painter.setPen(pen);

  QFont font; font.setPointSize(10);
  QFontMetrics fm(font);
  painter.setFont(font);

  double dy = (_plot->maxY()-_plot->minY())/8, v = _plot->maxY()-dy;
  for (size_t i=1; i<8; i++, v-=dy) {
    int y = (i*height)/8;
    QString label = QString::number(v, 'g', 3);
    QRectF bb = fm.boundingRect(label);
    float shift = bb.height()/2 - fm.ascent();
    painter.drawText(3, y-shift, label);
    painter.drawText(width-bb.width()-3, y-shift, label);
  }

  double dh = double(_plot->maxT())/8, h = dh;
  for (size_t i=1; i<8; i++, h+=dh) {
    int x = (i*width)/8;

    QString unit = "ms";
    QString label = QString("%1 %2");
    if (h > 1e3) { label = label.arg(QString::number(h/1000, 'g', 3), "s"); }
    else { label = label.arg(QString::number(h, 'g', 3), "ms"); }

    QRectF bb = fm.boundingRect(label);
    painter.drawText(x-bb.width()/2, height-3-fm.underlinePos(), label);
    painter.drawText(x-bb.width()/2, 3+bb.height(), label);

  }
}
