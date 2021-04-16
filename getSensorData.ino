/*
 * 
  FLOW:  Getting data from 4 sensors. 

  --> Press button 
  --> Delay of 5 seconds 
  --> Green LED turns on 
  --> Data collected from all 4 sensors for 5 seconds 
  --> Green LED turns off
  --> Red LED turns on 

   
  The circuit:
  - LED attached from pin 11 & 12 to ground
  - pushbutton attached to pin 3 from +5V
  - 10K resistor attached to pin 3 from ground
  - Piezos connected via 1 MegaOhm resistor 
...
<<<<<<< HEAD
=======

>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
*/

//use milis for 2+ timed concurrent events 

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

String dataLabel1 = "ACC X-raw"; 
String dataLabel2 = "ACC Y-raw"; 
String dataLabel3 = "ACC Z-raw"; 
String dataLabel1B = "ACC X-norm"; 
String dataLabel2B = "ACC Y-norm"; 
String dataLabel3B = "ACC Z-norm"; 
<<<<<<< HEAD
String dataLabel4 = "Ceramic Piezo:"; 
String dataLabel5 = "Film Piezo"; 
String dataLabel6 = "Weighted Film Piezo"; 
String dataLabel7 = "Vibration Sensor"; 
=======
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b

bool label = true; 

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 3;     // pushbutton pin
const int ledGreen = 12;  // LED START pin
const int ledRed = 11;  // LED STOP pin
<<<<<<< HEAD
const unsigned long eventInterval = 10000; //create a 10 second time interval   
=======
const unsigned long eventInterval = 5000; //create a 5 second time interval   
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
unsigned long startTime = 0;

const int ceramicPizeoSensor = A0; //  ceramic piezo is connected to analog pin 0
const int pizeoVibrationSensor = A1; // piezo vibration is connected to analog pin 1
const int weightedPizeoSensor = A2; // weighted piezo vibration is connected to analog pin 2
<<<<<<< HEAD
const int vibrationSensor = 6; // vibration sensor is connected to digital pin 6 

=======
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int ceramicPiezoSensorValue = 0;      // variable to store the value read from the sensor pin
int piezoVibrationSensorValue = 0;
int weightedPiezoSensorValue = 0;

void setup() {
  Serial.begin(115200);   //Start the serial communication
  Serial.println("Program started");
  Serial.println("Initialize MPU6050");

<<<<<<< HEAD
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
=======

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // initialize the LED pin as an output:
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
<<<<<<< HEAD
  pinMode(vibrationSensor, INPUT); 

  checkSettings();
}


void checkSettings(){  
=======

  checkSettings();

}

void checkSettings()
{
  Serial.println();
  
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  
  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
<<<<<<< HEAD
  Serial.println(mpu.getAccelOffsetZ());  
}// END of checkSettings function
=======
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b



void loop() {
  unsigned long currentTime = millis();
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  int ceramicPiezoSensorValue = analogRead(ceramicPizeoSensor);   // read the sensor and store it in the variable sensorReading:
  int piezoVibrationSensorValue = analogRead(pizeoVibrationSensor);   // read the sensor and store it in the variable sensorReading:
  int weightedPiezoSensorValue = analogRead(weightedPizeoSensor);   // read the sensor and store it in the variable sensorReading:
<<<<<<< HEAD
  long vibrationSensorValue  = pulseIn(vibrationSensor, HIGH); 
=======
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {

    Serial.println("button pressed");
<<<<<<< HEAD
    
    // turn LED on:
    delay(5000); //wait 5 seconds before you start collecting data 
    digitalWrite(ledRed, LOW);
=======
    digitalWrite(ledRed, LOW);
    // turn LED on:
    delay(5000); //wait 5 seconds before you start collecting data 

>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
    digitalWrite(ledGreen, HIGH);
    //collect sensor data here for 5 seconds

    //enable headers 
    while(label){
<<<<<<< HEAD
      Serial.println(dataLabel1 + ", ");
=======
      Serial.print(dataLabel1 + ", ");
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
      Serial.print(dataLabel2 + ",");
      Serial.print(dataLabel1 + ", ");
      Serial.print(dataLabel1B + ", ");
      Serial.print(dataLabel2B + ", ");
<<<<<<< HEAD
      Serial.print(dataLabel3B +", ");
      Serial.print(dataLabel4 +", ");
      Serial.print(dataLabel5 +", ");
      Serial.print(dataLabel6 +", ");
      Serial.print(dataLabel7 +"\n");
=======
      Serial.print(dataLabel3B +"\n");
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
      label = false; 
    }
    

    startTime = millis();
    //get data from sensors for 5 seconds 
    while(millis() - startTime <= eventInterval){
<<<<<<< HEAD
      
      Vector rawAccel = mpu.readRawAccel();
      Vector normAccel = mpu.readNormalizeAccel();
        
      Serial.print(String(rawAccel.XAxis) +",");
      Serial.print(String(rawAccel.YAxis) +",");
      Serial.print(String(rawAccel.ZAxis) +",");
      Serial.print(String(normAccel.XAxis) +",");
      Serial.print(String(normAccel.YAxis) +",");
      Serial.print(String(normAccel.ZAxis) +",");
      Serial.print(String(ceramicPiezoSensorValue) +",");
      Serial.print(String(piezoVibrationSensorValue) +",");
      Serial.print(String(weightedPiezoSensorValue) +",");
      Serial.print(String(vibrationSensorValue) +"\n");
=======
       Vector rawAccel = mpu.readRawAccel();
        Vector normAccel = mpu.readNormalizeAccel();
        
        Serial.print(rawAccel.XAxis);
        Serial.print(",");
        Serial.print(rawAccel.YAxis);
        Serial.print(",");
        Serial.print(rawAccel.ZAxis);
        Serial.print(",");
        Serial.print(normAccel.XAxis);
        Serial.print(",");
        Serial.print(normAccel.YAxis);
        Serial.print(",");
        Serial.println(normAccel.ZAxis);
          
        
        Serial.print("The value of the ceramic piezo sensor is: ");
        Serial.println(ceramicPiezoSensorValue);
        Serial.print("The value of the vibration piezo sensor is: ");
        Serial.println(piezoVibrationSensorValue);
        Serial.print("The value of the weighted piezo sensor is: ");
        Serial.println(weightedPiezoSensorValue);
>>>>>>> c2cbd5db70c49089a682a2b94d082c9c57c25a7b
    
    }//close while loop
  }//close if startment 

  else {
    //Serial.println("button released");
    // turn LED off:
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  }
}
