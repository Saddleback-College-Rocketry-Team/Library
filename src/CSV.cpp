/**
 * @file CSV.cpp
 * @brief implementation details for CSV methods
 */
#include "CSV.h"         // SD card utility class for creating and managing CSV files

/**
 * @brief Constructor for CSV.
 *
 * @param fileName creates file datatype
 */
CSV::CSV(const char* inputFileName) {
    fileName = inputFileName;

    /**
     * Open file in write mode.
     */
    writeFile = SD.open(fileName, FILE_WRITE);
}

/**
 * @brief Create a CSV file if it does not exist.
 *
 * Checks if the file exists on the SD card. If it does not,
 * a new file is created and the provided header is written.
 *
 * @param header String / character array. Header row to write into the file
 */
void CSV::createCSV(const char header[]) {
    /**
     * Check if file exists.
     */
    if (!SD.exists(fileName)) {

        /**
         * Write header if file opened successfully.
         */
        if (writeFile) {
            writeFile.println(header);
        }
        /**
         * If cannot open file print error message to serial
         */
        else {
            Serial.print("Error! Cannot open: ");
            Serial.println(fileName);
        }

    } // END if (!SD.exists(fileName))
} // END void createCSV

/**
 * @brief flushes 
 *
 * forces any buffer data to be physcially written
 * to the sd card. Ensures no data is lost when
 * microcontroller suddenly powers off
 */
void CSV::flush() {
    if (writeFile) {
        writeFile.flush();
    }
} // END flush