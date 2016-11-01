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
#include "../coloUi/colouimultilinetext.h"
#include "globaldefs.h"
#include "spectrum/spectrumcontroller.h"
#include "structuredsongdata.h"
#include "playlistmanager.h"

typedef QMap<QString,quint32> FileTypeCount;

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

    // Searching current playlist
    void filterList(const QString & searchFor);

    // Start playing selected song. Returns true if the song exists
    bool play(qint32 song, ColoUiMultiLineText *songboard);
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

    // The playlist manager
    PlayListManager playlistManager;

    // Pointer the list
    ColoUiList *playList;

    // Pointer to the song board
    ColoUiMultiLineText *songBoard;
    QFont songFont;

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

    // Update song board data
    void updateSongBoard();

};

#endif // FIELSCANNER_H
