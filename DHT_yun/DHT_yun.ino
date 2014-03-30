/*************************************
Duke University
EGR 355: Smart Home Computer Project
Logan Rooper
March 23rd, 2014

Arduino YUN Rest Inteface Based Three-
RHT03 Sensor Reader

Sends requests to Paul's server
*************************************/

#include <dht.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <HttpClient.h>

dht DHT;

#define DHT1_PIN 4
#define DHT2_PIN 5
#define DHT3_PIN 6

YunServer server;

//global data vars (indicies are sensor numbers 0-2)
long temperature[] = {0, 0, 0};
long humidity[] = {0, 0, 0};

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up...");
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  Serial.println("Done.");
  
  Bridge.begin();
  
}

void loop()
{
  // READ DATA
  Serial.print("DHT1, \t");
  int chk = DHT.read22(DHT1_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
		Serial.print("OK,\t"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.print("Checksum error,\t"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.print("Time out error,\t"); 
		break;
    default: 
		Serial.print("Unknown error,\t"); 
		break;
  }
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);
  humidity[0] = DHT.humidity;
  temperature[0] = DHT.temperature;
  delay(100);
  


    // READ DATA
  Serial.print("DHT2, \t");
  chk = DHT.read22(DHT2_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
		Serial.print("OK,\t"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.print("Checksum error,\t"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.print("Time out error,\t"); 
		break;
    default: 
		Serial.print("Unknown error,\t"); 
		break;
  }
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);

  humidity[1] = DHT.humidity;
  temperature[1] = DHT.temperature;
  delay(100);

  // READ DATA
  Serial.print("DHT3, \t");
  chk = DHT.read22(DHT3_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
		Serial.print("OK,\t"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.print("Checksum error,\t"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.print("Time out error,\t"); 
		break;
    default: 
		Serial.print("Unknown error,\t"); 
		break;
  }
 
 
  // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);

  humidity[2] = DHT.humidity;
  temperature[2] = DHT.temperature;
  
  
  //send  for temp
  HttpClient client;
  String a = "http://yilunzhou.site50.net/putInfo.php?temperature=";
  a = a +  temperature[0];
  client.get(a);
  
   //send  for humid
  a = "http://yilunzhou.site50.net/putInfo.php?humidity=";
  a = a +  humidity[0];
  client.get(a);
  
  
  
  
  delay(10000); // every 10 seconds
}
