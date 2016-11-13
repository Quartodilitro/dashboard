#include <stdio.h>
#include <iostream>

#include "bitalino.h"

void sampleBluetooth() {
    try {
        puts("Connecting to device...");
        
        BITalino dev("98:D3:31:B2:C1:16");
     
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

void qdlBluetooth() {
    const char *macAddress = "98:D3:31:B2:C1:16";
    try {
            std::cout << "Connecting to " <<  macAddress << " device\n";
            BITalino dev("98:D3:31:B2:C1:16");
            std::cout << "[!] Connected to " <<  macAddress << " device\n";

            dev.start(1000, {0, 1, 2, 3, 4, 5});
            BITalino::VFrame frames(100);

            while (true) {
                // get reference to first frame
                dev.read(frames);
                const BITalino::Frame &f = frames[0];

                dev.sendCanMessage(dev.sequence_code, f.seq);

                printf("%d : %d %d %d %d ; %d %d %d %d %d %d\n",
                        f.seq,
                        f.digital[0], f.digital[1], f.digital[2], f.digital[3],
                        f.analog[0], f.analog[1], f.analog[2], f.analog[3], f.analog[4], f.analog[5]);
            }
    } catch(BITalino::Exception &e) {
            std::cout << "Not connected to " <<  macAddress << " device\n";
            std::cout << "[!] BITalino exception: " << e.getDescription();
    }
}

int main() {
    qdl();
    
    return 0;
}
