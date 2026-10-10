#include <Arduino.h>
#include <Wire.h>
#include <Protocentral_FDC1004.h>

FDC1004 sensor(FDC1004_RATE_100HZ);

#define POSCHANNEL FDC1004_CHANNEL_0
#define NEGCHANNEL FDC1004_CHANNEL_3

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

    Serial.println("Differential measurement: CIN1 (CHA) - CIN4 (CHB)");
}

void loop()
{

    // Differential Raw
    fdc1004_differential_measurement_t measurement = sensor.getDifferentialMeasurement(
        POSCHANNEL, NEGCHANNEL);

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

    // Positive channel raw
    fdc1004_raw_measurement_t pos_measurement;
    fdc1004_error_t poserror = sensor.getRawCapacitance(POSCHANNEL, &pos_measurement);
    if (poserror == FDC1004_SUCCESS)
    {
        Serial.print("POSCHANNEL: ");
        Serial.println(pos_measurement.value);
    }

    // Negative channel raw
    fdc1004_raw_measurement_t neg_measurement;
    fdc1004_error_t negerror = sensor.getRawCapacitance(NEGCHANNEL, &neg_measurement);
    if (negerror == FDC1004_SUCCESS)
    {
        Serial.print("NEGCHANNEL: ");
        Serial.println(neg_measurement.value);
    }



    // // Do the differential measurements
    // float diffcap = sensor.getDifferentialCapacitancePicofarads(
    //     POSCHANNEL, NEGCHANNEL);

    // Serial.print("Diff: ");
    // Serial.print(diffcap);
    // Serial.println(" pF");


    // // Do single ended measuremnts for troubleshooting
    // float poscappf = sensor.getCapacitancePicofarads(POSCHANNEL);
    // Serial.print("CH1: ");
    // Serial.print(poscappf);
    // Serial.println(" pF");
    
    // float negcappf = sensor.getCapacitancePicofarads(NEGCHANNEL);
    // Serial.print("CH4: ");
    // Serial.print(negcappf);
    // Serial.println(" pF");

    delay(500);

}
