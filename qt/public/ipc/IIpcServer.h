#pragma once

#include <functional>
#include <QString>

class IIPCServer {
  public:
    using ReciveMsgCallback = std::function<void(const QString&)>;

    virtual ~IIPCServer() {
    }

    virtual bool sendMsg(const QString& strMsg) = 0;
    virtual void setReciveMsgCallback(ReciveMsgCallback callback) = 0;
    virtual bool isConnected() = 0;
};
