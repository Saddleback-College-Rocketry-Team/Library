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
}


/**
 * @brief Append a row of data to a CSV file for only 1 param
 *
 * Opens the file and writes a new line of data.
 *
 * @param data data to write to file
 */
template <typename T>
void CSV::writeOne(const T& data) {
    writeFile.print(data);
}

/**
 * @brief Append a row of data to a CSV file for any number of parameters
 *
 * Opens the file and writes a new line of data.
 *
 * @param value multiple data to write to file
 */
template <typename T, typename... Args>
void CSV::writeOne(const T& data, const Args&... args) {
    writeFile.print(data);
    writeFile.print(",");
    writeOne(args...);
}

/**
 * @brief Append a row of data to a CSV file.
 *
 * Opens the file and writes a new line of data.
 *
 * @param args data to write to file. Can be any number of arguments
 */
template <typename... Args>
void CSV::writeToFile(const Args&... args) {
    /**
     * writing to file
     */
    if (writeFile) {
        writeOne(args...);
        writeFile.println();
    }
    /**
     * Ouput error message if cannot find
     */
    else {
        Serial.print("Error! Cannot find file: ");
        Serial.println(fileName);
    }
} // END void writeToFile
