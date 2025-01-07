#pragma once
#include <QObject>
#include <QLocalSocket>
#include <QVector>
#include "IIpcClient.h"

class IpcLocalClient : public QObject, public IIPCClient {
    Q_OBJECT
public:
    IpcLocalClient(const QString& strName);
    ~IpcLocalClient();

    virtual bool sendMsg(const QString& strMsg) override;
    virtual void setReciveMsgCallback(ReciveMsgCallback callback) override;
    virtual bool isConnected() override;
    virtual void stop() override;

protected:
    void beginConnect();
    void sendAllBackupMsg();

    void onReadyRead();
    void onStatuChanged(QLocalSocket::LocalSocketState socketState);
    void onSocketConntected();

private:
    ReciveMsgCallback m_reciveCallback;
    QLocalSocket m_localSocket;
    QString m_strServerName;
    QVector<QString> m_vecBackupMsg;
};
