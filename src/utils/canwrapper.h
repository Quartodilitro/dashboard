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
