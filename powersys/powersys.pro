QT       += core gui datavisualization charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart_form.cpp \
    doc.cpp \
    form.cpp \
    form_debug.cpp \
    main.cpp \
    mainwindow.cpp \
    normal_regim.cpp \
    outline_power.cpp \
    relief_power.cpp

HEADERS += \
    chart_form.h \
    doc.h \
    form.h \
    form_debug.h \
    mainwindow.h \
    new_plain.h \
    normal_regim.h \
    outline_power.h \
    relief_power.h

FORMS += \
    chart_form.ui \
    doc.ui \
    form.ui \
    form_debug.ui \
    mainwindow.ui

RESOURCES = application.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
