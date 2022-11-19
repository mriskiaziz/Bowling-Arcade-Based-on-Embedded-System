//library servo
#include <Servo.h>
Servo myservo;

//library lcd
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//inisiasi skor awal = 0
int skor = 0;          //kondisi skor awal main
bool play = false;     //boolean main
bool tanda = true;     //boolean tanda waktu mulai
bool mulai = false;    // boolean kondisi awal lcd 

//ldr
int LDR = A0;   //inisiasi pin analog ldr
int nilaiLDR = 0;   //nilai awal ldr = 0

//buzzer 
#define buzzPin 9    //inisiasi pin buzzer
int amp = 1500;     //set aplitudo/volume buzzer
int nada[] = {  //inisiasi array nada dasar
  0, 523, 587, 659, 698,  783, 880, 987, 1046, 1174,
  1318, 1396, 1567, 1769, 1975, 2093
};

#define pin_servo 5  //inisiasi pin servo 

#define pin_pir 4    //inisiasi pin pir

#define pin_led 12   //inisiasi pin led
#define pin_led1 13

#define trig_pin 3   //inisiasi trig dan echo pin ultrasonik
#define echo_pin 2   
unsigned long duration;   
unsigned int distance;

#define pin_button 11    //inisiasi pin button

void setup() 
{  
  pinMode(pin_pir, INPUT);   
  
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
  myservo.attach(pin_servo);
  
  lcd.init();
  lcd.backlight();

  pinMode(buzzPin, OUTPUT);

  pinMode(pin_button, INPUT_PULLUP);

  Serial.begin(9600);

}
  

void loop() 
{ 
  arcade();
  
  ldr();

  status_led();
  
  ultrasonik();
 
  //monitoring sensor di serial monitor
  Serial.println((String)"ultrasonik: "+distance+" cm");
  Serial.println((String)"sensor pir: "+digitalRead(pin_pir));
  Serial.println ((String)"Nilai LDR : "+nilaiLDR); 
  Serial.println ();

  buka_servo();
  
  button_reset();

  int start;    //variabel menampung nilai waktu mulai
  int temp;     //variabel antisipasi bug
  //kondisi permainan dimulai
  if(play == true)
  {
    if(tanda == true) 
    { 
      start = millis() / 999;
      tanda = false; 
      lcd.clear();
     }
      int waktu = (millis() / 999) - start;
      temp = waktu;
      if(temp <= 30)
      {
        lcd.setCursor(0, 0);
        lcd.print((String)"--- time :"+waktu+" ---");
        hitung();
       }

    if(temp >= 31)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print((String)"   waktu habis  ");
      delay(1500);
      lcd.clear();
      tutup_servo();
      lcd.setCursor(0, 0);
      lcd.print((String)" skor akhir : "+skor);
      delay(5000);
      skor = 0;
      lcd.clear();
      play = false;
      tanda = true;
      mulai = false;
      arcade();
     }
   }
}

//tampilan lcd awal 
void arcade()
{
    if(mulai == false)
    {
      lcd.print((String)"BOWLING ARCADE");
      delay(3000);
      lcd.clear();
      lcd.print((String)"HAVE FUN");
      mulai = true;
    }
}

//fungsi menghitung skor dengan sensor pir
void hitung()
{
  if(digitalRead(pin_pir))
  {
    skor = skor + 1;
    lcd.setCursor(0, 1);
    lcd.print((String)"--- skor : "+ skor+" ---");
    tesNada();    //membunyikan nada buzzer
    //monitoring skor di serial monitor
    Serial.println((String)skor);
  }    
}

//fungsi pembacaan sensor ulrasonik
void ultrasonik()
{
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);  
  distance = duration / 58.2;    
  delay(100); 
}

// fungsi pembacaan sensor ldr
void ldr()
{
  nilaiLDR = analogRead(LDR);
}

//fungsi menyatakan status nyala/matinya led dengan sensor ldr
void status_led()
{
  //kondisi gelap maka led nyala
  if(nilaiLDR <= 10)
  {
    digitalWrite(pin_led, HIGH);
    digitalWrite(pin_led1, HIGH);
  }
  //kondisi terang maka led mati
  else
  {
    digitalWrite(pin_led, LOW);
    digitalWrite(pin_led1, LOW);
  }
}

//fungsi membuka sevo memulai permainan
void buka_servo()
{
  //kondisi servo terbuka 
  if(distance > 3 && distance <= 8)
    {
      myservo.write(0);
      delay(1000);
      myservo.write(90);
      delay(1000);  
      play = true;
    }
}

//fungsi menutup servo permainan selesai
void tutup_servo()
{
    myservo.write(90);
    delay(1000);
    myservo.write(0);
    delay(1000);  
}


//fungsi mereset skor 
void button_reset()
{
  if(digitalRead(pin_button) == LOW)
  {
    skor = 0;
    lcd.setCursor(0, 1);
    lcd.print((String)"--- skor : "+ skor+" ---");
  }
}

//fungsi set nada me gustas tu
void tesNada()
{
  bunyi(8, 400);
  bunyi(9, 500);
  bunyi(10, 800);
  bunyi(8, 500);
  bunyi(8, 300);
  bunyi(9, 300);
  bunyi(10, 1000);
  bunyi(8, 500);
  bunyi(10, 500);
  bunyi(10, 300);
  bunyi(9, 300);
  bunyi(9, 500);
  bunyi(8, 300);
  bunyi(9, 1000);
  noTone(buzzPin);    
}

//fungsi membunyikan nada me gustas tu
void bunyi(int nadaKe, int lama)
{
  tone(buzzPin, nada[nadaKe], amp);  
  delay(lama / 2);  
}
