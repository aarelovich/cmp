#ifndef DFTENGINE_H
#define DFTENGINE_H

#include <QtMath>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QHash>
#define     PI_VAL          3.14159265358979323846

struct ComplexVector{

    ComplexVector(){
    }

    void clear(){
        real.clear();
        imag.clear();
    }

    void append(qreal val){
        real << val;
        imag << 0;
    }

    QString getStringRepresentantionAt(quint64 i){
        QString ans;
        if (i < (quint64)real.size()){
            ans = QString::number(real.at(i));
        }
        if (i < (quint64)imag.size()){
            if (imag.at(i) >= 0) ans = ans + " + ";
            else ans = ans + " - ";
            ans = ans + QString::number(qAbs(imag.at(i))) + "i";
        }
        return ans;
    }

    QVector<qreal> getAbsMod(){
        QVector<qreal> mod;
        quint64 s = real.size();
        for (quint64 i = 0; i < s; i++){
            qreal v = qAbs(real.at(i)) + qAbs(imag.at(i));
            mod << v;
        }
        return mod;
    }

    quint64 size(){
        return qMin(real.size(),imag.size());
    }

    QVector<qreal> real;
    QVector<qreal> imag;
};

typedef QVector<qreal> RealVector;

class DFTEngine
{
public:
    DFTEngine();

    // Appending the data
    void setInput(const RealVector &v);
    ComplexVector getDFTResult(){return dft;}
    void doDFT() {dft.clear(); dft = calcDFT(input);}
    RealVector getModuleInBins(qint32 NBins);
    ComplexVector vonHannWindow(int start = 0, int end = -1);
    ComplexVector calcDFT(ComplexVector x);

private:

    ComplexVector dft;
    ComplexVector input;

};

#endif // DFTENGINE_H
