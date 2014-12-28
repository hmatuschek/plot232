#include "application.hh"
#include <iostream>

Application::Application(int argc, char *argv[])
  : QApplication(argc, argv), _enabled(true), _delimiter(";"), _source(), _plot(0)
{
  _plot = new Plot();
  QObject::connect(&_source, SIGNAL(readyRead()), this, SLOT(onDataReceived()));
}

int
Application::numPorts() const {
  return QSerialPortInfo::availablePorts().size();
}

QSerialPortInfo
Application::portInfo(int idx) const {
  return QSerialPortInfo::availablePorts().at(idx);
}

void
Application::openPort(int idx) {
  _source.close();
  _source.setPort(QSerialPortInfo::availablePorts().at(idx));
  _source.open(QIODevice::ReadOnly);
  if (!_source.isOpen() || !_source.isReadable()) {
    std::cerr << "Can not open device..." << std::endl;
  }
}

QSerialPort::BaudRate
Application::baudRate() const {
  return QSerialPort::BaudRate(_source.baudRate(QSerialPort::Input));
}

void
Application::setBaudRate(QSerialPort::BaudRate rate) {
  _source.setBaudRate(rate, QSerialPort::Input);
}

QSerialPort::Parity
Application::parity() const {
  return _source.parity();
}

void
Application::setParity(QSerialPort::Parity parity) {
  _source.setParity(parity);
}

QSerialPort::StopBits
Application::stopBits() const {
  return _source.stopBits();
}

void
Application::setStopBits(QSerialPort::StopBits bits) {
  _source.setStopBits(bits);
}

bool
Application::enabled() const {
  return _enabled;
}

void
Application::enable(bool en) {
  _enabled = en;
  if (_enabled) { _plot->reset(); }
}


Plot *
Application::plot() const {
  return _plot;
}

void
Application::resetPlot() {
  _plot->reset();
}

const QString &
Application::delimiter() const {
  return _delimiter;
}

void
Application::setDelimiter(const QString &del) {
  _delimiter = del;
}

void
Application::onDataReceived() {
  while (_source.canReadLine()) {
    QByteArray line = _source.readLine();
    QStringList csv = QString(line).split(_delimiter, QString::KeepEmptyParts);
    QStringList::iterator item = csv.begin();
    QList<double> values;
    for (; item != csv.end(); item++) {
      values.push_back(item->toDouble());
    }
    if (_enabled) {
      _plot->addValues(values);
    }
  }
}
