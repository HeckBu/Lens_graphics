QT += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = MOC_Lab5.pro
TEMPLATE = app

CONFIG += c++17
INCLUDEPATH += D:/fftw
LIBS += D:/fftw/libfftw3_dll.a




# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FFT.cpp \
    main.cpp \
    dqtplotdialog.cpp \
    object.cpp \
    optical_system.cpp \
    qcustomplot.cpp \
    sample_complex.cpp

HEADERS += \
    FFT.h \
    dqtplotdialog.h \
    object.h \
    optical_system.h \
    qcustomplot.h \
    sample.h \
    sample_complex.h

FORMS += \
    dqtplotdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
