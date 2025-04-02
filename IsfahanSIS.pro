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
    src/widgets/viewer/core/entityshow.cpp \
    src/widgets/viewer/core/personshow.cpp \
    src/widgets/viewer/studentshow.cpp \
    src/widgets/viewer/teachershow.cpp \
    src/widgets/viewer/lessonshow.cpp \
    src/widgets/editor/lessonedit.cpp \
    src/widgets/editor/core/entityedit.cpp \
    src/widgets/editor/core/namevalidator.cpp \
    src/screens/loginscreen.cpp \
    src/models/enrolledmodel.cpp \
    src/models/core/entityitem.cpp \
    src/models/lessonlistmodel.cpp \
    src/models/teachingloadmodel.cpp \
    src/models/core/lecturetreemodel.cpp \

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
    include/widgets/editor/core/namevalidator.h \
    include/widgets/editor/lessonedit.h \
    include/widgets/editor/core/entityedit.h \
    include/models/enrolledmodel.h \
    include/models/core/entityitem.h \
    include/models/core/lecturetreemodel.h \
    include/models/lessonlistmodel.h \
    include/models/teachingloadmodel.h \
    include/widgets/viewer/lessonshow.h \
    include/screens/loginscreen.h \
    include/widgets/viewer/core/personshow.h \
    include/widgets/viewer/studentshow.h \
    include/widgets/viewer/teachershow.h \
    include/widgets/viewer/core/entityshow.h


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/widgets/viewer/core/entityshow.ui \
    ui/widgets/viewer/lessonshow.ui \
    ui/widgets/viewer/core/personshow.ui \
    ui/widgets/viewer/studentshow.ui \
    ui/widgets/viewer/teachershow.ui \
    ui/screens/loginscreen.ui \
    ui/widgets/editor/lessonedit.ui \
    ui/widgets/editor/core/entityedit.ui

RESOURCES += \
    resources/main.qrc
