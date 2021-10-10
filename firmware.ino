/*
Adult Sock with 7 Pressure Sensitive Textile Sensors
Iman H. Enayati
Department of Orthopedic Surgery
University of California, Los Angeles
imanhenayati@ucla.edu
Author's Notes: The following project records values from an adult's sock embedded with
fabric pressure sensors positioned below the calcaneus and the ball of the foot. The 
pressure sensor readings are outputted via serial monitor/plotter. The following code does not 
support low-energy bluetooth functionality. Contact author for inquiries and support.
Last Updated: October 10th, 2021
*/ 
 
 #include <Filters.h>
  
  int sensorOutValue0 = 0;       //value from outside pressure sensor
  int sensorOutValue1 = 0;       //value from outside pressure sensor
  int sensorOutValue2 = 0;       //value from outside pressure sensor
  int sensorOutValue3 = 0;       //value from outside pressure sensor
  int sensorOutValue4 = 0;       //value from outside pressure sensor
  int sensorOutValue5 = 0;       //value from outside pressure sensor
  int sensorOutValue6 = 0;       //value from outside pressure sensor
  
  int FilteredSensorOutValue0 = 0;
  int FilteredSensorOutValue1 = 1;
  int FilteredSensorOutValue2 = 2;
  int FilteredSensorOutValue3 = 3;
  int FilteredSensorOutValue4 = 4;
  int FilteredSensorOutValue5 = 5;
  int FilteredSensorOutValue6 = 6;
  
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize analog pins as sensor input
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);

  // setup serial communication
  Serial.begin(9600);
}


void loop() {

  // read the analog in values from digital pin:
  sensorOutValue0 = analogRead(A0);
  sensorOutValue1 = analogRead(A1);
  sensorOutValue2 = analogRead(A2); 
  sensorOutValue3 = analogRead(A3);     
  sensorOutValue4 = analogRead(A4);     
  sensorOutValue5 = analogRead(A5);     
  sensorOutValue6 = analogRead(A6);  

  //set up for LowPass filter
  FilterOnePole lowpassFilter0(LOWPASS,500);
  FilterOnePole lowpassFilter1(LOWPASS,50000000000);
  FilterOnePole lowpassFilter2(LOWPASS,50000000000);
  FilterOnePole lowpassFilter3(LOWPASS,50000000000);
  FilterOnePole lowpassFilter4(LOWPASS,50000000000);
  FilterOnePole lowpassFilter5(LOWPASS,50000000000);
  FilterOnePole lowpassFilter6(LOWPASS,50000000000);

  //filter sensor signal value due to noise
  lowpassFilter0.input(sensorOutValue0);
  lowpassFilter0.input(lowpassFilter0.output());
  lowpassFilter0.input(lowpassFilter0.output());
  lowpassFilter0.input(lowpassFilter0.output());
  lowpassFilter1.input(sensorOutValue1);
  lowpassFilter2.input(sensorOutValue2);
  lowpassFilter3.input(sensorOutValue3);
  lowpassFilter4.input(sensorOutValue4);
  lowpassFilter5.input(sensorOutValue5);
  lowpassFilter6.input(sensorOutValue6);

  //create new variable to hold filtered signal
  FilteredSensorOutValue0 = lowpassFilter0.output();
  FilteredSensorOutValue1 = lowpassFilter1.output();
  FilteredSensorOutValue2 = lowpassFilter2.output();
  FilteredSensorOutValue3 = lowpassFilter3.output();
  FilteredSensorOutValue4 = lowpassFilter4.output();
  FilteredSensorOutValue5 = lowpassFilter5.output();
  FilteredSensorOutValue6 = lowpassFilter6.output();

  //serial output
  //color key: blue = toe sensor, heel sensor colors from left to right and again: cyan, red, green. grey, magenta, orange.
  Serial.print(FilteredSensorOutValue0); Serial.print(" "); //blue = toes
  Serial.print(FilteredSensorOutValue1); Serial.print(" ");
  Serial.print(FilteredSensorOutValue2); Serial.print(" ");
  Serial.print(FilteredSensorOutValue3); Serial.print(" ");
  Serial.print(FilteredSensorOutValue4); Serial.print(" ");
  Serial.print(FilteredSensorOutValue5); Serial.print(" ");
  Serial.print(FilteredSensorOutValue6); Serial.print(" ");
  Serial.println(" ");
    
  delay(2);
}
