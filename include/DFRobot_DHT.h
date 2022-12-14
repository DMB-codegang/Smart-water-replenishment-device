#ifndef DF_DHT_H
#define DF_DHT_H

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

typedef enum
{
  DHT11,
  DHT22
} dht_mode;

typedef enum
{
  ERROR_NONE = 0,
  ERROR_TIMEOUT,
  ERROR_CHECKSUM
} dht_error;

typedef struct
{
  int pin;
  dht_mode mode;
  float temperature;
  float humidity;
  uint8_t idle;
  unsigned long timestamp;
} dht_data_t;

class DFRobot_DHT
{
public:
  void begin(uint8_t pin, dht_mode mode = DHT11);
  float getTemperature();
  float getHumidity();

  DFRobot_DHT()
  {
    dht_data = NULL;
    mark = false;
  };
  ~DFRobot_DHT()
  {
    if (dht_data)
      free(dht_data);
  };

private:
  void readSensor();
  dht_data_t *dht_data;
  bool mark;

  float temperature;
  float _temperature;
  float humidity;
  float _humidity;
};

#endif /*dht_h*/
