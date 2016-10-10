//clears display
void cleardp()
{
  digitalWrite(vll, LOW);
  digitalWrite(hl, LOW);
  digitalWrite(vrl, LOW);
  digitalWrite(dd, LOW);
  digitalWrite(vru, LOW);
  digitalWrite(hu, LOW);
  digitalWrite(vlu, LOW);
  digitalWrite(hm, LOW);
}

void print_number_on_segment_display (int number)
{
  if(using_segment_display)
  {
  switch (number)
  {
    case (0):
      cleardp();
      digitalWrite(vll, HIGH);
      digitalWrite(vrl, HIGH);
      digitalWrite(vlu, HIGH);
      digitalWrite(vru, HIGH);
      digitalWrite(hu, HIGH);
      digitalWrite(hl, HIGH);
      break;
    case (1):
      cleardp();
      digitalWrite(vru, HIGH);
      digitalWrite(vrl, HIGH);
      break;
    case (2):
      cleardp();
      digitalWrite(hu, HIGH);
      digitalWrite(hm, HIGH);
      digitalWrite(hl, HIGH);
      digitalWrite(vru, HIGH);
      digitalWrite(vll, HIGH);
      break;
    case (3):
      cleardp();
      digitalWrite(hu, HIGH);
      digitalWrite(hm, HIGH);
      digitalWrite(hl, HIGH);
      digitalWrite(vru, HIGH);
      digitalWrite(vrl, HIGH);
      break;
    case (4):
      cleardp();
      digitalWrite(hm, HIGH);
      digitalWrite(vlu, HIGH);
      digitalWrite(vru, HIGH);
      digitalWrite(vrl, HIGH);
      break;
    case (5):
      cleardp();
      digitalWrite(hl, HIGH);
      digitalWrite(hm, HIGH);
      digitalWrite(hu, HIGH);
      digitalWrite(vlu, HIGH);
      digitalWrite(vrl, HIGH);
      break;
    case (6):
      cleardp();
      digitalWrite(hl, HIGH);
      digitalWrite(hm, HIGH);
      digitalWrite(vll, HIGH);
      digitalWrite(vrl, HIGH);
      digitalWrite(vlu, HIGH);
      digitalWrite(hu, HIGH);
      break;
    case (7):
      cleardp();
      digitalWrite(hu, HIGH);
      digitalWrite(vru, HIGH);
      digitalWrite(vrl, HIGH);
      break;
    case (8):
      cleardp();
      digitalWrite(hu, HIGH);
      digitalWrite(hm, HIGH);
      digitalWrite(hl, HIGH);
      digitalWrite(vlu, HIGH);
      digitalWrite(vru, HIGH);
      digitalWrite(vll, HIGH);
      digitalWrite(vrl, HIGH);
      break;
    case (9):
      cleardp();
      digitalWrite(hu, HIGH);
      digitalWrite(hm, HIGH);
      digitalWrite(hl, HIGH);
      digitalWrite(vlu, HIGH);
      digitalWrite(vru, HIGH);
      digitalWrite(vrl, HIGH);
      break;
  }
  }

}













