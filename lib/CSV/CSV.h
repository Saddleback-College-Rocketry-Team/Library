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
     * @brief Append a row of data to a CSV file.
     *
     * Opens the file and writes a new line of data.
     *
     * @param data data to write to file
     */
    template <typename T>
    void writeToFile(const T data);

}; // END class CSV
