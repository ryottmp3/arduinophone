/*
 * This is a test file for the keyboard for my phone.
 * Copyright © 2024 H. Ryott Glayzer
 * MIT LICENSE
 *
 *
 * mike = microphone/zero key.  bck = backspace/delete key, ret = carrige return key,
 * sh1 = left shift (up arrows key), sh2 = right shift (up arrows key)
 * 
 * Keyboard "row" mappings (outer ring)
 * 
 * ROW1 = PIN6    Q, E, R, U, O
 * ROW2 = PIN8    W, S, G, H, L
 * ROW3 = PIN18   T, Y, I, D, sym
 * ROW4 = PIN20   P, A, bck, ret, sh2
 * ROW5 = PIN21   alt, X, V, $, B
 * ROW6 = PIN22   spce, Z, C, M, N
 * ROW7 = PIN27   mike, sh1, F, K, J
 * 
 * Keyboard "column" mappings (inner circle)
 * 
 * COL1 = PIN7    Q, W, A, sym, alt, mike, space
 * COL2 = PIN9    S, D, X, sh1, E, P, Z
 * COL3 = PIN10   R, T, F, G, V, C, sh2
 * COL4 = PIN17   Y, U, ret, H, B, J, N
 * COL5 = PIN19   I, O, K, L, bck, M, $
 * 
 * Matrix scan technique:
 * 1. activate columns one at a time by pulling them low
 * 2. interrogate each row one at a time to see if it is pulled low
 * 
 * Columns and rows associated with their pin on the breakout board
 * in the keyboard matrix of the Q10 keyboard:
 * 
 *            COL1  COL2  COL3  COL4  COL5
 *            PIN7  PIN9  PIN10 PIN17 PIN19
 * ROW1 PIN6  Q     E     R     U     O
 * ROW2 PIN8  W     S     G     H     L
 * ROW3 PIN18 sym   D     T     Y     I
 * ROW4 PIN20 A     P     sh2   ret   bck
 * ROW5 PIN21 alt   Z     V     B     $
 * ROW6 PIN22 spc   X     C     N     M
 * ROW7 PIN27 mike  sh1   F     J     K
 *
 * * * * * * * * * * *
 * This program will read what is typed on the keyboard and print it to STDOUT
 */

// Arduino Pins for rows and cols
const byte row1 = 0;
const byte row2 = 1;
const byte row3 = 2;
const byte row4 = 3;
const byte row5 = 4;
const byte row6 = 5;
const byte row7 = 6;

const byte col1 = 7;
const byte col2 = 8;
const byte col3 = 9;
const byte col4 = 10;
const byte col5 = 11;


void setup() {
  // Setup code.
  Serial.begin(9600);  // Open the serial port at 9600 bps:

  // Set the cols to high-Z outputs
  digitalWrite(col1, LOW);
  digitalWrite(col2, LOW);
  digitalWrite(col3, LOW);
  digitalWrite(col4, LOW);
  digitalWrite(col5, LOW);

  pinMode(col1, INPUT);
  pinMode(col2, INPUT);
  pinMode(col3, INPUT);
  pinMode(col4, INPUT);
  pinMode(col5, INPUT);

  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(row3, INPUT);
  pinMode(row4, INPUT);
  pinMode(row5, INPUT);
  pinMode(row6, INPUT);
  pinMode(row7, INPUT);

  digitalWrite(row1, HIGH);
  digitalWrite(row2, HIGH);
  digitalWrite(row3, HIGH);
  digitalWrite(row4, HIGH);
  digitalWrite(row5, HIGH);
  digitalWrite(row6, HIGH);
  digitalWrite(row7, HIGH);

}

char oldchr = 0;
byte shiftock = 0;
byte shiftlockchanged = 0;
unsigned long time = 0;
byte displaychanged = 0;
byte curline = 0;

void loop() {
  // Assign OFF states to mod keys
  byte alt = 0;
  byte sym = 0;
  byte shift = 0;
  byte shl = 0;
  byte shr = 0;
  char chr = 0;
  char symb = 0;

  // figure out the current scan code, if any, and any modifier keys, if any

  pinMode(col1, OUTPUT);
  digitalWrite(col1, LOW);

  if (digitalRead(row1)==0) {chr = 'Q'; symb='#';}
  if (digitalRead(row2)==0) {chr = 'W'; symb='1';}
  if (digitalRead(row3)==0) {sym = 1;}             // symbol modifier key
  if (digitalRead(row4)==0) {chr = 'A'; symb='*';}
  if (digitalRead(row5)==0) {alt = 1;}             // alt modifier key - unimplemented
  if (digitalRead(row6)==0) {chr = ' '; symb=' ';}
  if (digitalRead(row7)==0) {chr = '~'; symb='0';}

  pinMode(col1, INPUT);
  pinMode(col2, OUTPUT);
  digitalWrite(col2, LOW);

  if (digitalRead(row1)==0) {chr = 'E'; symb='2';}
  if (digitalRead(row2)==0) {chr = 'S'; symb='4';}
  if (digitalRead(row3)==0) {chr = 'D'; symb='5';}
  if (digitalRead(row4)==0) {chr = 'P'; symb='@';}
  if (digitalRead(row5)==0) {chr = 'X'; symb='8';}
  if (digitalRead(row6)==0) {chr = 'Z'; symb='7';}
  if (digitalRead(row7)==0) {shift = 1; shl = 1;}  // shift modifier key

  pinMode(col2, INPUT);
  pinMode(col3, OUTPUT);
  digitalWrite(col3, LOW);

  if (digitalRead(row1)==0) {chr = 'R'; symb='3';}
  if (digitalRead(row2)==0) {chr = 'G'; symb='/';}
  if (digitalRead(row3)==0) {chr = 'T'; symb='(';}
  if (digitalRead(row4)==0) {shift = 1; shr = 1;}  // shift modifier key
  if (digitalRead(row5)==0) {chr = 'V'; symb='?';}
  if (digitalRead(row6)==0) {chr = 'C'; symb='9';}
  if (digitalRead(row7)==0) {chr = 'F'; symb='6';}

  pinMode(col3, INPUT);
  pinMode(col4, OUTPUT);
  digitalWrite(col4, LOW);

  if (digitalRead(row1)==0) {chr = 'U'; symb='_';}
  if (digitalRead(row2)==0) {chr = 'H'; symb=':';}
  if (digitalRead(row3)==0) {chr = 'Y'; symb=')';}
  if (digitalRead(row4)==0) {chr = '|'; symb='|';} // this should be a CR but I am substituting a pipe for CR in this implementation
  if (digitalRead(row5)==0) {chr = 'B'; symb='!';}
  if (digitalRead(row6)==0) {chr = 'N'; symb=',';}
  if (digitalRead(row7)==0) {chr = 'J'; symb=';';}

  pinMode(col4, INPUT);
  pinMode(col5, OUTPUT);
  digitalWrite(col5, LOW);

  if (digitalRead(row1)==0) {chr = 'O'; symb='+';}
  if (digitalRead(row2)==0) {chr = 'L'; symb='"';}
  if (digitalRead(row3)==0) {chr = 'I'; symb='-';}
  if (digitalRead(row4)==0) {chr = 8;}            // backspace
  if (digitalRead(row5)==0) {chr = '$'; symb='`';}
  if (digitalRead(row6)==0) {chr = 'M'; symb='.';}
  if (digitalRead(row7)==0) {chr = 'K'; symb='\'';}

  pinMode(col5, INPUT);

  if (chr != oldchr)
    if (chr==8)    // Deal with backspace
    {
      if ((pos > 0) || (curline > 0)) // don't underflow our buffer
      {
          if (pos==0) {pos=20; curline--;}
          buf[curline][--pos] = 0;
          time = millis();
          displaychanged = 1;
      }
    }
    else if (chr !=0)
    {
      if (curline < 6) // don't overflow our buffer
      {
        if (sym==1) // if the symbol key is pressed, put it in the buff as a symbol
          buf[curline][pos] = symb;
        // enter raw/upper case character if shift is selected or it is not a shiftable character
        else if (shift==1 || shiftlock==1 || chr=='$' || chr==' ' || chr=='~' || chr == 13)
          buf[curline][pos] = chr;
        // otherwise enter as a lower case character
        else
          buf[curline][pos] = (chr+32);

        // advance end of buffer
        buf[curline][++pos] = 0;
        if (pos>19) {curline++; pos=0;}
        time = millis();
        displaychanged = 1;
      }
    }

  // Pressing both shift keys together is taken as a shift lock operation

  if (shl == 1 && shr == 1 && shiftlockchanged == 0)
  {
    shiftlock = (shiftlock==0)?1:0;
    shiftlockchanged = 1;  // prevent multiple shift lock activations
  }

  // release shift lock multi-activation production when either shift key is released.
  if ((shl == 0) || (shr == 0))
    shiftlockchanged = 0;

  oldchr = chr; // remember old character so we don't have a high keyboard repeat rate

  // however, allow repeat if there has been no change in keypress in 200ms by clearing old character

  if ((millis()-time)>200)
  {
    oldchr = 0;
    time = millis();
  }

  // Print char to Serial
  Serial.print(chr)
}
