QT += core
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    entityshow.cpp \
    lessonshow.cpp \
    src/screens/loginscreen.cpp \
    main.cpp \
    personshow.cpp \
    src/data/entity.cpp \
    src/data/lesson.cpp \
    src/data/person.cpp \
    src/data/teacher.cpp \
    src/data/student.cpp \
    src/widgets/core/entityedit.cpp \
    src/widgets/core/namevalidator.cpp \
    src/widgets/lessonedit.cpp \
    src/widgets/core/personedit.cpp \
    src/models/enrolledmodel.cpp \
    src/models/core/entityitem.cpp \
    src/models/core/lecturetreemodel.cpp \
    src/models/lessonlistmodel.cpp \
    src/models/teachingloadmodel.cpp \
    src/widgets/studentedit.cpp \
    src/widgets/teacheredit.cpp \
    studentshow.cpp \
    teachershow.cpp

HEADERS += \
    include/data/core/queue.h \
    include/data/entity.h \
    include/data/lesson.h \
    include/data/teacher.h \
    include/data/person.h \
    include/data/student.h \
    include/errors/education.h \
    include/errors/resource.h \
    include/widgets/core/namevalidator.h \
    include/widgets/lessonedit.h \
    include/errors/general.h \
    include/widgets/core/entityedit.h \
    include/widgets/core/personedit.h \
    include/models/enrolledmodel.h \
    include/models/core/entityitem.h \
    include/models/core/lecturetreemodel.h \
    include/models/lessonlistmodel.h \
    include/models/teachingloadmodel.h \
    include/widgets/studentedit.h \
    include/widgets/teacheredit.h \
    lessonshow.h \
    include/screens/loginscreen.h \
    personshow.h \
    studentshow.h \
    teachershow.h \
    entityshow.h


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    entityshow.ui \
    lessonshow.ui \
    personshow.ui \
    studentshow.ui \
    teachershow.ui \
    ui/screens/loginscreen.ui \
    ui/widgets/studentedit.ui \
    ui/widgets/teacheredit.ui \
    ui/widgets/lessonedit.ui \
    ui/widgets/core/entityedit.ui \
    ui/widgets/core/personedit.ui

RESOURCES += \
    resources/main.qrc
