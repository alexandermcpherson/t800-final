#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// TERMINATOR 1

// Folder 1
const int terminator1MusicFolder = 1;
// Files
const int terminator1MusicTheme = 1;

// Folder 2
const int terminator1SfxDaDumFolder = 2;
// Files
const int terminator1SfxDa1 = 1;
const int terminator1SfxDa2 = 2;
const int terminator1SfxDa3 = 3;
const int terminator1SfxDum4 = 4;
const int terminator1SfxDum5 = 5;
const int terminator1SfxDum6 = 6;
const int terminator1SfxDa7 = 7;

// Folder 3
const int terminator1SfxGunFolder = 3;
// Files
const int terminator1SfxPistol1 = 1;
const int terminator1SfxPistol2 = 2;
const int terminator1SfxShotgun = 3;
const int terminator1SfxUzi = 4;

// Folder 4
const int terminator1SfxRoboticFolder = 4;
// Files
const int terminator1SfxRobotic1 = 1;
const int terminator1SfxRobotic2 = 2;
const int terminator1SfxRobotic3 = 3;
const int terminator1SfxRobotic4 = 4;
const int terminator1SfxRobotic5 = 5;
const int terminator1SfxRobotic6 = 6;

// Folder 5
const int terminator1SfxVisionFolder = 5;
// Files
const int terminator1SfxVision1 = 1;
const int terminator1SfxVision2 = 2;

// Folder 6
const int terminator1SpeechFolder = 6;
// Files
const int terminator1SpeechYourClothesGiveThemToMeNow = 1;
const int terminator1SpeechFirtyFiveLongSlideWithLaserSignting = 2;
const int terminator1SpeechUziNineMillimeter = 3;
const int terminator1SpeechSarahConnor = 4;
const int terminator1SpeechFuckYouAssHole = 5;
const int terminator1SpeechIllBeBack = 6;
const int terminator1SpeechGetOut = 7;

// TERMINATOR 2

// Folder 7
const int terminator2MusicFolder = 7;
// Files
const int terminator2MusicTheme = 1;

// Folder 8
const int terminator2SpeechFolder = 8;
// Files
const int terminator2SpeechINeedYourClothes = 1;
const int terminator2SpeechCyberdyneSystemsModel101 = 2;
const int terminator2SpeechIamATerminator = 3;
const int terminator2SpeechThatsOneOfMyMissionParamteres = 4;
const int terminator2SpeechIWould = 5;
const int terminator2SpeechHellLive = 6;
const int terminator2SpeechChillOutDickWad = 7;
const int terminator2SpeechListenToMeVeryCarefully = 8;
const int terminator2SpeechTrustMe = 9;
const int terminator2SpeechHastaLaVistaBaby = 10;
const int terminator2SpeechIKnowNowWhyYouCry = 11;

// Folder 9
const int terminator2SfxBootFolder = 9;
const int terminator2SfxBoot1 = 1;
const int terminator2SfxBoot2 = 2;

// Runtimes of tracks in milliseconds
const int termniator1SfxVisionRuntime = 84000; // 1:min 40secs

// Push buttons
const int t1Quotes = 2;
const int t2Quotes = 4;

// LEDs
const int leftEye = 13; // LEFT LED EYE
const int rightEye = 12; // RIGHT LED EYE

boolean trackHasFinsishedPlaying = false;

void setup()
{
  
  pinMode(t1Quotes, INPUT);
  digitalWrite(t1Quotes,HIGH);

  pinMode(t2Quotes, INPUT);
  digitalWrite(t2Quotes,HIGH);

  pinMode(leftEye, OUTPUT);
  pinMode(rightEye, OUTPUT); 
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  // Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  setEqualizer();
  setVolume(30);
  playBoot();
  runBlink();
}

void runBlink() {
  delay(400);
  blinkWithDelay(50, 4);
  delay(300);
  blinkWithDelay(20, 8);
  delay(300);
  blinkWithDelay(30, 14);
  delay(500);
  blinkWithDelay(50, 4);
  delay(600);
  blinkWithDelay(150, 5);
  stopBlink();
}

void stopBlink() {
  digitalWrite(leftEye, HIGH);
  digitalWrite(rightEye, HIGH);
  playT1Da();
}

void blinkWithDelay(int delayInMilliseconds, int iteration) {
    for (int i = 0; i < iteration; i++) {
      digitalWrite(leftEye, HIGH);
      digitalWrite(rightEye, HIGH);
      delay(delayInMilliseconds);
      digitalWrite(leftEye, LOW);
      digitalWrite(rightEye, LOW);
      delay(delayInMilliseconds);
    }
}

void getTrackStatus() {
  delay(300); 
  int stt = myDFPlayer.readState();
  while ( stt == 529 || stt == 513 || stt == 512){ 
    stt = myDFPlayer.readState();
    Serial.println( stt );
    Serial.println( myDFPlayer.readType() );
    trackHasFinsishedPlaying = false;
    delay(300);
  }
  trackHasFinsishedPlaying = true;
}

void setEqualizer() {
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
}

void setVolume(int volume) {
  myDFPlayer.volume(volume);
}

void playMp3(int folder, int file) {
  Serial.print(printFilePath(folder, file));
  myDFPlayer.playFolder(folder, file);
}

String printFilePath(int folder, int file) {
  String path1 = "Folder: ";
  String path2 = " File:";
  String fullPath = String(path1 + folder + path2 + file);
  return fullPath;
}

void loop() {
  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); // Print the detail message from DFPlayer to handle different errors and states.
  }

  if (digitalRead(t1Quotes) == LOW) {
    playMp3(terminator1SpeechFolder, random(1, 7));
    delay(1000);
    Serial.println(F("T1 Quotes button pressed:"));
  }

  if (digitalRead(t2Quotes) == LOW) {
    playMp3(terminator2SpeechFolder, random(1, 11));
    delay(1000);
    Serial.println(F("T2 Quotes button pressed:"));
  }
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

// 1
void playBoot() {
   playMp3(terminator2SfxBootFolder, terminator2SfxBoot2);
}

// 2
void playT1Da() {
   playMp3(terminator1SfxDaDumFolder, terminator1SfxDa7);
   getTrackStatus();
   if (trackHasFinsishedPlaying == true) {
    delay(500);
    playHUD();
  }
}

// 3
void playHUD() {
  playMp3(terminator1SfxVisionFolder, terminator1SfxVision2);
  getTrackStatus();
   if (trackHasFinsishedPlaying == true) {
    delay(500);
    playT2ThemeTune();
  }
}

// 4
void playT2ThemeTune() {
  playMp3(terminator2MusicFolder, terminator2MusicTheme);
}

void playT1ThemeTune() {
  playMp3(terminator1MusicFolder, terminator1MusicTheme);
}
