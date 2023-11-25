# INCLUDE <16F887.H>
# FUSES HS 
# USE DELAY (CLOCK = 20M)
# DEFINE UP          PIN_A0
# DEFINE DW          PIN_A1
# DEFINE START_STOP  PIN_A2
# DEFINE ENABLE      PIN_C7   // CHO PHEP L298 HOAT DONG

CONST UNSIGNED INT8 MA7DOAN [] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};
UNSIGNED INT16 VALUE, CAPTOCDO;
INT1 TTDC;

VOID HIENTHI_MA7DOAN_THEOCAPDO ()
{
   OUTPUT_B (MA7DOAN [CAPTOCDO/10]);
   OUTPUT_D (MA7DOAN [CAPTOCDO%10]);
}
VOID KT_START_STOP ()
{
   IF (INPUT(START_STOP) == 0)
   {
      DELAY_MS (20);
      IF (INPUT(START_STOP)==0)
      {  
         WHILE (INPUT(START_STOP)==0)  {}
         TTDC =~ TTDC;
         IF (TTDC == 1)
            TTDC = 1;
         ELSE 
            TTDC = 0;
         HIENTHI_MA7DOAN_THEOCAPDO ();
      }
   }
}
VOID KT_UP ()
{
   IF (INPUT(UP) == 0)
   {
      DELAY_MS (20);
      IF (INPUT(UP)==0)
      {  
         WHILE (INPUT(UP)==0)  {}
         CAPTOCDO ++;
         IF (CAPTOCDO > 10)
            CAPTOCDO = 10;
         HIENTHI_MA7DOAN_THEOCAPDO ();
      }
   }
}
VOID KT_DW ()
{
   IF (INPUT(DW) == 0)
   {
      DELAY_MS (20);
      IF (INPUT(DW)==0)
      {  
         WHILE (INPUT(DW)==0)  {}
         CAPTOCDO --;
         IF (CAPTOCDO < 1)
            CAPTOCDO = 1;
         HIENTHI_MA7DOAN_THEOCAPDO ();
      }
   }
}

VOID MAIN ()
{
   SET_TRIS_A (0XFF);
   SET_TRIS_B (0X00);
   SET_TRIS_C (0X00);
   SET_TRIS_D (0X00);
   
   OUTPUT_LOW (PIN_C3); // CHO PHEP DC CHAY THUAN 
   SETUP_CCP1 (CCP_PWM);   // CAU HINH CHAN CCP1 LA CHAN OUT PWM (PHAT XUNG)
   SETUP_TIMER_2 (T2_DIV_BY_16, 249, 1); // THIET LAP CHU KY XUNG PWM = 0,8MS
   SET_TIMER2 (0);
   OUTPUT_HIGH (ENABLE);
   
   VALUE = 0;
   TTDC = 0;
   CAPTOCDO = 0;
   SET_PWM1_DUTY (VALUE);
   HIENTHI_MA7DOAN_THEOCAPDO ();
   WHILE (TRUE)
   {
      IF (TTDC == 1)
      {
         KT_UP();
         KT_DW();
      }
      KT_START_STOP ();
      VALUE = CAPTOCDO * 100;
      SET_PWM1_DUTY (VALUE);
   }
}
