// Copyright (C) 2022. sollyu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "Arduino74HC4051.h"

Arduino74HC4051::Arduino74HC4051(uint8_t pinX, uint8_t pinINH, uint8_t pinA, uint8_t pinB, uint8_t pinC) :
        mPinX(pinX), mPinINH(pinINH), mPinA(pinA), mPinB(pinB), mPinC(pinC),
        mPinStateCallback(nullptr) {
}

Arduino74HC4051::Arduino74HC4051(uint8_t pinX, const OnCallback &callback) :
        mPinX(pinX), mPinINH(__ARDUINO_74HC4051_NOP_GPIO), mPinA(__ARDUINO_74HC4051_NOP_GPIO),
        mPinB(__ARDUINO_74HC4051_NOP_GPIO), mPinC(__ARDUINO_74HC4051_NOP_GPIO), mPinStateCallback(callback) {
}

void Arduino74HC4051::setup() {
    ::pinMode(mPinX, mLatestPinXMode);
    if (mPinStateCallback == nullptr) {
        pinMode(mPinINH, OUTPUT);
        pinMode(mPinA, OUTPUT);
        pinMode(mPinB, OUTPUT);
        pinMode(mPinC, OUTPUT);
        mPinStateCallback = &Arduino74HC4051::onDefaultCallback;
    }
}

bool Arduino74HC4051::getEnabled() {
    if (mPinINH == __ARDUINO_74HC4051_NOP_GPIO)
        return false;
    return ::digitalRead(mPinINH) == LOW;
}

void Arduino74HC4051::setEnabled(bool enabled) {
    if (mPinINH == __ARDUINO_74HC4051_NOP_GPIO)
        return;
    ::digitalWrite(mPinINH, enabled ? LOW : HIGH);
}

int Arduino74HC4051::analogRead(const Arduino74HC4051::CHANNEL &channel) {
    if (mLatestPinXMode != INPUT_PULLUP)
        ::pinMode(mPinX, INPUT_PULLUP);
    mLatestPinXMode = INPUT_PULLUP;
    (this->*(mPinStateCallback))(bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    return ::analogRead(mPinX);
}

bool Arduino74HC4051::digitalRead(const Arduino74HC4051::CHANNEL &channel) {
    (this->*(mPinStateCallback))(bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    if (mLatestPinXMode != INPUT_PULLUP)
        ::pinMode(mPinX, INPUT_PULLUP);
    mLatestPinXMode = INPUT_PULLUP;
    return ::digitalRead(mPinX) == HIGH;
}

void Arduino74HC4051::digitalWrite(const Arduino74HC4051::CHANNEL &channel, bool value) {
    (this->*(mPinStateCallback))(bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    if (mLatestPinXMode != OUTPUT)
        ::pinMode(mPinX, OUTPUT);
    mLatestPinXMode = OUTPUT;
    ::digitalWrite(mPinX, value ? HIGH : LOW);
}

void Arduino74HC4051::analogWrite(const Arduino74HC4051::CHANNEL &channel, int value) {
    (this->*(mPinStateCallback))(bitRead(channel, 2), bitRead(channel, 1), bitRead(channel, 0));
    if (mLatestPinXMode != OUTPUT)
        ::pinMode(mPinX, OUTPUT);
    mLatestPinXMode = OUTPUT;
#if defined(ARDUINO_ARCH_ESP32)
    ::ledcWrite(mPinX, value);
#else
    ::analogWrite(mPinX, value);
#endif
}

void Arduino74HC4051::onDefaultCallback(bool a, bool b, bool c) {
    auto readAndSet = [](uint8_t gpio, bool value) {
        int readValue = ::digitalRead(gpio);
        if (value && readValue != HIGH)
            ::digitalWrite(gpio, HIGH);
        if (!value && readValue != LOW)
            ::digitalWrite(gpio, LOW);
    };
    readAndSet(mPinA, a);
    readAndSet(mPinB, b);
    readAndSet(mPinC, c);
}




