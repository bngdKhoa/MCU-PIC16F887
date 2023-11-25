# INCLUDE <16F887.H> 
# FUSES HS 
# USE DELAY (CLOCK = 20M)
# DEFINE LCD_RS_PIN  PIN_E0
# DEFINE LCD_RW_PIN  PIN_E1
# DEFINE LCD_ENABLE_PIN PIN_E2
# DEFINE LCD_DATA4   PIN_D4
# DEFINE LCD_DATA5   PIN_D5
# DEFINE LCD_DATA6   PIN_D6
# DEFINE LCD_DATA7   PIN_D7
# INCLUDE <LCD.C>
UNSIGNED INT8 GIO, PHUT, GIAY;
VOID MAIN ()
{
   SET_TRIS_E (0);
   SET_TRIS_D (0);
   LCD_INIT ();
   LCD_GOTOXY (1,1);
   LCD_PUTC (" BAO NGOC DANG KHOA ");
   FOR (GIO = 0; GIO < 24; GIO ++)
      FOR (PHUT = 0; PHUT < 60; PHUT ++)
         FOR (GIAY = 0; GIAY < 60; GIAY ++)
         {
            LCD_GOTOXY (6,2);
            PRINTF (LCD_PUTC, "%02Uh %02Um %02Us", GIO, PHUT, GIAY);
            DELAY_MS (50);
         }
}
