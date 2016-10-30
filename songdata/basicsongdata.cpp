#include "basicsongdata.h"

const QString BasicSongData::HASH_PREFIX = "CPM__";

BasicSongData::BasicSongData()
{

}

QString BasicSongData::constructSongData(QString file){

    //qDebug() << "Constructing song data for" << file;

    filePath = file;

    // WORKS ON LINUX ???
    TagLib::FileRef fr(QFile::encodeName(file).constData());

    // WORKS ON WINDOWS
    //TagLib::FileRef fr( reinterpret_cast<const wchar_t*>(file.constData()) );

    QString comment;

    if ((!fr.isNull()) && (fr.tag() != NULL)){
        album = QString::fromUtf8(fr.tag()->album().toCString(true));
        artist = QString::fromUtf8(fr.tag()->artist().toCString(true));
        songName = QString::fromUtf8(fr.tag()->title().toCString(true));
        trackNumber = fr.tag()->track();
        songDuration = fr.audioProperties()->length();

        comment = QString::fromUtf8(fr.tag()->comment().toCString(true));
        if (!comment.startsWith(HASH_PREFIX)){
            QString hash = getHash(file);
            comment = HASH_PREFIX + hash;
            fr.tag()->setComment(TagLib::String(comment.toUtf8().data(), TagLib::String::UTF8));
            fr.save();
        }

        genDurationText();
    }
    else{
        return "";
    }

    return comment;

}


bool BasicSongData::matchesSearch(QString str) const{
    bool ret = songName.contains(str,Qt::CaseInsensitive) ||
               artist.contains(str,Qt::CaseInsensitive)   ||
               album.contains(str,Qt::CaseInsensitive)    ||
               filePath.contains(str,Qt::CaseInsensitive);
    return ret;
}

QString BasicSongData::printFullData(QString tab) const{

    QString result;

    result = "File: " + filePath + "\n";
    result = result + tab + "Title: " + songName + " (" + songDurationAsText  + ")\n";
    result = result + tab + "Artist: " + artist + "\n";
    result = result + tab + "Album: " + album + "\n";

    return result;

}

void BasicSongData::genDurationText(){
    qint32 length = songDuration;
    qint32 hours = length/3600;
    length = length - 3600*hours;
    qint32 minutes = length/60;
    qint32 secs = length - minutes*60;
    if (hours > 0){
        if (hours < 10){
            songDurationAsText = "0" + QString::number(hours) + ":";
        }
        else{
            songDurationAsText = QString::number(hours) + ":";
        }
    }
    if (minutes >= 0){
        if (minutes < 10){
            songDurationAsText = songDurationAsText + "0" + QString::number(minutes) + ":";
        }
        else{
            songDurationAsText = songDurationAsText + QString::number(minutes) + ":";
        }
    }
    if (secs < 10){
        songDurationAsText = songDurationAsText + "0" + QString::number(secs);
    }
    else{
        songDurationAsText = songDurationAsText + QString::number(secs);
    }

}

QString BasicSongData::getSongName() const{
    if (songName.isEmpty()){
        QFileInfo info(filePath);
        return info.baseName();
    }
    else return songName;
}

void BasicSongData::save(QDataStream *stream){
    *stream << filePath;
    *stream << artist;
    *stream << songName;
    *stream << album;
    *stream << trackNumber;
    *stream << songDuration;
    *stream << songDurationAsText;
}

void BasicSongData::load(QDataStream *stream){
    *stream >> filePath;
    *stream >> artist;
    *stream >> songName;
    *stream >> album;
    *stream >> trackNumber;
    *stream >> songDuration;
    *stream >> songDurationAsText;
}


QString BasicSongData::getHash(QString fileName){
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)){
        QByteArray data = file.readAll();
        QByteArray hash = QCryptographicHash::hash(data,QCryptographicHash::Sha256);
        return QString(hash.toHex());
    }
    else return "";
}
