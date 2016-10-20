#include "temp.h"
#include "ui_temp.h"

Temp::Temp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Temp)
{
    ui->setupUi(this);
    connect(&probe,&QAudioProbe::audioBufferProbed,this,&Temp::on_audioBeenBuffered);
    connect(&fft,&QThread::finished,this,&Temp::on_specAvailable);
    probe.setSource(&player);
    counter = 0;
    isRunning = false;
}

Temp::~Temp()
{
    delete ui;
}

void Temp::on_audioBeenBuffered(QAudioBuffer buffer){

    // Only process stereo frames
    if (buffer.format().channelCount() != 2) return;

    qreal peak;

    if (buffer.format().sampleType() == QAudioFormat::SignedInt){

        qWarning() << "Signed data" << counter; counter++;
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
        peak = 1;

        QAudioBuffer::S16S *data = buffer.data<QAudioBuffer::S16S>();

        for (qint32 i = 0; i < buffer.frameCount(); i++){
            currentBuffer.append(data[i].left/peak);
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

void Temp::processBuffer(){
    if (!dataBuffer.isEmpty()){
        if (!isRunning){
            fft.setInput(dataBuffer.first());
            dataBuffer.removeFirst();
            fft.start();
            isRunning = true;
        }
    }
}

void Temp::on_specAvailable(){

    //qWarning() << "Spec available";

    QVector<qreal> mod = fft.getDFTResult().getAbsMod();

//    std::cout << counter << ":";
//    for (qint32 i = 0; i < mod.size(); i++){
//         std::cout << mod.at(i);
//    }
//    std::cout << std::endl;
//    std::cout << std::endl;

//    counter++;

    QString show;
    for (qint32 i = 0; i < mod.size()/2; i++){
        qint32 val = mod.at(i);
        show = show + QString::number(val) + " ";
    }

    ui->lineEdit->setText(show);

    isRunning = false;
    processBuffer();

}

void Temp::on_pushButton_clicked()
{
    //player.setMedia(QUrl::fromLocalFile("/home/ariela/Music/2009 - Babylon/09 - Promised Land.mp3"));
    player.setMedia(QUrl::fromLocalFile("/home/ariel/Workspace/02  Air Supply - GH 2000 - All Out Of Love.mp3"));
    player.play();
    qWarning() << "A ver si se reproduce: " << player.mediaStatus();
    qWarning() << "Player state" << player.state();
}
