#pragma once

// Definisi Frekuensi Nada (Oktaf 6 & 7 untuk volume buzzer maksimal)
#define NOTE_C6  1047
#define NOTE_D6  1175
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_D7  2349
#define NOTE_DS7 2489

extern const int buzzer;

// =========================================================================
// LAGU 1: He's a Pirate (~12,15 detik)
// =========================================================================
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

// =========================================================================
// LAGU 3: Rocky 3 - Eye of the Tiger (~7,5 detik)
// =========================================================================
const int melodiRocky3[] = {
  // Riff utama bagian 1
  NOTE_G6, NOTE_G6, NOTE_AS6, NOTE_C7,
  NOTE_G6, NOTE_G6, NOTE_F6,  NOTE_G6,
  NOTE_G6, NOTE_G6, NOTE_AS6, NOTE_C7,
  NOTE_D7, NOTE_DS7, NOTE_D7, NOTE_C7,
  
  // Riff utama bagian 2 (Resolusi)
  NOTE_G6, NOTE_G6, NOTE_AS6, NOTE_C7,
  NOTE_G6, NOTE_G6, NOTE_F6,  NOTE_G6,
  NOTE_AS6, NOTE_C7, NOTE_D7, NOTE_DS7, NOTE_D7, NOTE_C7, NOTE_AS6, NOTE_G6
};

// Total = 52 ketukan * 145 ms = 7.540 ms (~7,5 detik)
const byte ketukanRocky3[] = {
  // Riff 1
  1, 1, 1, 3,
  1, 1, 1, 3,
  1, 1, 1, 3,
  2, 2, 2, 4,
  
  // Riff 2
  1, 1, 1, 3,
  1, 1, 1, 3,
  1, 1, 1, 1, 1, 1, 2, 4
};

const int tempoDasarRocky3 = 145; // ms per 1 ketukan
const int jumlahNadaRocky3 = sizeof(melodiRocky3) / sizeof(melodiRocky3[0]);

void buzz2() {
  int indeksNada = 0;
  unsigned long waktuMulaiNada = millis();
  bool sedangBunyi = false;

  while (indeksNada < jumlahNadaRocky3) {
    unsigned long sekarang = millis();
    unsigned long durasiTotal = (unsigned long)ketukanRocky3[indeksNada] * tempoDasarRocky3;
    unsigned long durasiBunyi = (durasiTotal * 85) / 100; // 85% bunyi, 15% jeda antar nada

    if (sekarang - waktuMulaiNada < durasiBunyi) {
      if (!sedangBunyi) {
        tone(buzzer, melodiRocky3[indeksNada]);
        sedangBunyi = true;
      }
    } else if (sekarang - waktuMulaiNada < durasiTotal) {
      if (sedangBunyi) {
        noTone(buzzer);
        sedangBunyi = false;
      }
    } else {
      indeksNada++;
      waktuMulaiNada = sekarang;
      sedangBunyi = false;
    }
  }

  noTone(buzzer);
}

void buzz() {
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
      indeksNada++;
      waktuMulaiNada = sekarang;
      sedangBunyi = false;
    }
  }

  noTone(buzzer);
}

// =========================================================================
// LAGU 2: Leave Her, Johnny - Chorus (~12,0 detik)
// =========================================================================
const int melodiJohnny[] = {
  // "Leave her, Johnny, leave her!"
  NOTE_G6, NOTE_A6, NOTE_B6, NOTE_G6, NOTE_E6, NOTE_D6,
  // "Oh, leave her, Johnny, leave her!"
  NOTE_D6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_D7, NOTE_B6, NOTE_A6,
  // "For the voyage is done and the winds don't blow,"
  NOTE_B6, NOTE_C7, NOTE_D7, NOTE_B6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_G6, NOTE_E6, NOTE_D6,
  // "And it's time for us to leave her."
  NOTE_D6, NOTE_E6, NOTE_G6, NOTE_B6, NOTE_A6, NOTE_G6
};

// Total = 60 ketukan * 200 ms = 12.000 ms (12,0 detik)
const byte ketukanJohnny[] = {
  // "Leave her, John-ny, leave her!"
  3, 1, 2, 2, 2, 4,
  // "Oh, leave her, John-ny, leave her!"
  2, 3, 1, 2, 2, 2, 4,
  // "For the voy-age is done and the winds don't blow,"
  1, 1, 2, 2, 2, 1, 1, 2, 2, 2,
  // "And it's time for us to leave her."
  1, 1, 2, 2, 2, 6
};

const int tempoDasarJohnny = 200; // ms per 1 ketukan
const int jumlahNadaJohnny = sizeof(melodiJohnny) / sizeof(melodiJohnny[0]);

void buzz1() {
  int indeksNada = 0;
  unsigned long waktuMulaiNada = millis();
  bool sedangBunyi = false;

  while (indeksNada < jumlahNadaJohnny) {
    unsigned long sekarang = millis();
    unsigned long durasiTotal = (unsigned long)ketukanJohnny[indeksNada] * tempoDasarJohnny;
    unsigned long durasiBunyi = (durasiTotal * 85) / 100; // 85% bunyi, 15% jeda artikulasi

    if (sekarang - waktuMulaiNada < durasiBunyi) {
      if (!sedangBunyi) {
        tone(buzzer, melodiJohnny[indeksNada]);
        sedangBunyi = true;
      }
    } else if (sekarang - waktuMulaiNada < durasiTotal) {
      if (sedangBunyi) {
        noTone(buzzer);
        sedangBunyi = false;
      }
    } else {
      indeksNada++;
      waktuMulaiNada = sekarang;
      sedangBunyi = false;
    }

    // Tambahkan pembacaan sensor atau kontrol LED di sini jika diperlukan
  }

  noTone(buzzer);
}