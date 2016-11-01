#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "QStringList"
#include "QHash"
#include "basicsongdata.h"

typedef QMap<QString,BasicSongData> HashFileMap;

class PlayListManager
{
public:
    PlayListManager();

    void setLibrary(const QStringList &lib);

    bool newPlaylist(QString name);

    // Adds the index of the song of the current playlist to the secondary.
    bool addToSecondaryPlaylist(qint32 index);

    bool setCurrentPlaylist(QString name);

    bool setSecondaryPlaylist(QString name);

    // Filter function.
    void filterPlaylist(const QString &searchfor, const HashFileMap &data);

    // Size fo the filter list
    qint32 getNumberOfResults();
    qint32 getCurrentPlaylistSize() {return playlists.value(currentPlayListName).size();}

    QString getSong(qint32 songid);

    // Iterate function
    void prepareIteration() {iterationIndex = 0;}
    QString nextIteration();

    void save(QDataStream *stream);
    void load(QDataStream *stream);

private:
    QHash<QString,QStringList> playlists;
    QString currentPlayListName;
    QString secondaryPlayListName;
    QStringList filteredList;
    qint32 iterationIndex;
    const QString LIBRARY_NAME = QString("LIBRARY");

};

#endif // PLAYLISTMANAGER_H
