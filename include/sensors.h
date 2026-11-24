#pragma once

// Toutes les mesures du système au même endroit
struct Mesures {
  float tempStockage = 0;
  bool stockageValide = false;   // false si le capteur est absent
  float tempAmbiante = 0;
  float humidite = 0;
  bool porteOuverte = false;
};

extern Mesures mesures;

void sensorsBegin();
void sensorsUpdate();