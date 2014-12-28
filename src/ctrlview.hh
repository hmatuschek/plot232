#ifndef CTRLVIEW_HH
#define CTRLVIEW_HH

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "application.hh"


class CtrlView : public QWidget
{
  Q_OBJECT

public:
  explicit CtrlView(Application *app, QWidget *parent = 0);

signals:
  void savePlot(QString filename);

protected slots:
  void _onStartStop(bool enabled);
  void _onSave();
  void _onDelimiterChanged(QString del);
  void _onPortSelected(int idx);
  void _onRateSelected(int idx);
  void _onParitySelected(int idx);
  void _onStopBitsSelected(int idx);

protected:
  Application *_application;
  QPushButton *_startStop;
  QLineEdit *_delimiter;
  QComboBox *_portSelect;
  QLabel    *_deviceName;
  QComboBox *_rate;
  QComboBox *_parity;
  QComboBox *_stopBits;
};

#endif // CTRLVIEW_HH
