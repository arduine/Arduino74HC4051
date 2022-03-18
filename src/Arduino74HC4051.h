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

#ifndef __ARDUINO_74HC4051_H
#define __ARDUINO_74HC4051_H

#include <Arduino.h>


#define __ARDUINO_74HC4051_NOP_GPIO 0xFF

class Arduino74HC4051 {

public:
    typedef void(Arduino74HC4051::*OnCallback)(bool a, bool b, bool c);

public:
    /**
     * X=不关心(Don't Care)
     * 0=低电平(Low)
     * 1=高电平(High)
     * +----+----+----+----+---------+
     * |  A |  B |  C | EN | CHANNEL |
     * +====+====+====+====+=========+
     * |  X |  X |  X |  1 |   None  |
     * +----+----+----+----+---------+
     * |  0 |  0 |  0 |  0 |    0    |
     * +----+----+----+----+---------+
     * |  1 |  0 |  0 |  0 |    1    |
     * +----+----+----+----+---------+
     * |  0 |  1 |  0 |  0 |    2    |
     * +----+----+----+----+---------+
     * |  1 |  1 |  0 |  0 |    3    |
     * +----+----+----+----+---------+
     * |  0 |  0 |  1 |  0 |    4    |
     * +----+----+----+----+---------+
     * |  1 |  0 |  1 |  0 |    5    |
     * +----+----+----+----+---------+
     * |  0 |  1 |  1 |  0 |    6    |
     * +----+----+----+----+---------+
     * |  1 |  1 |  1 |  0 |    7    |
     * +----+----+----+----+---------+
     */
    enum CHANNEL {
        X0 = B000,      // 开发板对应： Y0
        X1 = B100,      // 开发板对应： Y1
        X2 = B010,      // 开发板对应： Y2
        X3 = B110,      // 开发板对应： Y3
        X4 = B001,      // 开发板对应： Y4
        X5 = B101,      // 开发板对应： Y5
        X6 = B011,      // 开发板对应： Y6
        X7 = B111,      // 开发板对应： Y7
    };

public:
    /**
     * 使用内置引脚控制
     * @param pinX     信号读取接口 一般选取支持模拟量信号的接口  开发板对应： Z
     * @param pinINH   控制整体开关接口 普通IO口即可           开发板对应： E
     * @param pinA     控制A列接口 普通IO口即可               开发板对应： S0
     * @param pinB     控制B列接口 普通IO口即可               开发板对应： S1
     * @param pinC     控制C列接口 普通IO口即可               开发板对应： S2
     * @since 1.0.0
     */
    Arduino74HC4051(uint8_t pinX, uint8_t pinINH, uint8_t pinA, uint8_t pinB, uint8_t pinC);

    /**
     * 使用外部引脚控制，如拓展板的IO口
     * 注意：使用此模式需要自己手动去控制IN引脚的状态
     *
     * @param pinX      信号读取接口 一般选取支持模拟量信号的接口
     * @param callback  需要手动设置A,B,C的状态 true为高电平
     * @since 1.0.0
     */
    Arduino74HC4051(uint8_t pinX, const OnCallback &callback);

public:
    /**
     * 初始化设置
     * @since 1.0.0
     */
    void setup();

public:
    /**
     * 获取当前开关状态
     * 注意：如果使用手动控制模式，此接口将失效
     *
     * @return true启用 false关闭
     * @since 1.0.0
     */
    bool getEnabled();

    /**
     * 设置当前状态
     * 注意：如果使用手动控制模式，此接口将失效
     *
     * @param enabled true启用 false关闭
     * @since 1.0.0
     */
    void setEnabled(bool enabled);

public:

    /**
     * 读取模拟量接口
     * @param channel 通道
     * @return  一般在0～1024之间
     * @since 1.0.0
     * @see ::analogRead
     */
    int analogRead(const CHANNEL &channel);

    /**
     * 读取高低电平
     * @param channel 通道
     * @return true表示高电平
     * @since 1.0.0
     * @see ::digitalRead
     */
    bool digitalRead(const CHANNEL &channel);

    /**
     * 写入模拟量
     * @param channel 通道
     * @param value   数值，一般在0～1024之间
     * @since 1.0.0
     */
    void analogWrite(const CHANNEL &channel, int value);

    /**
     * 写入一个高低电平
     * @param channel 通道
     * @param value   数值，true表示高电平
     * @since 1.0.0
     */
    void digitalWrite(const CHANNEL &channel, bool value);


private:
    uint8_t mPinX, mPinINH, mPinA, mPinB, mPinC;
    OnCallback mPinStateCallback = nullptr;
    unsigned short mLatestPinXMode = INPUT_PULLUP;

private:
    void onDefaultCallback(bool a, bool b, bool c);
};


#endif // __ARDUINO_74HC4051_H
