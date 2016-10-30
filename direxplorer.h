#ifndef DIREXPLORER_H
#define DIREXPLORER_H

#include <QDir>
#include "colouilist.h"

class DirExplorer
{
public:
    DirExplorer();
    void setup(ColoUiList *list, ColoUiConfiguration itemConfig);
    void exploreStart(QString where);
    void goUp();
    void goInto(int rowOfDir);
    QString getCurrentDir() const {return current.absolutePath();}

private:
    QDir current;
    ColoUiList *dirList;
    ColoUiConfiguration listItemConfig;

    void listCurrent();
};

#endif // DIREXPLORER_H
