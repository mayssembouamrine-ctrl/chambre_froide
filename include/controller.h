#pragma once

enum Etat { NORMAL, REFROIDISSEMENT, PORTE_OUVERTE, ALARME };

extern Etat etat;
extern bool compresseur;
extern bool alerteTemp;
extern bool alertePorte;

void controllerUpdate();
const char* nomEtat(Etat e);