#include <Servo.h>          //include the servo library

// VARIABLES
const long ONE_MINUTE = 60000;

// POTENTIOMETER-RELIANT VARIABLES
int potPosition;  // the position that the potentiometer is turned to
int index;        // position of the song in the data arrays
int currentYear;
int currentBPM;
char currentSong;

// SERVO VARIABLES
Servo myservo; 
int servoPosition;  // the angle the servo is rotated at
int servoSpeed;     // the amount of time it should take between the drumstick being up or down

// DATA ARRAYS
int years[] = {2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024}; // List of years
int bpms[] = {115, 100, 96, 77, 136, 171, 103, 81, 204, 160}; // the BPM of the songs for the year with the same index
char *songTitles[] = {"Uptown Funk", "Love Yourself", "Shape of You", "God's Plan", "Old Town Road", "Blinding Lights", "Levitating", "Heat Waves", "Last Night", "Lose Control"};

// set up LCD display
#include <LiquidCrystal.h> 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// -------------


void setup() {

  myservo.attach(3);

  Serial.begin(9600);                       //begin serial communication with the computer

  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
}

void loop() {

 getChosenSongInfo();

 servoSpeed = ONE_MINUTE / (currentBPM * 2); // multiply the BPM by 2 to include time moving servo up and down 

 // Print statements to test that potentiometer is working
 Serial.print(songTitles[index]);
 Serial.print("-");
 Serial.println(currentYear);

 // Present the output (servo & LCD) based on potentiometer input
 displaySongInfo();
 moveServo(servoSpeed);

}

// Updates the current song based on the potentiometer posiiton
void getChosenSongInfo() {
  // Get input from potentiometer
  potPosition = analogRead(A0);
  index = map(potPosition, 0, 1023, 9, -1); // convert potentiometer dial position to an index 0-10;

  /* Our potentiometer had a hard time recognizing the edge value of 9 when turned all the way.
  Moved range up to 10 to let the last index double its potentiometer space. */
  if (index == -1) {
    index = 0;
  }

  // Get the relevant information from the selected year
  currentYear = years[index];
  currentBPM = bpms[index];
}

// Moves the servo arm up and down to match the current BPM
void moveServo(int speed) {
  if(speed != 0) {                  // only run this code if the speed is not 0 
    servoPosition = 40;
    delay(speed);
    myservo.write(servoPosition);

    servoPosition = 100;
    delay(speed);
    myservo.write(servoPosition);
  }
}

// Displays the current song information (title and year) on the LCD display
void displaySongInfo() {
  lcd.clear();                      // Have to clear display to remove previous letters
  lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print(songTitles[index]);

  lcd.setCursor(0, 1);              // move cursor to the next row
  lcd.print(currentYear);
}
