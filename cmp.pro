QT += core gui widgets network multimedia

CONFIG += c++11

TARGET = cmp

TEMPLATE = app

MOC_DIR += MOCS
OBJECTS_DIR += OBJS

################################### LINUX ###################################
#INCLUDEPATH += /home/ariela/repos/ColoUiDev/coloUi
#SOURCES += main.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouibase.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouibutton.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiconfiguration.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouicontainer.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouicreator.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouielement.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiitem.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouilist.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouisignalmanager.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouitransitionscreen.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouidropdownlist.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouicheckbox.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouislider.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiprogressbar.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiplaceholder.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouikeyboard.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiview.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouimultilinetext.cpp \
#    /home/ariela/repos/ColoUiDev/coloUi/colouilineedit.cpp \
#    colouiwindow.cpp \
#    network/datapacket.cpp \
#    network/transfermanager.cpp \
#    spectrum/dftengine.cpp \
#    spectrum/spectrumcontroller.cpp \
#    spectrum/spectrumdisplay.cpp \
#    songdata/basicsongdata.cpp \
#    songdata/filelibrary.cpp \
#    direxplorer.cpp \
#    songdata/structuredsongdata.cpp \
#    songdata/playlistmanager.cpp

#HEADERS += \
#    /home/ariela/repos/ColoUiDev/coloUi/colouibase.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouibutton.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiconfiguration.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouicontainer.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouicreator.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouidefines.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouielement.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiitem.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouilist.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouisignalmanager.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouitransitionscreen.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouidropdownlist.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouicheckbox.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouislider.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiprogressbar.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiplaceholder.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouikeyboard.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouiview.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouimultilinetext.h \
#    /home/ariela/repos/ColoUiDev/coloUi/colouilineedit.h \
#    colouiwindow.h \
#    elements.h \
#    network/datapacket.h \
#    network/transfermanager.h \
#    spectrum/dftengine.h \
#    spectrum/spectrumcontroller.h \
#    spectrum/spectrumdisplay.h \
#    songdata/basicsongdata.h \
#    songdata/filelibrary.h \
#    direxplorer.h \
#    globaldefs.h \
#    songdata/structuredsongdata.h \
#    songdata/playlistmanager.h
############################### LINUX END ###############################################


############################### WINDOWS ###############################################
INCLUDEPATH += E:/Repos/ColoUiDev/coloUi
SOURCES += main.cpp \
    E:/Repos/ColoUiDev/coloUi/colouibase.cpp \
    E:/Repos/ColoUiDev/coloUi/colouibutton.cpp \
    E:/Repos/ColoUiDev/coloUi/colouiconfiguration.cpp \
    E:/Repos/ColoUiDev/coloUi/colouicontainer.cpp \
    E:/Repos/ColoUiDev/coloUi/colouicreator.cpp \
    E:/Repos/ColoUiDev/coloUi/colouielement.cpp \
    E:/Repos/ColoUiDev/coloUi/colouiitem.cpp \
    E:/Repos/ColoUiDev/coloUi/colouilist.cpp \
    E:/Repos/ColoUiDev/coloUi/colouisignalmanager.cpp \
    E:/Repos/ColoUiDev/coloUi/colouitransitionscreen.cpp \
    E:/Repos/ColoUiDev/coloUi/colouidropdownlist.cpp \
    E:/Repos/ColoUiDev/coloUi/colouicheckbox.cpp \
    E:/Repos/ColoUiDev/coloUi/colouislider.cpp \
    E:/Repos/ColoUiDev/coloUi/colouiprogressbar.cpp \
    E:/Repos/ColoUiDev/coloUi/colouiplaceholder.cpp \
    E:/Repos/ColoUiDev/coloUi/colouikeyboard.cpp \
    E:/Repos/ColoUiDev/coloUi/colouiview.cpp \
    E:/Repos/ColoUiDev/coloUi/colouimultilinetext.cpp \
    E:/Repos/ColoUiDev/coloUi/colouilineedit.cpp \
    colouiwindow.cpp \
    network/datapacket.cpp \
    network/transfermanager.cpp \
    spectrum/dftengine.cpp \
    spectrum/spectrumcontroller.cpp \
    spectrum/spectrumdisplay.cpp \
    songdata/basicsongdata.cpp \
    songdata/filelibrary.cpp \
    direxplorer.cpp \
    songdata/structuredsongdata.cpp \
    songdata/playlistmanager.cpp

HEADERS += \
    E:/Repos/ColoUiDev/coloUi/colouibase.h \
    E:/Repos/ColoUiDev/coloUi/colouibutton.h \
    E:/Repos/ColoUiDev/coloUi/colouiconfiguration.h \
    E:/Repos/ColoUiDev/coloUi/colouicontainer.h \
    E:/Repos/ColoUiDev/coloUi/colouicreator.h \
    E:/Repos/ColoUiDev/coloUi/colouidefines.h \
    E:/Repos/ColoUiDev/coloUi/colouielement.h \
    E:/Repos/ColoUiDev/coloUi/colouiitem.h \
    E:/Repos/ColoUiDev/coloUi/colouilist.h \
    E:/Repos/ColoUiDev/coloUi/colouisignalmanager.h \
    E:/Repos/ColoUiDev/coloUi/colouitransitionscreen.h \
    E:/Repos/ColoUiDev/coloUi/colouidropdownlist.h \
    E:/Repos/ColoUiDev/coloUi/colouicheckbox.h \
    E:/Repos/ColoUiDev/coloUi/colouislider.h \
    E:/Repos/ColoUiDev/coloUi/colouiprogressbar.h \
    E:/Repos/ColoUiDev/coloUi/colouiplaceholder.h \
    E:/Repos/ColoUiDev/coloUi/colouikeyboard.h \
    E:/Repos/ColoUiDev/coloUi/colouiview.h \
    E:/Repos/ColoUiDev/coloUi/colouimultilinetext.h \
    E:/Repos/ColoUiDev/coloUi/colouilineedit.h \
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
    songdata/structuredsongdata.h \
    songdata/playlistmanager.h
############################### WINDOWS END ###############################################

RESOURCES += assets.qrc

############### THIS WORKS ON WINDOWS ###############
INCLUDEPATH += $$PWD/taglib/include
LIBS += -L$$PWD/taglib/ -ltaglib
####################################################

############### THIS WORKS ON LINUX ###############
#LIBS += -L/usr/lib/x86_64-linux-gnu/ -ltag
#INCLUDEPATH += $$PWD/taglib/include
#DEPENDPATH += $$PWD/taglib/include
####################################################

