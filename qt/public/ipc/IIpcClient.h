#pragma once

#include <functional>
#include <QString>

class IIPCClient {
  public:
    using ReciveMsgCallback = std::function<void(const QString&)>;

    virtual ~IIPCClient() {
    }

    virtual bool sendMsg(const QString& strMsg) = 0;
    virtual void setReciveMsgCallback(ReciveMsgCallback callback) = 0;
    virtual bool isConnected() = 0;
    virtual void stop() = 0;
};
