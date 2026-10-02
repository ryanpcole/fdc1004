#include <Arduino.h>
#include <Wire.h>
#include <Protocentral_FDC1004.h>

FDC1004 sensor(FDC1004_RATE_100HZ);

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    if (!sensor.begin())
    {
        Serial.println("FDC1004 initialization failed");
        while (1)
        {
            delay(1000);
        }
    }

    Serial.println("Differential measurement: CIN0 (CHA) - CIN3 (CHB)");
}

void loop()
{
    fdc1004_differential_measurement_t measurement = sensor.getDifferentialMeasurement(
        FDC1004_CHANNEL_0, FDC1004_CHANNEL_3);

    if (measurement.error == FDC1004_SUCCESS)
    {
        Serial.print("Signed raw difference: ");
        Serial.println(measurement.raw_value);
    }
    else
    {
        Serial.print("Measurement failed, error: ");
        Serial.println((int)measurement.error);
    }

    delay(500);
}