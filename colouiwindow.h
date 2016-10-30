#ifndef COLOUIWINDOW
#define COLOUIWINDOW

//########### QT ###########
#include <QMainWindow>

//########### COLOUI ###########
#include "colouicontainer.h"
#include "elements.h"

//########### CMP ###########
#include "direxplorer.h"
#include "globaldefs.h"
#include "spectrum/spectrumcontroller.h"
#include "songdata/filelibrary.h"

class ColoUiWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ColoUiWindow(QWidget *parent = 0);
    void setCentralWidget(QWidget * widget);

signals:

private slots:
    void on_coloUiManager_signal();
    void on_fileScanner_update(FileTypeCount ftc);
    void on_fileScanner_finished();
    void on_messageTimer_timeout();

protected:
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    ColoUiContainer *ui;

    // Own classes
    DirExplorer dirExplorer;

    // The music library.
    FileLibrary library;

    // The spectrum analyzer
    SpectrumController spectrumController;

    // Used for "Tooltips"
    QFont messageFont;
    QColor messageTextColor;
    ColoUiLineEdit *statusBar;

    // Fast access ui elements data
    ColoUiDropdownList *ddownPlaylist;
    ColoUiDropdownList *ddownPlayMode;

    // For logging
    ColoUiMultiLineText *logger;
    bool lockLog;
    QTimer messageTimer;
    void logMessage(QString string, bool timed = false, QString color = "#FFFFFF");

    // This is called right after the UI is drawn.
    void initialSetup();

    // Settings loaded.
    void loadSettings();
    void saveSettings();


};

#endif // COLOUIWINDOW
