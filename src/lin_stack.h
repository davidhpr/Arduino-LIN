/*  Copyright (c) 2016 Macchina
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  LIN STACK for TJA1021
 *  v2.0
 *
 *  Short description:
 *  Comunication stack for LIN and TJA1021 LIN transceiver.
 *  Can be modified for any Arduino board with UART available and any LIN slave.
 *
 *  Author: Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu)
 *  Author: Laszlo Hegedüs
 *
 *  Arduino IDE 1.6.9
 *  RoboSap, Institute of Technology, September 2016
 */

#include <Arduino.h>

/*
        Please, read Getting Started Guide firts.
*/

class lin_stack {
public:
    // Constructors
    lin_stack(Serial &_channel = Serial1, uint16_t _baud = 19200, int8_t _wakeup_pin = -1,
              uint8_t _ident = 0); // Constructor for Master and Slave Node

    // Methods

    // Writing data to bus
    int write(byte addr, byte data[], byte data_size); // write whole package
    int writeRequest(byte addr);                       // Write header only
    int writeResponse(byte data[], byte data_size);   // Write response only
    int writeStream(byte data[], byte data_size);     // Writing user data to LIN bus
    int read(byte data[], byte data_size);            // read data from LIN bus, checksum and ident validation
    int readStream(byte data[], byte data_size);      // read data from LIN bus
    int setSerial();                                  // set up Seril communication for receiving data.
    int busWakeUp();                                  // send wakeup frame for waking up all bus participants
    void sleep(bool sleep_state); // method for controlling transceiver modes (false - sleep, true - normal)

    // Private methods and variables
private:
    const uint16_t baud;  // 10417 is best for LIN Interface, most device should work
    Serial &channel;           // which channel should be used
    uint8_t ident;             // user defined Identification Byte
    int8_t wake_pin;

    void sleep_config();           // configuration of sleep pins
    void lin_break(); // for generating Synch Break
    validateParity(byte ident); // for validating Identification Byte, can be modified for validating parity
    bool validateChecksum(byte data[], byte data_size); // for validating Checksum Byte
    byte calcIdentParity(byte ident);
};