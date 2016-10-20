#ifndef SPECTRUMDISPLAY_H
#define SPECTRUMDISPLAY_H

#include "colouielement.h"
#include "dftengine.h"

#define  SPECD_FFT_SIZE  "specdFFTSize"

class SpectrumDisplay : public ColoUiElement
{
public:
    SpectrumDisplay(QString ID, ColoUiSignalManager *ss = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setConfiguration(ColoUiConfiguration c);

    void setSpectrum(RealVector rv) {spectrum = rv; update();}
    void setScaleFactor(qreal sf) {scaleFactor = sf;}

private:

    qint32 numberOfBars;
    qreal barWidth;
    qreal barSpace;
    RealVector spectrum;
    qreal scaleFactor;
    qreal maxCounter;
    qreal maxvalue;



};

#endif // SPECTRUMDISPLAY_H
