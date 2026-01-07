String mode = "MIX"; 
String newMode = ""; 

void setup() {
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  Serial.println("Zadaj mod (VYPNUTIE/MIX/CLASSIC/STRIEDANIE/VYPLN/STRIEDANIE150):");
}

void loop() {

  if (Serial.available()) {
    newMode = Serial.readString();
    newMode.trim();
    mode = newMode;
    Serial.print("Zmeneny mod na: ");
    Serial.println(mode);
  }

  if (mode == "VYPNUTIE") {
    vypnutie();
  }
  else if (mode == "MIX") {
    mixMode();
  }
  else if (mode == "CLASSIC") {
    classic();
  }
  else if (mode == "STRIEDANIE") {
    striedanie();
  }
  else if (mode == "VYPLN") {
    striedanieDva();
  }
  else if (mode == "STRIEDANIE150") {
    striedanieTri();
  }
  else {
    Serial.println("Neexistujuci mod");
  }
}



void vypnutie(){
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(4,HIGH);
  delay(50);
}
void classic()
{
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(200);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  delay(200);
}

void znova()
{
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  delay(100);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(8,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  delay(100);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(4,HIGH);
  delay(100);
  digitalWrite(8,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  delay(100);
}

void striedanie(){
  digitalWrite(7,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  delay(100);
  digitalWrite(7,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  delay(100);
  digitalWrite(7,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(4,HIGH);
  delay(100);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  delay(100);
}

void striedanieDva(){
  digitalWrite(9,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(6,LOW);
  delay(100);
  digitalWrite(4,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(7,LOW);
  delay(100);
  digitalWrite(4,LOW);
  digitalWrite(8,LOW);
  delay(100);
  digitalWrite(9,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(5,HIGH);
  delay(100);

}
void striedanieTri(){
  digitalWrite(7,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(150);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  delay(150);

}

void mixMode(){
    vypnutie();
    for(int i = 0;i < 3; i++){
      classic();
    }
    vypnutie();
    for(int i = 0;i < 6; i++){
      striedanie();
    }
    vypnutie();
    for(int i = 0;i < 3; i++){
      striedanieDva();
    }
    vypnutie();
    for(int i = 0;i < 3; i++){
      striedanieTri();
    }
    vypnutie();
    for(int i = 0;i < 6; i++){
      znova();
    }
    vypnutie();
    for(int i = 0;i < 3; i++){
      striedanieDva();
    }
    vypnutie();
    for(int i = 0;i < 6; i++){
      znova();
    }
    vypnutie();
    for(int i = 0;i < 3; i++){
      striedanieTri();
    }
}