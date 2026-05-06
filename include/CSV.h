/**
 * @file CSV.h
 * @brief class to keep track of CSV files and methods
 */
#pragma once
#include <SD.h>         // SD card utility class for creating and managing CSV files

/**
 * @brief Template class for CSV operations.
 *
 * This class provides helper functions for interacting with an SD card.
 * It allows checking if a file exists, creating a CSV file, and writing
 * headers if the file does not already exist.
 */
class CSV {
private:
    const char* fileName;
    File writeFile;

    /**
     * @brief Append a row of data to a CSV file for only 1 param
     *
     * Opens the file and writes a new line of data.
     *
     * @param data data to write to file
     */
    template <typename T>
    void writeOne(const T& data) {
        writeFile.print(data);
    } // END writeOne

    /**
     * @brief Append a row of data to a CSV file for any number of parameters
     *
     * Opens the file and writes a new line of data.
     *
     * @param value multiple data to write to file
     */
    template <typename T, typename... Args>
    void writeOne(const T& data, const Args&... args) {
        writeFile.print(data);
        writeFile.print(",");
        writeOne(args...);
    } // END writeOne

public:
    /**
     * @brief Constructor for CSV.
     *
     * @param fileName creates file datatype
     */
    CSV(const char* inputFileName);

    /**
     * @brief Create a CSV file if it does not exist.
     *
     * Checks if the file exists on the SD card. If it does not,
     * a new file is created and the provided header is written.
     *
     * @param header String / character array. Header row to write into the file
     */
    void createCSV(const char header[]);

    /**
     * @brief flushes 
     *
     * forces any buffer data to be physcially written
     * to the sd card. Ensures no data is lost when
     * microcontroller suddenly powers off
     */
    void flush();

    /**
     * @brief Append a row of data to a CSV file.
     *
     * Opens the file and writes a new line of data.
     *
     * @param args data to write to file. Can be any number of arguments
     */
    template <typename... Args>
    void writeToFile(const Args&... args) {
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

}; // END class CSV
