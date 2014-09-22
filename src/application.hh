#ifndef APPLICATION_HH
#define APPLICATION_HH

#include "plot.hh"
#include <QApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Application : public QApplication
{
  Q_OBJECT

public:
  explicit Application(int argc, char *argv[]);

  const QString &delimiter() const;
  void setDelimiter(const QString &del);

  int numPorts() const;
  QSerialPortInfo portInfo(int idx) const;
  void openPort(int idx);

  QSerialPort::BaudRate baudRate() const;
  void setBaudRate(QSerialPort::BaudRate rate);

  QSerialPort::Parity parity() const;
  void setParity(QSerialPort::Parity parity);

  QSerialPort::StopBits stopBits() const;
  void setStopBits(QSerialPort::StopBits bits);

  Plot *plot() const;

protected slots:
  void onDataReceived();

protected:
  QString _delimiter;
  QSerialPort _source;
  Plot *_plot;
};

#endif // APPLICATION_HH
