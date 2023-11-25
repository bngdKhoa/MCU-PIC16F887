# INCLUDE <16F887.H>
# FUSES HS
# USE DELAY (CLOCK = 20M)
CONST UNSIGNED INT8 MA7DOAN [] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
# DEFINE UP    PIN_B0
# DEFINE DW    PIN_B1
# DEFINE START PIN_B2
SIGNED INT8 DEM, I, SO;
VOID GIAIMA7DOAN (UNSIGNED INT8 SO)
{
   OUTPUT_C (MA7DOAN[SO/10]);
   OUTPUT_D (MA7DOAN[SO%10]);
}
VOID MAIN ()
{
   SET_TRIS_C (0);
   SET_TRIS_D (0);
   SET_TRIS_B (0xFF);
   PORT_B_PULLUPS (TRUE);
   DEM = 5;
GM:
   GIAIMA7DOAN (DEM);
   IF (INPUT(UP) == 0 )
   {
      DELAY_MS (10);
      IF (INPUT (UP) == 0)
      {  
         WHILE (INPUT (UP) == 0) {}
         DEM ++;
         IF (DEM > 15)
            DEM = 5;
      }
   }
   IF (INPUT (DW)== 0)
   {
      DELAY_MS (10);
      IF (INPUT (DW) == 0)
      {
         WHILE (INPUT(DW) == 0) {}
         DEM = DEM - 2;
         IF (DEM < 5)
            DEM = 15;
      }
   }
   IF (INPUT (START)==0)
   {
      DELAY_MS (10);
      IF (INPUT (START) == 0)
      {
         WHILE (INPUT (START) == 0) {}
         FOR (I = 0; I <= DEM; I++)
         {
            GIAIMA7DOAN (I);
            DELAY_MS (100);
         }
      }
   }
   GOTO GM;
}
         
