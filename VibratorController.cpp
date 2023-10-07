/*******************************************************************************
 * Copyright (c) 2020, 2022  Carnegie Mellon University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *******************************************************************************/

#include "VibratorController.h"

// keep the instance as static for callback
VibratorController * instance;

VibratorController::VibratorController(
  cabot::Handle & ch, int vib1_pin,
  int vib2_pin, int vib3_pin, int vib4_pin)
: SensorReader(ch)
{
  instance = this;

  vib_pin[0] = vib1_pin;
  vib_pin[1] = vib2_pin;
  vib_pin[2] = vib3_pin;
  vib_pin[3] = vib4_pin;

  ch.subscribe(0x20, [](const uint8_t msg) { instance->vibrations[0] = msg+1; });
  ch.subscribe(0x21, [](const uint8_t msg) { instance->vibrations[1] = msg+1; });
  ch.subscribe(0x22, [](const uint8_t msg) { instance->vibrations[2] = msg+1; });
  ch.subscribe(0x23, [](const uint8_t msg) { instance->vibrations[3] = msg+1; });
}

void VibratorController::init()
{
  for(int i = 0; i < 4; i++) {
    pinMode(vib_pin[i], OUTPUT);
    analogWrite(vib_pin[i], 0);
  }
}

void VibratorController::update() {
  for(int i = 0; i < 4; i++) {
    if (vibrations[i] > 0) {
      if (vibrations[i] == 1) {
        analogWrite(vib_pin[i], 0);
        vibrations[i] = 0;
      } else {
        analogWrite(vib_pin[i], 255);
        vibrations[i]--;
      }
    }
  }
}
