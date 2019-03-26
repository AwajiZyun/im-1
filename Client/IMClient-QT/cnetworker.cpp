#include "cnetworker.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "ctcpsocket.h"
#include "common.h"
#include "cutility.h"


CNetWorker::CNetWorker(QObject *parent)
    : QObject(parent)
{
    CTcpSocket *pSocket = new CTcpSocket();
    pSocket->moveToThread(&m_socketThread);

    connect(&m_socketThread, &QThread::finished, pSocket, &QObject::deleteLater);

    connect(this, &CNetWorker::signalStart, pSocket, &CTcpSocket::start);
    connect(this, &CNetWorker::signalStop, pSocket, &CTcpSocket::stop);
    connect(this, &CNetWorker::signalSendMsg, pSocket, &CTcpSocket::send);

    connect(pSocket, &CTcpSocket::signalMsgReceived, this, &CNetWorker::onReceive);
    connect(pSocket, &CTcpSocket::signalSocketError, this, &CNetWorker::onError);

    m_socketThread.start();
}

CNetWorker::~CNetWorker()
{
    m_socketThread.quit();
    m_socketThread.wait();
}

void CNetWorker::start(const QString &hostName, quint16 port)
{
    emit signalStart(hostName, port);
}

void CNetWorker::stop()
{
    emit signalStop();
}

void CNetWorker::sendMsg(quint16 msgType, const QString &msgData)
{
    emit signalSendMsg(msgType, msgData);
}

void CNetWorker::sendRegistRequest(const QString &email, const QString &pwd, const QString &nickName, const quint32 sex)
{
    QByteArray pwdArr = pwd.toLatin1();
    QString data = "{ \"email\": \"" + email + "\"," +
            "  \"nickname\": \"" + nickName + "\"," +
            "  \"sex\": " + QString(sex) + "\"," +
            "  \"password\": \"" + QString::fromStdString(CUtility::RSAEncrypt(pwdArr.data())) + "\"}";
    sendMsg(NET_MSG_TYPE_ACCOUNT_REGIST_REQUEST, data);
}

void CNetWorker::sendLoginRequest(const QString &code, const QString &pwd)
{
    QByteArray pwdArr = pwd.toLatin1();
    QString data = "{ \"code\": \"" + code + "\"," +
            "  \"password\": \"" + QString::fromStdString(CUtility::RSAEncrypt(pwdArr.data())) + "\"}";
    sendMsg(NET_MSG_TYPE_ACCOUNT_LOGIN_REQUEST, data);
    qDebug() << "sendLoginRequest:" << data;
}

void CNetWorker::sendUpdateAccountRequest(const QString &oldPwd, const QString &newPwd, const QString &nickName, const quint32 sex)
{
    QByteArray oldPwdArr = oldPwd.toLatin1();
    QByteArray newPwdArr = newPwd.toLatin1();
    QString data = "{\"oldPassword\":\"" + QString::fromStdString(CUtility::RSAEncrypt(oldPwdArr.data())) + "\"," +
            "  \"nickname\":\"" + nickName + "\"," +
            "  \"sex\":" + QString(sex) + "\"," +
            "  \"newPassword\":\"" + QString::fromStdString(CUtility::RSAEncrypt(newPwdArr.data())) + "\"}";
    sendMsg(NET_MSG_TYPE_ACCOUNT_UPDATE_REQUEST, data);
}

void CNetWorker::sendFriendMsgRequest(const QString &myCode, const QString &friendCode, const QString &msg)
{
    QString data = "{ \"fromUser\": \"" + myCode + "\"," +
            "  \"toUser\": \"" + friendCode + "\"," +
            "  \"message\": \"" + msg + "\"}";
    sendMsg(NET_MSG_TYPE_SEND_MESSAGE_REQUEST, data);
}

void CNetWorker::sendAddFriendRequest(const QString &friendCode)
{
    QString data = "{\"symbol\":\"" + friendCode + "\"}";
    sendMsg(NET_MSG_TYPE_ADD_FRIEND_REQUEST, data);
}

void CNetWorker::sendUpdateFriendListRequest()
{
    QString data = "{}";
    sendMsg(NET_MSG_TYPE_UPDATE_FRIEND_INFO_REQUEST, data);
}

void CNetWorker::sendUpdateFriendInfoRequest(const QString &friendCode)
{
    QString data = "{ \"code\": \"" + friendCode + "\"}";
    sendMsg(NET_MSG_TYPE_UPDATE_FRIEND_INFO_REQUEST, data);
}

void CNetWorker::sendDeleteFriendRequest(const QString &friendCode)
{
    QString data = "{ \"code\": \"" + friendCode + "\"}";
    sendMsg(NET_MSG_TYPE_DELETE_FRIEND_REQUEST, data);
}

void CNetWorker::onReceive(quint16 msgType, const QString &data)
{
    quint32 result = 1;     // 0:OK     others:NG
    QString retMsg;
    // dealing wit different responses
    switch (msgType) {
    case NET_MSG_TYPE_ACCOUNT_LOGIN_RESPONSE:{
        QByteArray jsonBuf = data.toUtf8();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBuf);
        if(jsonDoc.isObject()){
            QJsonObject jsonObj = jsonDoc.object();
            QJsonValue success = jsonObj.value("success");
            QJsonValue msg = jsonObj.value("msg");
            if(!success.isNull()){
                result = success.toBool() ? 0 : 1;
                retMsg = msg.isNull() ? "" : msg.toString();
                // saving account info

            }
        }
        break;
    }
    default:
        break;
    }
    emit signalLoginResponse(result, retMsg);
}
