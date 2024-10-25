/*
* SPDX-FileCopyrightText: 2024 yuki-denshi-1996 <matsukawa.software@gmail.com>
* SPDX-License-Identifier: BSD 3-Clause
*/

/*
 * ch32v203_mylib.c
 *
 *  Created on: Jun 30, 2024
 *      Author: denshi1996(yuki)
 */

#include "ch32v20x.h"
#include "ch32v203_mylib.h"

//GPIOAの有効化
void GPIOA_init(void) {
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;
}

//GPIOBの有効化
void GPIOB_init(void) {
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOB;
}

//GPIOCの有効化
void GPIOC_init(void) {
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;
}

//GPIODの有効化
void GPIOD_init(void) {
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;
}

//GPIO OUTPUT時の速度指定
//引数:speed:速度指定 mylib.h参照
//戻り値：入力されている値を返す。
//speedに0を指定すると、値が書き換わらない
int GPIO_output_speed(int speed) {
    static int mode_speed = OUTPUT_2MHz;
    if (speed) {
        mode_speed = speed;
    }
    return mode_speed;
}

//GPIO入出力設定
//pin:ピン番号(mylib.h参照)
//mode:モード(OUTPUTなど mylib.h参照)
void pinMode(int Pin, int mode) {
    //GPIOがA(0x1y)だったら
    if ((Pin & 0xF0) == 0x10) {
        //OUTPUTだったら
        if ((mode & 0b1000) == 0) {
            //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOA->CFGLR = bit_replace(GPIOA->CFGLR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOA->CFGLR = bit_replace(GPIOA->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOA->CFGHR = bit_replace(GPIOA->CFGHR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOA->CFGHR = bit_replace(GPIOA->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            }
        } else {                //INPUT
                                //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOA->CFGLR = bit_replace(GPIOA->CFGLR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOA->CFGLR = bit_replace(GPIOA->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOA->CFGHR = bit_replace(GPIOA->CFGHR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOA->CFGHR = bit_replace(GPIOA->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);

            }
            //プルアップもしくはプルダウンを選択している場合
            if ((mode & 0b0011) == 0b10) {
                GPIOA->OUTDR = bit_replace(GPIOA->OUTDR, ((mode & 0b0100) >> 2),
                        1, (Pin & 0x0F));
            }
        }
    }
    //GPIOがB(0x2y)だったら
    if ((Pin & 0xF0) == 0x20) {
        //OUTPUTだったら
        if ((mode & 0b1000) == 0) {
            //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOB->CFGLR = bit_replace(GPIOB->CFGLR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOB->CFGLR = bit_replace(GPIOB->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOB->CFGHR = bit_replace(GPIOB->CFGHR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOB->CFGHR = bit_replace(GPIOB->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            }
        } else {                //INPUT
                                //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOB->CFGLR = bit_replace(GPIOB->CFGLR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOB->CFGLR = bit_replace(GPIOB->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOB->CFGHR = bit_replace(GPIOB->CFGHR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOB->CFGHR = bit_replace(GPIOB->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            }
            //プルアップもしくはプルダウンを選択している場合
            if ((mode & 0b0011) == 0b10) {
                GPIOB->OUTDR = bit_replace(GPIOB->OUTDR, ((mode & 0b0100) >> 2),
                        1, (Pin & 0x0F));
            }
        }
    }
    //GPIOがC(0x3y)だったら
    if ((Pin & 0xF0) == 0x30) {
        //OUTPUTだったら
        if ((mode & 0b1000) == 0) {
            //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOC->CFGLR = bit_replace(GPIOC->CFGLR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOC->CFGLR = bit_replace(GPIOC->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOC->CFGHR = bit_replace(GPIOC->CFGHR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOC->CFGHR = bit_replace(GPIOC->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            }
        } else {                //INPUT
                                //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOC->CFGLR = bit_replace(GPIOC->CFGLR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOC->CFGLR = bit_replace(GPIOC->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOC->CFGHR = bit_replace(GPIOC->CFGHR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOC->CFGHR = bit_replace(GPIOC->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            }
            //プルアップもしくはプルダウンを選択している場合
            if ((mode & 0b0011) == 0b10) {
                GPIOC->OUTDR = bit_replace(GPIOC->OUTDR, ((mode & 0b0100) >> 2),
                        1, (Pin & 0x0F));
            }
        }
    }
    //GPIOがD(0x4y)だったら
    if ((Pin & 0xF0) == 0x40) {
        //OUTPUTだったら
        if ((mode & 0b1000) == 0) {
            //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOD->CFGLR = bit_replace(GPIOD->CFGLR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOD->CFGLR = bit_replace(GPIOD->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOD->CFGHR = bit_replace(GPIOD->CFGHR, GPIO_output_speed(0),
                        2, ((Pin & 0b0111) * 4));
                //CNF
                GPIOD->CFGHR = bit_replace(GPIOD->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            }
        } else {                //INPUT
                                //レジスタがHigh側かLow側か
            if ((Pin & 0b1000) == 0) {
                //LOW側
                //MODE
                GPIOD->CFGLR = bit_replace(GPIOD->CFGLR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOD->CFGLR = bit_replace(GPIOD->CFGLR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            } else {
                //HIGH側
                //MODE
                GPIOD->CFGHR = bit_replace(GPIOD->CFGHR, 0b00, 2,
                        ((Pin & 0b0111) * 4));
                //CNF
                GPIOD->CFGHR = bit_replace(GPIOD->CFGHR, (mode & 0b0011), 2,
                        (Pin & 0b0111) * 4 + 2);
            }
            //プルアップもしくはプルダウンを選択している場合
            if ((mode & 0b0011) == 0b10) {
                GPIOD->OUTDR = bit_replace(GPIOD->OUTDR, ((mode & 0b0100) >> 2),
                        1, (Pin & 0x0F));
            }
        }
    }
}

// GPIOを取得する関数
// 戻り値：ピンがHIGH(1)かLOW(0)か
// 0xFFが返却されたらエラー
unsigned char digitalRead(int Pin) {
    // GPIOxがA(0x1y)だったら
    if ((Pin & 0xF0) == 0x10) {
        if (GPIOA->INDR & (1 << (Pin & 0x0F))) {
            return 1;
        } else {
            return 0;
        }
    }
    // GPIOxがB(0x2y)だったら
    if ((Pin & 0xF0) == 0x20) {
        if (GPIOB->INDR & (1 << (Pin & 0x0F))) {
            return 1;
        } else {
            return 0;
        }
    }
    // GPIOxがC(0x3y)だったら
    if ((Pin & 0xF0) == 0x30) {
        if (GPIOC->INDR & (1 << (Pin & 0x0F))) {
            return 1;
        } else {
            return 0;
        }
    }
    // GPIOxがD(0x4y)だったら
    if ((Pin & 0xF0) == 0x40) {
        if (GPIOD->INDR & (1 << (Pin & 0x0F))) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0xFF; // エラー
}

// デジタル値出力
// Pin:ピン 名付け 0xYZ Y:GPIOx(A:1 B:2 C:3 ...)
//     Z:ポート番号 GPIOA-10 →　0x1Aとなる。
// val:出力値 (1or0)
void digitalWrite(int Pin, int val) {
    // GPIOxがA(0x1y)だったら
    if ((Pin & 0xF0) == 0x10) {
        if (val == 0) {
            GPIOA->OUTDR &= ~(1 << (Pin & 0x0F));
        } else {
            GPIOA->OUTDR |= (1 << (Pin & 0x0F));
        }
    }

    // GPIOxがB(0x2y)だったら
    if ((Pin & 0xF0) == 0x20) {
        if (val == 0) {
            GPIOB->OUTDR &= ~(1 << (Pin & 0x0F));
        } else {
            GPIOB->OUTDR |= (1 << (Pin & 0x0F));
        }
    }
    // GPIOxがC(0x3y)だったら
    if ((Pin & 0xF0) == 0x30) {
        if (val == 0) {
            GPIOC->OUTDR &= ~(1 << (Pin & 0x0F));
        } else {
            GPIOC->OUTDR |= (1 << (Pin & 0x0F));
        }
    }

    // GPIOxがD(0x4y)だったら
    if ((Pin & 0xF0) == 0x40) {
        if (val == 0) {
            GPIOD->OUTDR &= ~(1 << (Pin & 0x0F));
        } else {
            GPIOD->OUTDR |= (1 << (Pin & 0x0F));
        }
    }
}

//  ビット置き換え関数
//  引数 data:置き換え前のビット列 | byte:置き換えるビット |
//  len:置き換えるビットの長さ | shift:シフト数
uint32_t bit_replace(uint32_t data, uint32_t byte, uint8_t len, uint8_t shift) {
    uint32_t mask = ~(((1 << len) - 1) << shift);
    data &= mask;
    data |= byte << shift;
    return data;
}
