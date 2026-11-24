#include "projTickTock.h"
#include "TM1636.h"

extern TM1636 tm1636(7,8);

////////////////////////////////////
void allumeSonnerie(){
  digitalWrite(BUZZER, HIGH);
}

void eteintSonnerie(){
  digitalWrite(BUZZER, LOW);
}

////////////////////////////////////
void init7seg (){
  tm1636.start();     // démarre le tm1636
  tm1636.init();      // met le contraste par défaut
}

void do7seg (byte minute, byte heure){
  int8_t disp[4];

  disp[0]=heure/10;     // premier bloc 7seg : dizaines des heures
  disp[1]=heure%10;     // 2e bloc 7seg : unites des heures
  disp[2]=minute/10;     // 3e bloc : dizaines des minutes
  disp[3]=minute%10;     // 4e bloc : unites des minutes
  tm1636.display(disp);    // affiche les 4 blocs 7seg
}

void clignotePoint (boolean clignote){
  tm1636.point(clignote);
  
}
