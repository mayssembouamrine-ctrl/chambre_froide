#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "sensors.h"
#include "controller.h"
#include "display.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);
static unsigned long dernierAffichage = 0;

void displayBegin() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Chambre froide");
}

void displayUpdate() {
  if (millis() - dernierAffichage < 500) return;  // rafraîchit 2 fois par seconde
  dernierAffichage = millis();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(mesures.tempStockage, 1);
  lcd.print("C Comp:");
  lcd.print(compresseur ? "ON " : "OFF");
  lcd.print(" ");

  lcd.setCursor(0, 1);
  if (etat == ALARME) {
    if (alerteTemp && alertePorte) lcd.print("ALARME:TEMP+PORT");
    else if (alerteTemp) lcd.print("ALARME: TEMP    ");
    else lcd.print("ALARME: PORTE   ");
  }
  else if (etat == PORTE_OUVERTE) lcd.print("Porte: OUVERTE  ");
  else if (etat == REFROIDISSEMENT) lcd.print("REFROIDISSEMENT ");
  else lcd.print("NORMAL          ");
}