#ifndef DFTENGINE_H
#define DFTENGINE_H

#include <QThread>
#include <QtMath>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QHash>
#define     PI           3.14159265358979323846

struct ComplexVectorPointer{

    ComplexVectorPointer(){
        real = new QVector<qreal>();
        imag = new QVector<qreal>();
    }

    void clear(){
        real->clear();
        imag->clear();
    }

    void append(qreal val){
        *real << val;
        *imag << 0;
    }

    QString getStringRepresentantionAt(quint64 i){
        QString ans;
        if (i < (quint64)real->size()){
            ans = QString::number(real->at(i));
        }
        if (i < (quint64)imag->size()){
            if (imag->at(i) >= 0) ans = ans + " + ";
            else ans = ans + " - ";
            ans = ans + QString::number(qAbs(imag->at(i))) + "i";
        }
        return ans;
    }

    QVector<qreal> getAbsMod(){
        QVector<qreal> mod;
        quint64 s = real->size();
        for (quint64 i = 0; i < s; i++){
            qreal v = qAbs(real->at(i)) + qAbs(imag->at(i));
            mod << v;
        }
        return mod;
    }

    quint64 size(){
        return qMin(real->size(),imag->size());
    }

    QVector<qreal> *real;
    QVector<qreal> *imag;
};

class DFTEngine : public QThread
{
public:
    DFTEngine();


    void run();

    // Appending the data
    void resetBuffer() {buffer.clear();}
    void bufferValue(qreal datum){ *buffer.real << datum; *buffer.imag << 0; }
    void setBuffer(ComplexVectorPointer cvp) {buffer.clear(); buffer = cvp;}
    ComplexVectorPointer getDFTResult();
    bool isRunning() const {return running;}
    ComplexVectorPointer calcDFT(ComplexVectorPointer x);


private:
    ComplexVectorPointer buffer;
    QVector<ComplexVectorPointer> dftResults;


    // NOT USED
    ComplexVectorPointer twiddleFactors;
    QVector<quint64> bitReversal;
    quint64 Ns;
    bool running;

    // Getting the vectors and dbug functions
    ComplexVectorPointer getTwiddleFactors() {return twiddleFactors;}
    // Bit reversal. Not used.
    static quint64 reverseBitsOnN(quint64 value, quint64 N);
    // Pre calculates the twiddle factors. But was not used in the final implementation
    void prepare(qint32 twoExponent);
    // Printing a vector. For Debug
    static void printComplexVectorPointer(ComplexVectorPointer cvp,  QString file);
    void printBitReversalTable();


};

#endif // DFTENGINE_H
