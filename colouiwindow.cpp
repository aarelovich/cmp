#include "colouiwindow.h"

ColoUiWindow::ColoUiWindow(QWidget *parent) : QMainWindow(parent)
{
    qRegisterMetaType<FileTypeCount>("FileTypeCount");
    connect(&library,&FileLibrary::filesFound,this,&ColoUiWindow::on_fileScanner_update);
    connect(&library,&FileLibrary::finished,this,&ColoUiWindow::on_fileScanner_finished);
    connect(&messageTimer,&QTimer::timeout,this,&ColoUiWindow::on_messageTimer_timeout);
    useSongBoardA = true;
}

void ColoUiWindow::setCentralWidget(QWidget *widget){
   QMainWindow::setCentralWidget(widget);
   ui = (ColoUiContainer*)widget;   
   connect(ui,&ColoUiContainer::elementSignal,this,&ColoUiWindow::on_coloUiManager_signal);

   // The spectrum analyzer
   SpectrumDisplay *sd = library.getSpectrumDisplay();
   if (!ui->replacePlaceHolder(E_VIEWSPECTRUM_SPECTRUM,sd)){
       qWarning() << "Did not work!!";
   }

   // Configuration must be set for the first time here.
   ColoUiConfiguration c = sd->getConfiguration();
   sd->setConfiguration(c);

   // Actually drawing the UI.
   ui->drawUi();

   // Doing the initial setup of everything that requires the interface
   initialSetup();
   lockLog = false;
}


void ColoUiWindow::on_fileScanner_update(FileTypeCount ftc){
    QStringList keys = ftc.keys();
    logMessage("---> Update:");
    for (qint32 i = 0; i < keys.size(); i++){
        logMessage("Found " + QString::number(ftc.value(keys.at(i))) + " " + keys.at(i));
    }
}

void ColoUiWindow::on_fileScanner_finished(){

    logMessage("---> Updating local library");
    library.save(FILE_LIBRARY_DAT);

    if (!library.scanErrors().isEmpty()){
        logMessage("---> Scanning errors");
        for (qint32 i = 0; i < library.scanErrors().size(); i++){
            logMessage(library.scanErrors().at(i));
        }
    }

    logMessage("All done. Double click to return to spectrum",false,COLOR_LOG_SUCCESS);
    lockLog = false;
    library.changeCurrentPlaylist("");    
}

void ColoUiWindow::on_messageTimer_timeout(){
    logMessage("");
    messageTimer.stop();
}

void ColoUiWindow::on_coloUiManager_signal(){
    ColoUiSignalEventInfo info = ui->getSignalInfo();
    if (info.elementID == E_VIEWLOG_MTLOG ){
        if (info.type == ST_MOUSE_DOUBLE_CLICK){
            if (!lockLog){
                ui->startTranstion(E_VIEWLOG,E_VIEWSPECTRUM);
            }
        }
    }
    else if (info.elementID == E_VIEWLIST_LISTSONGLIST ){
        if (info.type == ST_MOUSE_DOUBLE_CLICK){

            ColoUiMultiLineText *board;
            if (useSongBoardA){
                board = (ColoUiMultiLineText *) ui->getElement(E_SONGINFOVIEWA_MTSONGINFOA);
            }
            else{
                board = (ColoUiMultiLineText *) ui->getElement(E_SONGINFOVIEWB_MTSONGINFOA);
            }
            useSongBoardA = !useSongBoardA;

            if (!library.play(info.data.toPoint().x(),board)){
                logMessage("Could not play selected song",true);
            }
        }
    }
    else if (info.elementID == E_VIEWSETTINGS_LTPLAYLIST ){
    }
    else if (info.elementID == E_VIEWFILTERBOX_LTSEARCHBOX ){
        ColoUiLineEdit * search = (ColoUiLineEdit *)(ui->getElement(E_VIEWFILTERBOX_LTSEARCHBOX));
        QString searchtext = search->getText();
        if (searchtext.size() >= 3){
            library.filterList(searchtext);
        }
        else library.filterList("");
    }
    else if (info.elementID == E_VIEWTOOLBAR_BTADDFOLDER ){
        if (info.type == ST_MOUSE_CLICK){
            ui->startTranstion(E_VIEWLIST,E_VIEWDIRLIST);
            dirExplorer.exploreStart("");
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("Scan folder into music library",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }
    else if (info.elementID == E_VIEWTOOLBAR_BTEXPORTPLAYLIST ){
        if (info.type == ST_MOUSE_CLICK){
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("Exports the current playlist",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }    
    else if (info.elementID == E_VIEWTOOLBAR_BTIMPORTPLAYLIST ){
        if (info.type == ST_MOUSE_CLICK){
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("Adds a playlist to the current playlist",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }
    else if (info.elementID == E_VIEWTOOLBAR_BTPINGSLAVE ){
        if (info.type == ST_MOUSE_CLICK){
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("Search for devices to transfer music",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }
    else if (info.elementID == E_VIEWTOOLBAR_BTRESCANFOLDERS ){
        if (info.type == ST_MOUSE_CLICK){
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("Rescans previously added folders ",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }
    else if (info.elementID == E_VIEWTOOLBAR_BTSENDPLAYLIST ){
        if (info.type == ST_MOUSE_CLICK){
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("If a device is connected, the current playlist is transfered to the device",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }
    else if (info.elementID == E_SONGINFOVIEWA ){
    }
    else if (info.elementID == E_SONGINFOVIEWA_MTSONGINFOA ){
    }
    else if (info.elementID == E_VIEWMESSAGES ){
    }
    else if (info.elementID == E_VIEWMESSAGES_LTSHOWBAR ){
    }
    else if (info.elementID == E_VIEWCONFIRMATION ){
    }
    else if (info.elementID == E_VIEWCONFIRMATION_BTACCEPT ){
    }
    else if (info.elementID == E_VIEWCONFIRMATION_BTCANCEL ){
    }
    else if (info.elementID == E_VIEWCONFIRMATION_CONFIRMATIONDIALOG ){
    }
    else if (info.elementID == E_VOLUMEVIEW_SLVOLUME ){
        setVolumeFromSliderPosition();
    }
    else if (info.elementID == E_VIEWCONTROLS ){
    }
    else if (info.elementID == E_VIEWCONTROLS_BTNEXT ){
    }
    else if (info.elementID == E_VIEWCONTROLS_BTPAUSE ){
        if (info.type == ST_MOUSE_CLICK){
            switch (library.getMediaPlayer()->state()){
            case QMediaPlayer::PlayingState:
                library.getMediaPlayer()->pause();
                break;
            case QMediaPlayer::PausedState:
                library.getMediaPlayer()->play();
                break;
            default:
                return;
            }
        }
    }
    else if (info.elementID == E_VIEWCONTROLS_BTPLAY ){
        if (info.type == ST_MOUSE_CLICK){
            switch (library.getMediaPlayer()->state()){
            case QMediaPlayer::PlayingState:
                library.getMediaPlayer()->stop();
                library.getMediaPlayer()->play();
                break;
            case QMediaPlayer::PausedState:
                library.getMediaPlayer()->play();
                break;
            case QMediaPlayer::StoppedState:
                // TODO get next song in playlist and play it
                break;
            }
        }
    }
    else if (info.elementID == E_VIEWCONTROLS_BTPREVIOUS ){
    }
    else if (info.elementID == E_VIEWCONTROLS_SLSEEKER ){
        if (info.type == ST_VALUE_CHANGED){
            library.updateSeekPosition(true);
        }
        else if (info.type == ST_SLIDING_STOPPED){
            library.updateSeekPosition(false);
        }
    }
    else if (info.elementID == E_SONGINFOVIEWB ){
    }
    else if (info.elementID == E_SONGINFOVIEWB_MTSONGINFOA ){
    }
    else if (info.elementID == E_VIEWSETTINGS ){
    }
    else if (info.elementID == E_VIEWSETTINGS_BTCREATEPLAYLIST ){
        if (info.type == ST_MOUSE_CLICK){
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("Creates a new, empty, playlist",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }
    else if (info.elementID == E_VIEWSETTINGS_BTDELETEPLAYLIST ){
        if (info.type == ST_MOUSE_CLICK){
        }
        else if (info.type == ST_HOVER_EVENT){
            if (info.data.toBool()){ // True means Hover in
                statusBar->setFormattedText("Deletes the current playlist",messageFont,messageTextColor);
            }
            else{ // False means Hover Out
                statusBar->setText("");
            }
        }
    }
    else if (info.elementID == E_VIEWSETTINGS_DPPLAYMODE ){
    }
    else if (info.elementID == E_VIEWSETTINGS_DPRIGHTMOUSEMODE ){
    }
    else if (info.elementID == E_VIEWSETTINGS_DPSECONDARYPLAYLIST ){
    }
    else if (info.elementID == E_VIEWSETTINGS_LTPLAYLISTINPUT ){
    }
    else if (info.elementID == E_VIEWSPECTRUM ){        
    }
    else if (info.elementID == E_VIEWSPECTRUM_SPECTRUM ){
    }
    else if (info.elementID == E_VIEWDIRLIST ){
    }
    else if (info.elementID == E_VIEWDIRLIST_BTACCEPT ){
        if (info.type == ST_MOUSE_CLICK){
            spectrumController.enableDataBuffering(false);
            ui->startTranstion(E_VIEWSPECTRUM,E_VIEWLOG);
            ui->startTranstion(E_VIEWDIRLIST,E_VIEWLIST);
            logMessage("Please wait while folder is analyzed ...");
            library.addSearchPath(dirExplorer.getCurrentDir());
            lockLog = true;
            library.start();
        }
    }
    else if (info.elementID == E_VIEWDIRLIST_BTCANCEL ){
        if (info.type == ST_MOUSE_CLICK){
            ui->startTranstion(E_VIEWLIST,E_VIEWDIRLIST);
        }
    }
    else if (info.elementID == E_VIEWDIRLIST_BTUPDIR ){
        if (info.type == ST_MOUSE_CLICK){
            dirExplorer.goUp();
        }
    }
    else if (info.elementID == E_VIEWDIRLIST_DIVIDER ){
    }
    else if (info.elementID == E_VIEWDIRLIST_LISTDIR ){
        QPoint where = info.data.toPoint(); // x is row and y is column
        dirExplorer.goInto(where.x());
    }

}

void ColoUiWindow::showEvent(QShowEvent *e){
    Q_UNUSED(e);
}

void ColoUiWindow::closeEvent(QCloseEvent *e){
    Q_UNUSED(e);
    saveSettings();
}

void ColoUiWindow::initialSetup(){

    // The directory list
    ColoUiConfiguration dirListItem;
    dirListItem.setFont(QFont(FONT_INTERFACE,FONT_SIZE_INTERFACE));
    dirListItem.setColor(CPR_BACKGROUND_COLOR,COLOR_UI_GRAY);
    dirListItem.setColor(CPR_TEXT_COLOR,"#FFFFFF");
    dirListItem.setColor(CPR_HOVER_BACKGROUND,"#747081");
    dirListItem.setColor(CPR_ALTERNATIVE_BACKGROUND_COLOR,"#FFFFFF");
    dirListItem.setColor(CPR_ALTERNATIVE_TEXT_COLOR,COLOR_UI_MAIN);

    dirExplorer.setup((ColoUiList *)ui->getElement(E_VIEWDIRLIST_LISTDIR),dirListItem);

    // The status bar
    messageFont = QFont(FONT_INFORMATION);
    messageFont.setPixelSize(FONT_SIZE_INFORMATION);
    messageTextColor = QColor(Qt::white);
    statusBar = (ColoUiLineEdit *)ui->getElement(E_VIEWMESSAGES_LTSHOWBAR);

    // Logger
    logger = (ColoUiMultiLineText *)ui->getElement(E_VIEWLOG_MTLOG);

    // The play list interface
    library.configureLibrary((ColoUiList *)ui->getElement(E_VIEWLIST_LISTSONGLIST),
                             (ColoUiSlider *)ui->getElement(E_VIEWCONTROLS_SLSEEKER));

    if (QFile(FILE_LIBRARY_DAT).exists()){
        library.load(FILE_LIBRARY_DAT);
    }

    // Setting the defaults options
    ddownPlaylist = (ColoUiDropdownList *)ui->getElement(E_VIEWSETTINGS_LTPLAYLIST);
    ddownPlayMode = (ColoUiDropdownList *)ui->getElement(E_VIEWSETTINGS_DPPLAYMODE);
    inputNameBox  = (ColoUiLineEdit *)ui->getElement(E_VIEWDIRLIST_LTINPUT);
    labelInputName  = (ColoUiLineEdit *)ui->getElement(E_VIEWDIRLIST_LABELINPUT);
    labelInputName->setVisible(false);
    inputNameBox->setVisible(false);

    ddownPlaylist->setCurrentIndex(0); // The library
    ddownPlayMode->setCurrentIndex(SONG_ORDER_LOOP);

    loadSettings();

    // TODO change current playlist to whichver playlist was loaded
    library.changeCurrentPlaylist("");


}

void ColoUiWindow::saveSettings(){
    QSettings settings(FILE_SETTINGS_INI,QSettings::IniFormat);
    library.saveSettings(&settings);
    settings.setValue(SETTINGS_PLAY_RANDOM,library.getRandom());
    settings.setValue(SETTINGS_PLAYLIST,ddownPlaylist->getCurrentItemIndex());
    ColoUiSlider *vol = (ColoUiSlider *)ui->getElement(E_VOLUMEVIEW_SLVOLUME);
    settings.setValue(SETTINGS_VOLUME,vol->getCurrentValue());
}

void ColoUiWindow::loadSettings(){
    QSettings settings(FILE_SETTINGS_INI,QSettings::IniFormat);
    library.loadSettings(&settings);

    library.playRandom(settings.value(SETTINGS_PLAY_RANDOM).toBool());
    if (library.getRandom()){
        ddownPlayMode->setCurrentIndex(SONG_ORDER_SHUFFLE);
    }
    else{
        ddownPlayMode->setCurrentIndex(SONG_ORDER_LOOP);
    }

    qint32 id = settings.value(SETTINGS_PLAYLIST).toInt();
    if (id == -1){
        ddownPlaylist->setCurrentIndex(0); // This is the library.
    }

    ColoUiSlider *vol = (ColoUiSlider *)ui->getElement(E_VOLUMEVIEW_SLVOLUME);
    vol->setCurrentValue(settings.value(SETTINGS_VOLUME,0).toInt());
    setVolumeFromSliderPosition();
}

void ColoUiWindow::logMessage(QString string, bool timed, QString color){
    QFont f(FONT_INFORMATION);
    f.setPixelSize(FONT_SIZE_INFORMATION);
    logger->appendFormattedText(string,f,QColor(color));
    messageTimer.stop();
    if (timed){
        messageTimer.start(3000);
    }
}

void ColoUiWindow::setVolumeFromSliderPosition(){
    ColoUiSlider *vol = (ColoUiSlider *)ui->getElement(E_VOLUMEVIEW_SLVOLUME);
    qreal sp = vol->getCurrentValue();
    qreal volume;
//    if (sp >= 98) volume = 0;
//    else volume = 50*qLn(100-sp)/qLn(10);
    if (sp >= 98) volume = 0;
    else volume = 100 - sp;
    library.getMediaPlayer()->setVolume(volume);
}

void ColoUiWindow::setSliderPositionFromVolume(){
    ColoUiSlider *vol = (ColoUiSlider *)ui->getElement(E_VOLUMEVIEW_SLVOLUME);
    qreal volume = library.getMediaPlayer()->volume();
    //qreal sp = 100 - qPow(10,volume/50);
    qreal sp = 100 - volume;
    vol->setCurrentValue(sp);
}
