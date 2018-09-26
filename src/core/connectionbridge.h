#ifndef CONNECTIONBRIDGE_H
#define CONNECTIONBRIDGE_H

#include <QMainWindow>
#include "can/canworkerthread.h"


class ConnectionBridge
{
public:
    ConnectionBridge();

    int DATA_CODE_SPEED = 0x00;
    int DATA_CODE_RPM = 0x01;
    int DATA_CODE_GEAR = 0x02;
    int DATA_CODE_TEMPERATURE_BODY = 0x03;
    int DATA_CODE_TEMPERATURE_OIL = 0x04;
    int DATA_CODE_TEMPERATURE_EXT = 0x05;
    int DATA_CODE_BPM = 0x06;
    int DATA_CODE_O2 = 0x07;

    CanWrapper *can;
    CanWorkerThread *workerThread;  // thread that listens for CAN messages

    void start();
};

#endif // CONNECTIONBRIDGE_H
