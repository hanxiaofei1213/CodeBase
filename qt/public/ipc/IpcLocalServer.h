#pragma once
// 进程间通讯服务类，支持服务端主动发送信息给客户端，但只会发送到最近一次的建立连接的客户端
#include "IIpcServer.h"
#include <QObject>
#include <QString>
#include <QLocalServer>
#include <QLocalSocket>
#include <QVector>

class IpcLocalServer : public QObject, public IIPCServer {
    Q_OBJECT
public:

    IpcLocalServer(const QString& strName);
    ~IpcLocalServer();

    virtual bool sendMsg(const QString& strMsg) override;
    virtual void setReciveMsgCallback(ReciveMsgCallback callback) override;
    virtual bool isConnected() override;

protected:
    void initServer();
    bool isValid();
    void sendAllBackupMsg();

    void onNewConnection();
    void onReadyRead();

private:
    ReciveMsgCallback m_reciveMsgCallback;
    QString m_strServerName;
    QLocalServer* m_server = nullptr;
    bool m_bValid = false;
    QLocalSocket* m_lastSocket = nullptr;
    QVector<QString> m_vecBackupMsg;
};





