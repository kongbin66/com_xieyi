 #include "xieyi.h"
 //1.引用外部函数 
 void test1(void);
 void test2(int x);
 void test3(void);
//2.填写指令参数格式
  NAME_TAB name_tab[]=
 {
	  (void*)test1,                         {0xaa,0x00, 0, 0, 0, 0, 0, 0,0,0, 0xbb},
      (void*)test2,                         {0xaa,0x01, 1, 0, 0, 0, 0, 0,0,0, 0xbb},
	  (void*)test3,                         {0xaa,0xa2, 0, 0, 0, 0, 0, 0,0,0, 0xbb},
 };
//3.根据函数表修改xieyi.h的tab
//4.在主程序中调用xieyi_scan();


//  uint8_t init_xieyi(void)
//  {
// 	 return sizeof(name_tab)/sizeof(name_tab[0]);
//  } 
 
  void init_xieyi(uint8_t *p)
 {
	 *p=sizeof(name_tab)/sizeof(name_tab[0]);
 } 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
NAME_par  M_name_par =
{
	 name_tab,
	 exe,
	 0,//ID
	 0,//CMD
	 0,// uint8_t GS;
	 0,//uint8_t pra1;
	 0,//uint8_t cs2;
};


