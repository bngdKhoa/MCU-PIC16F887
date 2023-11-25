#INCLUDE <16F887.H>
#FUSES HS
#USE DELAY (CLOCK = 20M)
#DEFINE ON_OFF1 PIN_B6 
#DEFINE ON_OFF2 PIN_B7
#DEFINE LED1    PIN_B0
#DEFINE LED2    PIN_B1

VOID MAIN ()
{
   SET_TRIS_B (0XFC);
   PORT_B_PULLUPS (0XFC);
   OUTPUT_LOW (LED1);
   OUTPUT_LOW (LED2);
   
KTR:
   IF (INPUT(ON_OFF1)==0)
   {
      DELAY_MS (10);
      IF (INPUT (ON_OFF1)== 0)
      {  WHILE(INPUT (ON_OFF1)==0)
         IF (INPUT_STATE (LED2)==0){}   
         {
            OUTPUT_TOGGLE (LED1);
         }
      }
   }
   ELSE IF (INPUT(ON_OFF2)==0)
   {
      DELAY_MS(5);
      IF (INPUT(ON_OFF2)== 0)
      {  WHILE (INPUT(ON_OFF2)==0){}
         IF (INPUT_STATE (LED1)==1)
         {
            OUTPUT_TOGGLE (LED2);
         }
      }
   }
   GOTO KTR;
}
