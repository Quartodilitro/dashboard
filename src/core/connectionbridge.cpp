#include <QDebug>  // DEBUG

#include "connectionbridge.h"


ConnectionBridge::ConnectionBridge()
{
    can = new CanWrapper();
    workerThread = new CanWorkerThread();

    can->Close();  // close old connection (if there is one) and shut down worker threads
    workerThread->shutDown();
    if(!workerThread->wait(3000)) {
        workerThread->terminate();
    }

    int errorCode;
    bool isThereCan = can->Init("vcan0", errorCode);  // DEBUG ONLY
    if(!isThereCan) {
        qDebug() << "Could not initialize CAN net. Error code: " + QString::number(errorCode) + "\nHave you run \"startCan.sh <interface name>\" as root?";
        return;
    }

    can->EnableErrorMessages();  // initialize worker thread
    workerThread->Init(can);
}

void ConnectionBridge::start() {
    workerThread->start();
}
