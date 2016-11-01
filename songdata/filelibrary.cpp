#include "filelibrary.h"

FileLibrary::FileLibrary()
{
    // The list of fileTypes to search
    fileTypes << "*.MP3" << "*.Mp3" << "flac" << "mp2" << "mp3" << "wma";
    connect(&probe,&QAudioProbe::audioBufferProbed,this,&FileLibrary::on_audioBuffered);
    connect(&player,&QMediaPlayer::stateChanged,this,&FileLibrary::on_mediaPlayer_stateChanged);
    connect(&player,&QMediaPlayer::positionChanged,this,&FileLibrary::on_positionChanged);
    probe.setSource(&player);
    sliderIsBeingMoved = false;
    songFont = QFont(FONT_INFORMATION);
    songFont.setPixelSize(FONT_SIZE_INFORMATION);
}

void FileLibrary::addSearchPath(QString dir){
    if (fileDirs.contains(dir)) return;
    else fileDirs << dir;
}

void FileLibrary::on_audioBuffered(QAudioBuffer buffer){
    spectrumController.setAudioBuffer(buffer);
}

void FileLibrary::on_mediaPlayer_stateChanged(QMediaPlayer::State state){
    qDebug() << "New state" << state;
}

void FileLibrary::on_positionChanged(qint64 pos){
    if (sliderIsBeingMoved) return;
    qreal val = (qreal)pos*100.0/(qreal)player.duration();
    seekSlider->setCurrentValue(val);
    updateSongBoard();
}

//--------------------------------- PLAYLIST MANAGEMENT ---------------------------

bool FileLibrary::play(qint32 song, ColoUiMultiLineText *songboard){
    QString songID = playlistManager.getSong(song);
    if (!songID.isEmpty()){

        songBoard = songboard;

        if (player.state() == QMediaPlayer::PlayingState){
            player.stop();
        }
        BasicSongData bsd = fileMap.value(songID);
        if (QFile(bsd.getFilePath()).exists()){
            currentSong = bsd;
            currentSongID = songID;
            player.setMedia(QUrl::fromLocalFile(bsd.getFilePath()));
            player.play();
            return true;
        }
        else return false;
    }
    return false;
}

void FileLibrary::updateSongBoard(){
    songBoard->clearText(); // Clear all text
    songBoard->appendFormattedText(currentSong.getSongName(),songFont,COLOR_WHITE);
    songBoard->appendFormattedText(currentSong.getArtist(),songFont,COLOR_WHITE);
    songBoard->appendFormattedText(currentSong.getAlbum(),songFont,COLOR_WHITE);
    songBoard->appendFormattedText(QString::number(player.position()/1000) + "/" + QString::number(currentSong.getDuration()),songFont,COLOR_WHITE);
}

void FileLibrary::filterList(const QString &searchFor){

    if (searchFor.isEmpty()){
        //qDebug() << "Playlist size" << playlistManager.getCurrentPlaylistSize() << "row count" << playList->getRowCount();
        if (playList->getRowCount() == playlistManager.getCurrentPlaylistSize()) return;
    }

    playlistManager.filterPlaylist(searchFor,fileMap);

    playList->clearData();

    ColoUiConfiguration c;

    playlistManager.prepareIteration();

    qint32 i = 0;

    //qDebug() << "searchfor" << searchFor << "yielded" << playlistManager.getNumberOfResults();

    while (true){

        QString keyID = playlistManager.nextIteration();
        if (keyID.isEmpty()) return; // DONE.

        playList->insertRow();

        // Playing
        playList->setItemConfiguration(i,0,configPlayColumn);
        // Title
        c = configInfoColumn; c.set(CPR_TEXT,fileMap.value(keyID).getSongName());
        playList->setItemConfiguration(i,1,c);
        // Artist
        c = configInfoColumn; c.set(CPR_TEXT,fileMap.value(keyID).getArtist());
        playList->setItemConfiguration(i,2,c);
        // Album
        c = configInfoColumn; c.set(CPR_TEXT,fileMap.value(keyID).getAlbum());
        playList->setItemConfiguration(i,3,c);
        // Duration
        c = configInfoColumn; c.set(CPR_TEXT,fileMap.value(keyID).getDurationAsText());
        playList->setItemConfiguration(i,4,c);
        // Track number
        c = configInfoColumn; c.set(CPR_TEXT,fileMap.value(keyID).getTrackNumber());
        playList->setItemConfiguration(i,5,c);

        i++;

    }

}

void FileLibrary::configureLibrary(ColoUiList *list, ColoUiSlider *seek){
    playList = list;

    // Creating vector
    QFont data(FONT_INTERFACE,FONT_SIZE_INTERFACE);
    QFont glyph(FONT_GLYPHS,FONT_SIZE_INTERFACE);

    ColoUiConfiguration c;

    c.setFont(glyph);
    c.setColor(CPR_TEXT_COLOR,COLOR_WHITE);
    c.setColor(CPR_BACKGROUND_COLOR,COLOR_UI_MAIN);
    c.setColor(CPR_HOVER_BACKGROUND,COLOR_UI_GRAY);
    configPlayColumn = c;

    c.setFont(data);
    configInfoColumn = c;

    seekSlider = seek;

}

void FileLibrary::changeCurrentPlaylist(QString name){
    Q_UNUSED(name);
    if (!playlistManager.setCurrentPlaylist(name)) return;
    this->filterList("");
}

//--------------------------------- SONG DATA AND CONTROL -----------------------------------
void FileLibrary::updateSeekPosition(bool start){
    sliderIsBeingMoved = start;
    qint32 newpos = seekSlider->getCurrentValue()*player.duration()/100;
    player.setPosition(newpos);
}

//--------------------------------- FILE DISCOVERY AND MANAGEMENT ---------------------------

void FileLibrary::run(){

    fileMap.clear();    
    fileTypeCount.clear();
    for (qint32 i = 0; i < fileDirs.size(); i++){
        recursiveSearch(fileDirs.at(i));
    }

    playlistManager.setLibrary(songDataSorter.finalizeSorting());


}

void FileLibrary::recursiveSearch(QString dir){

    QDir directory(dir);
    QStringList allFiles = directory.entryList(fileTypes,QDir::Files);
    QStringList allDirs = directory.entryList(fileTypes,QDir::AllDirs|QDir::NoDotAndDotDot);    

    for (qint32 i = 0; i < allFiles.size(); i++){

        QFileInfo info(directory.absolutePath() + "/" + allFiles.at(i));

        QString extension = info.suffix();
        if (fileTypeCount.contains(extension)){
            fileTypeCount[extension]++;
        }
        else{
            fileTypeCount[extension] = 1;
        }

        BasicSongData data;
        QString ID = data.constructSongData(info.absoluteFilePath());

        if (ID.isEmpty()){
            errorsOnScan << "Could not get metadata for file " << info.absoluteFilePath();
        }
        else{
            if (!fileMap.contains(ID)){
                fileMap.insert(ID,data);
                songDataSorter.addData(data,ID);
            }
        }

    }

    emit filesFound(fileTypeCount);

    for (qint32 i = 0; i < allDirs.size(); i++){
        recursiveSearch(directory.absolutePath() + "/" + allDirs.at(i));
    }

}

QList<QString> FileLibrary::search(QString searchFor){

    QList<QString> list;

    // Do no search for less than three chars
    if (searchFor.size() < 3) return list;

    QList<QString> keys = fileMap.keys();
    for (qint32 i = 0; i < keys.size(); i++){
        if (fileMap.value(keys.at(i)).matchesSearch(searchFor)) {
            list << keys.at(i);
        }
    }

    return list;

}

//--------------------------- SAVE AND LOAD SETTINGS -------------------------
void FileLibrary::saveSettings(QSettings *settings){
    QVariantList list;
    for (qint32 i = 0; i < playList->getColCount(); i++){
        list << playList->getHeaderConfig(i).getUInt16(CPR_WIDTH);
    }
    settings->setValue(SETTINGS_COLUMN_SIZES,list);
}

void FileLibrary::loadSettings(QSettings *settings){
    QVariantList list = settings->value(SETTINGS_COLUMN_SIZES).toList();
    if (list.size() != playList->getColCount()) return;
    for (qint32 i = 0; i < playList->getColCount(); i++){
        ColoUiConfiguration c = playList->getHeaderConfig(i);
        c.set(CPR_WIDTH,list.at(i));
        playList->setHeaderConfig(c,i);
    }
}

//----------------------------- SAVE AND LOAD DATA ------------------------------

bool FileLibrary::save(QString fileName){

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)){
        return false;
    }

    QDataStream stream(&file);

    playlistManager.save(&stream);

    stream << fileDirs;

    stream << (qint32) fileMap.size();
    QList<QString> keys = fileMap.keys();
    for (qint32 i = 0; i < keys.size(); i++){
        stream << keys.at(i);
        fileMap[keys.at(i)].save(&stream);
    }

    file.close();

    return true;
}

bool FileLibrary::load(QString fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)){
        return false;
    }

    fileMap.clear();

    QDataStream stream(&file);

    playlistManager.load(&stream);

    stream >> fileDirs;

    qint32 size;
    stream >> size;

    for (qint32 i = 0; i < size; i++){

        QString checksum;
        BasicSongData data;

        stream >> checksum;
        data.load(&stream);

        fileMap[checksum] = data;
    }

    file.close();

    //qDebug() << "File map size" << fileMap.size();

    return true;

}

