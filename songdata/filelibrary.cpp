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
}

//--------------------------------- PLAYLIST MANAGEMENT ---------------------------

bool FileLibrary::play(qint32 song, qint32 volume){
    if ((song >= 0) && (song < libraryKeys.size())){
        if (player.state() == QMediaPlayer::PlayingState){
            player.stop();
        }
        BasicSongData bsd = fileMap.value(libraryKeys.at(song));
        if (QFile(bsd.getFilePath()).exists()){
            currentSong = bsd;
            currentSongID = libraryKeys.at(song);
            player.setMedia(QUrl::fromLocalFile(bsd.getFilePath()));
            player.play();
            player.setVolume(volume);
            return true;
        }
        else return false;
    }
    return false;
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

    playList->clearData();

    if (name == ""){

        // This is the library

        if (libraryKeys.isEmpty()){
            libraryKeys = fileMap.keys();
        }

        //qDebug() << "Library keys" << libraryKeys.size() << fileMap.size();

        ColoUiConfiguration c;

        for (qint32 i = 0; i < libraryKeys.size(); i++){

            playList->insertRow();

            QString keyID = libraryKeys.at(i);
            //qDebug() << i << keyID << fileMap.value(keyID).getSongName();

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

        }
    }

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

    libraryKeys = songDataSorter.finalizeSorting();
    qDebug() << "Finalized Library keys" << libraryKeys.size() << fileMap.size();

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

    stream << libraryKeys;

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

    stream >> libraryKeys;

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

    return true;

}

