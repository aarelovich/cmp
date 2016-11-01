#include "playlistmanager.h"

PlayListManager::PlayListManager()
{
    currentPlayListName = "";
    secondaryPlayListName = "";
}

bool PlayListManager::newPlaylist(QString name){
    if (name.isEmpty()) return false;
    if (playlists.contains(name)) return false;
    playlists[name] = QStringList();
    return true;
}

void PlayListManager::setLibrary(const QStringList &lib){
    playlists[LIBRARY_NAME] = lib;
    currentPlayListName = LIBRARY_NAME;
}

bool PlayListManager::addToSecondaryPlaylist(qint32 index){
    if (secondaryPlayListName.isEmpty()) return false;

    if (secondaryPlayListName == currentPlayListName) return false;

    qint32 sizeToCheck;
    QString which;

    if (filteredList.isEmpty()){
        sizeToCheck = playlists.value(currentPlayListName).size();
        if ((index < 0) || (index >= sizeToCheck)) return false;
        which = playlists.value(currentPlayListName).at(index);
    }
    else{
        sizeToCheck = filteredList.size();
        if ((index < 0) || (index >= sizeToCheck)) return false;
        which = filteredList.at(index);
    }

    playlists[secondaryPlayListName] << which;
    return true;

}

bool PlayListManager::setCurrentPlaylist(QString name){
    if (name.isEmpty()){
        // This is the library so....
        currentPlayListName = LIBRARY_NAME;
        return true;
    }
    if (playlists.contains(name)){
        currentPlayListName = name;
    }
    else return false;

    return true;
}

bool PlayListManager::setSecondaryPlaylist(QString name){
    if (playlists.contains(name)){
        secondaryPlayListName = name;
        return true;
    }
    else return false;
}

QString PlayListManager::getSong(qint32 songid){
    if ((songid >= 0) && (songid < filteredList.size())){
        return filteredList.at(songid);
    }
    else return "";
}

void PlayListManager::filterPlaylist(const QString &searchfor, const HashFileMap &data){

    filteredList.clear();

    if (searchfor.isEmpty()){
        filteredList = playlists.value(currentPlayListName);
        return;
    }

    for (qint32 i = 0; i < playlists.value(currentPlayListName).size(); i++){
        QString id = playlists.value(currentPlayListName).at(i);
        if (data.value(id).matchesSearch(searchfor)){
            filteredList << id;
        }
    }

}

QString PlayListManager::nextIteration(){
    if (iterationIndex < filteredList.size()){
        QString data =  filteredList.at(iterationIndex);
        iterationIndex++;
        return data;
    }
    else return "";
}

qint32 PlayListManager::getNumberOfResults(){
    return filteredList.size();
}

void PlayListManager::save(QDataStream *stream){
    *stream << playlists;
}

void PlayListManager::load(QDataStream *stream){
    playlists.clear();
    *stream >> playlists;
    currentPlayListName = LIBRARY_NAME;
    filteredList = playlists.value(LIBRARY_NAME);
}
