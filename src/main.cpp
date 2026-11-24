#include <Arduino.h>
#include "config.h"
#include "sensors.h"
#include "controller.h"
#include "alarm.h"
#include "display.h"

unsigned long dernierLog = 0;

void setup() {
  Serial.begin(115200);
  sensorsBegin();
  alarmBegin();
  displayBegin();
  Serial.println("Demarrage OK");
}

void loop() {
  sensorsUpdate();                         // 1. lire les capteurs
  controllerUpdate();                      // 2. décider
  alarmUpdate(etat == ALARME, compresseur);  // 3. commander les sorties
  displayUpdate();                         // 4. afficher

  // Journal série (toutes les secondes)
  if (millis() - dernierLog >= 1000) {
    dernierLog = millis();
    Serial.print("T stockage : ");
    Serial.print(mesures.tempStockage);
    Serial.print(" C | Ambiance : ");
    Serial.print(mesures.tempAmbiante);
    Serial.print(" C, ");
    Serial.print(mesures.humidite);
    Serial.print(" % | Porte : ");
    Serial.print(mesures.porteOuverte ? "ouverte" : "fermee");
    Serial.print(" | Compresseur : ");
    Serial.println(compresseur ? "ON" : "OFF");
  }
}