#include <ch32v20x.h>
#include "ch32v203_mylib.h"

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
