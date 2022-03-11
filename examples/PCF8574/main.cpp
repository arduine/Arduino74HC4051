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

#include <ArduinoPCF8574.h>
#include <Arduino74HC4067.h>

#ifdef ARDUINO_ARCH_ESP8266
#define GPIO_SIG    17      // ADC
#elif ARDUINO_ARCH_ESP32
#define GPIO_SIG    14      // D14
#endif

#define GPIO_EN     ArduinoPCF8574::PIN::P0
#define GPIO_S0     ArduinoPCF8574::PIN::P1
#define GPIO_S1     ArduinoPCF8574::PIN::P2
#define GPIO_S2     ArduinoPCF8574::PIN::P3
#define GPIO_S3     ArduinoPCF8574::PIN::P4

static ArduinoPCF8574  sPCF8574(ArduinoPCF8574::JUMP::J32);
static Arduino74HC4067 s74HC4067(GPIO_SIG, [](bool s0, bool s1, bool s2, bool s3) {
    auto state = sPCF8574.read()
            .set(GPIO_S0, s0)
            .set(GPIO_S1, s1)
            .set(GPIO_S2, s2)
            .set(GPIO_S3, s3);
    sPCF8574.write(state);
});

void setup() {
    sPCF8574.setup();
    s74HC4067.setup();
    sPCF8574.write(sPCF8574.read().set(GPIO_EN, false));    // 设置EN接口为低电平表示开启
}

void loop() {
    auto value = s74HC4067.analogRead(Arduino74HC4067::CHANNEL::C0);
    Serial.printf("channel value %d", value);
    delay(3000);
}