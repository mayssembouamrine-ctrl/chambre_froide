#pragma once
#include <Arduino.h>

// ----- Broches -----
const int PIN_LED_ALERTE = 33;   // LED rouge : alarme
const int PIN_COMPRESSEUR = 26;  // LED bleue : compresseur simulé
const int PIN_BUZZER = 25;
const int PIN_DS18B20 = 15;      // température de stockage
const int PIN_PORTE = 14;        // interrupteur de la porte
const int PIN_DHT = 4;           // DHT22 : ambiance

// ----- Paramètres du scénario -----
const unsigned long DUREE_MAX_PORTE = 30000;  // 30 s
const float TEMP_DEMARRAGE = 6.0;   // compresseur ON au-dessus
const float TEMP_ARRET = 4.0;       // compresseur OFF à ce seuil ou en dessous
const float TEMP_CRITIQUE = 8.0;    // alarme au-dessus
const float TEMP_FIN_ALARME = 7.0;  // fin d'alarme en dessous