QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/data/entity.cpp \
    src/data/lesson.cpp \
    src/data/person.cpp \
    src/data/teacher.cpp \
    src/data/student.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/data/entity.h \
    include/data/lesson.h \
    include/data/teacher.h \
    include/data/person.h \
    include/data/student.h \
    include/errors/education.h \
    include/errors/resource.h \
    include/errors/general.h
