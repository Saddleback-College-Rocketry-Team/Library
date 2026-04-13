/**
 * @file main.cpp
 * @brief this file is a test and will try to be used a template
 * @date 2026-03-06
 * 
 */
#ifdef ARDUINO
#include <Arduino.h>  // To make it compatible for Platform.IO
                      // delete if you're using Arduino IDE
#endif

// put function declarations here:
int myFunction(int, int);

/**
 * @brief set up function, codes that run once go here
 */
void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

/**
 * @brief codes that will continuously run goes here
 * 
 */
void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
/**
 * @brief function to test things yippie
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int myFunction(int x, int y) {
  return x + y;
}