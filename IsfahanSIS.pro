QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/data/person.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/data/person.h
