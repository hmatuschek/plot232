#include "plot.hh"
#include <cmath>


/* ********************************************************************************************* *
 * Implementation of Graph
 * ********************************************************************************************* */
Graph::Graph()
  : _values(), _minY(0), _maxY(0)
{
  // Pass....
}

Graph::~Graph() {
  // pass....
}

void
Graph::addValue(double t, double y) {
  _values.push_back(QPair<double, double>(t,y));
  // Update min & max Y
  _minY = std::min(_minY, y);
  _maxY = std::max(_minY, y);
  _minY = std::floor(_minY/10)*10;
  _maxY = std::ceil(_maxY/10)*10;
}

double
Graph::minY() const {
  return _minY;
}

double
Graph::maxY() const {
  return _maxY;
}

size_t
Graph::numValues() const {
  return _values.size();
}

double
Graph::time(size_t i) const {
  return _values[i].first;
}

double
Graph::value(size_t i) const {
  return _values[i].second;
}


/* ********************************************************************************************* *
 * Implementation of Plot
 * ********************************************************************************************* */
Plot::Plot(QObject *parent) :
  QObject(parent), _graphs(), _timer(), _tmax(0)
{
  _timer.invalidate();
}

void
Plot::addValues(const QList<double> &values)
{
  // Get time
  qint64 time = 0;
  if (! _timer.isValid()) { _timer.start(); }
  else { time = _timer.elapsed(); }

  // Store new values
  QList<double>::const_iterator val = values.begin();
  QList<Graph>::iterator graph = _graphs.begin();
  for (; val != values.end(); val++, graph++) {
    // More columns that graphs -> add one
    if (_graphs.end() == graph) {
      _graphs.push_back(Graph());
      graph = _graphs.end(); graph--;
    }
    graph->addValue(time, *val);
  }

  // Update plot range
  _tmax = std::max(_tmax, double(time));
  _tmax = std::ceil(_tmax/10)*10;

  // Signal updated graphs
  emit update();
}

size_t
Plot::numGraphs() const {
  return _graphs.size();
}

const Graph &
Plot::graph(size_t i) const {
  return _graphs.at(i);
}

Plot::iterator
Plot::begin() {
  return _graphs.begin();
}

Plot::iterator
Plot::end() {
  return _graphs.end();
}

double
Plot::maxT() const {
  return _tmax;
}

double
Plot::minY() const {
  double minY = 0;
  QList<Graph>::const_iterator graph = _graphs.begin();
  for (; graph!=_graphs.end(); graph++) {
    minY = std::min(minY, graph->minY());
  }
  return minY;
}

double
Plot::maxY() const {
  double maxY = 0;
  QList<Graph>::const_iterator graph = _graphs.begin();
  for (; graph!=_graphs.end(); graph++) {
    maxY = std::max(maxY, graph->maxY());
  }
  return maxY;
}
