#include <Servo.h> //library servo

//inisialisasi variabel sensor warna tcs3200
#define S0 2 //pin s0 tcs3200 terhubung ke pin 2 digital
#define S1 3 //pin s1 tcs3200 terhubung ke pin 3 digital
#define S2 4 //pin s2 tcs3200 terhubung ke pin 4 digital
#define S3 5 //pin s3 tcs3200 terhubung ke pin 5 digital
#define sensorOut 6 //pin out tcs3200 terhubung ke pin 6 digital

//deklarasi variabel servo
Servo topServo; //deklarasi variabel servo atas
Servo bottomServo; //deklarasi variabel servo bawah

//deklarasi variabel frekuensi dan color
int frequency = 0; //set variabel frekuensi menjadi 0
int color = 0; ////set variabel color menjadi 0

void setup() {
  pinMode(S0, OUTPUT); //pin S0 sensor TCS3200 sebagai output
  pinMode(S1, OUTPUT); //pin S1 sensor TCS3200 sebagai output
  pinMode(S2, OUTPUT); //pin S2 sensor TCS3200 sebagai output
  pinMode(S3, OUTPUT); //pin S3 sensor TCS3200 sebagai output
  pinMode(sensorOut, INPUT); //pin Out sensor TCS3200 sebagai input

  // Menyetel penskalaan frekuensi ke 20%
  digitalWrite(S0, HIGH); //mengaktifkan pin S0 dengan kondisi HIGH
  digitalWrite(S1, LOW); //mengaktifkan pin S1 dengan kondisi LOW
  
  topServo.attach(7); // Menghubungkan pin out servo motor atas ke pin 7 digital
  bottomServo.attach(8); // Menghubungkan pin out servo motor bawah ke pin 8 digital

  Serial.begin(9600); //memulai komunikasi serial
}

void loop() {

  topServo.write(124); // Menggerakkan servo motor ke 124 derajat
  delay(500); //delay selama setengah detik
  
  for(int i = 124; i > 68; i--) { //menggerakan servo atas dari 124 derajat ke 68 derajat
    topServo.write(i);
    delay(2);
  }
  delay(1000); //delay selama 1 detik
  
  color = readColor(); //membaca warna
  delay(10);  

  switch (color) {
    case 1: //warna merah
    bottomServo.write(30); //servo berotasi ke 30 derajat
    break;

    case 2: //warna hijau
    bottomServo.write(70); //servo berotasi ke 70 derajat
    break;

    case 3: //warna kuning
    bottomServo.write(110); //servo berotasi ke 110 derajat
    break;

    case 4: //warna biru
    bottomServo.write(150); //servo berotasi ke 150 derajat
    break;
    
    default: //optional
    break;
  }
  delay(200);
  
  for(int i = 68; i >29; i--) { //menggerakan servo atas dari 68 derajat ke 29 derajat
    topServo.write(i);
    delay(2);
  } 
  delay(200);
  
  for(int i = 29; i < 124; i++) { //menggerakan servo atas dari 29 derajat ke 124 derajat
    topServo.write(i);
    delay(2);
  }
  color=0; //mereset color
}

// membuat fungsi color - readColor()
int readColor() {
  // Menyetel fotodioda berfilter merah untuk dibaca
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Membaca frekuensi output
  frequency = pulseIn(sensorOut, LOW); //membaca pulsa masukan dari pin sensorOut
  int R = frequency;
  // Mencetak nilai pada serial monitor
  Serial.print("R= ");
  Serial.print(frequency);//mencetak frekuensi warna MERAH
  Serial.print("  ");
  delay(50);

  // Mengatur fotodioda berfilter Hijau untuk dibaca
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Membaca frekuensi output
  frequency = pulseIn(sensorOut, LOW); //membaca pulsa masukan dari pin sensorOut
  int G = frequency;
  // Mencetak nilai pada serial monitor
  Serial.print("G= ");
  Serial.print(frequency);//mencetak frekuensi warna HIJAU
  Serial.print("  ");
  delay(50);

  // Mengatur fotodioda berfilter Biru untuk dibaca
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Membaca frekuensi output
  frequency = pulseIn(sensorOut, LOW); //membaca pulsa masukan dari pin sensorOut
  int B = frequency;
  // Mencetak nilai pada serial monitor
  Serial.print("B= ");
  Serial.print(frequency);//mencetak frekuensi warna BIRU
  Serial.println("  ");
  delay(50);

  if(R<122 & R>54 & G<172 & G>125 & B<111 & B>84){
    color = 1; // Merah
    Serial.println("Merah Terdeteksi");
  }
  if(R<181 & R>110 & G<148 & G>79 & B<118 & B>79){
    color = 2; // Hijau
    Serial.println("Hijau Terdeteksi");
  }
  if(R<100 & R>41 & G<113 & G>53 & B<115 & B>74){
    color = 3; // Kuning
    Serial.println("Kuning Terdeteksi");
  }
   if(R<168 & R>88 & G<118 & G>54 & B<73 & B>33){
     color = 4; // Biru
     Serial.println("Biru Terdeteksi");
   }
  return color;  
}
