
/*!
   file getVoltageCurrentPower.ino
   SEN0291 Gravity: I2C Digital Wattmeter
   The module is connected in series between the power supply and the load to read the voltage, current and power
   The module has four I2C, these addresses are:
   INA219_I2C_ADDRESS1  0x40   A0 = 0  A1 = 0
   INA219_I2C_ADDRESS2  0x41   A0 = 1  A1 = 0
   INA219_I2C_ADDRESS3  0x44   A0 = 0  A1 = 1
   INA219_I2C_ADDRESS4  0x45   A0 = 1  A1 = 1
  
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-2-27
*/

#include <Wire.h>
#include "DFRobot_INA219.h"

DFRobot_INA219_IIC     ina219_1_uno(&Wire, INA219_I2C_ADDRESS1);
DFRobot_INA219_IIC     ina219_2_rpi(&Wire, INA219_I2C_ADDRESS2);
DFRobot_INA219_IIC     ina219_3_motor(&Wire, INA219_I2C_ADDRESS3);
DFRobot_INA219_IIC     ina219_4_chg(&Wire, INA219_I2C_ADDRESS4);

// Revise the following two parameters according to actual reading of the INA219 and the multimeter
// for linearly calibration
float ina219_1_Reading_mA = 1000;
float extMeter_1_Reading_mA = 1010;
float ina219_2_Reading_mA = 1000;
float extMeter_2_Reading_mA = 1000;
float ina219_3_Reading_mA = 1000;
float extMeter_3_Reading_mA = 1000;
float ina219_4_Reading_mA = 1000;
float extMeter_4_Reading_mA = 1020;

void setup(void) 
{
    Serial.begin(115200);
    while(!Serial);
    
    Serial.println();
    Serial.println("Initializing 4 INA219s...");
    while(ina219_1_uno.begin() != true) {
        Serial.println("INA219_1_uno begin failed");
    }
    while(ina219_2_rpi.begin() != true) {
        Serial.println("INA219_2_rpi begin failed");
    }
    while(ina219_3_motor.begin() != true) {
        Serial.println("INA219_3_motor begin failed");
    }
    while(ina219_4_chg.begin() != true) {
        Serial.println("INA219_4_chg begin failed");
    }
    delay(2000);
    ina219_1_uno.setBRNG(eIna219BusVolRange_32V);
    ina219_1_uno.setPGA(eIna219PGABits_1);
    ina219_1_uno.setBADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_1_uno.setSADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_1_uno.linearCalibrate(ina219_1_Reading_mA, extMeter_1_Reading_mA);
    ina219_1_uno.setMode(eIna219SAndBVolCon);
    Serial.println("INA219_1_uno initialized.");

    ina219_2_rpi.setBRNG(eIna219BusVolRange_32V);
    ina219_2_rpi.setPGA(eIna219PGABits_1);
    ina219_2_rpi.setBADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_2_rpi.setSADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_2_rpi.linearCalibrate(ina219_2_Reading_mA, extMeter_2_Reading_mA);
    ina219_2_rpi.setMode(eIna219SAndBVolCon);
    Serial.println("INA219_2_rpi initialized.");

    ina219_3_motor.setBRNG(eIna219BusVolRange_32V);
    ina219_3_motor.setPGA(eIna219PGABits_1);
    ina219_3_motor.setBADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_3_motor.setSADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_3_motor.linearCalibrate(ina219_3_Reading_mA, extMeter_3_Reading_mA);
    ina219_3_motor.setMode(eIna219SAndBVolCon);
    Serial.println("INA219_3_motor initialized.");

    ina219_4_chg.setBRNG(eIna219BusVolRange_32V);
    ina219_4_chg.setPGA(eIna219PGABits_1);
    ina219_4_chg.setBADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_4_chg.setSADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219_4_chg.linearCalibrate(ina219_4_Reading_mA, extMeter_4_Reading_mA);
    ina219_4_chg.setMode(eIna219SAndBVolCon);
    Serial.println("INA219_4_chg initialized.");
}

void loop(void)
{
    Serial.println("\tBusV\tShuntmV\tCurrmA\tPowermW");

    Serial.print("uno\t");
    Serial.print(ina219_1_uno.getBusVoltage_V(), 2);
    Serial.print("\t");
    Serial.print(ina219_1_uno.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(ina219_1_uno.getCurrent_mA(), 1);
    
    Serial.print("\t");
    Serial.println(ina219_1_uno.getPower_mW(), 1);
    
    Serial.print("rpi\t");
    Serial.print(ina219_2_rpi.getBusVoltage_V(), 2);
    Serial.print("\t");
    Serial.print(ina219_2_rpi.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(ina219_2_rpi.getCurrent_mA(), 1);
    Serial.print("\t");
    Serial.println(ina219_2_rpi.getPower_mW(), 1);
    
    Serial.print("motor\t");
    Serial.print(ina219_3_motor.getBusVoltage_V(), 2);
    Serial.print("\t");
    Serial.print(ina219_3_motor.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(ina219_3_motor.getCurrent_mA(), 1);
    Serial.print("\t");
    Serial.println(ina219_3_motor.getPower_mW(), 1);
    
    Serial.print("chg\t");
    Serial.print(ina219_4_chg.getBusVoltage_V(), 2);
    Serial.print("\t");
    Serial.print(ina219_4_chg.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(ina219_4_chg.getCurrent_mA(), 1);
    Serial.print("\t");
    Serial.println(ina219_4_chg.getPower_mW(), 1);

    Serial.println("-----------------------------------------------------------");
    delay(1000);
}
