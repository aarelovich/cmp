#include "colouiwindow.h"

ColoUiWindow::ColoUiWindow(QWidget *parent) : QMainWindow(parent)
{

    connect(&probe,&QAudioProbe::audioBufferProbed,this,&ColoUiWindow::on_audioBeenBuffered);
    probe.setSource(&player);

}

void ColoUiWindow::setCentralWidget(QWidget *widget){
   QMainWindow::setCentralWidget(widget);
   ui = (ColoUiContainer*)widget;   
   connect(ui,&ColoUiContainer::elementSignal,this,&ColoUiWindow::on_coloUiManager_signal);

   // The spectrum analyzer
   SpectrumDisplay *sd = spectrumController.getSpectrumDisplay();
   if (!ui->replacePlaceHolder(E_PLACEHOLDERVIEW_FFT,sd)){
       qWarning() << "Did not work!!";
   }

   // Configuration must be set for the first time here.
   ColoUiConfiguration c = sd->getConfiguration();
   sd->setConfiguration(c);

   // Actually drawing the UI.
   ui->drawUi();
}

void ColoUiWindow::on_audioBeenBuffered(QAudioBuffer buffer){
    spectrumController.setAudioBuffer(buffer);
}

void ColoUiWindow::on_coloUiManager_signal(){
    ColoUiSignalEventInfo info = ui->getSignalInfo();
    if ( info.elementID == E_PLACEHOLDERVIEW){
    }
    else if (info.elementID == E_PLACEHOLDERVIEW_FFT ){
    }
    else if (info.elementID == E_BUTTONVIEW ){
    }
    else if (info.elementID == E_BUTTONVIEW_BTN1 ){
        player.setMedia(QUrl::fromLocalFile("/home/ariela/Workspace/02  Air Supply - GH 2000 - All Out Of Love.mp3"));
        player.setMedia(QUrl::fromLocalFile("/home/ariela/Music/Metal Misc/Accept_-_Amamos_La_Vida.mp3"));
        //player.setMedia(QUrl::fromLocalFile("/home/ariela/Music/Brian_Tyler-Iron_Man_3_(OST)_[iTunes_Version]-2013/20 Can You Dig It (Iron Man 3 Main T.m4a"));
        //player.setMedia(QUrl::fromLocalFile("/home/ariela/repos/cmp/tone.wav"));
        player.play();
    }
    else if (info.elementID == E_BUTTONVIEW_BTN2 ){
        player.setVolume(player.volume()+10);
    }
    else if (info.elementID == E_BUTTONVIEW_BTN3 ){
        player.setVolume(player.volume()-10);
    }

}
