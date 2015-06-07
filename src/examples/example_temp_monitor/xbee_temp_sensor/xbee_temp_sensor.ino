#include <XBee.h>
#include <OneWire.h>

#define PAYLOAD_SIZE sizeof(float)

typedef union {
    float float_variable;
    uint8_t bytes_array[4];
} float_sensor_result;

uint8_t *data                   = NULL; // received data
size_t data_len                 = 0;    // recevied data length
uint8_t option                  = 0;    // received packet option
uint8_t payload[PAYLOAD_SIZE]   = {0};  // data to be sent (4bytes (sizeof(float)=32bits))
int DS18S20_Pin                 = 2;    // DS18S20 Signal pin on digital 2

//Temperature chip i/o
OneWire ds(DS18S20_Pin); // on digital pin 2

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();
Tx16Request tx = Tx16Request(0x0, &payload[0], PAYLOAD_SIZE);

float getTemp(bool * success = NULL);

void setup() {
    Serial.begin(9600);
    xbee.setSerial(Serial);
}

void loop() {
    bool temp_success = false;
    xbee.readPacket();
    if (xbee.getResponse().isAvailable()) {
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
            if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
                xbee.getResponse().getRx16Response(rx16);
                option = rx16.getOption();
                data = rx16.getData();
                data_len = rx16.getDataLength();
            } else {
                xbee.getResponse().getRx64Response(rx64);
                option = rx64.getOption();
                data = rx64.getData();
                data_len = rx64.getDataLength();
            }
            if(NULL != data) {
                Serial.println("Received");
                Serial.write(data, data_len);
                Serial.println("");
                if(strcmp((char*)data, "temp") == 0) {
                    Serial.println("Temp request");
                    float temp = getTemp(&temp_success);
                    if(!temp_success) {
                        Serial.println("Failed to get temperature !!!");
                        return;
                    }
                    Serial.print("Temp: ");
                    Serial.print(temp, sizeof(float));
                    Serial.println("°C");
                    float_sensor_result res;
                    res.float_variable = temp;
                    memcpy(&payload, &res.bytes_array[0], PAYLOAD_SIZE);

                    xbee.send(tx);
                }
            }
            else {
                Serial.println("Failed to get data");
            }
        }
        else {
            //Serial.println("Ignoring received packet");
        }
    }
    else {
        //Serial.println("No data");
    }
}

//returns the temperature from one DS18S20 in DEG Celsius
float getTemp(bool * success) {
    bool l_success = false;
    byte l_data[12] = {0};
    byte l_addr[8] = {0};
    byte l_msb = 0;
    byte l_lsb = 0;
    float temperature = 0.0;

    if ( !ds.search(l_addr)) {
        //no more sensors on chain, reset search
        Serial.println("No sensor found!");
        ds.reset_search();
        goto exit;
    }

    if ( OneWire::crc8( l_addr, 7) != l_addr[7]) {
        Serial.println("CRC is not valid!");
        goto exit;
    }

    if ( l_addr[0] != 0x10 && l_addr[0] != 0x28) {
        Serial.print("Device is not recognized");
        goto exit;
    }

    ds.reset();
    ds.select(l_addr);
    ds.write(0x44,1); // start conversion, with parasite power on at the end

    ds.reset();
    ds.select(l_addr);
    ds.write(0xBE); // Read Scratchpad

    for (int i = 0; i < 9; i++) { // we need 9 bytes
        l_data[i] = ds.read();
    }

    ds.reset_search();

    l_msb = l_data[1];
    l_lsb = l_data[0];
    temperature = ((l_msb << 8) | l_lsb); //using two's compliment
    temperature /= 16;
    
    l_success = true;
    

exit:
    if(NULL != success) {
        *success = l_success;
    }
    return temperature;
}
