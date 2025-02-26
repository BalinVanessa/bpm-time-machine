#include <Servo.h>          //include the servo library

// VARIABLES
const long ONE_MINUTE = 60000;

int servoPosition; // the angle the servo is rotated at
int currentYear;
int currentBPM;
char currentSong;
int servoSpeed; // the amount of time it should take between the drumstick being up or down
int index; // number of the song we're looking at in the list
int potPosition; // the position that the potentiometer is dialed at

Servo myservo; 

int years[] = {2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024}; // List of years
int bpms[] = {115, 100, 96, 77, 136, 171, 103, 81, 204, 160}; // the BPM of the songs for the year with the same index
char *songTitles[] = {"Uptown Funk", "Love Yourself", "Shape of You", "God's Plan", "Old Town Road", "Blinding Lights", "Levitating", "Heat Waves", "Last Night", "Lose Control"};

void setup() {

  myservo.attach(9);

  Serial.begin(9600);                       //begin serial communication with the computer
}

void loop() {

 getChosenSongInfo();

 servoSpeed = ONE_MINUTE / (currentBPM * 2); // multiply the BPM by 2 to include time moving servo up and down 
 Serial.print(songTitles[index]);
 Serial.print("-");
 Serial.println(currentYear);
 moveServo(servoSpeed);

}

void getChosenSongInfo() {
  // Get input from potentiometer
  potPosition = analogRead(A0);
  index = map(potPosition, 0, 1023, 0, 10); // convert potentiometer dial position to an index 0-10;

  // potentiometer had a hard time reading the edge value of 9. Moved up to 10 to account for potentiometer glitches;
  if (index == 10) {
    index = 9;
  }

  // Get the relevant information from the selected year
  currentYear = years[index];
  currentBPM = bpms[index];
}

void moveServo(int speed) {
  if(speed != 0) {
    servoPosition = 40;
    delay(speed);
    myservo.write(servoPosition);

    servoPosition = 100;
    delay(speed);
    myservo.write(servoPosition);
  }
}
