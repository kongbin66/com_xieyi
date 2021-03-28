#include <Arduino.h>
#include "xieyi.h"




void(*p)(void);
void (*p1)(int);


uint8_t cs[10];



int j=0;

//调用函数示例
void test1(void)
{
   Serial.println("diaoyong test1 ok!\n");
}
void test2(int x)
{
   Serial.printf("diaoyong test2 ok! \t x=%d\n",x);
}
void test3(void)
{
   Serial.println("diaoyong test3 ok!\n");
}












void setup()
{
   Serial.begin(9600);
   //init_xieyi();
}

void loop()
{
  
   xieyi_scan();
   
  
}

