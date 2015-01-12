set(plot232_SOURCES main.cc
    application.cc ctrlview.cc mainwindow.cc plot.cc plotview.cc)
set(plot232_MOC_HEADERS
    application.hh ctrlview.hh mainwindow.hh plot.hh plotview.hh)
set(plot232_HEADERS ${plot232_MOC_HEADERS})

qt5_wrap_cpp(plot232_MOC_SOURCES ${plot232_MOC_HEADERS})

add_executable(plot232 ${plot232_SOURCES} ${plot232_MOC_SOURCES})
target_link_libraries(plot232 ${LIBS})

install(TARGETS plot232 DESTINATION bin)
