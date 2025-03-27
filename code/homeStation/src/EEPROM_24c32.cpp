#include "EEPROM_24c32.h"

// zapis i odczyt z pamieci EEPROM
// nalezy zawsze zapisyac dwa bajty nawet korzystajac z przestrzeni adresowej 0 - 255

bool eepromWrite(uint8_t REG, uint8_t VAL){
    Wire.beginTransmission(EEPROM_ADRESS);
    Wire.write(REG >> 8);
    Wire.write(REG & 0xFF);
    Wire.write(VAL);
    if(Wire.endTransmission())
        return true;
    else
        return false;
}

void eepromRead(uint8_t REG, uint8_t *BUF){
    Wire.beginTransmission(EEPROM_ADRESS);
    Wire.write(REG >> 8);
    Wire.write(REG & 0xFF);
    Wire.endTransmission();
    delay(10);
    Wire.requestFrom(EEPROM_ADRESS, 1);
    Wire.readBytes(BUF, 1);
}
