#ifndef FIELSCANNER_H
#define FIELSCANNER_H

#include <QThread>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QMap>
#include <QTextStream>
#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <QMediaPlayer>
#include <QAudioProbe>
#include <QVariantList>
#include <QSettings>

#include "../coloUi/colouilist.h"
#include "../coloUi/colouislider.h"
#include "globaldefs.h"
#include "spectrum/spectrumcontroller.h"
#include "structuredsongdata.h"

typedef QMap<QString,quint32> FileTypeCount;
typedef QMap<QString,BasicSongData> HashFileMap;


class FileLibrary : public QThread
{
    Q_OBJECT

public:

    FileLibrary();

    void run();

    //bool setFilterFileTypes(QString txtfile);
    void addSearchPath(QString dir);

    // Creating the configuration vector and list
    void configureLibrary(ColoUiList *list, ColoUiSlider *seek);

    // Change current playlist
    void changeCurrentPlaylist(QString playlist);

    // Start playing selected song. Returns true if the song exists
    bool play(qint32 song, qint32 volume);
    void updateSeekPosition(bool start);

    // Switches the type of looped play
    void playRandom(bool random) {randomPlay = random;}
    bool getRandom() const {return randomPlay;}

    QStringList scanErrors() const {return errorsOnScan;}

    // All files in libraray
    HashFileMap fileMap;

    // The search function in the library
    QList<QString> search(QString searchFor);

    // Get the directories added to library
    QStringList getFileDirs() const {return fileDirs;}

    // Getting the spectrum display to replace the placeholder
    SpectrumDisplay * getSpectrumDisplay() {return spectrumController.getSpectrumDisplay();}

    // Get media player for direct acces
    QMediaPlayer *getMediaPlayer() {return &player;}

    // Saving and loading settings
    void saveSettings(QSettings *settings);
    void loadSettings(QSettings *settings);

    // Saving and loading library data
    bool save(QString fileName);
    bool load(QString fileName);

signals:
    void filesFound(FileTypeCount ftc);

private slots:
    void on_audioBuffered(QAudioBuffer buffer);
    void on_mediaPlayer_stateChanged(QMediaPlayer::State state);
    void on_positionChanged(qint64 pos);

private:

    QStringList fileDirs;
    QStringList fileTypes;
    QStringList errorsOnScan;

    // Column configuration vector
    ColoUiConfiguration configPlayColumn;
    ColoUiConfiguration configInfoColumn;

    // The playlists
    QHash<QString,QStringList> playlists;
    qint32 currentPlayListIndex;

    // Sorted songs
    QStringList libraryKeys;

    // The queue which, takes priority over the current playlist.
    QStringList queue;

    // Pointer the list
    ColoUiList *playList;

    // The Media player and data.
    QMediaPlayer player;
    QAudioProbe probe;
    SpectrumController spectrumController;
    ColoUiSlider *seekSlider;
    BasicSongData currentSong;
    QString currentSongID;
    bool sliderIsBeingMoved;

    // Required for sorting of the main library
    StructuredSongData songDataSorter;

    // For statistics
    FileTypeCount fileTypeCount;

    // Random play
    bool randomPlay;

    void recursiveSearch(QString dir);

};

#endif // FIELSCANNER_H
