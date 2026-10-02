#ifndef TEST_ARDUINO_H
#define TEST_ARDUINO_H

#include <math.h>
#include <stdint.h>

inline void delay(unsigned long)
{
}

class HardwareSerial
{
public:
	void begin(unsigned long);
	void print(const char*);
	void print(int);
	void println(const char*);
	void println(int);
};

extern HardwareSerial Serial;

#endif