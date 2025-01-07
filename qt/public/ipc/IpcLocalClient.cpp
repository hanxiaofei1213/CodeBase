#include <QThread>
#include "IpcLocalClient.h"

namespace {
constexpr auto TIMEOUT_MSEC = 1000;
const int SPAN_TIME = 250;
} // namespace

IpcLocalClient::IpcLocalClient(const QString& strName) : m_strServerName(strName) {
    beginConnect();
    connect(&m_localSocket, &QLocalSocket::readyRead, this, &IpcLocalClient::onReadyRead);
    connect(&m_localSocket, &QLocalSocket::stateChanged, this, &IpcLocalClient::onStatuChanged);
    connect(&m_localSocket, &QLocalSocket::connected, this, &IpcLocalClient::onSocketConntected);
}

IpcLocalClient::~IpcLocalClient() {
}

bool IpcLocalClient::sendMsg(const QString& strMsg) {
    if (strMsg.isEmpty()) {
        return false;
    }

    if (!isConnected()) {
        beginConnect();
        m_vecBackupMsg.push_back(strMsg);
        return false;
    }


    m_localSocket.write(strMsg.toUtf8());
    m_localSocket.flush();
    return true;
}

void IpcLocalClient::setReciveMsgCallback(ReciveMsgCallback callback) {
    m_reciveCallback = callback;
}

void IpcLocalClient::stop() {
    m_localSocket.disconnectFromServer();
}

bool IpcLocalClient::isConnected() {
    return m_localSocket.state() == QLocalSocket::ConnectedState;
}

void IpcLocalClient::beginConnect() {
    if (isConnected()) {
        return;
    }

    m_localSocket.connectToServer(m_strServerName);
}

void IpcLocalClient::sendAllBackupMsg() {
    if (!isConnected()) {
        return;
    }

    for (auto it : m_vecBackupMsg) {
        sendMsg(it);
    }

    m_vecBackupMsg.clear();
}

void IpcLocalClient::onReadyRead() {
    if (!m_localSocket.isValid()) {
    	return;
    }

    QString strData = m_localSocket.readAll();
    if (m_reciveCallback) {
        m_reciveCallback(strData);
    }
}

void IpcLocalClient::onStatuChanged(QLocalSocket::LocalSocketState socketState) {
}

void IpcLocalClient::onSocketConntected() {
    sendAllBackupMsg();
}
