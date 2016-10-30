QT += core gui widgets network multimedia

CONFIG += c++11

TARGET = cmp

TEMPLATE = app

MOC_DIR += MOCS
OBJECTS_DIR += OBJS

INCLUDEPATH += /home/ariela/repos/ColoUiDev/coloUi

SOURCES += main.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouibase.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouibutton.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouiconfiguration.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouicontainer.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouicreator.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouielement.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouiitem.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouilist.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouisignalmanager.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouitransitionscreen.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouidropdownlist.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouicheckbox.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouislider.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouiprogressbar.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouiplaceholder.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouikeyboard.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouiview.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouimultilinetext.cpp \
    /home/ariela/repos/ColoUiDev/coloUi/colouilineedit.cpp \
    colouiwindow.cpp \
    network/datapacket.cpp \
    network/transfermanager.cpp \
    spectrum/dftengine.cpp \
    spectrum/spectrumcontroller.cpp \
    spectrum/spectrumdisplay.cpp \
    songdata/basicsongdata.cpp \
    songdata/filelibrary.cpp \
    direxplorer.cpp \
    songdata/structuredsongdata.cpp

HEADERS += \
    /home/ariela/repos/ColoUiDev/coloUi/colouibase.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouibutton.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouiconfiguration.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouicontainer.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouicreator.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouidefines.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouielement.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouiitem.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouilist.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouisignalmanager.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouitransitionscreen.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouidropdownlist.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouicheckbox.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouislider.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouiprogressbar.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouiplaceholder.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouikeyboard.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouiview.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouimultilinetext.h \
    /home/ariela/repos/ColoUiDev/coloUi/colouilineedit.h \
    colouiwindow.h \
    elements.h \
    network/datapacket.h \
    network/transfermanager.h \
    spectrum/dftengine.h \
    spectrum/spectrumcontroller.h \
    spectrum/spectrumdisplay.h \
    songdata/basicsongdata.h \
    songdata/filelibrary.h \
    direxplorer.h \
    globaldefs.h \
    songdata/structuredsongdata.h

RESOURCES += assets.qrc

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/taglib/ -ltaglib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/taglib/ -ltaglib
#LIBS += -L$$PWD/taglib/ -ltaglib

############### THIS WORKS ON LAPTOP ###############
LIBS += -L/usr/lib/x86_64-linux-gnu/ -ltag
####################################################

INCLUDEPATH += $$PWD/taglib/include
DEPENDPATH += $$PWD/taglib/include

