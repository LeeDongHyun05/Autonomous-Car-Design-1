#include <NewPing.h>

#define SONAR_NUM  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 150// Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
float UltrasonicSensorData[SONAR_NUM];

int mode;
NewPing sonar[SONAR_NUM]=// NewPing setup of pins and maximum distance.
{
  NewPing(8,8,MAX_DISTANCE), //Front
  NewPing(9,9,MAX_DISTANCE), //Rear
  NewPing(10,10,MAX_DISTANCE), //Right
  NewPing(11,11,MAX_DISTANCE) //Left
  
};
void read_ultrasonic_sensor(void)
{
  UltrasonicSensorData[0] = sonar[0].ping_cm(); //Front
  UltrasonicSensorData[1] = sonar[1].ping_cm(); //Rear
  UltrasonicSensorData[2] = sonar[2].ping_cm(); //Right
  UltrasonicSensorData[3] = sonar[3].ping_cm(); //Left
  
}

void Sonar_Data_Display(int flag)
{
  char Sonar_data_display[40];
  if(flag == 0) return;
  else
  {
    sprintf(Sonar_data_display,"F:");
    Serial.print(Sonar_data_display);
    Serial.print(UltrasonicSensorData[0]);
    Serial.print("B:");
    Serial.print(UltrasonicSensorData[1]);
    Serial.print("R:");
    Serial.print(UltrasonicSensorData[2]);
    Serial.print("L:");
    Serial.print(UltrasonicSensorData[3]);
  }
}

void Robot_Mode_Define(void)
{
  int i;
  mode = -1;
  read_ultrasonic_sensor();
  for(i=0;i<4;i++)
  {
    if(UltrasonicSensorData[i] ==0) UltrasonicSensorData[i] = MAX_DISTANCE;
  }
  Sonar_Data_Display(1);
  // mode == 0
  if( (UltrasonicSensorData[2] >= 15) && (UltrasonicSensorData[3] >= 15) )
  {
    mode = 0;
  }
  //mode == 1
  if( (UltrasonicSensorData[2] <= 15) && (UltrasonicSensorData[3] <= 15) )
  {
    mode = 1;
  }
  // mode == 2
  if( (UltrasonicSensorData[3] <=35) && (UltrasonicSensorData[2] >= 40) )
  {
    mode = 2;
  }
  // mode == 3
  if( (UltrasonicSensorData[2] <= 35) && (UltrasonicSensorData[3] >= 40) )
  {
    mode = 3;
  }
}

#define ledPin 13 // LED는 디지털 핀 13에 연결됨
#define LINE_DETECT_WHITE 1
int linesensor_data[5] = {0,0,0,0,0};
int linesensor_pin[5] = {2,3,4,5,6};


int read_digital_line_sensor(void)
{
  int i;
  int sum= 0;
  for(i=0;i<5;i++)
  {
    if(LINE_DETECT_WHITE == 0)
    {
      linesensor_data[i] = 1 - digitalRead(linesensor_pin[i]);
    }
    else
    {
      linesensor_data[i] = digitalRead(linesensor_pin[i]);
    }
    sum += linesensor_data[i];
  }
  return sum;
}

void setup(){
  int i;
  pinMode(ledPin, OUTPUT);

  for(i=0;i<5;i++)
  {
      pinMode(linesensor_pin[i], INPUT);
  }
  Serial.begin(9600);
}



void loop(){
  int i;
  int sum = 0;

  sum = read_digital_line_sensor();

  Serial.print("Input data =");
  for(i=0;i<5;i++)
  {
      Serial.print(linesensor_data[i]);
      Serial.print(" ");
  }
  Serial.print(sum);
  Serial.println(" ");
  Serial.print("Ping: ");
  Serial.print(UltrasonicSensorData[i]); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}
