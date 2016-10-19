#include "temp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Temp w;
    w.show();

    return a.exec();
}
