HEADERS = src/plot.hh src/plotview.hh src/application.hh \
    src/ctrlview.hh \
    src/mainwindow.hh
SOURCES = src/main.cc src/plot.cc src/plotview.cc src/application.cc \
    src/ctrlview.cc \
    src/mainwindow.cc

CONFIG += debug
TARGET = plot232

QT += serialport widgets
 
