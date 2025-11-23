#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include "AbstractComChannel.hh"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

class ComChannel : public AbstractComChannel {
    int _socket;
    std::mutex _mutex;

public:
    ComChannel();
    virtual ~ComChannel();
    
    virtual void Init(int Socket) override { _socket = Socket; }
    virtual int GetSocket() const override { return _socket; }
    virtual void LockAccess() override { _mutex.lock(); }
    virtual void UnlockAccess() override { _mutex.unlock(); }
    virtual std::mutex &UseGuard() override { return _mutex; }
    
    bool Connect(const char* host, int port);
    bool Send(const std::string& cmd);
    void Close();
};

#endif
