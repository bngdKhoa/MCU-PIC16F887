# include <demgiophutgiay.h>
UNSIGNED INT8 DLHT [8] = { 0xFF, 0xFF, 0xBF, 0xFF, 0xFF, 0xBF, 0xFF, 0xFF};
CONST UNSIGNED INT8 MA7DOAN [] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
UNSIGNED INT8 QUET, GIO, PHUT, GIAY;
VOID HIENTHI ()
{
   UNSIGNED INT8 I, Q;
   FOR (Q = 0; Q < 30; Q++)
   {
      QUET = 0xFE;
      FOR (I = 0; I < 8; I++)
      {
         OUTPUT_D (QUET);
         OUTPUT_C (DLHT[I]);
         DELAY_MS (4);
         OUTPUT_C (0xFF);
         QUET = (QUET << 1) + 1;
      }
   }
}
void main()
{
     SET_TRIS_C (0x00);
     SET_TRIS_D (0x00);
     GIAY = 0;
     PHUT = 0;
     GIO  = 0;
while(TRUE)
   {  FOR (GIO = 0; GIO < 24; GIO ++)
      {
         FOR (PHUT = 0; PHUT < 60; PHUT ++)
         {
            FOR (GIAY = 0; GIAY < 60; GIAY ++)
            {
               DLHT [7] = MA7DOAN [GIAY % 10];
               DLHT [6] = MA7DOAN [GIAY / 10];
               HIENTHI ();
            }
         }
      }
   }
}
