#pragma once
#include<Arduino.h>

class NMEAGPS{
private:
    HardwareSerial* _serial;
    String _buffer;
    String _lastGGA;
    String _lastRMC;

    // Basic NMEA checksum validation (optional but very helpful)
    bool validateChecksum(const String &s);

public:
    NMEAGPS(HardwareSerial &ser);

    void begin(unsigned long baud);

    void update();

    String getGGA();
    String getRMC();
};
