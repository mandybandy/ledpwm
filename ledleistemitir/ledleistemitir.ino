#include <IRremote.h>

const int rpin = 9;
const int gpin = 6;
const int bpin = 5;


const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

short brightness = 7;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  randomSeed(analogRead(0));

  pinMode(rpin, OUTPUT); //set pin as OUTPUT
  pinMode(gpin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(RECV_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RECV_PIN), irchange, CHANGE);
}

void irchange() {
  detachInterrupt(digitalPinToInterrupt(RECV_PIN));
  if (irrecv.decode(&results)) {
    irrecv.resume();
  }
  attachInterrupt(digitalPinToInterrupt(RECV_PIN), irchange, CHANGE);
}

void loop() {
  switch (results.value)
  {
    case 16748655:     if (brightness < 10) {
        brightness++;
      }     break;
    case 16758855:     if (brightness > 1)  {
        brightness--;
      }     break;
    case 16775175:      brightness = 0;       break;
    case 16756815:      brightness = 8;       break;
    case 16750695:      rgb(255, 0, 0);       break;
    case 16767015:      rgb(0, 255, 0);       break;
    case 16746615:      rgb(0, 0, 255);       break;
    case 16754775:      rgb(255, 255, 255);   break;
    case 16771095:      rgb(255, 140 , 0);    break;
    case 16730295:      rgb(150, 250, 150);   break;
    case 16738455:      rgb(50, 10, 255);     break;
    case 16757325:      randomblink();        break;
    case 16712445:      rgb(255, 150, 0);     break;
    case 16724685:      rgb(50, 250, 180);    break;
    case 16720095:      rgb(150, 30, 255);    break;
    case 16711935:      strobe();             break;
    case 16732335:      rgb(255, 160, 10);    break;
    case 16742535:      rgb(150, 255, 240);   break;
    case 16740495:      rgb(200, 50, 255);    break;
    case 16734375:      pulse();              break;
    case 16726215:      rgb(255, 230, 170);   break;
    case 16722135:      rgb(100, 240, 255);   break;
    case 16773135:      rgb(250, 80, 255);    break;
    case 16724175:      favs();               break;
    default:            rgb(0, 0, 0);
  }
}

void rgb(int r, int g, int b) {
  analogWrite(rpin * brightness / 10, r);
  analogWrite(gpin * brightness / 10, g);
  analogWrite(bpin * brightness / 10, b);
}
void pulse() {
  switch (random(0, 2)) {
    case 0:
      redpulse();
      break;
    case 1:
      greenpulse();
      break;
    case 2:
      bluepulse();
      break;
    default:
      pulse();
      break;
  }
}
void redpulse() {
  int x = 1;
  for (int i = 0; i > -1; i = i + x) {
    delay(20);
    rgb(i, 0, 0);
    if (i == 255) {
      x = -1;  // switch direction at peak
    }
  }
}

void greenpulse() {
  int x = 1;
  for (int i = 0; i > -1; i = i + x) {
    delay(20);
    rgb(0, i, 0);
    if (i == 255) {
      x = -1;  // switch direction at peak
    }
  }
}

void bluepulse() {
  int x = 1;
  for (int i = 0; i > -1; i = i + x) {
    delay(20);
    rgb(0, 0, i);
    if (i == 255) {
      x = -1;  // switch direction at peak
    }
  }
}

void favs() {
  rgb(50, 170, 255); //türkis
  delay(3000);
  rgb(255, 100, 100);
  delay(3000);
  rgb(255, 20, 255);
  delay(3000);
}

void randomblink() {
  rgb(random(0, 255), random(0, 255), random(254, 255));
  delay(1000);
}

void strobe() {
  int x = 1;
  int y = 1;
  int z = 1;
  for (int i = 0; i > -1; i = i + x) {
    delay(20);
    rgb(i, 0, 0);
    if (i == 255) {
      x = -1;  // switch direction at peak
    }
  }
  for (int j = 100; j > -1; j = j + y) {
    delay(20);
    rgb(0, j, 0);
    if (j == 255) {
      y = -1;  // switch direction at peak
    }
  }
  for (int k = 255; k > -1; k = k + z) {
    delay(20);
    rgb(0, 0, k);
    if (k == 255) {
      z = -1;  // switch direction at peak
    }
  }
}
