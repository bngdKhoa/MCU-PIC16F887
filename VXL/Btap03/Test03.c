#INCLUDE <16F887.H>
#FUSES HS
#USE DELAY (CLOCK = 20M)

UNSIGNED INT8 YC, YD;
UNSIGNED INT16 Y, I, K, RUN, SAVE;

VOID XUAT_16LED()
{
   YD = Y;
   YC = Y >> 8;
   OUTPUT_C(YC);
   OUTPUT_D(YD);
}
VOID SANGDON()
{
   Y = 0; 
   XUAT_16LED ();
   SAVE = 0;
   FOR (K = 0; K<16; K++)
   {
      RUN = 0X0001;
      FOR (I=K; I<16; I++)
      {
         Y = RUN|SAVE;
         XUAT_16LED();
         DELAY_MS(70);
         RUN = RUN << 1; // dich run sang trai 1 bit
      }
      SAVE = Y;
   }
}
VOID TATDON ()
{
   Y = 0XFFFF;//Cac led deu sang, 1111 1111 1111 1111 
   XUAT_16LED();
   SAVE = 0XFFFE;//Cac led deu sang, 1 led tat 
   FOR (K=0; K<16; K++)
   {
      RUN = 0X0001 << K;// dich sang trai theo k
      FOR (I=0; I<K+1; I++)
      {
         RUN = RUN >> 1;
         Y = RUN|SAVE;
         XUAT_16LED();
         DELAY_MS(70);
      }
      SAVE = SAVE << 1;
   }
}
VOID SANGNGOAIVAO()
{
   Y = 0X0000;
   FOR (I = 0; I < 8; I++)
   {
      YD = (YD << 1) + 1; // led ngoai cung phia ben phai
      YC = (YC >> 1) + 0X80; // 1000 0000
      OUTPUT_D (YD);
      OUTPUT_C (YC);
      DELAY_MS (200);
   }
}
VOID TATNGOAIVAO ()
{
   Y = 1;
   FOR (I=0; I<8; I++)
   {
      YD = (YD << 1); //1111 1110
      YC = (YC >> 1); 
      OUTPUT_D (YD);
      OUTPUT_C (YC);
      DELAY_MS(150);
   }
}
VOID TATGIUARA ()
{
   Y = 1; 
   FOR (I = 0; I<8; I++)
   {
      YD = (YD>>1);
      YC = (YC<<1);
      OUTPUT_D (YD);
      OUTPUT_C (YC);
      DELAY_MS (150);
   }
}
VOID SANGGIUARA ()
{
   Y = 0; 
   FOR (I=0; I<8; I++)
   {
      YD = (YD >> 1) + 0X80;
      YC = (YC << 1) + 1;
      OUTPUT_D (YD);
      OUTPUT_C (YC);
      DELAY_MS (150);
   }
}
VOID XENKE ()
{
   FOR (I=0; I<2; I++)
   {
      Y = 0XAAAA; //1010.1010.1010.1010
      XUAT_16LED();
      DELAY_MS (200);
      Y = 0X5555;// 101.101.101.101
      XUAT_16LED();
      DELAY_MS (200);
   }
}
VOID SANGDANTRAI ()
{
   Y = 0;
   FOR (I=0; I<16; I++)
   {
      Y = (Y<<1) + 1;
      OUTPUT_D (Y);
      OUTPUT_C (Y>>8);
      DELAY_MS (100);
   }
}
VOID SANGDANPHAI ()
{
   Y = 0;
   FOR (I=0; I<16; I++)
   {
      Y = (Y>>1) + 0X8000;
      OUTPUT_D (Y);
      OUTPUT_C (Y>>8);
      DELAY_MS (100);
   }
}
VOID TATDANTRAI ()
{
   FOR (I=0; I<16; I++)
   {
      Y = (Y<<1);
      OUTPUT_D (Y);
      OUTPUT_C (Y>>8);
      DELAY_MS(100);
   }
}
VOID TATDANPHAI()
{
   FOR(I=0; I<16; I++)
   {
      Y = (Y>>1);
      OUTPUT_D(Y);
      OUTPUT_C(Y>>8);
      DELAY_MS (100);
   }
}
VOID CHOPTAT ()
{
   Y = 0;
   FOR (I=0; I<10; I++)
   {
      XUAT_16LED ();
      DELAY_MS(100);
      Y = ~Y;
   }
}
VOID MAIN ()
{
   WHILE (TRUE)
   {
      SANGDON ();
      TATDON  ();
      SANGNGOAIVAO(); //H�m con sang tat tu ngoai vao thuc hien
      TATNGOAIVAO();  // Thuc hien dong thoi de theo doi led hoat dong 
      SANGNGOAIVAO();
      TATGIUARA();
      SANGNGOAIVAO();
      SANGGIUARA();
      XENKE();
      SANGDANTRAI();
      TATDANTRAI ();
      SANGDANPHAI();
      TATDANPHAI ();
      CHOPTAT ();
   }
}
