# INCLUDE <16F887.H>
# FUSES HS 
# USE DELAY (CLOCK = 20M)

# DEFINE SER PIN_D0  //dinh nghia cac chan 
# DEFINE SCK PIN_D1
# DEFINE RCK PIN_D2

# DEFINE X1_D2 0x11 // tuong ung 0001 0001 theo kieu hexa
# DEFINE V1_D2 0x14
# DEFINE D1_X2 0x0A
# DEFINE D1_V2 0x22

# DEFINE TG_DO 29   // dinh nghia thoi gian den
# DEFINE TG_XANH 26
# DEFINE TG_VANG 2

VOID XUAT_1BYTE (UNSIGNED INT8 BYTEXUAT)  // xuat 1 byte du lieu, lay lan luot tung bit du lieu dich ra
{
   UNSIGNED INT8 I; // 1001 0100 bit co trong so thap nhat 
   # BIT BSER = BYTEXUAT.7 // dich bit co trong so cao nhat duoc truy xuat dia chi bit 
   FOR (I = 0; I < 8; I++)
   {
      OUTPUT_BIT (SER, BSER); 
      OUTPUT_LOW (SCK); // tao xung clock (canh len) dich du lieu
      OUTPUT_HIGH (SCK);
      BYTEXUAT = BYTEXUAT << 1; // tiep theo toi bit thu 6 
   }
}
VOID XUAT_4LED_7DOAN (UNSIGNED INT8 LED4, LED3, LED2, LED1)
{
   XUAT_1BYTE (LED4);
   XUAT_1BYTE (LED3);
   XUAT_1BYTE (LED2);
   XUAT_1BYTE (LED1);
   OUTPUT_LOW (RCK); // tac dong tang chot du lieu
   OUTPUT_HIGH (RCK);
}
UNSIGNED INT8 DEM1, DEM2;
UNSIGNED INT8 MA7D [] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

VOID MAIN ()
{
   SET_TRIS_D (0x00);// cau hinh port xuat du lieu 
   SET_TRIS_C (0x00);
LAP:
   // TRANG THAI X1_D2
   OUTPUT_C (X1_D2);
   DEM1 = TG_XANH;
   DEM2 = TG_DO;
   DO 
   {
      XUAT_4LED_7DOAN (MA7D [DEM1/10], MA7D [DEM1%10], MA7D [DEM2/10], MA7D [DEM2%10]);
      DELAY_MS (1000);
      DEM1 --;
      DEM2 --;
   }
   WHILE (DEM1 != 255);
   // TRANG THAI V1_D2
   OUTPUT_C (V1_D2);
   DEM1 = TG_VANG;
   DO
   {
      XUAT_4LED_7DOAN (MA7D[DEM1/10], MA7D[DEM1%10], MA7D[DEM2/10], MA7D[DEM2%10]);
      DELAY_MS (1000);
      DEM1--;
      DEM2--;
   }
   WHILE (DEM1 != 255);
   // TRANG THAI D1_X2
   OUTPUT_C (D1_X2);
   DEM1 = TG_DO;
   DEM2 = TG_XANH;
   DO
   {
      XUAT_4LED_7DOAN (MA7D[DEM1/10], MA7D[DEM1%10], MA7D[DEM2/10], MA7D[DEM2%10]);
      DELAY_MS (1000);
      DEM1--;
      DEM2--;
   }
   WHILE (DEM2 != 255);
   // TRANG THAI D1_V2
   OUTPUT_C (D1_V2);
   DEM2 = TG_VANG;
   DO
   {
      XUAT_4LED_7DOAN (MA7D[DEM1/10], MA7D[DEM1%10], MA7D[DEM2/10], MA7D[DEM2%10]);
      DELAY_MS (1000);
      DEM1--;
      DEM2--;
   }
   WHILE (DEM1 != 255);
      GOTO LAP;
}

