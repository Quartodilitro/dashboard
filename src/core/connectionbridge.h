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
    int DATA_CODE_GPS_X = 0x08;
    int DATA_CODE_GPS_Y = 0x09;
    int DATA_CODE_TIME_S_1S = 0x010;
    int DATA_CODE_TIME_S_2S = 0x011;
    int DATA_CODE_TIME_S_3S = 0x012;
    int DATA_CODE_TIME_S_4S = 0x013;

    CanWrapper *can;
    CanWorkerThread *workerThread;  // thread that listens for CAN messages

    void start();
};

#endif // CONNECTIONBRIDGE_H
