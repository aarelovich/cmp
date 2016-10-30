#ifndef STRUCTUREDSONGDATA_H
#define STRUCTUREDSONGDATA_H

#include <QHash>
#include <QString>
#include <QDebug>
#include <QDataStream>
#include <QtAlgorithms>

#include "basicsongdata.h"

class StructuredSongData
{
public:
    StructuredSongData();
    void addData(const BasicSongData &data, const QString &id);
    QStringList finalizeSorting();


private:
    // List of all albums
    QStringList albumList;

    // Ordered songs inside album
    QHash<QString,QStringList> songList;

    // Used for ordering the songs
    QHash< QString,QList<quint32> > songTrackNumbers;

    qint32 currentAlbum;
    qint32 currentSong;

    // Binary insertion search in order to "order" songs by track number as they are found
    qint32 findInsertionPoint(QList<quint32> vector, quint32 val);

};

#endif // STRUCTUREDSONGDATA_H
