#ifndef CTRLVIEW_HH
#define CTRLVIEW_HH

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include "application.hh"


class CtrlView : public QWidget
{
  Q_OBJECT

public:
  explicit CtrlView(Application *app, QWidget *parent = 0);

protected slots:
  void _onDelimiterChanged(QString del);
  void _onPortSelected(int idx);
  void _onRateSelected(int idx);
  void _onParitySelected(int idx);
  void _onStopBitsSelected(int idx);

protected:
  Application *_application;
  QLineEdit *_delimiter;
  QComboBox *_portSelect;
  QLabel    *_deviceName;
  QComboBox *_rate;
  QComboBox *_parity;
  QComboBox *_stopBits;
};

#endif // CTRLVIEW_HH
