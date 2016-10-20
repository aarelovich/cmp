#ifndef SPECTRUMCONTROLLER_H
#define SPECTRUMCONTROLLER_H

#include <QObject>
#include <QAudioBuffer>
#include "spectrumdisplay.h"

class SpectrumController : public QObject
{
    Q_OBJECT
public:
    explicit SpectrumController(QObject *parent = 0);
    SpectrumDisplay *getSpectrumDisplay(){return display;}
    void setAudioBuffer(QAudioBuffer buffer);

signals:

public slots:    
    void on_specAvailable();

private:

    const qint32 FFTSize = 1024;

    QVector<RealVector> dataBuffer;
    RealVector currentBuffer;
    bool isRunning;
    DFTEngine fft;

    SpectrumDisplay *display;

    void processBuffer();
};

#endif // SPECTRUMCONTROLLER_H
