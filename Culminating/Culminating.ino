#include <Servo.h>
#define SERVO_PIN 9
#define GROUND_JOY_PIN A3            //joystick ground pin will connect to Arduino analog pin A3
#define VOUT_JOY_PIN A2              //joystick +5 V pin will connect to Arduino analog pin A2
#define XJOY_PIN A0               //X axis reading from joystick will go into analog pin A0
Servo myservo ;

int motorPin = 3; //motor connected to pin 3.
int potenPin = 1; //potentiometer connected to pin A1.

#include <Keypad.h> //imports Keypad 3.1.1 .zip file.
const int ROW_NUM = 4; //4 Rows.
const int COLUMN_NUM = 4; //4 Columns.

char keys [ROW_NUM] [COLUMN_NUM] = {
  {'1','2','3','A'}, //Row 1.
  {'4','5','6','B'}, //Row 2.
  {'7','8','9','C'}, //Row 3.
  {'*','0','#','D'}  //Row 4.
};

byte pin_rows[ROW_NUM] = {12,11,10,8}; //pins on the arduino connected to Rows.
byte pin_column[COLUMN_NUM] = {7,6,5,4}; //pins on the arduino connected to Columns.

Keypad keypad = Keypad(makeKeymap(keys),pin_rows,pin_column,ROW_NUM,COLUMN_NUM);  
 
void setup()
{
 Serial.begin(9600); //9600 baud.
 pinMode(VOUT_JOY_PIN, OUTPUT) ;    //pin A3 shall be used as output
 pinMode(GROUND_JOY_PIN, OUTPUT) ;  //pin A2 shall be used as output
 digitalWrite(VOUT_JOY_PIN, HIGH) ; //set pin A3 to high (+5V)
 digitalWrite(GROUND_JOY_PIN,LOW) ; //set pin A3 to low (ground)
 myservo.attach(9);

 pinMode(motorPin,OUTPUT); //motor is an Output.
}
 
void loop()
{
 delay(200);                    
 int joystickXVal = analogRead(XJOY_PIN) ;  //read joystick input on pin A1
 Serial.print(joystickXVal);                //print the value from A1
 Serial.println(" = input from joystick");  //print "=input from joystick" next to the value
 Serial.print((joystickXVal+520));       //print a from A1 calculated, scaled value
 Serial.println(" = output to servo");      //print "=output to servo" next to the value
 Serial.println() ;
 myservo.write((joystickXVal+520));      //write the calculated value to the servo  

 int PWMoutput,potReading;

 potReading = analogRead(potenPin); //value of PotReading is the data from the PotenPin.
 PWMoutput = map(potReading,0,1023,0,255);
 analogWrite(motorPin,PWMoutput); //spins the motor at the speed indicated by the potentiometer.

 char key = keypad.getKey();
 if (key)
 {
  Serial.println(key); //prints the keypad input on a new line of the Serial Monitor.
  if (key = '1') //Sweep speed 1.
  {
    do
    { 
      myservo.write(10); //set servo angle to 10 degrees.
      delay(500); //wait half a sec.

      myservo.write(90); //set servo angle to 90 degrees.
      delay(500); //wait half a sec.

      myservo.write(150); //set servo angle to 150 degrees.
      delay(500); //wait half a sec.

      myservo.write(90); //set servo angle to 90 degrees.
      delay(500); //wait half a sec.

      myservo.write(10); //set servo angle to 10 degrees.
      delay(500); //wait half a sec.
    } while(key = '1');
  }
  else if (key = '2') //Sweep speed 2.
  {
    do
    {
      myservo.write(10); //set servo angle to 10 degrees.
      delay(1000); //wait 1 sec.

      myservo.write(90); //set servo angle to 90 degrees.
      delay(1000); //wait 1 sec.

      myservo.write(150); //set servo angle to 150 degrees.
      delay(1000); //wait 1 sec.

      myservo.write(90); //set servo angle to 90 degrees.
      delay(1000); //wait 1 sec.

      myservo.write(10); //set servo angle to 10 degrees.
      delay(1000); //wait 1 sec.
    } while(key = '2');
  }
 }
}
