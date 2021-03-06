#include "Arduino.h"
#include "xieyi.h"

 uint8_t CMD_NUM=0;//被调用函数总数

 uint8_t rx_buff[num];
//娓呮帴鏀剁紦鍐插尯
void clear_rx_buff(void)
{
  int i;
  for(i=0;i<num;i++) rx_buff[i]=0;
}
uint8_t exe(void)
{
    int res=0;
    switch(M_name_par.GS)
    {
    case 0://鏃犲弬鏁?(void绫诲瀷)
        res=(*(int(*)())M_name_par.pfune->pf)();
        break;
    case 1:
        res=(*(int(*)(uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0]);
        break;
    case 2://鏈?2涓?鍙傛暟
        res=(*(int(*)(uint32_t,uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0],M_name_par.cs[1]);
        break;
    case 3://鏈?3涓?鍙傛暟
        res=(*(int(*)(uint32_t,uint32_t,uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0],M_name_par.cs[1],M_name_par.cs[2]);
        break;
    case 4://鏈?4涓?鍙傛暟
        res=(*(int(*)(uint32_t,uint32_t,uint32_t,uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0],M_name_par.cs[1],M_name_par.cs[2],M_name_par.cs[3]);
        break;
    case 5://鏈?5涓?鍙傛暟
        res=(*(int(*)(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0],M_name_par.cs[1],M_name_par.cs[2],M_name_par.cs[3],M_name_par.cs[4]);
        break;
    case 6://鏈?6涓?鍙傛暟
        res=(*(int(*)(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0],M_name_par.cs[1],M_name_par.cs[2],M_name_par.cs[3],M_name_par.cs[4],M_name_par.cs[5]);
        break;
    case 7://鏈?7涓?鍙傛暟
        res=(*(int(*)(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0],M_name_par.cs[1],M_name_par.cs[2],M_name_par.cs[3],M_name_par.cs[4],M_name_par.cs[5],M_name_par.cs[6]);
        break;
    case 8://鏈?8涓?鍙傛暟
        res=(*(int(*)(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t))M_name_par.pfune->pf)(M_name_par.cs[0],M_name_par.cs[1],M_name_par.cs[2],M_name_par.cs[3],M_name_par.cs[4],M_name_par.cs[5],M_name_par.cs[6],M_name_par.cs[7]);
        break;
    }
    return res;
}

//获取调用函数功能码位置
//输入：接收到的功能码 CMD ,
//输出：功能码位置 *p
//返回：0成功 ，！0错误
uint8_t get_fun_ID(uint8_t cmd,uint8_t *p)
{
    uint8_t i=0;
    for(i=0; i<CMD_NUM; i++)
    {
        if(cmd==name_tab[i].cmd[1])
        {
            *p=i;
            return 0;
        }
    }
    return 1;
}
//杈ㄨ?ゅ弬鏁版牸寮?:涓?鏁板拰绫诲瀷
void get_fun_par_gslx()
{
     uint8_t i,j;
     uint8_t buf[CMD_data];
     uint8_t par[CMD_data]; //鐘舵?佹殏瀛?
    for(i=0; i<(CMD_data); i++) par[i]=0;
    j=2;//鎸囦护瀛楄妭鎵?鍦ㄤ綅缃?
    for(i=0; i<(CMD_data); i++) //灏嗙函鍙傛暟鏀惧叆鏁扮粍
    {
        buf[i]=name_tab[M_name_par.ID].cmd[j];
        j++;
    }
#if 0
    printf("*****************************************\r\n");
    for(i=0; i<(CMD_data); i++) //鏄剧ず涓插彛鎺ユ敹鍊?
    {
        printf("buf[%d]=%d\r\n",i,buf[i]);
    }
#endif
    for(i=0; i<(CMD_data); i++) //杈ㄨ?ゅ弬鏁? pra
    {
        if(buf[i]!=0)  par[buf[i]-1]++;
    }
    j=0;
    for(i=0; i<(CMD_data); i++) //杈ㄨ?ゅ弬鏁? GS
    {
        if(par[i]!=0) j++;
    }
    M_name_par.GS=j;
    for(i=0; i<(CMD_data); i++) M_name_par.pra[i]=par[i];
#if 0
    printf("*****************************************\r\n");
    for(i=0; i<(CMD_data); i++) //鏄剧ず涓插彛鎺ユ敹鍊?
    {
        printf("par[%d]=%d\r\n",i,M_name_par.pra[i]);
    }
    printf("GS=%d\r\n",M_name_par.GS);
#endif
}

//获取指令格式、指令、参数个数、参数类型、返回类型
//输入：获取到的函数表位置 id
void get_fun_par(uint8_t id)
{
    M_name_par.pfune =&name_tab[id];//位置
    M_name_par.ID=id;
    M_name_par.CMD=name_tab[id].cmd[1];
    //解析函数参数的个数和类型
    get_fun_par_gslx();
}


//鍙栨暟鎹?
uint32_t yiwei1(uint8_t *buf)
{
    uint32_t i;
    uint8_t j;
    i=buf[0];//灏嗘暟鎹?瀛樻斁

    for(j=0; j<(CMD_data-1); j++)//灏嗙??涓?涓?鏁版嵁绉婚櫎鎺?
    {
        buf[j]=buf[j+1];
    }
    return i;
}
//鍙杣int16_t鏁版嵁
uint32_t yiwei2(uint8_t*buf)
{
    uint32_t i;
    uint8_t j;
    uint8_t k=2;
    i=((uint16_t)buf[0]<<8)+buf[1];


    for(j=0; j<(CMD_data-2); j++)
    {
        buf[j]=buf[k];//绗?浜屾?¤?呰浇BUF,
        k++;
    }
    return i;

}
//鍙杣int32_t鏁版嵁
uint32_t yiwei4(uint8_t *buf)
{
    uint32_t i;
    uint8_t j;
    uint8_t k=4;
    i=((uint32_t)buf[0]<<24)+((uint32_t)buf[1]<<16)+((uint32_t)buf[2]<<8)+buf[3];

    for(j=0; j<(CMD_data-4); j++)
    {
        buf[j]=buf[k];;//绗?浜屾?¤?呰浇BUF,
        k++;
    }

    return i;
}



void get_uart_par(uint8_t *buf)
{
     uint8_t i;
     uint8_t cbuf[CMD_data];

    for(i=0; i<(CMD_data); i++)
    {
        cbuf[i]=buf[i];
    }
#if 0
    printf("*****************************************\r\n");
    for(i=0; i<(CMD_data); i++) //鏄剧ず涓插彛鎺ユ敹鍊?
    {
        printf("cbuf[%d]=%d\r\n",i,cbuf[i]);
    }
#endif
    //鍙傛暟鏄?鏈夐檺鍒剁殑
    for(i=0; i<CMD_data; i++)
    {
        if(M_name_par.pra[i]!=0)
        {
            switch(M_name_par.pra[i])
            {
            case 1://
                M_name_par.cs[i]= yiwei1(cbuf);
                break;
            case 2://uint16_t
                M_name_par.cs[i]= yiwei2(cbuf);
                break;
            case 4://uint32_t
                M_name_par.cs[i]=yiwei4(cbuf);
                break;
            }
        }
    }

#if 0
    printf("*****************************************\r\n");
    for(i=0; i<(CMD_data); i++) //鏄剧ず涓插彛鎺ユ敹鍊?
    {
        printf("cs[%d]=%d\r\n",i,M_name_par.cs[i]);
    }
#endif
}

uint8_t jiexi(uint8_t *buf,int x)
{
  uint8_t res=0,id=0;
  //核对AA BB
  if(rx_buff[0]==0xaa&&rx_buff[x-1]==0xbb)
  {
       #if 0
       Serial.println("指令获取AABB正确\n");
       #endif

       
       res=get_fun_ID(rx_buff[1],&id);
       if(!res)
       {
           //Serial.printf("获取ID:%d\n",id);
                get_fun_par(id);////鑾峰彇鍑芥暟琛ㄤ腑鐨勬牸寮? 鎸囦护 鍙傛暟涓?鏁帮紝鍙傛暟绫诲瀷 杩斿洖绫诲瀷
                get_uart_par(&rx_buff[2]);
                clear_rx_buff();
                exe();
                return 0;
       }
       else Serial.println("无此指令！");
  }
  else
  {
     Serial.println("指令没获取到AABB!\n");
  }
  return 1;
}





//aa 00 a0 01 01 01 01 01 01 01 bb
void xieyi_scan(void)
{
    static uint8_t f=0;
    static int i= 0,J=0;
   // uint8_t sta=0;//状态
    if(J==0)
	 {
		  J=1;
		  init_xieyi(&CMD_NUM);
		  #if DEBUG
		  printf("NUM=%d\r\n",CMD_NUM);
		  #endif
	 }
    //接收通讯数据，找到指令长度，和数据长度
    while(Serial.available())
   {
      rx_buff[i++] =Serial.read(); 
      f=1;    
   }
   if(f==1)
   {
      f=0;


      
      #if DEBUG
        //查看接收的数据没验证
      Serial.println("接收到数据！");
      Serial.println();
      for(i=0;i<x;i++)
      Serial.write(rx_buff[i]);
      Serial.println();
      Serial.println();
      uint8_t I_CMDlong=i;//指令长度
      uint8_t I_CMDdata =i-3;//数据长度
      uint8_t CMD=rx_buff[1];//本指令功能码
      Serial.printf("通讯指令长%d字节，参数长度%d字节，本指令功能码%d\r\n",I_CMDlong,I_CMDdata,CMD);
      #endif




      if(i==CMD_long)//等长指令
      {
              //解析指令
        jiexi(rx_buff,i);
      
      }
      else Serial.println("指令长度格式错误！");
      
 
   }
   i=0;
  





	//   if(i==0)
	//  {
	// 	  i=1;
	// 	  init_xieyi(&CMD_NUM);
	// 	  #if 0
	// 	  printf("NUM=%d\r\n",CMD_NUM);
	// 	  #endif
	//  }
//     if(USART1_RX_STA&0x8000)
//     {
//         if((USART1_rx_buff[0]==0xaa)&&(USART1_rx_buff[CMD_long-1]==0xbb))
//         {
//             res=get_fun_ID(USART1_rx_buff[1],&id);//灏嗕覆鍙ｇ殑鏁版嵁瑙ｆ瀽鎴愬嚱鏁拌〃涓?鐨勫摢涓?鍑芥暟ID
//             if(!res)
//             {
//                 get_fun_par(id);////鑾峰彇鍑芥暟琛ㄤ腑鐨勬牸寮? 鎸囦护 鍙傛暟涓?鏁帮紝鍙傛暟绫诲瀷 杩斿洖绫诲瀷
//                 get_uart_par(&USART1_rx_buff[2]);
//                 exe();
//             }
// #if DEBUG
//             else printf("鏃犳?ゆ寚浠わ紒锛侊紒\r\n");
// #endif
// #if 0
//             printf("*****************************************\r\n");
// 						if(!res)//鏄剧ず鎸囦护鐘舵??
//                 printf("璇诲彇鎸囦护鎴愬姛锛?,璇诲彇鐨勬寚浠?=%d,涓插彛鎸囦护鍙?=%d,鐘舵?侊細OK!!\r\n",id,USART1_rx_buff[1]);
//             else printf("璇诲彇鎸囦护澶辫触锛?,璇诲彇鐨勬寚浠?=%d,cmd=%d,err!!\r\n",id,USART1_rx_buff[1]);
//             for(id=0; id<CMD_long; id++) //鏄剧ず涓插彛鎺ユ敹鍊?
//             {
//                 printf("buf[%d]=%d\r\n",id,USART1_rx_buff[id]);
//             }

// #endif
//             USART1_rx_buff[0]=0;
//              USART1_rx_buff[CMD_long-1]=0;
//         }
// #if DEBUG
//         else printf("鏍煎紡閿欒??锛乗r\n");
// #endif
//         USART1_RX_STA=0;
//     }
}




// void jiexi(char *buf,int x)
// {
//   uint8_t i,res,id;
//   //鏄剧ず浼犻?佽繃鏉ョ殑鍐呭??
//   #if 1
//      for(i=0;i<x;i++)
//       Serial.write(rx_buff[i]);
//       Serial.println();
//   #endif
//   //鍒ゆ柇AA BB
//   if(rx_buff[0]==0xaa&&rx_buff[x-1]==0xbb)
//   {
//        Serial.println("CMD ok!");
//        //鍒ゆ柇鍔熻兘鐮?
//        res=get_fun_ID(rx_buff[1],&id);
    
//        //鍒ゆ柇鍙傛暟涓?鏁?
//        //鎵ц?屽懡浠ゆ搷浣?
//   }
//   else
//   {
//      Serial.println("CMD ERR!");

//   }
// }


// void xieyi(void)
// {
//    static uint8_t f=0;
//    static int i= 0;
//    while(Serial.available())
//    {
//       rx_buff[i++] =Serial.read(); 
//       f=1;    
//    }
//    if(f==1)
//    {
//       f=0;
//       jiexi(rx_buff,i);
//    }
//    i=0;
// }






















































