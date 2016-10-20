#include "spectrumdisplay.h"

SpectrumDisplay::SpectrumDisplay(QString ID, ColoUiSignalManager *ss):ColoUiElement(ID,ss)
{
}

void SpectrumDisplay::setConfiguration(ColoUiConfiguration c){
    ColoUiElement::setConfiguration(c);
    numberOfBars = 128;
    qreal K = 10;
    barSpace = this->w/(K*numberOfBars + numberOfBars + 1);
    barWidth = K*barSpace;
    maxCounter = 0;
}

void SpectrumDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Background
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawRect(boundingBox);

    //qWarning() << "Spectrum size" << spectrum.size();

    if (spectrum.size() < numberOfBars) return;

    // Bars
    painter->setBrush(QBrush(QColor(Qt::red)));

    qreal x = barSpace;
    for (qint32 i = 0; i < numberOfBars; i++){
        if (spectrum.at(i) > maxvalue){
            qWarning() << "MAX: " << maxvalue;
            maxvalue = maxvalue + spectrum.at(i);
            maxCounter++;
            scaleFactor = maxvalue/maxCounter;
            qWarning() << "SF" << scaleFactor;
        }
        qreal bh = qMin((qreal)this->h,spectrum.at(i)*this->h/scaleFactor);
        QRectF bar(x, this->h - bh, barWidth, bh);
        painter->drawRect(bar);
        x = x + barWidth + barSpace;
    }


}


