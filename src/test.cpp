for (int run = 0; run < this->max_runs; run++){
            // get reference to the first frame
            BITalino::VFrame frames(this->frames);
            dev->read(frames);
            const BITalino::Frame &f = frames[0];

            sendMessage(this->sequence_code, f.seq);
            sendMessage(this->analog0_code, f.analog[0]);
            sendMessage(this->analog1_code, f.analog[1]);
            sendMessage(this->analog2_code, f.analog[2]);
            sendMessage(this->analog3_code, f.analog[3]);
            sendMessage(this->analog4_code, f.analog[4]);
            sendMessage(this->analog5_code, f.analog[5]);
            sendMessage(this->digital0_code, f.digital[0]);
            sendMessage(this->digital1_code, f.digital[1]);
            sendMessage(this->digital2_code, f.digital[2]);
            sendMessage(this->digital3_code, f.digital[3]);

            // sleep
            usleep(1000.0 / this->frequency);  // 1/frequency * 1000
        }



g++ -DHASBLUETOOTH -c bitalino.cpp -o bitalino.o
g++ -std=c++0x -c test.cpp -o test.o
g++ bitalino.o test.o -lbluetooth -o test