/*
  FlexiTimer2:
  Arduino library to use timer 2 with a configurable resolution.
  Based on MsTimer2 by Javier Valencia. It is called FlexiTimer2 because it
  is based on MsTimer2, but offers more flexibility,
  since it has a configurable timer resolution.
  MsTimer2 library: http://www.arduino.cc/playground/Main/MsTimer2

  For more details on FlexiTimer2 see:
  http://www.arduino.cc/playground/Main/FlexiTimer2
  https://github.com/wimleers/flexitimer2

*/

#include <FlexiTimer2.h>


const double timer_t = 1.0 / 10000;//タイマー割込み周期s

int pulse[14];

void SdigitalWrite(int pin, bool state) {
  //PORT- |= _BV(-);
  if (state == true) {
    if (pin == 2)PORTE |= _BV(4);
    if (pin == 3)PORTE |= _BV(5);
    if (pin == 4)PORTG |= _BV(5);
    if (pin == 5)PORTE |= _BV(3);
    if (pin == 6)PORTH |= _BV(3);
    if (pin == 7)PORTH |= _BV(4);
    if (pin == 8)PORTH |= _BV(5);
    if (pin == 9)PORTH |= _BV(6);
    if (pin == 10)PORTB |= _BV(4);
    if (pin == 11)PORTB |= _BV(5);
    if (pin == 12)PORTB |= _BV(6);
    //if (pin == 13)PORTB |= _BV(7);
    if (pin == 13)digitalWrite(13, HIGH);
  }
  if (state == false) {
    if (pin == 2)PORTE &= ~_BV(4);
    if (pin == 3)PORTE &= ~_BV(5);
    if (pin == 4)PORTG &= ~_BV(5);
    if (pin == 5)PORTE &= ~_BV(3);
    if (pin == 6)PORTH &= ~_BV(3);
    if (pin == 7)PORTH &= ~_BV(4);
    if (pin == 8)PORTH &= ~_BV(5);
    if (pin == 9)PORTH &= ~_BV(6);
    if (pin == 10)PORTB &= ~_BV(4);
    if (pin == 11)PORTB &= ~_BV(5);
    if (pin == 12)PORTB &= ~_BV(6);
    //if (pin == 13)PORTB &= _BV(7);
    if (pin == 13)digitalWrite(13, LOW);
  }
}

void flash()
{
  static long timer[14];
  static int flag[14];

  for (int i = 2; i < 14; i++) {
    timer[i] += 100; 
    if (timer[i] <= 1500) {
      if (flag[i] == 0) {
        SdigitalWrite(i, HIGH);
        flag[i] = 1;
      }
    }
    else if (timer[i] <= 10000) {
      if (flag[i] == 1) {
        SdigitalWrite(i, LOW);
        flag[i] = 0;
      }
    }
    else timer[i] = 0;
  }

}




void setup()
{
  for (int i = 2; i < 14; i++)pinMode(i, OUTPUT);
  FlexiTimer2::set(1, timer_t, flash); // call every 1ms "ticks"
  FlexiTimer2::start();
  Serial.begin(9600);
}

void loop()
{
  for (int i = 2; i < 14; i++)pulse[i] = 1500;
  //Serial.println(timer_t_u);
}
