#include <Arduino.h>
#include "config.h"
#include "alarm.h"

static bool bipActif = false;

void alarmBegin() {
  pinMode(PIN_LED_ALERTE, OUTPUT);
  pinMode(PIN_COMPRESSEUR, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void alarmUpdate(bool alarme, bool compresseurActif) {
  digitalWrite(PIN_LED_ALERTE, alarme);
  digitalWrite(PIN_COMPRESSEUR, compresseurActif);

  // Buzzer : bip 0,5 s ON / 0,5 s OFF pendant l'alarme
  bool bip = alarme && ((millis() / 500) % 2 == 0);
  if (bip && !bipActif) {
    tone(PIN_BUZZER, 2000);
    bipActif = true;
  }
  if (!bip && bipActif) {
    noTone(PIN_BUZZER);
    bipActif = false;
  }
}