/**
 * @file NMEAGPS.cpp
 * @author your name (you@domain.com)
 * @brief implmentation details of NMEAGPS functions
 */
#include "NMEAGPS.h"


NMEAGPS::NMEAGPS(HardwareSerial &ser){
    _serial = &ser;
    _buffer = "";
    _lastGGA = "";
    _lastRMC = "";
}

    // Basic NMEA checksum validation (optional but very helpful)
    bool NMEAGPS::validateChecksum(const String &s) {
        if (s.length() < 6) return false;
        if (s[0] != '$') return false;
        int star = s.indexOf('*');
        if (star < 0 || star + 2 >= (int)s.length()) return false;
        uint8_t sum = 0;
        for (int i = 1; i < star; i++) sum ^= (uint8_t)s[i];
        // Parse two hex chars after '*'
        char h1 = s[star + 1];
        char h2 = s[star + 2];
        auto hexVal = [](char c) -> int {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
            if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
            return -1;
        };
        int v1 = hexVal(h1), v2 = hexVal(h2);
        if (v1 < 0 || v2 < 0) return false;
        uint8_t expected = (uint8_t)((v1 << 4) | v2);
        return sum == expected;
    }

    void NMEAGPS::begin(unsigned long baud) {
        _serial->begin(baud);
    }

    void NMEAGPS::update() {
        // Check if there are any bytes waiting in the Serial Port ("hardware's incoming mailbox")
        while (_serial->available()) {

            // Read one single character (byte)
            char c = _serial->read();

            // NMEA sentences always start with '$'. 
            if (c == '$') { 
                _buffer = "$"; // If we see this, we reset our buffer to start a fresh sentence.
                continue; // Skip the rest of this loop iteration and get the next char
            }

            // Check if the character is a 'Newline' (\n), which marks the end of a sentence
            if (c == '\n') {
                // We have a full line! Now we validate it using the checksum.
                if (validateChecksum(_buffer)) {
                    // If the sentence is valid, check the "Header" to see what data it is.
                    // $GNGGA contains altitude, time, and fix quality.
                    if (_buffer.startsWith("$GNGGA")){
                        _lastGGA = _buffer; // Save it to our "storage" variable _lastGGA
                    } 
                    // $GNRMC contains speed, date, and basic coordinates.
                    else if (_buffer.startsWith("$GNRMC")){
                        _lastRMC = _buffer; // Save it to our "storage" variable _lastRMC
                    }
                }
                _buffer = ""; // Clear the buffer so we are ready to build the next sentence.
            } else {
                // If it's not a '$' or a '\n', it's just a regular character (like a '5' or a ',').
                // Add it to the end of our growing string in _buffer
                _buffer += c;
            }
        }
    }

    String NMEAGPS::getGGA(){ 
        return _lastGGA; 
    }
    
    String NMEAGPS::getRMC(){
        return _lastRMC;
    }