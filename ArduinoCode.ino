/*
	Intelligent sterilization system which can display 
		the number of sterilized people
			and has gel level alarm.

*/


#include <LiquidCrystal.h>
#include <Servo.h>

int pos = 0;
#define NOTE_G3  196

#define trigPin2 4 // attach pin D4 Arduino to pin Echo of HC-SR04
#define echoPin2 5 // attach pin D5 Arduino to pin Echo of HC-SR04
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR047

// variable for the duration of sound wave travel..
// variable for the distance measurement..
// variable for the level of liquid..
long duration,duration2,pourcentage; 
int distance,distance2,personne=0; 

LiquidCrystal lcd(6, 7, 10, 11, 12, 13);
  
Servo servo_9;

void setup()
{

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("M2 GSI TP SysEm");
  servo_9.attach(9, 500, 2500);
  
  
  pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin2 as an INPUT
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("MASTER GSI 2"); // print some text in Serial Monitor
  Serial.println("Welcome");
  


  
}

void loop()
{

  /*  						Stérilisateur			*/
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  //Pulse duration: Time it takes for one pulse to occur
  duration2 = pulseIn(echoPin2, HIGH);
  
  //calculate distance
  distance2 = (duration2/2) / 29.1;
  Serial.print("distance de l'eau: ");
  Serial.print(distance2);
  Serial.println(" cm");
  //calculating the liquid level
  pourcentage=distance2*100/20;
  //si le niveau du gel est inferieur a 15% le buzzer fait un son
  if(pourcentage>15){
  	 Serial.print("le niveau du gel % = ");  
     Serial.println(pourcentage);
  }else{  
    Serial.print(pourcentage);
    
    tone(8, NOTE_G3, 500);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////
  /*			This is for hand ultrasonic sensor			*/
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = (duration/2) / 29.1;
 // Speed of sound wave divided by 2 (go and back)
  
  /*
  if his hand is closer with distance < 5 give him liquid
  by sweeping the servo motor
  */
  
  if(distance <5){
  //incremente le nbr de personne strelise
  personne=personne+1;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= 90; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
  delay(250);
  for (pos = 9; pos >= 0; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    // wait 10 ms for servo to reach the position
    delay(10); // Wait for 10 millisecond(s)
  }
  }
	/* 				LCD part			*/
  //Displaying niveau de gel 
	lcd.clear();
    lcd.setCursor(0, 0);
  	lcd.print("Gel %:");
    lcd.setCursor(9, 0);
 	lcd.print(pourcentage);
  //displaying le nbr de personne sterilise
  lcd.setCursor(0, 1);
  	lcd.print("NPS:");
    lcd.setCursor(4, 1);
 	lcd.print(personne);

  
    delay(1000);

}
