QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UsuarioRegistro.cpp \
    clasesplantilla.cpp \
    examen.cpp \
    main.cpp \
    mainwindow.cpp \
    manejocuentas.cpp \
    pregunta.cpp \
    usuarioalumno.cpp \
    usuariomaestro.cpp

HEADERS += \
    UsuarioRegistro.h \
    clasesplantilla.h \
    examen.h \
    mainwindow.h \
    manejocuentas.h \
    pregunta.h \
    usuarioalumno.h \
    usuariomaestro.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes.qrc

DISTFILES += \
    Fondos/Menu Alumno.png \
    Fondos/Menu Maestro.png \
    Fondos/Menu Registro.png
