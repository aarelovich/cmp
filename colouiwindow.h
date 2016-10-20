#ifndef COLOUIWINDOW
#define COLOUIWINDOW

#include <QMainWindow>
#include <QAudioProbe>
#include <QMediaPlayer>
#include "colouicontainer.h"
#include "elements.h"
#include "spectrumcontroller.h"

class ColoUiWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ColoUiWindow(QWidget *parent = 0);
    void setCentralWidget(QWidget * widget);

signals:

private slots:
    void on_coloUiManager_signal();
    void on_audioBeenBuffered(QAudioBuffer buffer);

private:
    ColoUiContainer *ui;
    SpectrumController spectrumController;
    QMediaPlayer player;
    QAudioProbe probe;
};

#endif // COLOUIWINDOW
