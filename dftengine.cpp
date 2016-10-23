#include "dftengine.h"

DFTEngine::DFTEngine()
{
}

void  DFTEngine::setInput(const RealVector &v){
    input.clear();
    for (qint32 i = 0; i < v.size(); i++){
        input.append(v.at(i));
    }
}

ComplexVector DFTEngine::vonHannWindow(int start, int end){

    if (end == -1){
        end = dft.size();
    }

    ComplexVector res;
    if (dft.size() < 2) return res;
    if (end - start < 2) return res;

    // First value
    res.real << 0.5*dft.real.at(start) - 0.25*dft.real.at(start+1);
    res.imag << 0.5*dft.imag.at(start) - 0.25*dft.imag.at(start+1);
    if (start > 0){
        res.real[0] = res.real.at(0) - 0.25*dft.real.at(start-1);
        res.imag[0] = res.imag.at(0) - 0.25*dft.imag.at(start-1);
    }

    for (qint32 i = start+1; i < end-1; i++){
        res.real << 0.5*dft.real.at(i) - 0.25*dft.real.at(i-1) - 0.25*dft.real.at(i+1);
        res.imag << 0.5*dft.imag.at(i) - 0.25*dft.imag.at(i-1) - 0.25*dft.imag.at(i+1);
    }

    // Last value
    res.real << 0.5*dft.real.at(end) - 0.25*dft.real.at(end-1);
    res.imag << 0.5*dft.imag.at(end) - 0.25*dft.imag.at(end-1);
    qint32 last = res.real.size()-1;
    if (end <  (qint32)dft.size()-1){
        res.real[last] = res.real.at(last) - 0.25*dft.real.at(end+1);
        res.imag[last] = res.imag.at(last) - 0.25*dft.imag.at(end+1);
    }

    return res;

}

RealVector DFTEngine::getModuleInBins(qint32 NBins){

    // Windowing the real proyection.
    ComplexVector windowed = vonHannWindow(0,dft.size()/2);
    if (windowed.size() == 0) return RealVector();


    // Check that the number of bins perfectly divides the number of bars
    if ((windowed.size() % NBins) != 0) return RealVector();

    qint32 barsInBin = windowed.size()/NBins;

    qreal avg = 0;
    qreal barCounter = 0;
    RealVector result;
    for (quint32 i = 0; i < windowed.size(); i++){
        //qDebug() << "Abs mod" << (qAbs(windowed.imag.at(i)) + qAbs(windowed.real.at(i)));
        avg = avg + qAbs(windowed.imag.at(i)) + qAbs(windowed.real.at(i));
        barCounter++;
        if (barCounter == barsInBin){
            result << avg/barCounter;
            barCounter = 0;
            avg = 0;
        }
    }



    return result;

}


ComplexVector DFTEngine::calcDFT(ComplexVector x){

    //qWarning() << "DFT Start";

    if (x.size() == 1) return x;
    quint64 N = x.size();
    quint64 M = N/2;

    ComplexVector even;
    ComplexVector odd;

    for (quint64 j = 0; j < M; j++){
        even.real << x.real.at(2*j);
        even.imag << x.imag.at(2*j);
        odd.real << x.real.at(2*j+1);
        odd.imag << x.imag.at(2*j+1);
    }

    even = calcDFT(even);
    odd = calcDFT(odd);

    ComplexVector final;

    qreal alpha = -2*PI_VAL/N;

    // Calculating product of twiddle factor only once
    QVector<qreal> WOr;
    QVector<qreal> WOi;

    for (quint64 k = 0; k < M; k++){
        // Argument for trig functions.
        qreal t = alpha*k;

        // The twiddle factor
        qreal Wr = qCos(t);
        qreal Wi = qSin(t);

        WOr << Wr*odd.real.at(k) - Wi*odd.imag.at(k);
        WOi << Wr*odd.imag.at(k) + Wi*odd.real.at(k);

    }


    // First half
    for (quint64 k = 0; k < M; k++){
        final.real << even.real.at(k) + WOr.at(k);
        final.imag << even.imag.at(k) + WOi.at(k);
    }

    // Second half
    for (quint64 k = 0; k < M; k++){
        final.real << even.real.at(k) - WOr.at(k);
        final.imag << even.imag.at(k) - WOi.at(k);
    }

    //qWarning() << "DFT End";

    return final;

}

