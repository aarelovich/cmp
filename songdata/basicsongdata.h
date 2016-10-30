#ifndef BASICSONGDATA_H
#define BASICSONGDATA_H

#include <QString>
#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QCryptographicHash>

#include "taglib/tag.h"
#include "taglib/fileref.h"

//#include <taglib/tag.h>
//#include <taglib/fileref.h>

class BasicSongData
{
public:

    BasicSongData();

    // A constructor for all data;
    QString constructSongData(QString file);

    // Change the file path;
    void changeFilePath(QString path){filePath = path;}

    // Saving the data
    void save(QDataStream *stream);
    void load(QDataStream *stream);

    bool matchesSearch(QString str) const;

    // Getting the data
    QString getFilePath() const {return filePath;}
    QString getArtist() const {return artist;}
    QString getSongName() const;
    QString getAlbum() const {return album;}
    quint32 getTrackNumber()  const {return trackNumber;}
    qint32 getDuration() const {return songDuration;}
    QString getDurationAsText() const {return songDurationAsText;}
    QString printFullData(QString tab) const;

    static const QString HASH_PREFIX;

private:


    QString filePath;
    QString songName;
    QString artist;
    QString album;
    quint32 trackNumber;
    qint32 songDuration;
    QString songDurationAsText;

    // Helper functions
    void genDurationText();
    QString getHash(QString fileName);

};

#endif // BASICSONGDATA_H
