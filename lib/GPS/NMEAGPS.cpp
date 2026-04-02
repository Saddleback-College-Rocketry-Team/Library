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
        while (_serial->available()) {
            char c = _serial->read();
            if (c == '$') { _buffer = "$"; continue; }
            if (c == '\n') {
                if (validateChecksum(_buffer)) {
                    if (_buffer.startsWith("$GNGGA")) _lastGGA = _buffer;
                    if (_buffer.startsWith("$GNRMC")) _lastRMC = _buffer;
                }
                _buffer = "";
            } else {
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