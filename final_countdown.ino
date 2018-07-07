#include <LiquidCrystal.h>
#include <pitches.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ultrasonic sensor
#define trigPin 9
#define echoPin 8

// tone
#define tonePin 7
#define MELODY_LENGTH 10
int melody[] = {
  NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_FS4, 0, NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_CS5, NOTE_B4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 8, 2, 1, 8, 8, 8, 4, 4, 2
};

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Distance (cm):");

  // ultrasonic sensor setup
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void tone() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < MELODY_LENGTH; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(tonePin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(tonePin);
  }
}

void loop() {

  // get distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance (cm):");
  lcd.setCursor(0, 1);
  lcd.print(distance);

  if(distance < 12) {
    tone();
  }

  delay(100);
}
