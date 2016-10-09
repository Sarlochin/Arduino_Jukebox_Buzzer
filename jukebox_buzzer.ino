/*
  PublicInfo:
  Jukebox_Buzzer by Jan
  Project started: 10.11.2015
  Versions+Changes:
  Public: yes
  GitHub: https://github.com/Sarlochin/Arduino_Jukebox_Buzzer
  Publisher: Sarlochin
*/


#define delay_decrementer 50  //Decrease the timings by a fixed value to be able to speed up the music with the potentiometer

//Define the Pins
const int Poti_Speed_pin = A7;
const int start_button_Pin = 2;  //Pin for Start Button
const int stop_button_Pin = 3;


int current_note = 0;
bool tone_marker = 0;
unsigned long previous_delaytime = 0;


#define ledPin1  13    //Pin for LED5
#define ledPin2  12    //Pin for LED2
#define buzzerPin  4  //Pin for the ActiveBuzzer

//Define the notes for the Music Array

#define  C0  16
#define CI0 17
#define D0  18
#define DI0 19
#define E0  21
#define F0  22
#define FI0 23
#define G0  25
#define GI0 26
#define A0  28
#define AI0 29
#define B0  31
#define C1  33
#define CI1 35
#define D1  37
#define DI1 39
#define E1  41
#define F1  44
#define FI1 46
#define G1  49
#define GI1 52
#define A1  55
#define AI1 58
#define B1  62
#define C2  65
#define CI2 69
#define D2  73
#define DI2 78
#define E2  82
#define F2  87
#define FI2 93
#define G2  98
#define GI2 104
#define A2  110
#define AI2 117
#define B2  123
#define C3  131
#define CI3 139
#define D3  147
#define DI3 156
#define E3  165
#define F3  175
#define FI3 185
#define G3  196
#define GI3 208
#define A3  220
#define AI3 233
#define B3  247
#define C4  262
#define CI4 277
#define D4  294
#define DI4 311
#define E4  330
#define F4  349
#define FI4 370
#define G4  392
#define GI4 415
#define A4  440
#define AI4 466
#define B4  494
#define C5  523
#define CI5 554
#define D5  587
#define DI5 622
#define E5  659
#define F5  698
#define FI5 740
#define G5  784
#define GI5 831
#define A5  880
#define AI5 932
#define B5  988
#define C6  1047
#define CI6 1109
#define D6  1175
#define DI6 1245
#define E6  1319
#define F6  1397
#define FI6 1480
#define G6  1568
#define GI6 1661
#define A6  1760
#define AI6 1865
#define B6  1976
#define C7  2093
#define CI7 2217
#define D7  2349
#define DI7 2489
#define E7  2637
#define F7  2794
#define FI7 2960
#define G7  3136
#define GI7 3322
#define A7  3520
#define AI7 3729
#define B7  3951
#define C8  4186
#define CI8 4435
#define D8  4699
#define DI8 4978
#define E8  5274
#define F8  5588
#define FI8 5920
#define G8  6272
#define GI8 6645
#define A8  7040
#define AI8 7459
#define B8  7902
#define pause 0

//Define the note delays

#define f 1000
#define h 500
#define hq 750
#define q 250
#define qe 375
#define e 125
#define s 63


//Arrays for music and timings: StarWars Imperial March

int StarWars_musiC[] = {
  A4, A4, A4, F4, C5, A4, F4, C5, A4, pause, E5, E5, E5, F5, C5, GI4, F4, C5, A4, pause,
  A5, A4, A4, A5, GI5, G5, FI5, F5, FI5, pause, AI4, DI5, D5, CI5, C5, B4, C5, pause,
  F4, GI4, F4, A4, C5, A4, C5, E5, pause,
  A5, A4, A4, A5, GI5, G5, FI5, F5, FI5, pause, AI4, DI5, D5, CI5, C5, B4, C5, pause,
  F4, GI4, F4, C5, A4, F4, C5, A4, pause
};

int StarWars_delayS[] = {
  500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500,
  500, 300, 150, 500, 325, 175, 125, 125, 250, 325, 250, 500, 325, 175, 125, 125, 250, 350,
  250, 500, 350, 125, 500, 375, 125, 650, 500,
  500, 300, 150, 500, 325, 175, 125, 125, 250, 325, 250, 500, 325, 175, 125, 125, 250, 350,
  250, 500, 375, 125, 500, 375, 125, 650, 650
};
/*
  int Mario_Main_Theme_music[] = {
  E7, E7, pause, E7, pause, C7, E7, pause, G7, pause, pause,  pause, G6, pause, pause, pause, C7, pause, pause, G6, pause, pause, E6, pause, pause, A6, pause, B6, pause, AI6, A6, pause, G6, E7, G7, A7, pause, F7, G7, pause, E7, pause, C7, D7, B6, pause, pause, C7, pause, pause, G6, pause, pause, E6, pause, pause, A6, pause, B6, pause, AI6, A6, pause, G6, E7, G7, A7, pause, F7, G7, pause, E7, pause, C7, D7, B6, pause, pause};

  int Mario_Main_Theme_delayS[] = {
  83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 111, 111, 111, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 111, 111, 111, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 500};*/

/*int Mario_Starman_Theme_musiC[] = {
  F5, F5, F5, D5, F5, pause, F5, D5, F5, D5, F5, E5, E5, E5, C5, E5, pause, E5, C5, E5, C5, E5, F5, F5, F5, D5, F5, pause, F5, D5, F5, D5, F5, E5, E5, E5, C5, E5, pause, E5, C5, E5, C5, E5, F5, F5, F5, D5, F5, pause, F5, D5, F5, D5, F5, E5, E5, E5, C5, E5, pause, E5, C5, E5, C5, E5, pause};

  int Mario_Starman_Theme_delayS[] = {
  100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, f};
*/
int Davy_Jones_musiC[] = {
  0, D5, E5, F5, G5, A5, AI5, A5, D5, //Line 1
  A5, AI5, C6, D6, A5, G5, A5, pause, AI5, C6, A5, F5, G5, A5, F5, D5, E5, C5, A4, E5, D5, //Line 2
  D5, pause, E5, FI5, G5, A5, B5, C6, B5, E5, B5, C6, D6, E6, B5, A5, B5, C6, D6, //Line 3
  B5, G5, A5, B5, G5, E5, FI5, D5, B4, FI5, E5, E5, pause
}; //Line 4

int Davy_Jones_delayS[] = {
  0, h, q, h, q, h, q , h, q, //Line 1
  h, q, h, q, h, q, h, q, h, q, h, q, h, q, h, q, h, q, h, q, hq, //Line 2
  h, q, h, q, h, q, h, q, h, q, h, q, h, q, h, q, hq, h, q, //Line 3
  h, q, h, q, h, q, h, q, h, q, hq, h, f
}; //Line 4


int song = 0;

void setup()
{
  //Setup pin modes
  pinMode(buzzerPin, OUTPUT);  //Setting the input and output modes
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(start_button_Pin, INPUT);
  pinMode(stop_button_Pin, INPUT);
  Serial.begin(9600); //Debug only
  Serial.println("Setup finished"); //Debug only
}

int testmarker = 0;

void loop()
{
  int sizeof_music = 0;

  if (digitalRead(start_button_Pin) == HIGH)
  {
    song = random(1,3);
    Serial.print("Song= ");
    Serial.println(song);
  }

  switch (song)
  {
    case (0):
    Serial.println("Case 0");
    testmarker=0;
    current_note=0;
      break;

    case (1):

      Serial.println("Song 1");
      sizeof_music = sizeof(Davy_Jones_musiC) / sizeof(int);
      while ((!testmarker))
      {
        testmarker = play_music (Davy_Jones_musiC, Davy_Jones_delayS, sizeof_music);
        if (testmarker)
        {
          song = 0;
          break;
        }
      }
      break;

    case (2):

      Serial.println("Song 2");
      sizeof_music = sizeof(StarWars_musiC) / sizeof(int);
      while ((!testmarker))
      {
        testmarker = play_music (StarWars_musiC, StarWars_delayS, sizeof_music);
        if (testmarker)
        {
          song = 0;
          break;
        }
      }
      break;

    default:
      song = 0;
      break;
  }
}


int play_music (int musiC[], int delayS[], int music_length)
{
  unsigned long current_delaytime = millis();
  int note_duration = 0;
  int delay_between_notes = 0;

  note_duration = (delayS[current_note] + ((analogRead(Poti_Speed_pin) >> 2) - delay_decrementer)); //Read the delay value from the Potentiometer (returns value from 0-1023 converted to the range from 0-255)

  if (note_duration <= 10)
  {
    note_duration = 10;
  }

  delay_between_notes = (note_duration + (note_duration >> 3));

  if (!tone_marker)
  {
    tone_marker = 1;
    tone(buzzerPin, musiC[current_note], note_duration);  //Playing the note with calculated duration
  }

  if (current_delaytime - previous_delaytime >= delay_between_notes)
  {
    previous_delaytime = current_delaytime;
    tone_marker = 0;
    current_note++;

  }

  if (current_note >= music_length || (digitalRead(stop_button_Pin)==HIGH))
  {
    Serial.println("returned 1");
    current_note = 0;
    return (1);
  } else {
    return (0);
  }

}
