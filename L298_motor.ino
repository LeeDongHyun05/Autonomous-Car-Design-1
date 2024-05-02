#define IN1 11
#define IN2 10
#define ENR 6

#define IN3 9
#define IN4 8
#define ENL 7


void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENL, OUTPUT);
  pinMode(ENR, OUTPUT);

}

void motor_l(int speed)
{
  if(speed >=0)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENL, speed);
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENL, -speed);
  }
}

void motor_r(int speed)
{
  if(speed >=0)
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENR, speed);
  }
  else
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENR, -speed);
  }
}

void loop() 
{
  motor_l(-40);
  motor_r(40);
}
