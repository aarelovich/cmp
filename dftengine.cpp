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

ComplexVectorPointer DFTEngine::calcDFT(ComplexVectorPointer x){

    //qWarning() << "DFT Start";

    if (x.size() == 1) return x;
    quint64 N = x.size();
    quint64 M = N/2;

    ComplexVectorPointer even;
    ComplexVectorPointer odd;

    for (quint64 j = 0; j < M; j++){
        even.real << x.real.at(2*j);
        even.imag << x.imag.at(2*j);
        odd.real << x.real.at(2*j+1);
        odd.imag << x.imag.at(2*j+1);
    }

    even = calcDFT(even);
    odd = calcDFT(odd);

    ComplexVectorPointer final;

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

//void DFTEngine::prepare(qint32 twoExponent){

//    quint64 N = 2 << (twoExponent-1);
//    Ns = N;
//    quint64 M = N/2;

//    twiddleFactors.clear();

//    qreal expr = 2*PI/N;

//    for (quint64 i = 0; i < M; i++){
//        *twiddleFactors.real << qCos(expr*i);
//        *twiddleFactors.imag << qSin(expr*i);
//    }


//    for (quint64 i = 0; i < M; i++){
//        *twiddleFactors.real << -twiddleFactors.real.at(i);
//        *twiddleFactors.imag << -twiddleFactors.imag.at(i);
//    }

//    bitReversal.clear();

//    for (quint64 i = 0; i < N; i++){
//        bitReversal << reverseBitsOnN(i,twoExponent);
//    }

//}

//quint64 DFTEngine::reverseBitsOnN(quint64 value, quint64 N){

//    quint64 resvalue = 0;
//    for (quint64 i = 0; i < N; i++){
//        if ((value % 2) != 0) resvalue++;
//        if (i < N-1){
//        resvalue = resvalue << 1;
//        value = value >> 1;
//        }
//    }
//    return resvalue;

//}

//void DFTEngine::printComplexVectorPointer(ComplexVectorPointer cvp, QString file){

//    quint64 s = cvp.size();

//    QFile f(file);
//    if (!f.open(QFile::WriteOnly)){
//        return;
//    }

//    QTextStream writer(&f);

//    for (quint64 i = 0; i < s; i++){
//        writer << cvp.getStringRepresentantionAt(i) << "\n";
//    }

//    f.close();

//}

//void DFTEngine::printBitReversalTable(){

//    for (qint32 i = 0; i < bitReversal.size(); i++){
//        qWarning() << i << " --- " << bitReversal.at(i);
//    }

//}
