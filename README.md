# Arduino 74HC4067

## 说明

一个Arduino的`74HC4067`的I/O拓展板库。 74HC4067 作用是选通一路对十六路模拟信号。

## 导入

#### PlatformIO

```ini
; Library options
lib_deps =
    https://github.com/arduine/Arduino74HC4067.git#main
```

#### ArduinoIDE

```c++
// TODO
```

## 使用

1. 增加头文件导入：

```c++
#include <Arduino74HC4067.h>
```

2. 编写代码

```c++
//
// 定义引脚
//
static Arduino74HC4067 s74HC4067(GPIO_SIG, GPIO_EN, GPIO_S0, GPIO_S1, GPIO_S2, GPIO_S3);

void setup() {
    s74HC4067.setup();              // <-- 初始化
    s74HC4067.setEnabled(true);     // <-- 启动功能
}

void onTest1() {
    // 读取
    auto value = s74HC4067.analogRead(Arduino74HC4067::CHANNEL::C0);
    Serial.printf("channel value %d", value);
    delay(3000);
    
    // 设置
    s74HC4067.analogWrite(Arduino74HC4067::CHANNEL::C0, 800);
}
```

## 状态
| S0  | S1  | S2  | S3  | EN  |  CHANNEL  |
|:---:|:---:|:---:|:---:|:---:|:---------:|
|  X  |  X  |  X  |  X  |  1  |   None    |
|  0  |  0  |  0  |  0  |  0  |     0     |
|  1  |  0  |  0  |  0  |  0  |     1     |
|  0  |  1  |  0  |  0  |  0  |     2     |
|  1  |  1  |  0  |  0  |  0  |     3     |
|  0  |  0  |  1  |  0  |  0  |     4     |
|  1  |  0  |  1  |  0  |  0  |     5     |
|  0  |  1  |  1  |  0  |  0  |     6     |
|  1  |  1  |  1  |  0  |  0  |     7     |
|  0  |  0  |  0  |  1  |  0  |     8     |
|  1  |  0  |  0  |  1  |  0  |     9     |
|  0  |  1  |  0  |  1  |  0  |    10     |
|  1  |  1  |  0  |  1  |  0  |    11     |
|  0  |  0  |  1  |  1  |  0  |    12     |
|  1  |  0  |  1  |  1  |  0  |    13     |
|  0  |  1  |  1  |  1  |  0  |    14     |
|  1  |  1  |  1  |  1  |  0  |    15     |

> ##### 说明
> * X=不关心(Don't Care)
> * 0=低电平(Low)
> * 1=高电平(High)


## LICENSE

```c++
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
```