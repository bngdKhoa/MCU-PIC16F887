# include <16f887.h>
# fuses hs 
# use delay (clock = 20M )
unsigned int8 dlht [] = {0xFF, 0xFF, 0xBF, 0xBF, 0xBF, 0xBF, 0xFF, 0xFF};
unsigned int8 ma7doan [] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned int8 i, q, n, m, k, giay, quet;
signed int8 dem1, dem2; 

void hienthi ()
{
   for (q=0; q<44; q++) // chay 48 lan sap xi 1 giay 
   {
      quet = 0xFE; //1111 1101
      for (i=0; i<8; i++)
      {
         output_d (quet); // chon led dau tien xuat ra port d theo bien quet
         output_c (dlht[i]); // xuat ra port c mang du lieu hien thi theo bien i 
         delay_ms (2);
         output_c (0xFF); // chong lem 
         quet = (quet << 1) + 1;
      }
   }
}
void hienthimssv ()
{
   unsigned int8 mssv [] = {0xA4, 0xF9, 0xF9, 0x92, 0xF9, 0x99, 0xC0, 0x80};
   for (k=0; k<100; k++)
   {
      quet = 0xFE;
      for (i=0; i<8; i++)
      {  
         output_d (quet);
         output_c (mssv [i]);
         delay_ms (2);
         output_c (0xFF);
         quet = (quet << 1) + 1;
      }
   }
}
void demgiay ()
{  
   unsigned int8 giay;
   for (giay = 0; giay < 60; giay++)
   {
      dlht [7] = ma7doan [giay%10];
      dlht [6] = ma7doan [giay/10];
      hienthi ();
   }
}
void demlenxuongdongthoi ()
{  
   signed int8 dem1, dem2;
   dem1 = 00;
   dem2 = 26;
   for (n=0; n<30; n++)
   {
      dlht [0] = ma7doan [dem2 /10];
      dlht [1] = ma7doan [dem2 % 10];
      dlht [6] = ma7doan [dem1 /10];
      dlht [7] = ma7doan [dem1 %10];
      hienthi ();
      dem1 = dem1 + 1;
      if (dem1 > 15)
         dem1 = 00;
      dem2 = dem2 - 2;
      if (dem2 < 0)
         dem2 = 26;
   }
}
void chaychu_hello ()
{
   unsigned int8 hello [] = {0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X89, 0X86, 0XC7, 0XC7, 0XC0, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF};
   for (m=0; m<14; m++)
   {
      for (n=0; n<8; n++)
         dlht [n] = hello [n+m];
      hienthi ();
   }
}
void chaychu_cocacola ()
{
   const unsigned int8 cocacola [] = {0XC6, 0XC0, 0XC6, 0X88, 0XC6, 0XC0, 0XC7, 0X88};
   for (n=0; n<16; n++)
   {
      for (k=0; k<7; k++)
         dlht [k] = dlht [k+1];
      if (n<8)
         dlht [7] = cocacola [n];
      else 
         dlht [7] = 0xFF;
      hienthi ();
   }
}
void main()
{
   set_tris_c (0);
   set_tris_d (0);
   while(TRUE)
   {
      hienthimssv();
      demgiay();
      demlenxuongdongthoi ();
      chaychu_hello ();
      chaychu_cocacola ();
   }
}

