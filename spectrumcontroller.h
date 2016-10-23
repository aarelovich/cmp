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
    void songChanged() {peakAnalyzer.reset(); display->resetPeakVars(); }

    void run();

signals:

private:

    const qint32 FFT_SIZE          = 1024;
    const qint32 GROUP_BAR_COUNT   = 128;
    const qint32 BARS_TO_DISPLAY   = 80;

    struct PeakAverager{

        void reset(){
            peakAverageValue = 1;
            peakCounter = 0;
            peakAcc = 0;
        }

        void update (qreal peak){
            if (peak > peakAverageValue){
                peakCounter++;
                peakAcc = peakAcc + peak;
                peakAverageValue = peakAcc/peakCounter;
            }
        }

        qreal getAvg() const {return peakAverageValue;}

    private:
        qreal peakCounter;
        qreal peakAverageValue;
        qreal peakAcc;

    };

    QVector<RealVector> dataBuffer;
    RealVector currentBuffer;
    bool isRunning;
    DFTEngine fft;

    SpectrumDisplay *display;

    PeakAverager peakAnalyzer;

    template<typename T>
    void bufferData(T *data, qint32 N);


};

#endif // SPECTRUMCONTROLLER_H
