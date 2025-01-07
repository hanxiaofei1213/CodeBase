#pragma once
// ���̼�ͨѶ�����֧࣬�ַ��������������Ϣ���ͻ��ˣ���ֻ�ᷢ�͵����һ�εĽ������ӵĿͻ���
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





