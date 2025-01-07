#include <QTimer>
#include "IpcLocalServer.h"

IpcLocalServer::IpcLocalServer(const QString& strName) : m_strServerName(strName) {
    initServer();
}

IpcLocalServer::~IpcLocalServer() {
}

bool IpcLocalServer::sendMsg(const QString& strMsg) {
    if (!m_server || !isValid() || strMsg.isEmpty()) {
    	return false;
    }

    if (!isConnected()) {
        m_vecBackupMsg.push_back(strMsg);
        return false;
    }

    m_lastSocket->write(strMsg.toUtf8());
    m_lastSocket->flush();
    return true;
}

void IpcLocalServer::setReciveMsgCallback(ReciveMsgCallback callback) {
    m_reciveMsgCallback = callback;
}

bool IpcLocalServer::isConnected() {
    return m_lastSocket != nullptr;
}

bool IpcLocalServer::isValid() {
    return m_bValid;
}

void IpcLocalServer::sendAllBackupMsg() {
    if (!isConnected()) {
        return;
    }

    for (auto it : m_vecBackupMsg) {
        sendMsg(it);
    }

    m_vecBackupMsg.clear();
}

void IpcLocalServer::initServer() {
    m_server = new QLocalServer(this);
    connect(m_server, &QLocalServer::newConnection, this, &IpcLocalServer::onNewConnection);
    QLocalServer::removeServer(m_strServerName);
    m_bValid = m_server->listen(m_strServerName);
}

void IpcLocalServer::onNewConnection() {
    m_lastSocket = m_server->nextPendingConnection();
    if (!m_lastSocket) {
        return;
    }

    connect(m_lastSocket, &QLocalSocket::readyRead, this, &IpcLocalServer::onReadyRead);
    sendAllBackupMsg();
}

void IpcLocalServer::onReadyRead() {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if (!socket) {
    	return;
    }

    QString strData = socket->readAll();
    if (m_reciveMsgCallback) {
        m_reciveMsgCallback(strData);
    }
}
