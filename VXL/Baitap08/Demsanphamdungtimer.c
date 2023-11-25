# INCLUDE < 16F887.H > 
# FUSES HS 
# USE DELAY (CLOCK = 20M)
// KHAI BAO CAC CHAN CUA LCD 
# DEFINE LCD_ENABLE_PIN    PIN_E2
# DEFINE LCD_RS_PIN        PIN_E0
# DEFINE LCD_RW_PIN        PIN_E1
# DEFINE LCD_DATA4         PIN_D4
# DEFINE LCD_DATA5         PIN_D5
# DEFINE LCD_DATA6         PIN_D6
# DEFINE LCD_DATA7         PIN_D7
# INCLUDE < LCD.C >
# DEFINE UP                PIN_B0
# DEFINE DW                PIN_B1
UNSIGNED INT8 SP, SPMAX;
VOID HIENTHI_SP ()
{
   LCD_GOTOXY (1,2);
   PRINTF (LCD_PUTC, "SAN PHAM: %02U", SP);
}
VOID HIENTHI_SPMAX ()
{
   LCD_GOTOXY (1,1);
   PRINTF (LCD_PUTC, "SAN PHAM MAX: %2U", SPMAX);
}

VOID MAIN ()
{
   SET_TRIS_D (0);
   SET_TRIS_E (0);
   LCD_INIT ();
   SPMAX = 15;
   HIENTHI_SP ();
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1);
   SET_TIMER0 (0);
LOOP:
   SP = GET_TIMER0();
   HIENTHI_SP();
   IF (INPUT(UP) == 0)
   {
      DELAY_MS (10);
      IF (INPUT (UP) == 0)
      WHILE (INPUT(UP)==0) {}
      IF (SPMAX < 20)
         SPMAX ++;
   }
   IF (INPUT(DW) == 0)
   {  
      DELAY_MS (10);
      IF (INPUT (DW) == 0)
      WHILE (INPUT (DW) == 0) {}
      IF (SPMAX > 10)
         SPMAX --;
   }
   HIENTHI_SPMAX ();
   IF (SP = SPMAX)
   {
      WHILE (TRUE)
      {
         LCD_GOTOXY (1,2);
         LCD_PUTC ("DA DU SAN PHAM");
         DELAY_MS (300);
         LCD_GOTOXY(1,2);
         LCD_PUTC ("              ");
         DELAY_MS (300);
      }
   }
   GOTO LOOP:
}
         
      
