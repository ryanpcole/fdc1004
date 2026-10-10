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
    // Do the differential measurements
    float diffcap = sensor.getDifferentialCapacitancePicofarads(
        POSCHANNEL, NEGCHANNEL);

    Serial.print("Diff: ");
    Serial.print(diffcap);
    Serial.println(" pF");


    // Do single ended measuremnts for troubleshooting
    float poscappf = sensor.getCapacitancePicofarads(POSCHANNEL);
    Serial.print("CH1: ");
    Serial.print(poscappf);
    Serial.println(" pF");
    
    float negcappf = sensor.getCapacitancePicofarads(NEGCHANNEL);
    Serial.print("CH4: ");
    Serial.print(negcappf);
    Serial.println(" pF");

    delay(500);

}
