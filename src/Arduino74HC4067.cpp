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

#include "Arduino74HC4067.h"

Arduino74HC4067::Arduino74HC4067(uint8_t gpioSIG, uint8_t gpioEn, uint8_t gpioS0, uint8_t gpioS1, uint8_t gpioS2, uint8_t gpioS3) :
        mGpioSig(gpioSIG), mGpioEn(gpioEn), mGpioS0(gpioS0), mGpioS1(gpioS1), mGpioS2(gpioS2), mGpioS3(gpioS3), mPinStateCallback(nullptr) {
}

Arduino74HC4067::Arduino74HC4067(uint8_t gpioSIG, const std::function<void(bool, bool, bool, bool)> &callback) :
        mGpioSig(gpioSIG), mGpioEn(__ARDUINO_74HC4067_NOP_GPIO), mGpioS0(__ARDUINO_74HC4067_NOP_GPIO), mGpioS1(__ARDUINO_74HC4067_NOP_GPIO), mGpioS2(__ARDUINO_74HC4067_NOP_GPIO), mGpioS3(__ARDUINO_74HC4067_NOP_GPIO), mPinStateCallback(callback) {
}

void Arduino74HC4067::setup() {
    if (mPinStateCallback == nullptr) {
        pinMode(mGpioEn, OUTPUT);
        pinMode(mGpioS0, OUTPUT);
        pinMode(mGpioS1, OUTPUT);
        pinMode(mGpioS2, OUTPUT);
        pinMode(mGpioS3, OUTPUT);
        mPinStateCallback = [&](bool s0, bool s1, bool s2, bool s3) {
            ::digitalWrite(mGpioS0, s0 ? HIGH : LOW);
            ::digitalWrite(mGpioS1, s1 ? HIGH : LOW);
            ::digitalWrite(mGpioS2, s2 ? HIGH : LOW);
            ::digitalWrite(mGpioS3, s3 ? HIGH : LOW);
        };
    }
}

bool Arduino74HC4067::getEnabled() {
    if (mGpioEn == __ARDUINO_74HC4067_NOP_GPIO)
        return false;
    return ::digitalRead(mGpioEn) == LOW;
}

void Arduino74HC4067::setEnabled(bool enabled) {
    if (mGpioEn == __ARDUINO_74HC4067_NOP_GPIO)
        return;
    ::digitalWrite(mGpioEn, enabled ? LOW : HIGH);
}

int Arduino74HC4067::analogRead(const Arduino74HC4067::CHANNEL &channel) {
    mPinStateCallback(bitRead(channel, 3), bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    return ::analogRead(mGpioSig);
}

bool Arduino74HC4067::digitalRead(const Arduino74HC4067::CHANNEL &channel) {
    mPinStateCallback(bitRead(channel, 3), bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    return ::digitalRead(mGpioSig) == HIGH;
}

void Arduino74HC4067::digitalWrite(const Arduino74HC4067::CHANNEL &channel, bool value) {
    mPinStateCallback(bitRead(channel, 3), bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    ::digitalWrite(mGpioSig, value ? HIGH : LOW);
}

void Arduino74HC4067::analogWrite(const Arduino74HC4067::CHANNEL &channel, int value) {
    mPinStateCallback(bitRead(channel, 3), bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    ::analogWrite(mGpioSig, value);
}




