#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

#include "application.hh"
#include "plotview.hh"
#include "ctrlview.hh"


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(Application *app, QWidget *parent = 0);

protected:
  Application *_application;
  PlotView *_plotView;
  CtrlView *_ctrlView;
};

#endif // MAINWINDOW_HH
