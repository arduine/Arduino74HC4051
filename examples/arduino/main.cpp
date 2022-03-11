/*
 * Copyright (C) 2022. sollyu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <Arduino.h>

#include <Arduino74HC4067.h>

#ifdef ARDUINO_ARCH_ESP8266
#define GPIO_SIG    17      // ADC
#define GPIO_EN     05      // D1
#define GPIO_S0     04      // D2
#define GPIO_S1     00      // D3
#define GPIO_S2     02      // D4
#define GPIO_S3     14      // D5
#elif ARDUINO_ARCH_ESP32
#define GPIO_SIG    14      // D14
#define GPIO_EN     21      // D21
#define GPIO_S0     19      // D19
#define GPIO_S1     18      // D18
#define GPIO_S2      5      // D5
#define GPIO_S3      4      // D4
#endif

static Arduino74HC4067 s74HC4067(GPIO_SIG, GPIO_EN, GPIO_S0, GPIO_S1, GPIO_S2, GPIO_S3);

void setup() {
    s74HC4067.setup();
    s74HC4067.setEnabled(true);
}

void loop() {
    auto value = s74HC4067.analogRead(Arduino74HC4067::CHANNEL::C0);
    Serial.printf("channel value %d", value);
    delay(3000);

    s74HC4067.analogWrite(Arduino74HC4067::CHANNEL::C0, 800);
}