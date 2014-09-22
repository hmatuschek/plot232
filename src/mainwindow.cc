#include "mainwindow.hh"
#include <QSplitter>


MainWindow::MainWindow(Application *app, QWidget *parent) :
  QMainWindow(parent), _application(app)
{
  _plotView = new PlotView(_application->plot());
  _ctrlView = new CtrlView(_application);

  QSplitter *splitter = new QSplitter();
  splitter->addWidget(_plotView);
  splitter->addWidget(_ctrlView);
  setCentralWidget(splitter);
}


