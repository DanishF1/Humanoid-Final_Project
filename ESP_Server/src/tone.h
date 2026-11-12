#pragma once
#define NOTE_D6  1175
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_C7  2093
#define NOTE_D7  2349
#define NOTE_DS7 2489

// Melodi utama "He's a Pirate" (Oktaf tinggi agar suara maksimal)
const int melodi[] = {
  NOTE_D6, NOTE_F6,
  NOTE_G6, NOTE_G6, NOTE_G6, NOTE_A6,
  NOTE_AS6, NOTE_AS6, NOTE_AS6, NOTE_C7, NOTE_A6,
  NOTE_A6, NOTE_G6, NOTE_F6, NOTE_G6,

  NOTE_D6, NOTE_F6,
  NOTE_G6, NOTE_G6, NOTE_G6, NOTE_A6,
  NOTE_AS6, NOTE_AS6, NOTE_AS6, NOTE_C7, NOTE_A6,
  NOTE_A6, NOTE_G6, NOTE_F6,

  NOTE_D6, NOTE_F6,
  NOTE_G6, NOTE_G6, NOTE_G6, NOTE_AS6,
  NOTE_C7, NOTE_C7, NOTE_C7, NOTE_D7, NOTE_DS7,
  NOTE_D7, NOTE_C7, NOTE_D7, NOTE_G6,

  NOTE_G6, NOTE_A6,
  NOTE_AS6, NOTE_AS6, NOTE_C7, NOTE_D7,
  NOTE_G6, NOTE_G6, NOTE_AS6, NOTE_A6,
  NOTE_A6, NOTE_FS6, NOTE_G6
};

// Durasi tiap nada dalam kelipatan ketukan (Total ~12,15 detik)
const byte ketukan[] = {
  1, 1,
  2, 1, 1, 2,
  2, 1, 1, 1, 1,
  2, 1, 1, 2,

  1, 1,
  2, 1, 1, 2,
  2, 1, 1, 1, 1,
  2, 1, 3,

  1, 1,
  2, 1, 1, 2,
  2, 1, 1, 1, 1,
  2, 1, 1, 2,

  1, 1,
  2, 1, 2, 1,
  3, 1, 1, 1,
  2, 1, 4
};

const int tempoDasar = 150; // ms per 1 ketukan
const int jumlahNada = sizeof(melodi) / sizeof(melodi[0]);
extern const int buzzer;

void buzz(){
int indeksNada = 0;
  unsigned long waktuMulaiNada = millis();
  bool sedangBunyi = false;

  while (indeksNada < jumlahNada) {
    unsigned long sekarang = millis();
    unsigned long durasiTotal = (unsigned long)ketukan[indeksNada] * tempoDasar;
    unsigned long durasiBunyi = (durasiTotal * 85) / 100; // 85% bunyi, 15% jeda antar nada

    if (sekarang - waktuMulaiNada < durasiBunyi) {
      if (!sedangBunyi) {
        tone(buzzer, melodi[indeksNada]);
        sedangBunyi = true;
      }
    } else if (sekarang - waktuMulaiNada < durasiTotal) {
      if (sedangBunyi) {
        noTone(buzzer);
        sedangBunyi = false;
      }
    } else {
      // Pindah ke nada berikutnya setelah durasi total tercapai
      indeksNada++;
      waktuMulaiNada = sekarang;
      sedangBunyi = false;
    }

    // Anda bisa menambahkan pembacaan sensor atau kontrol LED di sini agar tetap berjalan paralel
  }

  noTone(buzzer);
}