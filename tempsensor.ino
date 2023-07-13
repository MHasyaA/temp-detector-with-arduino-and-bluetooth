#include <Servo.h>
#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#define PIN_TRIG 7
#define PIN_ECHO 6

Servo my_servo;
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int BUZZER = 3;
const byte SIMBOLDERAJAT = B11011111;
double temp_obj;

void setup() {
  // put your setup code here, to run once:
  
  lcd.init();                  
  lcd.backlight();
  lcd.clear();
  mlx.begin();
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  my_servo.attach(4);
  my_servo.write(0);
  delay(50);

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(BUZZER, HIGH);
  
  temp_obj = mlx.readObjectTempC()*1.128; //*1.128 (UNTUK PENGALI KALIBRASI)

  //Tampilkan di serial monitor
  Serial.println("Ambient = ");
  Serial.println("*C");
  Serial.println(temp_obj);
  

  //BUZZER peringatan jika suhu >37 celcius
  if(temp_obj > 37.5)
  {
    digitalWrite(BUZZER, HIGH);
    delay(30);
    lcd.setCursor(0, 0);
    lcd.print("SUHU ANDA TINGGI");
    lcd.setCursor(0, 1);
    lcd.print("Suhu: ");
    lcd.setCursor(7, 1);
    lcd.print(temp_obj);
    lcd.setCursor(12, 1);
    lcd.write(SIMBOLDERAJAT);
    lcd.setCursor(13, 1);
    lcd.print("C");
    my_servo.write(180);
    delay(50);
  }
  else
  {
    digitalWrite(BUZZER, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Selamat Datang  ");
    lcd.setCursor(0, 1);
    lcd.print("Suhu:");
    lcd.setCursor(7, 1);
    lcd.print(temp_obj);
    lcd.setCursor(12, 1);
    lcd.write(SIMBOLDERAJAT);
    lcd.setCursor(13, 1);
    lcd.print("C"); 
    my_servo.write(0);
    delay(50);  
  }

  // Motor Servo
  

  //my_servo.write(180);
  //delay(500);

  // Berikan isyarat HIGH pada pin trig 10 mikrodetik
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);    // Tunda 10 mikrodetik
  digitalWrite(PIN_TRIG, LOW);

  // Baca hasilnya di pin echo
  double selang = pulseIn(PIN_ECHO, HIGH);

  // Hitung jarak yang diperoleh
  double jarak = 0.0343 * ( selang / 2);

  if (jarak > 25 || jarak <= 0)
  {
   //digitalWrite(BUZZER, LOW);
   Serial.print(jarak);
   Serial.println("cm");
  } 
  else
  {
   //digitalWrite(BUZZER, HIGH);
   Serial.print(jarak);
   Serial.println("cm");
  }
  delay(1000);
}
