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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <QThread>
#include <QDebug>


class VirtualCan : public QThread
{
    Q_OBJECT

public:
    const char* canbus;  // canbus data
    int refreshTime;
    int max_runs;

    int s;  // canbus connection
    int nbytes;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

    int waterTemp_code = 0x0A;  // default codes
    int speed_code = 0x0D;
    int engineTemp_code = 0x0F;
    int oilTemp_code = 0x5C;
    int gear_code = 0xD4;
    int rpm_code = 0x0C;

    VirtualCan() {
        this->canbus = "vcan0";
        this->refreshTime = 100;
        this->max_runs = 1;

        checkStatus();
    }

    VirtualCan(char* canbus, int refresh_time, int max_runs){
        this->canbus = canbus;
        this->refreshTime = refresh_time;
        this->max_runs = max_runs;

        checkStatus();
    }

    void checkStatus(){
        if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
            perror("Error while opening socket");
        }

        strcpy(ifr.ifr_name, canbus);
        ioctl(s, SIOCGIFINDEX, &ifr);

        addr.can_family  = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("Error in socket bind");
        }
    }

    void sendMessage(int id, int data0, int data1){
        frame.can_id  = id;
        frame.can_dlc = 2;
        frame.data[0] = data0;
        frame.data[1] = data1;

        nbytes = write(s, &frame, sizeof(struct can_frame));
    }

    void run() {
        for (int run = 0; run < this->max_runs; run++){
            int milliseconds = qrand() % 256;

            // send message
            sendMessage(this->waterTemp_code, 0, milliseconds * 0.5);
            sendMessage(this->speed_code, 0, milliseconds);
            sendMessage(this->engineTemp_code, 1, milliseconds);
            sendMessage(this->oilTemp_code, 0, milliseconds * 0.5);
            sendMessage(this->gear_code, 0, milliseconds % 7);
            sendMessage(this->rpm_code, milliseconds * 0.1, milliseconds * 0.5);

            // sleep
            usleep(this->refreshTime * 1000);
        }
    }

protected:
    bool finish;
};
