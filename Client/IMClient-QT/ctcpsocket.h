#ifndef CTCPSOCKET_H
#define CTCPSOCKET_H
#include <QTcpSocket>

#define STATE_UNCONNECTED   (0)
#define STATE_CONNECTING    (1)
#define STATE_CONNECTED     (2)

typedef struct ST_NET_MSG_T
{
    unsigned char magic[3];		// Magic:0x5A 0x48 0x48
    unsigned char resv1;
    quint32 dataLen;				// msg data length in bytes
    quint16 msgType;
    unsigned char resv2[6];
}ST_NET_MSG;

class CTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    CTcpSocket();

signals:
    void signalMsgReceived(quint16 msgType, const QString &data);
    void signalSocketError(const QString &errMsg);

public slots:
    void start(const QString &hostName, quint16 port);
    void stop();
    void send(quint16 msgType, const QString &msgData);
    void onRecv();
private slots:
    void onConnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void sendRetry();
private:
    uint m_nConnectionState;
    QString m_strHostName;
    quint16 m_nPort;
    QByteArray m_buffer;

    quint16 m_nLastRequestType;
    QString m_strLastRequsetData;
};

#endif // CTCPSOCKET_H
