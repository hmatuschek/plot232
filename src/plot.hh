#ifndef PLOT_HH
#define PLOT_HH

#include <QObject>
#include <QPair>
#include <QVector>
#include <QElapsedTimer>

/** Represents a single graph in the plot. */
class Graph
{
public:
  Graph();
  virtual ~Graph();

  void addValue(double t, double y);

  double minY() const;
  double maxY() const;

  size_t numValues() const;
  double value(size_t i) const;
  double time(size_t i) const;

protected:
  QVector< QPair<double, double> > _values;
  double _minY, _maxY;
};


/** Represetns the plot, a collection of Graphs. */
class Plot : public QObject
{
  Q_OBJECT

public:
  typedef QList<Graph>::iterator iterator;

public:
  explicit Plot(QObject *parent = 0);

  void addValues(const QList<double> &values);

  void reset();

  size_t numGraphs() const;
  const Graph &graph(size_t i) const;
  iterator begin();
  iterator end();

  double maxT() const;
  double minY() const;
  double maxY() const;

signals:
  void update();

protected:
  QList<Graph> _graphs;
  QElapsedTimer _timer;
  double _tmax;
};

#endif // PLOT_HH
