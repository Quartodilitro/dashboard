#ifndef CANWRAPPER_H
#define CANWRAPPER_H

#include <QString>

class CanWrapper
{
public:
    CanWrapper();

    bool Init(const char *interfaceName, int &errorCode);
    void Close();
    bool GetMsg(struct can_frame &frame, bool &extended, bool &rtr, bool &error, int &errorCode);
    bool SetRecvBufferSize(int size);
    void EnableErrorMessages();

private:
    bool m_initialized; // indicates if socket is initialized
    int m_socket;       // Socket


};

#endif // CANWRAPPER_H
