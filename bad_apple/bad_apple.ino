#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "video_data2.h" // Mengimpor data frame dari file header

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Inisialisasi display dengan alamat I2C 0x3C (umum untuk OLED 128x64)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Konstanta untuk video
const int FRAME_RATE = 24; // Harus sesuai dengan saat konversi video
const int FRAME_DELAY = 1000 / FRAME_RATE;
const int FRAME_SIZE = (SCREEN_WIDTH * SCREEN_HEIGHT) / 8; // Ukuran data untuk satu frame dalam byte
const int TOTAL_FRAMES = sizeof(video_frames) / FRAME_SIZE;

unsigned long lastFrameTime = 0;

void setup() {
  Serial.begin(115200);

  // Inisialisasi OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Alokasi SSD1306 gagal"));
    for(;;); // Jangan lanjutkan, biarkan loop di sini
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  // Loop untuk memutar video berulang kali
  for (int frame = 0; frame < TOTAL_FRAMES; frame++) {

    // Cek waktu untuk menjaga frame rate tetap stabil
    while (millis() - lastFrameTime < FRAME_DELAY) {
      // Tunggu
    }
    lastFrameTime = millis();

    // Ambil data frame dari PROGMEM dan tampilkan
    display.clearDisplay();
    display.drawBitmap(0, 0, video_frames + (frame * FRAME_SIZE), SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    display.display();
  }
}