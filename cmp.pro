QT += core gui widgets multimedia

CONFIG += c++11

TARGET = cmp

TEMPLATE = app

MOC_DIR = MOCS
OBJECTS_DIR = OBJS

INCLUDEPATH += /home/ariel/repos/ColoUiDev/coloUi

SOURCES += main.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouibase.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouibutton.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouiconfiguration.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouicontainer.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouicreator.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouielement.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouiitem.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouilist.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouisignalmanager.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouimultilinetext.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouitransitionscreen.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouidropdownlist.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouicheckbox.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouislider.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouiprogressbar.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouiplaceholder.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouikeyboard.cpp \
    /home/ariel/repos/ColoUiDev/coloUi/colouiview.cpp \
    colouiwindow.cpp \
    spectrumdisplay.cpp \
    dftengine.cpp \
    spectrumcontroller.cpp

HEADERS += \
    /home/ariel/repos/ColoUiDev/coloUi/colouibase.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouibutton.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouiconfiguration.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouicontainer.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouicreator.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouidefines.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouielement.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouiitem.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouilist.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouisignalmanager.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouimultilinetext.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouitransitionscreen.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouidropdownlist.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouicheckbox.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouislider.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouiprogressbar.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouiplaceholder.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouikeyboard.h \
    /home/ariel/repos/ColoUiDev/coloUi/colouiview.h \
    colouiwindow.h \
    elements.h \
    spectrumdisplay.h \
    dftengine.h \
    spectrumcontroller.h

RESOURCES += assets.qrc


