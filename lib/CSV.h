#pragma once
#include <Arduino.h>
#include <SD.h>

/**
 * @file SD.h
 * @brief SD card utility class for creating and managing CSV files.
 */

/**
 * @brief Template class for SD card operations.
 *
 * This class provides helper functions for interacting with an SD card.
 * It allows checking if a file exists, creating a CSV file, and writing
 * headers if the file does not already exist.
 *
 * @tparam SDT Type of the SD interface (e.g., SD, SdFat).
 */
template <typename SDT>
class SDManager {
public:
    /**
     * @brief Constructor for SDManager.
     *
     * @param sd Reference to the SD interface.
     */
    SDManager(SDT& sd)
        : _sd(sd) {}

    /**
     * @brief Create a CSV file if it does not exist.
     *
     * Checks if the file exists on the SD card. If it does not,
     * a new file is created and the provided header is written.
     *
     * @param fileName Name of the CSV file.
     * @param header Header row to write into the file.
     */
    void createCSV(const char* fileName, const char* header) {
        /**
         * @brief Check if file exists.
         */
        if (!_sd.exists(fileName)) {

            /**
             * @brief Open file in write mode.
             */
            File file = _sd.open(fileName, FILE_WRITE);

            /**
             * @brief Write header if file opened successfully.
             */
            if (file) {
                file.println(header);
                file.close();
            }
        }
    }

    /**
     * @brief Append a row of data to a CSV file.
     *
     * Opens the file and writes a new line of data.
     *
     * @param fileName Name of the CSV file.
     * @param data Row of CSV-formatted data.
     */
    void appendRow(const char* fileName, const char* data) {
        File file = _sd.open(fileName, FILE_WRITE);

        if (file) {
            file.println(data);
            file.close();
        }
    }

    /**
     * @brief Check if a file exists on the SD card.
     *
     * @param fileName Name of the file.
     * @return true if file exists, false otherwise.
     */
    bool fileExists(const char* fileName) {
        return _sd.exists(fileName);
    }

private:
    SDT& _sd; /**< SD interface */
};