#include "spectrumcontroller.h"

SpectrumController::SpectrumController()
{
    display = new SpectrumDisplay("");
    isRunning = false;
    display->setScaleFactor(FFTSize);

}

void SpectrumController::run(){
    if (!dataBuffer.isEmpty()){
        isRunning = true;

        fft.setInput(dataBuffer.first());
        dataBuffer.removeFirst();
        fft.doDFT();

        QVector<qreal> mod = fft.getDFTResult().getAbsMod();
        display->setSpectrum(mod.mid(0,mod.size()/2));

        isRunning = false;
    }
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
            currentBuffer << data[i].left/peak;
            if (currentBuffer.size() == FFTSize){
                dataBuffer << currentBuffer;
                currentBuffer.clear();
                if (!isRunning) run();
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
//            if (currentBuffer.size() == FFTSize){
//                dataBuffer << currentBuffer;
//                currentBuffer.clear();
//            }
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



}




