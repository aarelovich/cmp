#include "spectrumcontroller.h"

SpectrumController::SpectrumController(QObject *parent) : QObject(parent)
{
    display = new SpectrumDisplay("");
    isRunning = false;
    connect(&fft,&QThread::finished,this,&SpectrumController::on_specAvailable);
    display->setScaleFactor(FFTSize);
}


void SpectrumController::setAudioBuffer(QAudioBuffer buffer){

    // Only process stereo frames
    if (buffer.format().channelCount() != 2) return;

    qreal peak;

    if (buffer.format().sampleType() == QAudioFormat::SignedInt){

        //qWarning() << "Signed data" << counter; counter++;
        switch (buffer.format().sampleSize()){
        case 32:
            peak = INT_MAX;
            break;
        case 16:
            peak = SHRT_MAX;
            break;
        default:
            peak = CHAR_MAX;
            break;
        }

        QAudioBuffer::S16S *data = buffer.data<QAudioBuffer::S16S>();

        for (qint32 i = 0; i < buffer.frameCount(); i++){
            currentBuffer.append(data[i].left);
            if (currentBuffer.size() == FFTSize){
                //qWarning() << "Adding to data buffer";
                dataBuffer << currentBuffer;
                currentBuffer.clear();
                //qWarning() << "All clear";
            }
        }

    }
    else if (buffer.format().sampleType() == QAudioFormat::UnSignedInt){

        //qWarning() << "Unsigned data";

        switch (buffer.format().sampleSize()){
        case 32:
            peak = UINT_MAX;
            break;
        case 16:
            peak = USHRT_MAX;
            break;
        default:
            peak = UCHAR_MAX;
            break;
        }

        QAudioBuffer::S16U *data = buffer.data<QAudioBuffer::S16U>();

        for (qint32 i = 0; i < buffer.frameCount(); i++){
            currentBuffer.append(data[i].left/peak);
            if (currentBuffer.size() == FFTSize){
                dataBuffer << currentBuffer;
                currentBuffer.clear();
            }
        }

    }
    else if(buffer.format().sampleType() == QAudioFormat::Float){

        //qWarning() << "Float data";

        peak = 1.00003;
        QAudioBuffer::S32F *data = buffer.data<QAudioBuffer::S32F>();

        for (qint32 i = 0; i < buffer.frameCount(); i++){
            currentBuffer.append(data[i].left/peak);
            if (currentBuffer.size() == FFTSize){
                dataBuffer << currentBuffer;
                currentBuffer.clear();
            }
        }


    }

    processBuffer();

}

void SpectrumController::processBuffer(){
    if (!dataBuffer.isEmpty()){
        if (!isRunning){
            fft.setInput(dataBuffer.first());
            dataBuffer.removeFirst();
            //qWarning() << "Data buffer size" << dataBuffer.size();
            fft.start();
            isRunning = true;
        }
    }
}

void SpectrumController::on_specAvailable(){

    //qWarning() << "Spec available";

    QVector<qreal> mod = fft.getDFTResult().getAbsMod();
    display->setSpectrum(mod.mid(0,mod.size()/2));

//    std::cout << counter << ":";
//    for (qint32 i = 0; i < mod.size(); i++){
//         std::cout << mod.at(i);
//    }
//    std::cout << std::endl;
//    std::cout << std::endl;

//    counter++;

    isRunning = false;
    processBuffer();

}


