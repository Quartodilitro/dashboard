/**
 * Copyright 2016 Quartodilitro Team Unipd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


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
