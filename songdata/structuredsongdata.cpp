#include "structuredsongdata.h"

StructuredSongData::StructuredSongData()
{

}

void StructuredSongData::addData(const BasicSongData &data, const QString &id){

    QStringList songs;
    QList<quint32> tnums;

    if (albumList.contains(data.getAlbum())){
        // Add song to existing album
        songs = songList.value(data.getAlbum());
        tnums = songTrackNumbers.value(data.getAlbum());

        qint32 location = findInsertionPoint(tnums,data.getTrackNumber());
        tnums.insert(location,data.getTrackNumber());
        songs.insert(location,id);

    }
    else{
        // New album
        songs << id;
        tnums << data.getTrackNumber();

        // Adding it to the list of albums
        QStringList::Iterator location = qLowerBound(albumList.begin(),albumList.end(),data.getAlbum());
        albumList.insert(location,data.getAlbum());

    }

    songList[data.getAlbum()] = songs;
    songTrackNumbers[data.getAlbum()] = tnums;
}


QStringList StructuredSongData::finalizeSorting(){
    QStringList allsongs;

    for (qint32 i = 0; i < albumList.size(); i++){
        allsongs << songList.value(albumList.at(i));
    }

    // Freeing up memory.
    albumList.clear();
    songList.clear();
    songTrackNumbers.clear();

    return allsongs;
}


qint32 StructuredSongData::findInsertionPoint(QList<quint32> vector, quint32 val){

    if (vector.isEmpty()){
        return 0;
    }

    qint32 a = 0;
    qint32 b = vector.size()-1;
    qint32 ci = (a+b)/2;

    while (true){
        if ((b-a) > 1){
            if (val < vector.at(ci)){
                b = ci;
            }
            else{
                a = ci;
            }
            ci = (a+b)/2;
        }
        else{
            if (val < vector.at(b)){
                if (val > vector.at(a)){
                    ci = a+1;
                }
                else ci = a;
            }
            else{
                ci = b+1;
            }
            break;
        }
    }
    return ci;

}

