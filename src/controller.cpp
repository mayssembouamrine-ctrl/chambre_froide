#include <Arduino.h>
#include "config.h"
#include "sensors.h"
#include "controller.h"

Etat etat = NORMAL;
bool compresseur = false;
bool alerteTemp = false;
bool alertePorte = false;

static Etat etatPrecedent = NORMAL;
static bool porteAvant = false;
static unsigned long debutOuverture = 0;

const char* nomEtat(Etat e) {
  switch (e) {
    case NORMAL: return "NORMAL";
    case REFROIDISSEMENT: return "REFROIDISSEMENT";
    case PORTE_OUVERTE: return "PORTE_OUVERTE";
    case ALARME: return "ALARME";
  }
  return "?";
}

void controllerUpdate() {
  // ----- Porte + chrono non bloquant -----
  bool ouverte = mesures.porteOuverte;

  if (ouverte && !porteAvant) {
    debutOuverture = millis();
    Serial.println("Porte OUVERTE");
  }
  if (!ouverte && porteAvant) {
    alertePorte = false;
    Serial.println("Porte FERMEE");
  }
  porteAvant = ouverte;

  if (ouverte && millis() - debutOuverture >= DUREE_MAX_PORTE) {
    if (!alertePorte) Serial.println("ALERTE : porte ouverte trop longtemps !");
    alertePorte = true;
  }

  // ----- Température : compresseur et alarme (avec hystérésis) -----
  if (mesures.stockageValide) {
    float t = mesures.tempStockage;

    if (t > TEMP_DEMARRAGE) compresseur = true;
    else if (t <= TEMP_ARRET) compresseur = false;

    if (t > TEMP_CRITIQUE) {
      if (!alerteTemp) Serial.println("ALERTE : temperature critique !");
      alerteTemp = true;
    } else if (t < TEMP_FIN_ALARME) {
      alerteTemp = false;
    }
  }

  // ----- Machine à états -----
  if (alerteTemp || alertePorte) etat = ALARME;
  else if (ouverte) etat = PORTE_OUVERTE;
  else if (compresseur) etat = REFROIDISSEMENT;
  else etat = NORMAL;

  if (etat != etatPrecedent) {
    Serial.print("Etat : ");
    Serial.println(nomEtat(etat));
    etatPrecedent = etat;
  }
}