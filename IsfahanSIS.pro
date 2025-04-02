QT += core
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/data/entity.cpp \
    src/data/lesson.cpp \
    src/data/person.cpp \
    src/data/teacher.cpp \
    src/data/student.cpp \
    src/screens/loginscreen.cpp \
    src/models/enrolledmodel.cpp \
    src/models/core/entityitem.cpp \
    src/models/lessonlistmodel.cpp \
    src/models/teachingloadmodel.cpp \
    src/models/core/lecturetreemodel.cpp \
    src/widgets/editor/core/namevalidator.cpp \

HEADERS += \
    include/data/entity.h \
    include/data/lesson.h \
    include/data/teacher.h \
    include/data/person.h \
    include/data/student.h \
    include/data/core/queue.h \
    include/errors/education.h \
    include/errors/resource.h \
    include/errors/general.h \
    include/screens/loginscreen.h \
    include/models/enrolledmodel.h \
    include/models/core/entityitem.h \
    include/models/lessonlistmodel.h \
    include/models/teachingloadmodel.h \
    include/models/core/lecturetreemodel.h \
    include/widgets/editor/core/namevalidator.h \


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/screens/loginscreen.ui \

RESOURCES += \
    resources/main.qrc
