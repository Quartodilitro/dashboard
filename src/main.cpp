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


#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
// #include <QWSServer>  // needed to hide cursor DEBUG ONLY

#include "windows/mainwindow.h"
#include "virtualcan/canbus.h"  // DEBUG ONLY
#include "bitalino/bitalino.h"

#define HAS_CAN 0  // DEBUG ONLY
#define is_splash_Screen 1
#define BITALINO_ADDRESS "98:D3:31:B2:C1:16"


void bitalinoSample() {
    const char *macAddress = "98:D3:31:B2:C1:16";
    try {
        puts("Connecting to device...");
        BITalino dev(macAddress);
        puts("Connected to device. Press Enter to exit.");
        std::string ver = dev.version();     // get device version string
        printf("BITalino version: %s\n", ver.c_str());
        dev.battery(10);  // set battery threshold (optional)

        dev.start(1000, {0, 1, 2, 3, 4, 5});    // start acquisition of all channels at 1000 Hz
        BITalino::VFrame frames(100); // initialize the frames vector with 100 frames
        do
        {
            dev.read(frames); // get 100 frames from device
            const BITalino::Frame &f = frames[0];  // get a reference to the first frame of each 100 frames block
            printf("%d : %d %d %d %d ; %d %d %d %d %d %d\n",    // dump the first frame
                     f.seq,
                     f.digital[0], f.digital[1], f.digital[2], f.digital[3],
                     f.analog[0], f.analog[1], f.analog[2], f.analog[3], f.analog[4], f.analog[5]);
        } while (true); // until a key is pressed
        dev.stop(); // stop acquisition
    } catch(BITalino::Exception &e) {
        printf("BITalino exception: %s\n", e.getDescription());
    }
}


int main(int argc, char *argv[]) {    
    /*  // DEBUG ONLY
     * #ifdef Q_WS_QWS  // this line
     * QWSServer::setCursorVisible(false);  // and this
     * #endif //and this, are needed to hide the cursor
     *
     * window->setWindowFlags(Qt::FramelessWindowHint);
     * window->setWindowState(Qt::WindowMaximized);
    */

    QApplication app(argc, argv);
    app.setOrganizationName(QString::fromUtf8("Quartodilitro"));
    app.setApplicationName(QString::fromUtf8("GUI"));
    MainWindow *window = new MainWindow();  // create new window

    if (is_splash_Screen) {  // make splash screen turn up
        QSplashScreen splash(QPixmap("../res/logo.png"));  // deploy splash screen
        QTimer down_window;  // timer to keep window hidden
        down_window.setSingleShot(true);
        down_window.setInterval(1500);
        QObject::connect(&down_window, SIGNAL(timeout() ), window, SLOT( show()) );

        QTimer up_splash;  // timer to keep splash up
        up_splash.setSingleShot(true);
        up_splash.setInterval(1400);
        QObject::connect(&up_splash, SIGNAL(timeout() ), &splash, SLOT( close()) );

        QTimer msg_splash;  // timer to show messages in splashscreen
        msg_splash.setSingleShot(true);
        msg_splash.setInterval(900);
        QObject::connect(&msg_splash, SIGNAL(timeout() ), &splash, SLOT( close()) );

        down_window.start();
        up_splash.start();
        splash.show();
    }

    if (!HAS_CAN) {
        VirtualCan *virtualCan = new VirtualCan("vcan0", 100, 1000);  // ask virtual can to start and send each 100ms a message for a total of 1000 times
        virtualCan->start();  // start virtual can

        // start bitalino module
        // bitalinoSample();  // DEBUG ONLY
    }

    window->show();
    window->setGeometry((SCREEN_WIDTH / 2) - (window->width() / 2), (SCREEN_HEIGHT / 2) - (window->height() / 2), window->width(), window->height());
    return app.exec();
}
