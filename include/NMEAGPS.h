/**
 * @file NMEAGPS.h
 * @brief function signatures for NMEAGPS
 */
#pragma once
#include <Arduino.h>

class NMEAGPS{
private:
    HardwareSerial* _serial;
    String _buffer; // used as a temp variable to read NEMA data sentences until they are detected to be full GNGGA or GNRMC strings
    String _lastGGA;
    String _lastRMC;

    /**
     * @brief checks if nema sentence 
     * 
     * @param s nmea sentece to check
     * @return true, valid sentence
     * @return false, not valid
     */
    bool validateChecksum(const String &s);

public:
    NMEAGPS(HardwareSerial &ser);

    // This tells the UART hardware to start listening at the specified speed.
    // baud: The speed of the connection (bits per second, e.g. 115200).
    // Add object.begin(115200) in setup()
    void begin(unsigned long baud);


    // Reads NEMA data from port specified in object constructor
    // ONLY READS GNGGA AND GNRMC DATA CURRENTLY, then stores it in _lastGGA and _lastRMC respectively 
    // If we don't call update() constantly in the loop(), 
    // the internal Serial buffer (usually only 64 bytes) will overflow, and you will lose data.
    void update();

    String getGGA();
    String getRMC();
};
