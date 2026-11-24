///////////INCLUSION///////////////
#include "projTickTock.h"
#include "TM1636.h"
#include "pitches.h"
///////////CONSTANTE LED///////////////
#define LED_D1 2  //LED bleu
#define LED_D2 3  //LED vert
#define LED_D3 4  //LED rouge
#define LED_D4 5  //2e LED rouge
//////////CONSTANTE INTERRUPTEUR///////////
#define KEY_3 11  //Interrupteur K3 
#define KEY_2 10  //Interrupteur K2 
#define KEY_1 9   //Interrupteur K1
/////////CONSTANTE MODES//////////////
#define HEURE false
#define ALARME true
//////////CONSTANTE TEMPS////////////
#define HEURE_MAX 23
#define MINUTE_SEC_MAX 59
#define HEURE_MINUTE_SEC_MIN 0
/////////CONSTANTE VITESSE///////////
#define SPEED 9600
#define DELAY 200 
/////////CONSTANTE MUSIQUE//////////////
#define MARIO 134
#define PIRATE 204
////////NOTE POUR L'ALARME/////////////
int melody[] = {
  // Pirate des caraibes
  /*
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,NOTE_A4, NOTE_G4, NOTE_A4, 0,
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,NOTE_A4, NOTE_G4, NOTE_A4, 0,
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,NOTE_C5, NOTE_A4, NOTE_B4, 0,
    NOTE_A4, NOTE_A4,NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,NOTE_A4, NOTE_G4, NOTE_A4, 0,
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,NOTE_A4, NOTE_G4, NOTE_A4, 0,
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,NOTE_C5, NOTE_A4, NOTE_B4, 0,
    NOTE_E5, 0, 0, NOTE_F5, 0, 0,NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,
    NOTE_E5, 0, 0, NOTE_F5, 0, 0,NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,
  */
  //Mario theme
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0, 0, NOTE_G6, 0, 0, 0,
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0, 0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0,
  0, NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0, 0, NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0, 0, NOTE_DS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3, NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_GS3, 0, 0, 0
};
/////////TEMPO POUR L'ALARME//////////////
int noteDurations[] = {
  //Pirate des caraibes
  /*
    12, 12, 8, 12, 12,12, 12, 8, 12, 12,
    12, 12, 6, 12,12, 12, 8, 12, 12,
    12, 12, 8, 12, 12,12, 12, 6, 12,
    12, 12, 8, 12, 12,12, 12, 12, 12, 12,
    12, 12, 8, 12, 12,12, 12, 12, 8, 12,
    12, 12, 8, 12, 12,8, 12, 8, 12,
    12, 12, 8, 12, 12,12, 12, 6, 6,
    12, 12, 8, 12, 12,12, 12, 8, 12, 12,
    12, 12, 6, 12,12, 12, 8, 12, 12,
    12, 12, 8, 12, 12,12, 12, 6, 12,
    12, 12, 8, 12, 12,12, 12, 12, 12, 12,
    12, 12, 8, 12, 12,12, 12, 12, 8, 12,
    12, 12, 8, 12, 12,8, 12, 8, 12,
    12, 12, 8, 12, 12,12, 12, 6, 6,
    8, 12, 12, 8, 12, 6,12, 12, 12, 12, 12, 12, 12, 12, 6,
    8, 12, 6, 8, 12, 6,12, 12, 12, 12, 12, 4,8,
    12, 6, 8, 12, 6,12, 12, 12, 12, 12, 12, 12, 12, 6,
    8, 12, 6, 8, 12, 6,12, 12, 12, 12, 12, 4,
  */
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  9, 9, 9, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  9, 9, 9, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 6, 3,
  12, 12, 12, 12, 12, 12, 6, 3,
  12, 12, 12, 12, 12, 12, 6, 3,
  12, 12, 12, 12, 12, 12, 6, 6, 18, 18, 18,
  6, 6, 6, 6, 6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10, 10, 10, 10, 3, 3, 3,
};
int thisNote = 0;
////////VARIABLE MODE///////
bool mode = false; //Defini si on est en mode heure ou mode alarme
bool etatb = false;//Defini si le buzzer est actif
char snooze = 0;//Defini si le snooze est actif
///////VARIABLE MISC///////
bool b = false;//Variable servant a faire clignoté les 2 point de l'afficheur
bool a = false;//Variable permettant a la sonnerie de partir plus d'une fois par utilisation et a ne pas repartir si les heure n'ont pas changer
bool c = false;//Variable servant a faire alterner les 2 LED rouges quand la sonnerie pars
//////VARIABLE HEURE/////////
char heure = 12;//Variable determinant les heures courantes
char minute = 0;//Variable determinant les minutes courantes
char heure2 = 0;//Variable determinant les heures de l'alarme
char minute2 = 0;//Variable determinant les minutes de l'alarme
char seconde = 0;//Variable determinant les secondes
////////VARIABLE DELAI ET SNOOZE//////////
//Variable utiliser pour delai non bloquant et le snooze
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
const long interval = 1000;
const long interval2 = 400;
long interval3 = 0;
char minute_snooze = 0;
/////////VARIABLE INTERRUPTEUR K3////////////////////
bool key_3_state = true;      // État du bouton K3 (0 = appuyé, 1 = non-appuyé)
bool key_3_released = false;  // Si K3 a été appuyé et relaché

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SPEED);          //Initialization port série
  initTickTockShield();         //Appel fonction pour initializer tick tock shield
  init7seg();                   //Appel fonction pour initializer afficheur 7 segment
}

void loop() {
  // put your main code here, to run repeatedly:
  if (etatb == true)           // Lancer l'alarme quand le buzzer est defini actif
    musique();                  // Appel de la fonction pour la mélodie de l'alarme
  incrementerTemps();           // Appel de la fonction qui augment le temps
  afficherTemps();              // Appel de la fonction qui affiche le temps
  modifierTemps();              // Appel de la fonction qui modifie le temps
  modes();                      // Appel de la fonction quie permet de changer de mode
}
void afficherTemps() {          // Affiche le temps
  if (mode == HEURE) {          // Affiche le temps courant lorsque le mode est celui des heures
    do7seg(minute, heure);      // Appel de la fonction affichant les entrants sur l'afficheur 7 segment
    clignote();                 // Appel de la fonction fesant clignoté les 2 point de l'afficheur
  }
  if ((mode == ALARME) && (etatb == false)) {     // affiche Le temps de reveil lorsque le mode est celui de l'alarme
    do7seg(minute2, heure2);    // Appel de la fonction affichant les entrants sur l'afficheur 7 segment
    clignotePoint(0);           // Eteint les 2 points de l'afficheur
  }
}
void modifierTemps() {          // Modifier le temps
  if ((mode == HEURE) && (etatb == false)) {              // Modifier le temps pour l'heure courante si le mode est celui des heures et si le buzzer est inactif
    digitalWrite(LED_D1, HIGH);           // Allumer la Led bleue et eteindre les autres
    digitalWrite(LED_D2, LOW);
    digitalWrite(LED_D3, LOW);
    digitalWrite(LED_D4, LOW);
    if ((digitalRead(KEY_2) == LOW) && (snooze == 0)) {   // Augmenter les heures courantes lorsque bouton K2 est appuyer et que le snooze n'est pas actif
      heure++;
      delay(DELAY);
    }
    if ((digitalRead(KEY_1) == LOW) && (snooze == 0)) {   // Augmenter les minutes courantes lorsque bouton K3 est appuyer et que le snooze n'est pas actif
      minute++;
      delay(DELAY);
    }
  }
  if (mode == ALARME) {                       // Modifier le temps  de l'alarme si le mode est celui de l'alarme
    digitalWrite(LED_D2, HIGH);              // Allumer la LED verte et eteindre les autres
    digitalWrite(LED_D1, LOW);
    digitalWrite(LED_D3, LOW);
    digitalWrite(LED_D4, LOW);
    etatb = false;
    if (digitalRead(KEY_2) == LOW) {           // Augmenter les heures de l'alarme lorsque bouton K2 est appuyer
      heure2++;
      delay(DELAY);
    }

    if (digitalRead(KEY_1) == LOW) {           // Augmenter les minutes de l'alarme lorsque bouton K3 est appuyer
      minute2++;
      delay(DELAY);
    }
    if (heure2 > HEURE_MAX)                   //Retourner les heures a 0 lorsque elle ateigne 24
      heure2 = HEURE_MINUTE_SEC_MIN;

    if (minute2 > MINUTE_SEC_MAX)             //Retourner les minutes a 0 lorsque elle ateigne 60
      minute2 = HEURE_MINUTE_SEC_MIN;
  }
}

void incrementerTemps() {                    // Augmente le temps sans intervention humaine
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {       //Delai non-bloquant
    previousMillis = currentMillis;
    seconde++;                                        //Augmente les secondes
    Serial.println(seconde, DEC);
    if (seconde > MINUTE_SEC_MAX) {               //Retourner les secondes a 0 lorsque elle ateigne 60 et augmentes les minutes
      seconde = HEURE_MINUTE_SEC_MIN;
      minute++;
      if (snooze == 1) {                       // Si le snooze est activé, commence compteure pour temps elapsé
        minute_snooze ++;
      }
    }
  }
  if (minute > MINUTE_SEC_MAX) {          //Retourner les minutes a 0 lorsque elle ateigne 60 et augmente les heures
    heure++;
    minute = HEURE_MINUTE_SEC_MIN;
  }
  if (heure > HEURE_MAX)                      //Retourner les heures a 0 lorsque elle ateigne 24
    heure = HEURE_MINUTE_SEC_MIN;
}
void modes() {                                //Change les modes
  if (key_3_state != digitalRead(KEY_3)) {           //Detecte quand K3 est appuyé
    if (key_3_state == true) {
      key_3_state = false;
    } else {
      key_3_state = true;
      key_3_released = true;
    }
  }
  if ((key_3_released) && (snooze == 0)) {           // Change le mode lorsque K3 est appuyé et que snooze n'est pas actif
    mode = !mode;
    key_3_released = false;
    delay(DELAY);
  }

  if ((heure == heure2) && (minute == minute2)) {       // Lance la sonnerie quand le temps courant et de l'alarme sont les mêmes
    if (a == false) {
      etatb = true;
      a = true;
      thisNote = 0;
    }
  }
  if ((digitalRead(KEY_1) == LOW) && (digitalRead(KEY_2) == LOW)) {    // Arrete la sonnerie
    key_3_released = false;
    noTone(BUZZER);
    etatb = false;
    delay(500);
    snooze = 0;
  }
  if ((digitalRead(KEY_3) == LOW) && (etatb == true)) {         //Arrete la sonnerie et lance le snooze
    noTone(BUZZER);
    etatb = false;
    delay(500);
    snooze = 1;
    thisNote = 0;
  }
  if (!(heure == heure2) || !(minute == minute2)) {           // Modifie une varible pour permettre a la sonnerie de sonner plusieur fois d'affiler sans repartir directement si l'heure est toujours pareille
    a = false;
  }
  if ((minute_snooze == 15) && (snooze == 1)) {             // Lancent la sonnerie quand 15 minutes sont passer
    etatb = true;
    minute_snooze = 0;
  }
}
void clignote() {       //Fait clignoter les 2 points de l'afficheur 7 segment et les LED rouges quand la sonnerie et active
  unsigned long currentMillis2 = millis();       //Delai non-bloquant
  if (currentMillis2 - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis2;

    if (b == true) {
      clignotePoint(1);
      b = false;
      c = false;
    } else {
      clignotePoint(0);
      b = true;
      c = true;
    }
  }
  if (etatb == true) {  //Change l'état des Led lorsque la sonnerie est active
    if (c == true) {
      digitalWrite(LED_D3, HIGH);
      digitalWrite(LED_D1, LOW);
      digitalWrite(LED_D4, LOW);
      digitalWrite(LED_D2, LOW);
    }
    if (c == false) {
      digitalWrite(LED_D4, HIGH);
      digitalWrite(LED_D1, LOW);
      digitalWrite(LED_D3, LOW);
      digitalWrite(LED_D2, LOW);
    }
  }
}
void musique() {  //Fait jouer la musique lorsque la sonnerie est active

  unsigned long currentMillis3 = millis();
  if (currentMillis3 - previousMillis3 >= interval3) {  //Delai non-bloquant
    previousMillis3 = currentMillis3;
    int noteDuration = 1000 / noteDurations[thisNote]; //Tempo
    interval3 = noteDuration * 1.70;  //Defini l'interval entre chaque note
    tone(BUZZER, melody[thisNote], noteDuration);  //Active le buzzer selon la note et le tempo
    thisNote++;  //Change la note et le tempo
    if (thisNote > MARIO)    //Fait reccomencer la musique lorsqu'elle est fini
      thisNote = 0;
  }
}
void initTickTockShield() { //Initialization du Tick tock shield
  //Initialisation DELs
  pinMode(LED_D1, OUTPUT);  //Definir LED bleu en output
  pinMode(LED_D2, OUTPUT);  //Definir LED vert en output
  pinMode(LED_D3, OUTPUT);  //Definir LED rouge en output

  digitalWrite(LED_D1, LOW);  //Eteindre LED bleu
  digitalWrite(LED_D2, LOW);  //Eteindre LED vert
  digitalWrite(LED_D3, LOW);  //Eteindre LED rouge

  //Initialisation Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  //Initialisation Boutons
  pinMode(KEY_3, INPUT_PULLUP);  //Definir bouton poussoir K3 en input
  pinMode(KEY_2, INPUT_PULLUP);  //Definir bouton poussoir K2 en input
  pinMode(KEY_1, INPUT_PULLUP);  //Definir bouton poussoir K1 en input
}
