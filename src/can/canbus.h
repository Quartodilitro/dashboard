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

    int SPEED = 0x00;  // default codes
    int RPM = 0x01;
    int GEAR = 0x02;
    int TEMPERATURE_BODY = 0x03;
    int TEMPERATURE_OIL = 0x04;
    int TEMPERATURE_EXT = 0x05;
    int BPM = 0X06;
    int O2 = 0x07;
    int GPS_X = 0X08;
    int GPX_Y = 0x09;

    VirtualCan() {
        this->canbus = "vcan0";
        this->refreshTime = 200;
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
            sendMessage(this->SPEED, 0, milliseconds % 300);
            sendMessage(this->RPM, milliseconds % 30, milliseconds % 9999);
            sendMessage(this->GEAR, 0, milliseconds % 7 + 1);
            sendMessage(this->TEMPERATURE_BODY, 0, milliseconds % 2 + 36);
            sendMessage(this->TEMPERATURE_OIL, 0, milliseconds % 10 + 90);
            sendMessage(this->TEMPERATURE_EXT, 0, milliseconds * 0.5);
            sendMessage(this->BPM, 0, milliseconds % 50 + 150);
            sendMessage(this->O2, 1, milliseconds % 30 + 450);

            // sleep
            usleep(this->refreshTime * 1000);
        }
    }

protected:
    bool finish;
};
