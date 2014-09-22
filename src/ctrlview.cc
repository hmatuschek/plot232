#include "ctrlview.hh"
#include <QFormLayout>
#include <QLineEdit>


CtrlView::CtrlView(Application *app, QWidget *parent)
  : QWidget(parent), _application(app)
{
  _delimiter = new QLineEdit(_application->delimiter());

  _portSelect = new QComboBox();
  for (int i=0; i<app->numPorts(); i++) {
    QSerialPortInfo info = app->portInfo(i);
    _portSelect->addItem(info.portName());
  }

  _deviceName = new QLabel("---");

  _rate = new QComboBox();
  _rate->addItem("Unknown", QSerialPort::UnknownBaud);
  _rate->addItem("1200", QSerialPort::Baud1200);
  _rate->addItem("2400", QSerialPort::Baud2400);
  _rate->addItem("4800", QSerialPort::Baud4800);
  _rate->addItem("9600", QSerialPort::Baud9600);
  _rate->addItem("19200", QSerialPort::Baud19200);
  _rate->addItem("38400", QSerialPort::Baud38400);
  _rate->addItem("57600", QSerialPort::Baud57600);
  _rate->addItem("115200", QSerialPort::Baud115200);

  _parity = new QComboBox();
  _parity->addItem("Unknown", QSerialPort::UnknownParity);
  _parity->addItem("None", QSerialPort::NoParity);
  _parity->addItem("Even", QSerialPort::EvenParity);
  _parity->addItem("Odd", QSerialPort::OddParity);
  _parity->addItem("Space", QSerialPort::SpaceParity);
  _parity->addItem("Mark", QSerialPort::MarkParity);

  _stopBits = new QComboBox();
  _stopBits->addItem("Unknown", QSerialPort::UnknownStopBits);
  _stopBits->addItem("1", QSerialPort::OneStop);
  _stopBits->addItem("1.5", QSerialPort::OneAndHalfStop);
  _stopBits->addItem("2", QSerialPort::TwoStop);

  QObject::connect(app, SIGNAL(destroyed()), this, SLOT(deleteLater()));
  QObject::connect(_delimiter, SIGNAL(textEdited(QString)), this, SLOT(_onDelimiterChanged(QString)));
  QObject::connect(_portSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(_onPortSelected(int)));
  QObject::connect(_rate, SIGNAL(currentIndexChanged(int)), this, SLOT(_onRateSelected(int)));
  QObject::connect(_parity, SIGNAL(currentIndexChanged(int)), this, SLOT(_onParitySelected(int)));
  QObject::connect(_stopBits, SIGNAL(currentIndexChanged(int)), this, SLOT(_onStopBitsSelected(int)));

  QFormLayout *layout = new QFormLayout();
  layout->addRow("Port", _portSelect);
  layout->addRow("Device", _deviceName);
  layout->addRow("Baud rate", _rate);
  layout->addRow("Parity", _parity);
  layout->addRow("Stop bits", _stopBits);

  setLayout(layout);
}


void
CtrlView::_onDelimiterChanged(QString del) {
  _application->setDelimiter(del);
}

void
CtrlView::_onPortSelected(int idx) {
  _application->openPort(idx);

  QSerialPortInfo info = QSerialPortInfo::availablePorts().at(idx);
  _deviceName->setText(info.systemLocation());

  switch (_application->baudRate()) {
  case QSerialPort::UnknownBaud: _rate->setCurrentIndex(0); break;
  case QSerialPort::Baud1200: _rate->setCurrentIndex(1); break;
  case QSerialPort::Baud2400: _rate->setCurrentIndex(2); break;
  case QSerialPort::Baud4800: _rate->setCurrentIndex(3); break;
  case QSerialPort::Baud9600: _rate->setCurrentIndex(4); break;
  case QSerialPort::Baud19200: _rate->setCurrentIndex(5); break;
  case QSerialPort::Baud38400: _rate->setCurrentIndex(6); break;
  case QSerialPort::Baud57600: _rate->setCurrentIndex(7); break;
  case QSerialPort::Baud115200: _rate->setCurrentIndex(8); break;
  }

  switch (_application->parity()) {
  case QSerialPort::UnknownParity: _parity->setCurrentIndex(0); break;
  case QSerialPort::NoParity: _parity->setCurrentIndex(1); break;
  case QSerialPort::EvenParity: _parity->setCurrentIndex(2); break;
  case QSerialPort::OddParity: _parity->setCurrentIndex(3); break;
  case QSerialPort::SpaceParity: _parity->setCurrentIndex(4); break;
  case QSerialPort::MarkParity: _parity->setCurrentIndex(5); break;
  }

  switch (_application->stopBits()) {
  case QSerialPort::UnknownStopBits: _stopBits->setCurrentIndex(0); break;
  case QSerialPort::OneStop: _stopBits->setCurrentIndex(1); break;
  case QSerialPort::OneAndHalfStop: _stopBits->setCurrentIndex(2); break;
  case QSerialPort::TwoStop: _stopBits->setCurrentIndex(3); break;
  }
}

void
CtrlView::_onRateSelected(int idx) {
  _application->setBaudRate(QSerialPort::BaudRate(_rate->itemData(idx).toInt()));
}

void
CtrlView::_onParitySelected(int idx) {
  _application->setParity(QSerialPort::Parity(_parity->itemData(idx).toInt()));
}

void
CtrlView::_onStopBitsSelected(int idx) {
  _application->setStopBits(QSerialPort::StopBits(_parity->itemData(idx).toInt()));
}
