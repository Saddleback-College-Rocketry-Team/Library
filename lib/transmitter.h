#pragma once
#include <Arduino.h>

/**
 * @file transmitter.h
 * @brief Transmitter class for configuring a radio module via AT commands.
 */

/**
 * @brief Template class for a transmitter device using serial communication.
 *
 * This class initializes and configures a transmitter module using AT commands.
 * It allows setting the network ID and device address over a serial interface.
 *
 * @tparam SerialT Type of the serial interface (e.g., HardwareSerial, SoftwareSerial).
 */


template <typename SerialT>
class Transmitter {
public:
    /**
     * @brief Constructor for Transmitter.
     *
     * @param serial Reference to the serial interface.
     * @param network Network ID for the transmitter.
     * @param address Address ID for the transmitter.
     * @param baudRate Baud rate for communication (default: 115200).
     * @param waitMs Delay between commands in milliseconds (default: 200).
     */
    Transmitter(
        SerialT& serial,
        long network,
        long address,
        unsigned long baudRate = 115200,
    )
        : _serial(serial),
          _network(network),
          _address(address),
          _baudRate(baudRate),
          _waitMs(waitMs) {}

    /**
     * @brief Initialize and configure the transmitter.
     *
     * Sends AT commands to verify communication, set network ID,
     * and assign device address.
     */
    void begin() {
        /** Initialize serial communication */
        _serial.begin(_baudRate);
        

        /**
         * @brief Check communication with module.
         *
         * "AT" command verifies that the module is responsive.
         */
        _serial.println("AT");
        

        /**
         * @brief Set network ID.
         *
         * Devices must share the same network ID to communicate.
         */
        _serial.print("AT+NETWORKID=");
        _serial.println(_network);


        /**
         * @brief Set device address.
         *
         * Assigns a unique identifier to this transmitter.
         */
        _serial.print("AT+ADDRESS=");
        _serial.println(_address);
        
    }

private:
    SerialT& _serial;           /**< Serial interface */
    long _network;              /**< Network ID */
    long _address;              /**< Device address */
    unsigned long _baudRate;    /**< Communication baud rate */
    unsigned long _waitMs;      /**< Delay between commands */
};