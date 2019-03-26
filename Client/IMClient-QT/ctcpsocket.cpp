#include "ctcpsocket.h"
#include <QDebug>
#include <QThread>
#include <QDataStream>
#include <QTimer>
#include "common.h"

CTcpSocket::CTcpSocket()
    : m_nConnectionState(STATE_UNCONNECTED)
    , m_nLastRequestType(0)
{
    connect(this, &CTcpSocket::connected, this, &CTcpSocket::onConnected);
    connect(this, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &CTcpSocket::onSocketError);
    connect(this, &CTcpSocket::readyRead, this, &CTcpSocket::onRecv);
}

void CTcpSocket::start(const QString &hostName, quint16 port)
{
    if(STATE_CONNECTED == m_nConnectionState ||
       STATE_CONNECTING == m_nConnectionState){
        qDebug("Connecting or connected");
        return;
    }
    if(hostName != m_strHostName ||
       port != m_nPort){
       m_strHostName = hostName;
       m_nPort = port;
    }
    qDebug() << "Start connection:" << hostName << ":" << port;
    m_nConnectionState = STATE_CONNECTING;
    connectToHost(hostName, port);
}

void CTcpSocket::onConnected()
{
    qDebug("Connected");
    m_nConnectionState = STATE_CONNECTED;
}

void CTcpSocket::stop()
{
    qDebug("Unconnected");
    abort();
    m_nConnectionState = STATE_UNCONNECTED;
}

void CTcpSocket::send(quint16 msgType, const QString &msgData)
{
    const quint32 MAX_RETRY_CNTS = 10;
    static quint32 retryCnt = 0;
    if(STATE_CONNECTED != m_nConnectionState){
        // used when regist new account or login
        if(retryCnt++ < MAX_RETRY_CNTS){
                m_nLastRequestType = msgType;
                m_strLastRequsetData = msgData;
                QTimer::singleShot(500, this, &CTcpSocket::sendRetry);
        }
        else{
            // send timedout signal
            retryCnt = 0;
            emit signalSocketError("send time out");
        }
        return;
    }

    m_nLastRequestType = 0;
    retryCnt = 0;
    qDebug() << "send:" << msgType << " " << msgData;
    QByteArray data;
    QDataStream packet(&data, QIODevice::WriteOnly);
    packet.setVersion(QDataStream::Qt_4_0);
    packet.setByteOrder(QDataStream::BigEndian);
    packet << quint8(0x5A) << quint8(0x48) << quint8(0x48) << quint8(0) << quint32(msgData.toUtf8().size())
           << msgType << quint8(0) << quint8(0) << quint8(0) << quint8(0) << quint8(0) << quint8(0);
    packet.device()->seek(data.size());
    packet.writeRawData(msgData.toUtf8().data(), msgData.toUtf8().size());
    write(data);

}

void CTcpSocket::sendRetry()
{
    if(0 == m_nLastRequestType){
        return;
    }
    qDebug("send retrying");
    send(m_nLastRequestType, m_strLastRequsetData);
}

void CTcpSocket::onRecv()
{
    if(bytesAvailable() <= 0){
        return;
    }
    QByteArray buffer;
    buffer = readAll();
    m_buffer.append(buffer);
    qDebug() << "OnRecv:" << buffer.size() << " Bytes";

    uint totalLen = static_cast<uint>(m_buffer.size());
    while(totalLen){
        if(totalLen < sizeof(ST_NET_MSG)){
            break;
        }
        // get message head
        ST_NET_MSG stMsg;
        QDataStream packet(m_buffer);
        packet.setByteOrder(QDataStream::BigEndian);
        packet >> stMsg.magic[0] >> stMsg.magic[1] >> stMsg.magic[2] >> stMsg.resv1 >> stMsg.dataLen
               >> stMsg.msgType >> stMsg.resv2[0] >> stMsg.resv2[1] >> stMsg.resv2[2] >> stMsg.resv2[3]
               >> stMsg.resv2[4] >> stMsg.resv2[5];
        // check magic
        if('Z' != stMsg.magic[0] || 'H' != stMsg.magic[1] || 'H' != stMsg.magic[2]){
            qDebug("Magic error");
        }
        // check total package size
        if(totalLen < stMsg.dataLen + sizeof(ST_NET_MSG)){
            break;
        }
        // dealing with heartbeat msg
        if(NET_MSG_TYPE_HEARTBEAT_REQUEST == stMsg.msgType){
            ;
        }
        else{
            // emitting signal
            char* temp = new char[stMsg.dataLen + 1];
            memset(temp, 0, stMsg.dataLen + 1);
            packet.device()->seek(sizeof(ST_NET_MSG));
            packet.readRawData(temp, static_cast<int>(stMsg.dataLen));
            QByteArray restdata(temp);
            delete[] temp;
            QString msgData = QString::fromUtf8(restdata);
            emit signalMsgReceived(stMsg.msgType, msgData);
        }
        // go on dealing with another packet or exit the loop
        buffer = m_buffer.right(static_cast<int>(totalLen - stMsg.dataLen - sizeof(ST_NET_MSG)));
        totalLen = static_cast<uint>(buffer.size());
        m_buffer = buffer;
    }
}



void CTcpSocket::onSocketError(QAbstractSocket::SocketError socketError)
{
    abort();
    m_nConnectionState = STATE_UNCONNECTED;
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug("Remote host closed");
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug("Host not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug("Connection refused");
        break;
    default:
        qDebug("Socket error:%d", socketError);
    }

    // Try to connect to server again
    start(m_strHostName, m_nPort);

    // send signal
    emit signalSocketError("");
}
