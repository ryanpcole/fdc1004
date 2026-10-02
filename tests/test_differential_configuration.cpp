#include <assert.h>

#include <Protocentral_FDC1004.h>
#include <Wire.h>

TwoWire Wire;
HardwareSerial Serial;

int main()
{
    FDC1004 sensor;

    fdc1004_differential_measurement_t measurement =
        sensor.getDifferentialMeasurement(FDC1004_CHANNEL_0, FDC1004_CHANNEL_1);
    assert(measurement.error == FDC1004_ERROR_DEVICE_NOT_FOUND);

    assert(sensor.configureMeasurementDifferential(FDC1004_MEASUREMENT_1,
                                                   FDC1004_CHANNEL_0,
                                                   FDC1004_CHANNEL_1) == FDC1004_SUCCESS);
    assert(Wire.last_register == FDC1004_REG_CONF_MEAS1);
    assert(Wire.last_value == (1 << FDC1004_CONF_MEAS_CHB_SHIFT));

    assert(sensor.configureMeasurementDifferential(FDC1004_MEASUREMENT_4,
                                                   FDC1004_CHANNEL_3,
                                                   FDC1004_CHANNEL_2) == FDC1004_SUCCESS);
    assert(Wire.last_register == FDC1004_REG_CONF_MEAS4);
    assert(Wire.last_value == ((3 << FDC1004_CONF_MEAS_CHA_SHIFT) |
                               (2 << FDC1004_CONF_MEAS_CHB_SHIFT)));

    assert(sensor.configureMeasurementSingle(FDC1004_MEASUREMENT_2,
                                             FDC1004_CHANNEL_2,
                                             0) == FDC1004_SUCCESS);
    assert(Wire.last_value == ((2 << FDC1004_CONF_MEAS_CHA_SHIFT) |
                               (FDC1004_CONF_MEAS_CHB_DISABLED << FDC1004_CONF_MEAS_CHB_SHIFT)));

    assert(sensor.configureMeasurementSingle(FDC1004_MEASUREMENT_2,
                                             FDC1004_CHANNEL_2,
                                             3) == FDC1004_SUCCESS);
    assert(Wire.last_value == ((2 << FDC1004_CONF_MEAS_CHA_SHIFT) |
                               (FDC1004_CONF_MEAS_CHB_CAPDAC << FDC1004_CONF_MEAS_CHB_SHIFT) |
                               (3 << FDC1004_CONF_MEAS_CAPDAC_SHIFT)));

    assert(sensor.configureMeasurementDifferential(FDC1004_MEASUREMENT_1,
                                                   FDC1004_CHANNEL_0,
                                                   (fdc1004_channel_t)4) == FDC1004_ERROR_INVALID_PARAMETER);

        Wire.registers[FDC1004_REG_MEAS1_MSB] = 0xFFFE;
        Wire.registers[FDC1004_REG_MEAS1_LSB] = 0xC000;
        assert(sensor.setCapdac(FDC1004_CHANNEL_0, 5) == FDC1004_SUCCESS);
        assert(sensor.begin());

        measurement = sensor.getDifferentialMeasurement(FDC1004_CHANNEL_0,
                                                        FDC1004_CHANNEL_1);
        assert(measurement.error == FDC1004_SUCCESS);
        assert(measurement.raw_value == -2);
        assert(sensor.getCapdac(FDC1004_CHANNEL_0) == 5);
        assert(Wire.registers[FDC1004_REG_CONF_MEAS1] ==
            (1 << FDC1004_CONF_MEAS_CHB_SHIFT));
        measurement = sensor.getDifferentialMeasurement(FDC1004_CHANNEL_0,
                                                        (fdc1004_channel_t)4);
        assert(measurement.error == FDC1004_ERROR_INVALID_PARAMETER);
}