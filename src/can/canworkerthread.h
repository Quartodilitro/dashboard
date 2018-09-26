#ifndef CANWORKERTHREAD_H
#define CANWORKERTHREAD_H

#include <QThread>
#include "canwrapper.h"


class CanWorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit CanWorkerThread(QObject *parent = 0);
    void Init(CanWrapper *wrapper);
    void run();
    void shutDown();

signals:
    void msgReceived(int id, int data);

private:
    CanWrapper *m_can;  // Pointer to can wrapper class
    bool m_running;     // Set to false to stop thread
};

#endif // CANWORKERTHREAD_H
