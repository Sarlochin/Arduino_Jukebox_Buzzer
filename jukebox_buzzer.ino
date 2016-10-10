/*
  PublicInfo:
  Jukebox_Buzzer by Jan
  Project started: 10.11.2015
  Versions+Changes:
  Public: yes
  GitHub: https://github.com/Sarlochin/Arduino_Jukebox_Buzzer
  Publisher: Sarlochin


  For using a 7 Segment Display use the following Pinout:

      middle pin (lower side) is ground connect with 220 Ohm resistor!
      the middle pins are ground
      Pins are connected starting from 1 going up

      e f G h i
          8.
      a b G c d
*/

#define using_segment_display 0


#define minimal_Delay_value 60
#define maximal_Delay_value 200

#define minimal_Pitch_value -4
#define maxiaml_Pitch_value 3

//Define the Pins
const int Poti_Speed_pin = A7;
const int Poti_Pitch_pin = A6;
const int start_button_Pin = 2;  //Pin for Start Button
const int stop_button_Pin = 3;
const int next_song_button_Pin = 5;


int current_note = 0;
bool tone_marker = 0;
unsigned long previous_delaytime = 0;

int return_of_play_music = 0;


#define ledPin1  13    //Pin for LED5
#define ledPin2  12    //Pin for LED2
#define buzzerPin  4  //Pin for the ActiveBuzzer


//Defines for Segment Display

const int vll = 1; //Vertical Left Lower Segment 'a'
const int hl = 2; //Horizontal Lower Segment 'b'
const int vrl = 3; //Vertical Right Lower Segment  'c'
const int dd = 4; //Decimal Dot Segment  'd'
const int hm = 5; //Horizontal Middle Segment 'e'
const int vlu = 6; //Vertical Left Upper Segment 'f'
const int hu = 7; //Horizontal Upper Segment 'h'
const int vru = 8; //Vertical Right Uper Segment 'i'

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


//Star Wars Imperial March
int StarWars_musiC[] = {
  0, A4, A4, A4, F4, C5, A4, F4, C5, A4, pause, E5, E5, E5, F5, C5, GI4, F4, C5, A4, pause,
  A5, A4, A4, A5, GI5, G5, FI5, F5, FI5, pause, AI4, DI5, D5, CI5, C5, B4, C5, pause,
  F4, GI4, F4, A4, C5, A4, C5, E5, pause,
  A5, A4, A4, A5, GI5, G5, FI5, F5, FI5, pause, AI4, DI5, D5, CI5, C5, B4, C5, pause,
  F4, GI4, F4, C5, A4, F4, C5, A4, pause
};

int StarWars_delayS[] = {
  0, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500,
  500, 300, 150, 500, 325, 175, 125, 125, 250, 325, 250, 500, 325, 175, 125, 125, 250, 350,
  250, 500, 350, 125, 500, 375, 125, 650, 500,
  500, 300, 150, 500, 325, 175, 125, 125, 250, 325, 250, 500, 325, 175, 125, 125, 250, 350,
  250, 500, 375, 125, 500, 375, 125, 650, 650
};


//Mario Main Music
int Mario_Main_Theme_music[] = {
  0, 7, E7, pause, E7, pause, C7, E7, pause, G7, pause, pause,  pause, G6, pause, pause, pause, C7, pause, pause, G6, pause, pause, E6, pause, pause, A6, pause, B6, pause, AI6, A6, pause, G6, E7, G7, A7, pause, F7, G7, pause, E7, pause, C7, D7, B6, pause, pause, C7, pause, pause, G6, pause, pause, E6, pause, pause, A6, pause, B6, pause, AI6, A6, pause, G6, E7, G7, A7, pause, F7, G7, pause, E7, pause, C7, D7, B6, pause, pause
};

int Mario_Main_Theme_delayS[] = {
  0, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 111, 111, 111, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 111, 111, 111, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83
};

//Mario StarmanTheme
int Mario_Starman_Theme_musiC[] = {
  0, F5, F5, F5, D5, F5, pause, F5, D5, F5, D5, F5, E5, E5, E5, C5, E5, pause, E5, C5, E5, C5, E5, F5, F5, F5, D5, F5, pause, F5, D5, F5, D5, F5, E5, E5, E5, C5, E5, pause, E5, C5, E5, C5, E5, F5, F5, F5, D5, F5, pause, F5, D5, F5, D5, F5, E5, E5, E5, C5, E5, pause, E5, C5, E5, C5, E5, pause
};

int Mario_Starman_Theme_delayS[] = {
  0, 100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 100, 50, 100, 50, 50, 50, 100, 100, 100, 100, 50, 50, 50, 100, 50, 50, 50, 100, f
};


//Axel F
int Axel_F_musiC[] = {
  0, F5, pause, GI5, pause, F5, F5, AI5, F5, DI5, F5, pause, C6, pause, F5, F5, CI6, C6, GI5, F5, C6, F6, F5, DI5, DI5, C5, G5, F5, pause, //Line 1 high voice
  F5, pause, GI5, pause, F5, F5, AI5, F5, DI5, F5, pause, C6, pause, F5, F5, CI6, C6, GI5, F5, C6, F6, F5, DI5, DI5, C5, G5, F5, pause, //Line 2 high voice
  F3, pause, F4, pause, DI4, DI5, C4, C5, DI5, F3, pause, F4, pause, pause, C3, C4, DI4, F4, CI3, pause, CI4, pause, DI3, DI4, C3, C4, DI4, F4, F3, pause, pause, DI4, C4, B3, GI3,  //Line 3 low voice
  F3, pause, F4, pause, DI4, DI5, C4, C5, DI5, F3, pause, F4, pause, pause, C3, C4, DI4, F4, CI3, pause, CI4, pause, DI3, DI4, C3, C4, DI4, F4, F3, pause, pause
}; //Line 4 low voice

int Axel_F_delayS[] = {
  0, e, e, e, s, e, s, e, e, e, e, e, e, s, e, s, e, e, e, e, e, e, s, e, s, e, e, h, h,  //Line 1 high voice
  e, e, e, s, e, s, e, e, e, e, e, e, s, e, s, e, e, e, e, e, e, s, e, s, e, e, h, h,  //Line 2 high voice
  e, e, e, s, e, s, e, e, e, e, e, e, e, s, s, e, e, e, e, e, e, s, e, s, e, e, e, e, e, q, s, e, s, e, e,  //Line 3 low voice
  e, e, e, s, e, s, e, e, e, e, e, e, e, s, s, e, e, e, e, e, e, s, e, s, e, e, e, e, e, q, f
}; //Line 4 low voice


//Davy Jones Theme
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


//Pirates of the Caribbean Theme
int Pirates_Of_The_Caribbean_musiC [] = {
  0, A4, C5, D5, D5, D5, E5, F5, F5, F5, G5, E5, E5, D5, C5, C5, D5, pause, //Line 1
  A4, C5, D5, D5, D5, E5, F5, F5, F5, G5, E5, E5, D5, C5, D5, pause, //Line 2
  A4, C5, D5, D5, D5, F5, G5, G5, G5, A5, AI5, AI5, A5, G5, A5, D5, pause, //Line 3
  D5, E5, F5, F5, G5, A5, D5, pause, D5, F5, E5, E5, F5, D5, E5, pause, //Line 4

  A5, C6, D6, D6, D6, E6, F6, F6, F6, G6, E6, E6, D6, C6, C6, D6, pause, //Line 5
  A5, C6, D6, D6, D6, E6, F6, F6, F6, G6, E6, E6, D6, C6, D6, pause,  //Line 6
  A5, C6, D6, D6, D6, F6, G6, G6, G6, A6, AI6, AI6, A6, G6, A6, D6, pause, //Line 7
  D6, E6, F6, F6, G6, A6, D6, pause,  //Line 8
  D6, F6, E6, E6, D6, CI6, D6, D6, E6, F6, F6, G6, A6, pause, //Line 9
  pause, F6, E6, A5, pause, AI6, pause, F6, D6, //Line 10
  AI5, pause, E5, pause, F5, pause, F5, pause, E6, G6, A6, A6, A6, AI6, A6, pause, //Line 11
  G6, G6, G6, G6, A6, pause, A6, A6, A6, AI6, A6, pause, G6, F6, E6, D6, pause, //Line 12
  D5, E5, F5, G5, A5, G5, F5, E5, F5, G5, A5, G5, pause, F5, G5, A5, G5, F5, //Line 13
  E5, F5, E5, D5, C5, D5, pause, D6, E6, F6, E6, F6, G6, F6, G6, //Line 14
  A6, G6, F6, D6, pause, D6, E6, F6, G6, A6, AI6, D6, G6, F6, G6, E6, D6, E6, CI6, //Line 15
  A6, pause, AI6, pause, A6, A6, A6, A6, G6, pause, G6, pause, F6, pause, //Line 16
  E6, F6, E6, E6, D6, pause, D6, E6, F6, A6, pause, D6, E6, F6, AI6, pause, D6, E6, F6, A6, A6, C7, //Line 17
  A6, G6, pause, G6, pause, F6, pause, E6, F6, E6, D6 //Line 18
};

int Pirates_Of_The_Caribbean_delayS [] = {
  0, e, e, q, q, e, e, q, q, e, e, q, q, e, e, e, e, q, //Line 1
  e, e, q, q, e, e, q, q, e, e, q, q, e, e, q, q, //Line 2
  e, e, q, q, e, e, q, q, e, e, q, q, e, e, e, e, q,  //Line 3
  e, e, q, q, q, e, e, q, e, e, q, q, e, e, q, q, //Line 4

  e, e, q, q, e, e, q, q, e, e, q, q, e, e, e, e, q, //Line 5
  e, e, q, q, e, e, q, q, e, e, q, q, e, e, q, q, //Line 6
  e, e, q, q, e, e, q, q, e, e, q, q, e, e, e, e, q, //Line 7
  e, e, q, q, q, e, e, q,  //Line 8
  e, e, q, q, e, e, q, q , q, q, q, q, q, q, //Line 9
  e, s, s, q, h, q, qe, e, e, //Line 10
  q, h, q, e, q, e, q, qe, s, s, q, q, q, s, s, h, //Line 11
  q, q, q, s, s, h, q, q, q, s, s, h, q, q, q, q, q, //Line 12
  e, e, h, e, e, q, q, q, q, q, q, qe, e, e, e, h, e, e, //Line 13
  q, q, q, h, q, qe, e, e, e, h, e, e, q, q, q, //Line 14
  q, q, q, qe, e, e, e, q, q, q, q, q, q, qe, e, q, qe, e, q, //Line 15
  q, h, q, h, q, q, q, e, e, h, q, h, q, h, //Line 16
  q, q, q, s, s, q, e, e, e, q, e, e, e, e, q, e, e, e, e, q, q, q, //Line 17
  s, s, h, q, h, q, h, q, q, q, hq //Line 18
};





int song = 0;
int prev_song = 0;

void setup()
{
  //Setup pin modes
  pinMode(buzzerPin, OUTPUT);  //Setting the input and output modes
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(start_button_Pin, INPUT);
  pinMode(stop_button_Pin, INPUT);
  pinMode(next_song_button_Pin, INPUT);

  if (using_segment_display)
  {
    pinMode (hu, OUTPUT);
    pinMode (vlu, OUTPUT);
    pinMode (vru, OUTPUT);
    pinMode (hm, OUTPUT);
    pinMode (vll, OUTPUT);
    pinMode (vrl, OUTPUT);
    pinMode (hl, OUTPUT);
    pinMode (dd, OUTPUT);
  }

  Serial.begin(9600); //Debug only
  Serial.println("Setup finished"); //Debug only
}

void loop()
{
  int sizeof_music = 0;

  if (digitalRead(start_button_Pin) == HIGH)
  {
    song = prev_song;
    while (song == prev_song)
    {
      song = random(1, 7);
    }
    prev_song = song;
  }

  switch (song)
  {
    case (0):
      return_of_play_music = 0;
      current_note = 0;
      break;

    case (1):

      Serial.println("Song 1: Star Wars");
      print_number_on_segment_display (song);

      sizeof_music = sizeof(StarWars_musiC) / sizeof(int);
      while ((!return_of_play_music))
      {
        return_of_play_music = play_music (StarWars_musiC, StarWars_delayS, sizeof_music);
        if (return_of_play_music)
        {
          if (return_of_play_music == 2)
          {
            return_of_play_music = 0;
            break;
          } else {
            song = 0;
            break;
          }
        }
      }
      break;

    case (2):

      Serial.println("Song 2: Mario Main Theme");
      print_number_on_segment_display (song);

      sizeof_music = sizeof(Mario_Main_Theme_music) / sizeof(int);
      while ((!return_of_play_music))
      {
        return_of_play_music = play_music (Mario_Main_Theme_music, Mario_Main_Theme_delayS, sizeof_music);
        if (return_of_play_music)
        {
          if (return_of_play_music == 2)
          {
            return_of_play_music = 0;
            break;
          } else {
            song = 0;
            break;
          }
        }
      }
      break;

    case (3):

      Serial.println("Song 3: Mario Starman Theme");
      print_number_on_segment_display (song);

      sizeof_music = sizeof(Mario_Starman_Theme_musiC) / sizeof(int);
      while ((!return_of_play_music))
      {
        return_of_play_music = play_music (Mario_Starman_Theme_musiC, Mario_Starman_Theme_delayS, sizeof_music);
        if (return_of_play_music)
        {
          if (return_of_play_music == 2)
          {
            return_of_play_music = 0;
            break;
          } else {
            song = 0;
            break;
          }
        }
      }
      break;


    case (4):

      Serial.println("Song 4: Axel F");
      print_number_on_segment_display (song);

      sizeof_music = sizeof(Axel_F_musiC) / sizeof(int);
      while ((!return_of_play_music))
      {
        return_of_play_music = play_music (Axel_F_musiC, Axel_F_delayS, sizeof_music);
        if (return_of_play_music)
        {
          if (return_of_play_music == 2)
          {
            return_of_play_music = 0;
            break;
          } else {
            song = 0;
            break;
          }
        }
      }
      break;


    case (5):

      Serial.println("Song 5: Davy Jones Theme");
      print_number_on_segment_display (song);

      sizeof_music = sizeof(Davy_Jones_musiC) / sizeof(int);
      while ((!return_of_play_music))
      {
        return_of_play_music = play_music (Davy_Jones_musiC, Davy_Jones_delayS, sizeof_music);
        if (return_of_play_music)
        {
          if (return_of_play_music == 2)
          {
            return_of_play_music = 0;
            break;
          } else {
            song = 0;
            break;
          }
        }
      }
      break;


    case (6):

      Serial.println("Song 6: Pirates of the Caribbean Theme");
      print_number_on_segment_display (song);

      sizeof_music = sizeof(Pirates_Of_The_Caribbean_musiC ) / sizeof(int);
      while ((!return_of_play_music))
      {
        return_of_play_music = play_music (Pirates_Of_The_Caribbean_musiC , Pirates_Of_The_Caribbean_delayS , sizeof_music);
        if (return_of_play_music)
        {
          if (return_of_play_music == 2)
          {
            return_of_play_music = 0;
            break;
          } else {
            song = 0;
            break;
          }
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
  int oktave = 0;
  int bpm = 0;
  int note_pitch = 0;
  int delay_between_notes = 0;

  // note_duration = (delayS[current_note] + ((analogRead(Poti_Speed_pin) >> 2) - delay_decrementer)); //Read the delay value from the Potentiometer (returns value from 0-1023 converted to the range from 0-255)

  bpm = map((analogRead(Poti_Speed_pin)), 0, 1023, minimal_Delay_value, maximal_Delay_value);

  note_duration = (bpm / 60) * delayS[current_note];

  if (note_duration <= 10)
  {
    note_duration = 10;
  }

  delay_between_notes = (note_duration + (note_duration >> 3));

/* Currently not Working

  oktave = map((analogRead(Poti_Pitch_pin)), 0, 1023, minimal_Pitch_value, maxiaml_Pitch_value);

  Serial.print("OKTAVE = ");
  Serial.println(oktave);


  note_pitch = musiC[current_note] + (oktave * 260);

  if (note_pitch <= 16)
  {
    note_pitch = 16;
  }

  if (note_pitch >= 7902)
  {
    note_pitch = 7902;
  }

  Serial.print("Pitch = ");
  Serial.println(note_pitch);
*/


  if (!tone_marker)
  {
    tone_marker = 1;
    tone(buzzerPin, musiC[current_note] , note_duration);  //Playing the note with calculated duration
  }

  if (current_delaytime - previous_delaytime >= delay_between_notes)
  {
    previous_delaytime = current_delaytime;
    tone_marker = 0;
    current_note++;

  }

  if ((digitalRead(next_song_button_Pin) == HIGH))
  {
    current_note = 0;
    song = random(1, 7);
    return (2);

  }


  if (current_note >= music_length || (digitalRead(stop_button_Pin) == HIGH))
  {
    Serial.println("returned 1");
    current_note = 0;
    return (1);
  } else {
    return (0);
  }



}
