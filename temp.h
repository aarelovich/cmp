#ifndef TEMP_H
#define TEMP_H

#include <QMainWindow>
#include <QAudioProbe>
#include <QAudioBuffer>
#include <QMediaPlayer>

#include "dftengine.h"

namespace Ui {
class Temp;
}

class Temp : public QMainWindow
{
    Q_OBJECT

public:
    explicit Temp(QWidget *parent = 0);
    ~Temp();

private slots:
    void on_pushButton_clicked();
    void on_audioBeenBuffered(QAudioBuffer buffer);
    void on_specAvailable();

private:

    const quint64 FFTSize = 64;

    Ui::Temp *ui;
    QAudioProbe probe;
    QMediaPlayer player;

    QVector<ComplexVectorPointer> dataBuffer;
    ComplexVectorPointer currentBuffer;

    DFTEngine fft;

};

#endif // TEMP_H