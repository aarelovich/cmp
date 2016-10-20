#ifndef SPECTRUMCONTROLLER_H
#define SPECTRUMCONTROLLER_H

#include <QThread>
#include <QAudioBuffer>
#include "spectrumdisplay.h"

class SpectrumController : public QThread
{
    Q_OBJECT
public:
    explicit SpectrumController();
    SpectrumDisplay *getSpectrumDisplay(){return display;}
    void setAudioBuffer(QAudioBuffer buffer);

    void run();

signals:

private:

    const qint32 FFTSize = 1024;

    QVector<RealVector> dataBuffer;
    RealVector currentBuffer;
    bool isRunning;
    DFTEngine fft;

    SpectrumDisplay *display;


};

#endif // SPECTRUMCONTROLLER_H
