#include "mbed.h"
#include "platform/mbed_thread.h"
#include "DHT.h"

// define DHT                                                   
DHT humid_sensor(D8, DHT22);      // pin 5 


// define input for photocell/moisture_sensor
AnalogIn pCell(A0); 
AnalogIn m_sensor(A2);

// define digital outputs for LEDs
DigitalOut redLED(D7);
DigitalOut blueLED(D6);
DigitalOut greenLED(D5);

// define float for brightness, temp and humidity
float temp, humidity, brightness, moisture;

void plantStatus(float humidity, float temp, float brightness, float moisture){
    if(humidity<30.00 || humidity>80.00){
        redLED=1; 
       greenLED=0;
    }

    else if(temp<45.00 || temp>95.00){
        redLED=1;  
        greenLED=0;
    }

    else if(brightness<50){
        redLED=1;
        greenLED=0;
    }

    else if(moisture<60){
        redLED=1;
        greenLED=0;    
    }
    else{
        redLED=0; 
        greenLED=1;
    }
}

int main()
{
    while (true) {
        //initializes DHT to read data
        humid_sensor.readData();

        // get data from each sensor
        humidity = humid_sensor.ReadHumidity();
        temp = humid_sensor.ReadTemperature(FARENHEIT);
        brightness = (0.1-(pCell.read()/3.0))*1000;
        moisture = m_sensor.read()*100;

        // print out data
        printf("Humidity: %.2f%% Temperature: %.2f F Brightness Level: %.2f Soil Moisture: %.2f%%\n", humidity, temp, brightness, moisture);
        
        //call plantStatus function to update LEDs
        plantStatus(humidity, temp, brightness, moisture);

        // wait for 2 seconds
        ThisThread::sleep_for(2000);

    }
}