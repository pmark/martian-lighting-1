//
// see https://www.hackster.io/AgustinP/logging-temperature-data-using-the-spark-core-b9c60c
// 

#include "application.h"
#include "HttpClient.h"
#include "OneWire.h"
#include "spark-dallas-temperature.h"
 
#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
 
float temperature = 0.0;
char resultstr[64];
HttpClient http;
 
// ubidots sensor dashboard support
// http://ubidots.com/
#define VARIABLE_ID "56871c587625421c3844d644"
#define TOKEN "u80i5jxgrvdRij5rKydxi2qbCinSY8LapYAluptBVb6BBC09b7KZNvB3Qpjn"
 
http_header_t headers[] = {
      { "Content-Type", "application/json" },
      { "X-Auth-Token" , TOKEN },
    { NULL, NULL } // NOTE: Always terminate headers with NULL
};
 
http_request_t request;
http_response_t response;
 
void setup() {
    request.port = 80;
    request.hostname = "things.ubidots.com";
    request.path = "/api/v1.6/variables/" VARIABLE_ID "/values";
    Serial.begin(9600);
    sensor.begin();
}
 
void loop() {
 sensor.requestTemperatures();
 temperature = sensor.getTempFByIndex( 0 );

 if (temperature > 0 && temperature < 115) {
 	sprintf(resultstr, "{\"value\":%.4f}",temperature); 
 	request.body = resultstr;//Sending presence to Ubidots
 	http.post(request, response, headers);
 	Serial.println(response.status); //For debug only
 	Serial.println(response.body); 	
 }
 delay(5000);
}
