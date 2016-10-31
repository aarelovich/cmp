#include "spectrumcontroller.h"

SpectrumController::SpectrumController()
{
    display = new SpectrumDisplay("");
    isRunning = false;
    ColoUiConfiguration c = display->getConfiguration();
    c.set(SD_DISPLAY_BAR_NUM,BARS_TO_DISPLAY);
    c.set(SD_SEGMENTS_IN_BAR,20);
    display->setConfiguration(c);
    this->songChanged();
    enableBuffering = true;

    writeFile = new QFile("accept.txt");
    writeFile->open(QFile::WriteOnly);
    writer = new QTextStream(writeFile);

}

void SpectrumController::enableDataBuffering(bool enable){
    if (!enable){
        dataBuffer.clear();
        currentBuffer.clear();
    }
    enableBuffering = enable;
}

void SpectrumController::run(){
    if (!dataBuffer.isEmpty()){
        isRunning = true;

        fft.setInput(dataBuffer.first());
        dataBuffer.removeFirst();
        fft.doDFT();

        RealVector mod  = fft.getModuleInBins(GROUP_BAR_COUNT);

        RealVector toDraw;
        for (qint32 i = 0; i < BARS_TO_DISPLAY; i++){
            peakAnalyzer.update(mod.at(i));
            //qWarning() << "Mod @ i" << mod.at(i) << "Average" << peakAnalyzer.getAvg();
            toDraw << mod.at(i)/(peakAnalyzer.getAvg());
            //qWarning() << "To draw" << toDraw.last();
        }

        display->setSpectrum(toDraw);


        isRunning = false;
    }
}

void SpectrumController::setAudioBuffer(QAudioBuffer buffer){

    // Used to momentarily stop the process.
    if (!enableBuffering) return;

    // Only process stereo frames
    if (buffer.format().channelCount() != 2) return;

    if (buffer.format().sampleType() == QAudioFormat::SignedInt){

        //qWarning() << "Signed";
        QAudioBuffer::S16S *data = buffer.data<QAudioBuffer::S16S>();
        bufferData(data,buffer.frameCount());

    }
    else if (buffer.format().sampleType() == QAudioFormat::UnSignedInt){

        //qWarning() << "Unsigned";
        QAudioBuffer::S16U *data = buffer.data<QAudioBuffer::S16U>();
        bufferData(data,buffer.frameCount());

    }
    else if(buffer.format().sampleType() == QAudioFormat::Float){

        //qWarning() << "Float";
        QAudioBuffer::S32F *data = buffer.data<QAudioBuffer::S32F>();
        bufferData(data,buffer.frameCount());

    }

}

template<typename T>
void SpectrumController::bufferData(T *data, qint32 N){
    for (qint32 i = 0; i < N; i++){
        //if (qAbs(data[i].left) > largest){largest = qAbs(data[i].left); qDebug() << "Largest" << largest;}
        //currentBuffer << ((qreal)data[i].left/(largest));
        //qWarning() << "Added data" << currentBuffer.last();
        currentBuffer << data[i].left;

        if (datcounter < 100000){
            *writer << data[i].left;
            *writer << "\n";
            datcounter++;
        }
        else if (writeFile->isOpen()){
            qWarning() << "Closed file";
            writeFile->close();
        }

        if (currentBuffer.size() == FFT_SIZE){
            dataBuffer << currentBuffer;
            currentBuffer.clear();
            if (!isRunning) run();
        }
    }
}




