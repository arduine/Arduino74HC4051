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

#ifndef __ARDUINO_74HC4067_H
#define __ARDUINO_74HC4067_H

#include <Arduino.h>
#include <functional>

#define __ARDUINO_74HC4067_NOP_GPIO 0xFF

class Arduino74HC4067 {

public:
    /**
     * X=不关心(Don't Care)
     * 0=低电平(Low)
     * 1=高电平(High)
     * +----+----+----+----+----+---------+
     * | S0 | S1 | S2 | S3 | EN | CHANNEL |
     * +====+====+====+====+====+=========+
     * |  X |  X |  X |  X |  1 |   None  |
     * +----+----+----+----+----+---------+
     * |  0 |  0 |  0 |  0 |  0 |    0    |
     * +----+----+----+----+----+---------+
     * |  1 |  0 |  0 |  0 |  0 |    1    |
     * +----+----+----+----+----+---------+
     * |  0 |  1 |  0 |  0 |  0 |    2    |
     * +----+----+----+----+----+---------+
     * |  1 |  1 |  0 |  0 |  0 |    3    |
     * +----+----+----+----+----+---------+
     * |  0 |  0 |  1 |  0 |  0 |    4    |
     * +----+----+----+----+----+---------+
     * |  1 |  0 |  1 |  0 |  0 |    5    |
     * +----+----+----+----+----+---------+
     * |  0 |  1 |  1 |  0 |  0 |    6    |
     * +----+----+----+----+----+---------+
     * |  1 |  1 |  1 |  0 |  0 |    7    |
     * +----+----+----+----+----+---------+
     * |  0 |  0 |  0 |  1 |  0 |    8    |
     * +----+----+----+----+----+---------+
     * |  1 |  0 |  0 |  1 |  0 |    9    |
     * +----+----+----+----+----+---------+
     * |  0 |  1 |  0 |  1 |  0 |    10   |
     * +----+----+----+----+----+---------+
     * |  1 |  1 |  0 |  1 |  0 |    11   |
     * +----+----+----+----+----+---------+
     * |  0 |  0 |  1 |  1 |  0 |    12   |
     * +----+----+----+----+----+---------+
     * |  1 |  0 |  1 |  1 |  0 |    13   |
     * +----+----+----+----+----+---------+
     * |  0 |  1 |  1 |  1 |  0 |    14   |
     * +----+----+----+----+----+---------+
     * |  1 |  1 |  1 |  1 |  0 |    15   |
     * +----+----+----+----+----+---------+
     */
    enum CHANNEL {
        C0 = B0000,
        C1 = B1000,
        C2 = B0100,
        C3 = B1100,
        C4 = B0010,
        C5 = B1010,
        C6 = B0110,
        C7 = B1110,
        C8 = B0001,
        C9 = B1001,
        C10 = B0101,
        C11 = B1101,
        C12 = B0011,
        C13 = B1011,
        C14 = B0111,
        C15 = B1111
    };

public:
    /**
     * 使用内置引脚控制
     * @param gpioSIG   信号读取接口 一般选取支持模拟量信号的接口
     * @param gpioEn    控制整体开关接口 普通IO口即可
     * @param gpioS0    控制S0列接口 普通IO口即可
     * @param gpioS1    控制S1列接口 普通IO口即可
     * @param gpioS2    控制S2列接口 普通IO口即可
     * @param gpioS3    控制S3列接口 普通IO口即可
     * @since 1.0.0
     */
    Arduino74HC4067(uint8_t gpioSIG, uint8_t gpioEn, uint8_t gpioS0, uint8_t gpioS1, uint8_t gpioS2, uint8_t gpioS3);

    /**
     * 使用外部引脚控制，如拓展板的IO口
     * 注意：使用此模式需要自己手动去控制EN引脚的状态
     *
     * @param gpioSIG   信号读取接口 一般选取支持模拟量信号的接口
     * @param callback  需要手动设置S0~S3的状态 true为高电平
     * @since 1.0.0
     */
    Arduino74HC4067(uint8_t gpioSIG, const std::function<void(bool s0, bool s1, bool s2, bool s3)> &callback);

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
    uint8_t mGpioSig, mGpioEn, mGpioS0, mGpioS1, mGpioS2, mGpioS3;
    std::function<void(bool s0, bool s1, bool s2, bool s3)> mPinStateCallback = nullptr;

};


#endif // __ARDUINO_74HC4067_H
