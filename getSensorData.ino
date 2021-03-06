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
*/

//use milis for 2+ timed concurrent events 

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

String dataLabel0 = "Time"; 

String dataLabel1A = "ACC X-raw"; 
String dataLabel1B = "ACC Y-raw"; 
String dataLabel1C = "ACC Z-raw"; 
String dataLabel2A = "ACC X-norm"; 
String dataLabel2B = "ACC Y-norm"; 
String dataLabel2C = "ACC Z-norm"; 

String dataLabel3A = "GYRO X-raw"; 
String dataLabel3B = "GYRO Y-raw"; 
String dataLabel3C = "GYRO Z-raw"; 
String dataLabel4A = "GYRO X-norm"; 
String dataLabel4B = "GYRO Y-norm"; 
String dataLabel4C = "GYRO Z-norm"; 

String dataLabel5 = "Ceramic Piezo:"; 
String dataLabel6 = "Film Piezo"; 
String dataLabel7 = "Weighted Film Piezo"; 
String dataLabel8 = "Vibration Sensor"; 

bool label = true; 

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 3;     // pushbutton pin
const int ledGreen = 12;  // LED START pin
const int ledRed = 11;  // LED STOP pin
const unsigned long eventInterval = 10000; //create a 10 second time interval   
unsigned long startTime = 0;

const int ceramicPizeoSensor = A0; //  ceramic piezo is connected to analog pin 0
const int pizeoVibrationSensor = A1; // piezo vibration is connected to analog pin 1
const int weightedPizeoSensor = A2; // weighted piezo vibration is connected to analog pin 2
const int vibrationSensor = 6; // vibration sensor is connected to digital pin 6 


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int ceramicPiezoSensorValue = 0;      // variable to store the value read from the sensor pin
int piezoVibrationSensorValue = 0;
int weightedPiezoSensorValue = 0;

void setup() {
  Serial.begin(115200);   //Start the serial communication
  Serial.println("Program started");
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  //Set accelerometer and gyroscope offsets
  //mpu.setAccelOffsetX();
  //mpu.setAccelOffsetY();
  //mpu.setAccelOffsetZ();
  mpu.setGyroOffsetX(155);
  mpu.setGyroOffsetY(15);
  mpu.setGyroOffsetZ(15);

  // Calibrate gyroscope. The calibration must be at rest.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // mpu.setThreshold(3);

  // initialize the LED pin as an output:
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(vibrationSensor, INPUT); 

  checkSettings();
}


void checkSettings(){  
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
  Serial.println(mpu.getAccelOffsetZ());  

  Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  } 
  
  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getGyroOffsetZ());
  
}// END of checkSettings function



void loop() {  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledRed, HIGH);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.println("button pressed");
    
    // turn LED on:
    delay(5000); //wait 5 seconds before you start collecting data 
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    //collect sensor data here for 5 seconds

    //enable headers 
    while(label){  
      Serial.print(dataLabel0 + ", ");
      Serial.print(dataLabel1A + ", ");
      Serial.print(dataLabel1B + ", ");
      Serial.print(dataLabel1C + ", ");
      Serial.print(dataLabel2A + ", ");
      Serial.print(dataLabel2B + ", ");
      Serial.print(dataLabel2C +", ");
      Serial.print(dataLabel3A + ", ");
      Serial.print(dataLabel3B + ",");
      Serial.print(dataLabel3C + ", ");
      Serial.print(dataLabel4A + ", ");
      Serial.print(dataLabel4B + ", ");
      Serial.print(dataLabel4C +", ");
      Serial.print(dataLabel5 +", ");
      Serial.print(dataLabel6 +", ");
      Serial.print(dataLabel7 +", ");
      Serial.print(dataLabel8 +"\n");
      label = false; 
    }
    

    startTime = millis();
    //get data from sensors for eventInterval (10) seconds 
    while(millis() - startTime <= eventInterval){
      int ceramicPiezoSensorValue = analogRead(ceramicPizeoSensor);   // read the sensor and store it in the variable sensorReading:
      int piezoVibrationSensorValue = analogRead(pizeoVibrationSensor);   // read the sensor and store it in the variable sensorReading:
      int weightedPiezoSensorValue = analogRead(weightedPizeoSensor);   // read the sensor and store it in the variable sensorReading:
      long vibrationSensorValue  = pulseIn(vibrationSensor, HIGH); 
      Vector rawAccel = mpu.readRawAccel();
      Vector normAccel = mpu.readNormalizeAccel();
      Vector rawGyro = mpu.readRawGyro();
      Vector normGyro = mpu.readNormalizeGyro();

      //Add time to document 
      Serial.print(String(millis() - startTime) +",");
        
      Serial.print(String(rawAccel.XAxis) +",");
      Serial.print(String(rawAccel.YAxis) +",");
      Serial.print(String(rawAccel.ZAxis) +",");
      Serial.print(String(normAccel.XAxis) +",");
      Serial.print(String(normAccel.YAxis) +",");
      Serial.print(String(normAccel.ZAxis) +",");

      Serial.print(String(rawGyro.XAxis) +",");
      Serial.print(String(rawGyro.YAxis) +",");
      Serial.print(String(rawGyro.ZAxis) +",");
      Serial.print(String(normGyro.XAxis) +",");
      Serial.print(String(normGyro.YAxis) +",");
      Serial.print(String(normGyro.ZAxis) +",");
      
      Serial.print(String(ceramicPiezoSensorValue) +",");
      Serial.print(String(piezoVibrationSensorValue) +",");
      Serial.print(String(weightedPiezoSensorValue) +" ,");
      Serial.print(String(vibrationSensorValue) +"\n");

    
    }//close while loop
  }//close if startment 

  else {
    //Serial.println("button released");
    // turn LED off:
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  }
}
