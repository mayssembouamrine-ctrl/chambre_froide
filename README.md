# Smart Cold Chain & Storage Monitoring System (S.C.C.S.)

Mini-projet ENET'COM Sfax : système embarqué de surveillance d'une chambre froide, basé sur l'ESP32.

## Fonctionnalités
- Mesure de la température de stockage (DS18B20)
- Température et humidité ambiantes (DHT22)
- Détection d'ouverture de porte, avec alarme après 30 s
- Refroidissement simulé (LED bleue) avec hystérésis
- Alarme lumineuse et sonore (LED rouge + buzzer)
- Affichage LCD 16×2 I2C
- Machine à états : NORMAL, REFROIDISSEMENT, PORTE_OUVERTE, ALARME

## Outils
VS Code, PlatformIO (ESP32, framework Arduino), Wokwi

## Simulation
https://wokwi.com/projects/479801827729125377

## Organisation du code
- `src/main.cpp` : initialisation et boucle principale
- `src/sensors.cpp`, `src/controller.cpp`, `src/alarm.cpp`, `src/display.cpp` : modules
- `include/` : fichiers d'en-tête et `config.h` (broches, seuils)

## Auteur
Mayssem Bouamrine, encadrée par M. Jmal Wassim
