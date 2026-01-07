#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);

// UID PRVEJ A DRUHEJ KARTY
byte card1[4] = {0xF5, 0x2A, 0x52, 0xA3};
byte card2[4] = {0x80, 0x90, 0x6D, 0xA4};

bool compareUID(byte *uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != rfid.uid.uidByte[i]) return false;
  }
  return true;
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Prilož RFID kartu...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  // === PODMIENKY PRE KARTY ===
  if (compareUID(card1)) {
    Serial.println("PRISTUP POVOLENY — karta 1!");
    // sem môžeš pridať servo, LED, relé...
  }
  else if (compareUID(card2)) {
    Serial.println("PRISTUP POVOLENY — karta 2!");
  }
  else {
    Serial.println("NEZNAMA KARTA — pristup zamietnuty!");
  }

  rfid.PICC_HaltA();
}
