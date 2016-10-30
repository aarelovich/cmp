#ifndef MASTERCONNECTION_H
#define MASTERCONNECTION_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include "datapacket.h"

//------------------------ DEFINES ----------------------------------------
#define   UDP_HEADER                "CMP_MASTER_PING"
#define   UDP_PORT                  25001
#define   UDP_ANNOUNCEMENT_FIELDS   2

#define   TCP_FILE_CHUNK_SIZE       5000

#define   TCP_HEADER_GREETING       "CMP_GREETING"
#define   TCP_HEADER_RAWDATA        "CMP_RAWDATA"
#define   TCP_HEADER_FILEINFO       "CMP_FILESIZE"
#define   TCP_HEADER_FILE_EXISTS    "CMP_FILE_EXISTS"
#define   TCP_HEADER_FILE_ERROR     "CMP_FILE_ERROR"
#define   TCP_HEADER_ACKNOWLEDGE    "CMP_ACK"
#define   TCP_HEADER_TRANSFER_START "CMP_TRANSFER_START"
#define   TCP_HEADER_TRANSFER_END   "CMP_TRANSFER_END"
#define   TCP_HEADER_TSTART_ACK     "CMP_TRANSFER_START_ACK"


class TransferManager : public QObject
{
    Q_OBJECT
public:
    explicit TransferManager(QObject *parent = 0);

    // Functions for self discovery
    Q_INVOKABLE QString startTCPServer();
    Q_INVOKABLE void listenForUDPAnnouncement(QString slave_name);
    Q_INVOKABLE QString sendUDPAnnouncement(QString master_name);

    Q_INVOKABLE void setTransferList(QStringList tlist){fileList = tlist;}
    Q_INVOKABLE void startTransfer();
    Q_INVOKABLE void setSaveDirectory(QString savedir){destinationDirectory = savedir;}

    // Getting basic data
    Q_INVOKABLE QString getMasterID() const {return masterID;}
    Q_INVOKABLE QString getSlaveID() const {return slaveID;}
    Q_INVOKABLE quint16 getCurrentIP() const {return ownIP;}

signals:
    void connectionEstablished();
    void error(QString error);
    void notify(QString message);
    void updateCurrentFile(qint32 percent);

private slots:
    void on_newUDPData();
    void on_newTCPData();
    void on_connectionEstablished();
    void on_incommingConnection();
    void on_tcpSocket_Disconnected();

private:

    // Network classes
    QTcpSocket *tcpSocket;
    QTcpServer tcpServer;
    QUdpSocket udpSocket;
    quint32 ownIP;

    // Slave and master identification
    QString masterID;
    QString slaveID;
    bool isMaster;

    // TCP Data packet
    DataPacket tcpData;

    // File transfer variables
    qint64 currentFileSize;
    qint64 bytesReceivedOfCurrentFile;
    qint64 bytesSentOfCurrentFile;
    QFile fileBeingReceived;
    QFile fileBeingTransfered;
    qint32 fileTransferID;
    qint32 numOfFilesToTransfer;
    QStringList fileList;
    QString destinationDirectory;

    void sendFileInfoNextFile();
    void processPacket();

};

#endif // MASTERCONNECTION_H
