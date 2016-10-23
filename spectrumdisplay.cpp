#include "spectrumdisplay.h"

SpectrumDisplay::SpectrumDisplay(QString ID, ColoUiSignalManager *ss):ColoUiElement(ID,ss)
{
}

void SpectrumDisplay::setConfiguration(ColoUiConfiguration c){
    ColoUiElement::setConfiguration(c);
    numberOfBars = c.getUInt16(SD_DISPLAY_BAR_NUM);
    numberSegments = c.getUInt16(SD_SEGMENTS_IN_BAR);

    // Bar width calculations for dimensions
    qreal K = 10;
    barSpace = this->w/(K*numberOfBars + numberOfBars + 1);
    barWidth = K*barSpace;
    maxvalue = 0;
    scaleFactor = 1;

    // Segment (or Slice) height calculations for dimensions
    K = 6;
    sliceSpace = this->h/(numberSegments*K + numberSegments-1);
    sliceHeight = K*sliceSpace;


    // Segment color spectrum
    qreal alphaDelta = 1/(numberSegments-1);

    QColor start   = QColor("#000088");
    QColor end     = QColor("#FFFFFF");

    // In order to transtion out of white faster an exponetial scale is used, with base 10
    for (qint32 i = 0; i < numberSegments; i++){
        QColor c;
        qreal alpha = 1 - qPow(10,-2*alphaDelta*i);  // alpha = 1 - 10^(-2*x) su that when x = 1 then alpha = 0.99.
        c.setRed(start.red()*alpha + (1-alpha)*end.red());
        c.setBlue(start.blue()*alpha + (1-alpha)*end.blue());
        c.setGreen(start.green()*alpha + (1-alpha)*end.green());
        sliceColors << c;
    }


}

void SpectrumDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Background
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawRect(boundingBox);

    if (spectrum.size() < numberOfBars) return;

    // Bars
    painter->setBrush(QBrush(QColor(Qt::red)));

    QPen pen; pen.setWidth(0); pen.setColor(Qt::white);
    painter->setPen(pen);

    qreal x = barSpace;
    for (qint32 i = 0; i < numberOfBars; i++){

//        qreal v = log10(spectrum.at(i)*this->h);
//        if (v > maxvalue){
//            maxvalue = v;
//            scaleFactor = (this->h)/maxvalue;
//        }
//        qreal bh = qMin((qreal)this->h,scaleFactor*v);

        qreal bh = this->h*(1-qPow(10,-5*spectrum.at(i)));
        drawBar(painter,x,bh);

        x = x + barWidth + barSpace;
    }


}


void SpectrumDisplay::drawBar(QPainter*painter, qreal x, qreal h){

    qreal ys = this->h - sliceHeight;
    qreal threshY = 0;
    qreal deltaY = sliceHeight + sliceSpace;

    //qDebug() << "---------------ONE BAR----------------------";

    for (qint32 i = 0; i < numberSegments; i++){

        //qDebug() << "Comparing " << h << "with" << threshY;

        if (h > threshY){
            painter->setBrush(QBrush(sliceColors.at(i)));
        }
        else{
            painter->setBrush(QBrush(Qt::black));
        }


        painter->drawRect(x,ys,barWidth,sliceHeight);

        ys = ys - deltaY;
        threshY = threshY + deltaY;

    }

    //qDebug() << "---------------ONE BAR----------------------";

}

