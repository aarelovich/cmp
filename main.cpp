#include <QApplication>
#include "colouiwindow.h"
#include "colouicreator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColoUiWindow *mainWindow = new ColoUiWindow();
    ColoUiContainer *ui = new ColoUiContainer(mainWindow);

    // Creating the Ui
    ColoUiCreator creator;
    creator.createFromResource(ui);

    mainWindow->setCentralWidget(ui);
    mainWindow->showMaximized();

    return a.exec();
}
