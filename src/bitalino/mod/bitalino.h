#ifndef BITALINO
#define BITALINO

#include <stdio.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <string>
#include <vector>


class BITalino
{
public:
    typedef std::vector<bool>  Vbool;    ///< Vector of bools.
    typedef std::vector<int>    Vint;     ///< Vector of ints.

    /// Information about a Bluetooth device found by BITalino::find().
    struct DevInfo
    {
        std::string macAddr; ///< MAC address of a Bluetooth device
        std::string name;     ///< Name of a Bluetooth device
    };
    typedef std::vector<DevInfo> VDevInfo; ///< Vector of DevInfo's.

    /// A frame returned by BITalino::read()
    struct Frame
    {
        char  seq;
        bool  digital[4]; 

        /// Array of analog inputs values (0...1023 on the first 4 channels and 0...63 on the remaining channels)
        short analog[6];
    };
    typedef std::vector<Frame> VFrame;  ///< Vector of Frame's.

    /// Current device state returned by BITalino::state()
    struct State
    {
        int    analog[6],      ///< Array of analog inputs values (0...1023)
                battery,         ///< Battery voltage value (0...1023)
                batThreshold;  ///< Low-battery LED threshold (last value set with BITalino::battery())
        /// Array of digital ports states (false for low level or true for high level).
        /// The array contents are: I1 I2 O1 O2.
        bool  digital[4];
    };

    /// %Exception class thrown from BITalino methods.
    class Exception
    {
    public:
        /// %Exception code enumeration.
        enum Code
        {
            INVALID_ADDRESS = 1,         ///< The specified address is invalid
            BT_ADAPTER_NOT_FOUND,        ///< No Bluetooth adapter was found
            DEVICE_NOT_FOUND,             ///< The device could not be found
            CONTACTING_DEVICE,            ///< The computer lost communication with the device
            PORT_COULD_NOT_BE_OPENED,  ///< The communication port does not exist or it is already being used
            PORT_INITIALIZATION,         ///< The communication port could not be initialized
            DEVICE_NOT_IDLE,              ///< The device is not idle
            DEVICE_NOT_IN_ACQUISITION, ///< The device is not in acquisition mode
            INVALID_PARAMETER,            ///< Invalid parameter
            NOT_SUPPORTED,                 ///< Operation not supported by the device 
        } code;  ///< %Exception code.

        Exception(Code c) : code(c) {}        ///< Exception constructor.
        const char* getDescription(void);    ///< Returns an exception description string
    };

    static VDevInfo find(void);

    BITalino(const char *address);
    ~BITalino();

    std::string version(void);
    void start(int samplingRate = 1000, const Vint &channels = Vint(), bool simulated = false);
    void stop(void);
    int read(VFrame &frames);
    void battery(int value = 0);
    void trigger(const Vbool &digitalOutput = Vbool());
    void pwm(int pwmOutput = 100);
    State state(void);

     // qthread start

    // qthread
    void run();

    // canbus 
    void sendCanMessage(int id, int data);

    int s;
    int nbytes;
    struct can_frame frame;
    int sequence_code = 0xBB;
    int analog0_code = 0xB0;
    int analog1_code = 0xB1;
    int analog2_code = 0xB2;
    int analog3_code = 0xB3;
    int analog4_code = 0xB4;
    int analog5_code = 0xB5;
    int digital0_code = 0xC0;
    int digital1_code = 0xC1;
    int digital2_code = 0xC2;
    int digital3_code = 0xC3;

private:
    void send(char cmd);
    int  recv(void *data, int nbyttoread);
    void close(void);
    
    char nChannels;
    bool isBitalino2;
    int fd;
    bool isTTY;
};

#endif // BITALINO
