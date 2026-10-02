#ifndef TEST_WIRE_H
#define TEST_WIRE_H

#include <stdint.h>
#include <stddef.h>

#include <string.h>

class TwoWire
{
public:
    uint8_t transmission[3];
    uint8_t transmission_size;
    uint8_t last_register;
    uint16_t last_value;
    uint16_t registers[256];
    uint8_t current_register;
    uint8_t read_offset;

    TwoWire()
        : transmission_size(0), last_register(0), last_value(0), current_register(0), read_offset(0)
    {
        memset(registers, 0, sizeof(registers));
    }

    void begin()
    {
    }

    void beginTransmission(uint8_t)
    {
        transmission_size = 0;
    }

    size_t write(uint8_t value)
    {
        transmission[transmission_size++] = value;
        return 1;
    }

    uint8_t endTransmission()
    {
        if (transmission_size == 1)
        {
            current_register = transmission[0];
            read_offset = 0;
        }
        else if (transmission_size == 3)
        {
            last_register = transmission[0];
            last_value = ((uint16_t)transmission[1] << 8) | transmission[2];
            registers[last_register] = last_value;
            if (last_register == 0x0C)
            {
                for (uint8_t measurement = 0; measurement < 4; measurement++)
                {
                    if (last_value & (1 << (7 - measurement)))
                    {
                        registers[last_register] |= 1 << (3 - measurement);
                    }
                }
            }
        }
        return 0;
    }

    uint8_t requestFrom(uint8_t, uint8_t quantity)
    {
        read_offset = 0;
        return quantity;
    }

    int read()
    {
        uint16_t value = registers[current_register];
        return read_offset++ == 0 ? value >> 8 : value & 0xFF;
    }
};

extern TwoWire Wire;

#endif