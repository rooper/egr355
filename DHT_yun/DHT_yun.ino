/*************************************
Duke University
EGR 355: Smart Home Computer Project
Logan Rooper
March 23rd, 2014

Arduino YUN Rest Inteface Based Three-
RHT03 Sensor Reader

Make calls to %ip%/arduino/read/1 to
read sensor 1
*************************************/

#include <dht.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

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
  delay(100);
  
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);
  
    // Close connection and free resources.
    client.stop();
  }
}

void process(YunClient client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "read") {
    readSensor(client);
  }
}

void readSensor(YunClient client) {
  int num, value;

  // Read pin number
  num = client.parseInt();

  // Send feedback to client
  client.print(humidity[num]);
  client.print(",");
  client.print(temperature[num]);
}
