HEADERS = src/plot.hh src/plotview.hh src/application.hh \
    src/ctrlview.hh \
    src/mainwindow.hh
SOURCES = src/main.cc src/plot.cc src/plotview.cc src/application.cc \
    src/ctrlview.cc \
    src/mainwindow.cc

CONFIG += qt debug windows
TARGET = plot232

QT += gui widgets serialport

package.path = $${OUT_PWD}/package
package.files += plot232.exe plot232.nsi # somelib.dll
INSTALLS += package

unset(MANGLED_INSTALLS)
for(x, INSTALLS):MANGLED_INSTALLS += install_$${x}
build_package.path = $${OUT_PWD}/package
build_package.commands = \"C:/Program Files (x86)/NSIS/makensisw.exe\" \"$${OUT_PWD}/package/plot232.nsi\"
build_package.depends = $${MANGLED_INSTALLS}
INSTALLS += build_package
