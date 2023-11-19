#include <16f877.h> // pic mikrodenetleyiciyi ttan�mlaama yap�yoruz.
#device ADC=10 // analogtan gelen de�er ne ise onu 10 bittik de�ere d�n��t�r�yoruz. Yani gelen de�er 0 ile 1023 aras�nda birde�ere d�n��t�r�l�r. 
#use delay(clock=4000000) //
#fuses XT,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(a) // portA kullan�ca��m�z� belirtiyoruz
#use fast_io(b) // portB kullan�ca��m�z� belirtiyoruz

#define use_portb_lcd TRUE // Lcd tan�ml�yoruz
#include <lcd.c> // lcd k�t�phanesini tan�ml�yoruz.

//Global de�i�kenler tan�m� yap�yoruz.
unsigned long int deger; 
float gerilim,sicaklik;

//Ana fonksiyon tan�m� 
void main()
{
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x20); // a portunun giri� portu oldu�unu bildiriyoruz.
   set_tris_b(0x00); //  b portunun da hepsini ��k�� oldu�unu tan�ml�yoruz.
   
   lcd_init(); // lcd ba�latma fonksiyonu
   
   setup_adc(adc_clock_div_32); // A/D biriminin mod ayar� kullan�lacak frekans bildirilir.
   setup_adc_ports(ALL_ANALOG); 
   
   set_adc_channel(4); // kanal� tan�mlama yap�yoruz.  AN4 prortuna s�cakl�k �l�er ba�l� oldu�undan ona ba�l�yoruz.
   delay_us(20); // Bekleme fonksiyonu
   
   printf(lcd_putc,"\fSicaklik ="); // Termometre ekran�na yazd�rama i�lemi yap�yoruz. \f de ekran� temizliyor.
   
   while(true){
      
      deger=read_adc(); // Analog sinyal ijital veriye cevrilir ve degere atan�r.
      /* Okunan de�eri ondal�kl� ve derece cinsine cevirme i�lemin matematiksel i�lemi:
         5V(en b�y�k de�erimiz) de�eri 1023 b�l�yoruz ��nk� ADC de�eri 10 bitlik oldu�undan buraadan sonuc 0.0048759 V olur
         1000 mv = 1 V oldu�undan 
         0.0048759 V da 4.88759 olur.
         0 mV = 1 derecedir
         10 mv = 3 derecedir.
         buradan denklem olu�turursak her mV'tu 10'a' b�l�p + 2 eklersek de�ere ula�m�� oluruz.
      */
      gerilim=deger*4.88759;
      sicaklik=(gerilim/10)+2; 
      lcd_gotoxy(10,1); // lcd ekran�n� 1 sat�rda 10 birim kayd�r�yoruz. 
      printf(lcd_putc,"%f C",sicaklik);  // ekrana sicaklik de�erini yazd�r�yoruz. 
      delay_ms(100);
   
   }
   
}

