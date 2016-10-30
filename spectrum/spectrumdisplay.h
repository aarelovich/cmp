#ifndef SPECTRUMDISPLAY_H
#define SPECTRUMDISPLAY_H

#include "colouielement.h"
#include "dftengine.h"

#define  SD_DISPLAY_BAR_NUM  "numberOfBarsToDisplay"
#define  SD_SEGMENTS_IN_BAR  "numberOfSegmentsInBAr"

class SpectrumDisplay : public ColoUiElement
{
public:
    SpectrumDisplay(QString ID, ColoUiSignalManager *ss = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setConfiguration(ColoUiConfiguration c);

    void setSpectrum(RealVector rv) {spectrum = rv; update();}
    void resetPeakVars() {maxvalue = 0; scaleFactor = 1;}

private:

    qint32 numberOfBars;
    qreal barWidth;
    qreal barSpace;
    qreal numberSegments;
    RealVector spectrum;
    qreal scaleFactor;
    qreal maxvalue;    

    qreal sliceHeight;
    qreal sliceSpace;

    QList<QColor> sliceColors;

    void drawBar(QPainter*painter, qreal x, qreal h);


};

#endif // SPECTRUMDISPLAY_H
