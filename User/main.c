/*
* SPDX-FileCopyrightText: 2024 yuki-denshi-1996 <matsukawa.software@gmail.com>
* SPDX-License-Identifier: BSD 3-Clause
*/

#include <ch32v20x.h>
#include "ch32v203_GPIO_mylib.h"

int main(void){
    Delay_Init();

    pinMode(PA15,OUTPUT);

    while(1){
        digitalWrite(PA15, 1);
        Delay_Ms(1000);
        digitalWrite(PA15, 0);
        Delay_Ms(1000);
    }
}
