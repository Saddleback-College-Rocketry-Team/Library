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
 * @brief Append a row of data to a CSV file.
 *
 * Opens the file and writes a new line of data.
 *
 * @param data data to write to file
 */
template <typename T>
void CSV::writeToFile(const T data) {
    
    File writeFile = SD.open(fileName, FILE_WRITE);

    /**
     * writing to file
     */
    if (writeFile) {
        writeFile.println(data);
    }
    /**
     * Ouput error message if cannot find
     */
    else {
        Serial.print("Error! Cannot find file: ");
        Serial.println(fileName);
    }

    /**
     * write to file and flush buffer
     */
    writeFile.flush();
} // END void writeToFile