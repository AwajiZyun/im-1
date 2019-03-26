#ifndef CNETWORKER_H
#define CNETWORKER_H

#include <QObject>
#include <QThread>

class CNetWorker : public QObject
{
    Q_OBJECT
public:
    explicit CNetWorker(QObject *parent = nullptr);
    ~CNetWorker();
    Q_INVOKABLE void start(const QString &hostName, quint16 port);
    Q_INVOKABLE void stop();
    void sendMsg(quint16 msgType, const QString &msgData);

    Q_INVOKABLE void sendRegistRequest(const QString &email, const QString &pwd, const QString &nickName, const quint32 sex);
    Q_INVOKABLE void sendLoginRequest(const QString &code, const QString &pwd);
    Q_INVOKABLE void sendUpdateAccountRequest(const QString &oldPwd, const QString &newPwd, const QString &nickName, const quint32 sex);
    Q_INVOKABLE void sendFriendMsgRequest(const QString &myCode, const QString &friendCode, const QString &msg);
    Q_INVOKABLE void sendAddFriendRequest(const QString &friendCode);
    Q_INVOKABLE void sendUpdateFriendListRequest();
    Q_INVOKABLE void sendUpdateFriendInfoRequest(const QString &friendCode);
    Q_INVOKABLE void sendDeleteFriendRequest(const QString &friendCode);

    void sendHeartbeat();
signals:
    void signalStart(const QString &hostName, quint16 port);
    void signalStop();

    void signalError(const QString &errMsg);
    void signalSendMsg(quint16 msgType, const QString &data);

    void signalRegistResponse(quint32 result, const QString &data);
    void signalLoginResponse(quint32 result, const QString &data);
    void signalUpdateAccountResponse(quint32 result, const QString &data);
    void signalAddFriendResponse(quint32 result, const QString &data);
    void signalAddFriendPush(quint32 result, const QString &data);
    void signalUpdateFriendListResponse(quint32 result, const QString &data);
    void signalDeleteFriendResponse(quint32 result, const QString &data);
    void signalRecvFriendMsgPush(quint32 result, const QString &data);
    void signalSendFriendMsgResponse(quint32 result, const QString &data);
    void signalOnlineInfoPush(quint32 result, const QString &data);
    void signalDeleteFriendPush(quint32 result, const QString &data);
    void signalUpdateFriendInfoPush(quint32 result, const QString &data);

public slots:
    void onError(const QString &errMsg){ emit signalError(errMsg); }
    void onReceive(quint16 msgType, const QString &data);

private:
    QThread m_socketThread;
};

#endif // CNETWORKER_H
