/*
 * ch32v203_mylib.h
 *
 *  Created on: Jun 30, 2024
 *      Author: denshi1996(yuki)
 *      CH32V203K8T6に合わせて作っています
 */

#ifndef USER_CH32V203_MYLIB_H_
#define USER_CH32V203_MYLIB_H_

//ピン番号
#define PA0 0x10
#define PA1 0x11
#define PA2 0x12
#define PA3 0x13
#define PA4 0x14
#define PA5 0x15
#define PA6 0x16
#define PA7 0x17
#define PA8 0x18
#define PA9 0x19
#define PA10 0x1A
#define PA11 0x1B
#define PA12 0x1C
#define PA13 0x1D
#define PA14 0x1E
#define PA15 0x1F

#define PB0 0x20
#define PB1 0x21
#define PB3 0x23
#define PB4 0x24
#define PB5 0x25
#define PB6 0x26
#define PB7 0x27
#define PB8 0x28

#define PD0 0x40
#define PD1 0x41

//OUTPUT SPEED
#define OUTPUT_2MHz 0b10
#define OUTPUT_10MHz 0b01
#define OUTPUT_50MHz 0b11

//PINMODE
//0xQWER; Q:インプットかアウトプットか
//W:プルアップかプルダウンか(outputでは常に0)
//ER:CNFのビット
#define INPUT 0b1001
#define INPUT_PULLUP 0b1110
#define INPUT_PULLDOWN 0b1010
#define INPUT_ANALOG 0b1000
#define OUTPUT 0b0000
#define OUTPUT_OPENDRAIN 0b0001
#define OUTPUT_FUNC 0b0010
#define OUTPUT_OPENDRAIN_FUNC 0b0011


void GPIOA_init(void); //GPIOAのセットアップ
void GPIOB_init(void); //GPIOBのセットアップ
void GPIOC_init(void); //GPIOCのセットアップ
void GPIOD_init(void); //GPIODのセットアップ
int GPIO_output_speed(int speed); //GPIO OUTPUT時の速度指定
void pinMode(int Pin,int mode); //GPIO入出力設定
unsigned char digitalRead(int Pin); //GPIO入力
void digitalWrite(int Pin, int val); //GPIO出力
//ビット置き換え関数
uint32_t bit_replace(uint32_t data, uint32_t byte, uint8_t len, uint8_t shift);

#endif /* USER_CH32V203_MYLIB_H_ */
