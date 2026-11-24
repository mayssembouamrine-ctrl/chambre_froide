#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include "config.h"
#include "sensors.h"

Mesures mesures;

static OneWire oneWire(PIN_DS18B20);
static DallasTemperature capteur(&oneWire);
static DHT dht(PIN_DHT, DHT22);

static unsigned long derniereLecture = 0;
static unsigned long derniereLectureDHT = 0;

void sensorsBegin() {
  pinMode(PIN_PORTE, INPUT_PULLUP);  // LOW = porte ouverte
  capteur.begin();
  capteur.setWaitForConversion(false);  // pas d'attente bloquante
  capteur.requestTemperatures();
  dht.begin();
}

void sensorsUpdate() {
  // Porte : lue à chaque tour
  mesures.porteOuverte = (digitalRead(PIN_PORTE) == LOW);

  // Température de stockage : toutes les secondes
  if (millis() - derniereLecture >= 1000) {
    derniereLecture = millis();
    float t = capteur.getTempCByIndex(0);
    capteur.requestTemperatures();  // prépare la prochaine mesure

    if (t == DEVICE_DISCONNECTED_C) {
      mesures.stockageValide = false;
    } else {
      mesures.tempStockage = t;
      mesures.stockageValide = true;
    }
  }

  // Ambiance : toutes les 2 secondes
  if (millis() - derniereLectureDHT >= 2000) {
    derniereLectureDHT = millis();
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {  // on ignore les mesures invalides
      mesures.tempAmbiante = t;
      mesures.humidite = h;
    }
  }
}