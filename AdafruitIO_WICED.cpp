#ifdef ARDUINO_STM32_FEATHER

#include "AdafruitIO_WICED.h"

AdafruitIO_WICED::AdafruitIO_WICED(const char *ssid, const char *pass):AdafruitIO()
{
  _ssid = ssid;
  _pass = pass;
  _client = new AdafruitIO_WICED_SSL;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

AdafruitIO_WICED::AdafruitIO_WICED(const __FlashStringHelper *ssid, const __FlashStringHelper *pass):AdafruitIO()
{
  _ssid = (const char*)ssid;
  _pass = (const char*)pass;
  _client = new AdafruitIO_WICED_SSL;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

void AdafruitIO_WICED::_connect()
{
  Feather.connect(_ssid, _pass);
  _status = AIO_NET_DISCONNECTED;
}

aio_status_t AdafruitIO_WICED::networkStatus()
{
  if(Feather.connected())
    return AIO_NET_CONNECTED;

  // if granular status is needed, we can
  // check Feather.errno() codes:
  // https://learn.adafruit.com/introducing-the-adafruit-wiced-feather-wifi/constants#err-t
  // for now we will try connecting again and return disconnected status
  Feather.connect(_ssid, _pass);
  return AIO_NET_DISCONNECTED;
}

#endif // ARDUINO_STM32_FEATHER
