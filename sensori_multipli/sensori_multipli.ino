#include<Servo.h>

#define SERVO_PIN 9

Servo servo;

int pos = 90; // posizione del servo, di partenza centrata

int pinS[] = {A0, A1, A2, A3, A4};

int lett[] = {0, 0, 0,0,0};

void setup(){
    /*
        - imposta i pin
        - imposta il servo
        - inizializza serial per debug
    */
    for(int i = 0; i < 5; i++){
        pinMode(pinS[i], INPUT);
    }

   servo.attach(SERVO_PIN);
   servo.write(pos);

   Serial.begin(9600);
}

void loop(){
    // legge i valori dei sensori
     for(int i = 0; i < 5; i++){
        lett[i] = analogRead(pinS[i]);
        Serial.print("{");
        Serial.print(i);
        Serial.print(":");
        Serial.print(lett[i]);
        Serial.print("}");
    }
    Serial.println();
    // fa cose
    /* 
        quello che deve succedere: 
            ho una funzione F che ha come parametri i valori letti dai 5 sensori.
            con una funzione matematica calcolo il valore di offset della posizione. (se devo spostarmi da una parte o dall'altra)
    */
    int off = calcolaOffset(lett[0], lett[1], lett[2], lett[3], lett[4]);
    // gira il servo nella direzione dettata, utilizzando una funzione che controlli che non sia fuori dal bound il nuovo valore  
    // Serial.print("posizione attuale:"); Serial.print(pos); 
    
    servo.write(pos + off);   
    pos = servo.read();
    // Serial.print("posizione mod:"); Serial.println(pos); 
    // aspetta un attimo
    delay(15);
}

/*
    funzione che presi i valori letti dai vari sensori (con x3 quello centrale e x1 quello più a sinistra)
    calcola l'offset
    per farlo mi baso sull'errore:
    voglio essere nella situazione dove i due sensori opposti hanno un valore uguale.
    quindi calcolo per ogni coppia l'errore quadratico e in base a quale è minore da un certo contributo all'offset
    poi capirò come usare x3 (idea: per piccoli aggiustamenti mi baso su x2 e x3 e x4 e x3)
*/
int calcolaOffset(int x1, int x2, int x3, int x4, int x5){
    // calcolo errori quadratici
    // Serial.print("diff estremi semplice:");
    // Serial.print((x1-x5));
    // Serial.print("diff centrali semplice:");
    // Serial.print((x2-x4));
    // Serial.println();
    int diffEstremi =  (x1-x5) * (x1-x5);
    int diffCentrali = (x2-x4) * (x2-x4);
    // Serial.print("diff estremi:");
    // Serial.print(diffEstremi);
    // Serial.print("diff centrali:");
    // Serial.print(diffCentrali);
    if(diffEstremi > diffCentrali){
        return (x1-x5) > 0 ? -5 : +5;
    }else{
        return (x2-x4) > 0 ? -2 : +2;
    }
    return 0;
}

/*
    funzione che data una posizione (globale) e un offset restituisce il valore che:
        - è posizione + offset se <= 180 e >= 0
        - 180 se posizione + offset > 180
        - 0 se posizione + offset < 0
*/
int ottieniPos(int offset){
    if(pos + offset < 0){
        return 0;
    }else if(pos + offset > 180){
        return 180;
    }
    return pos + offset;
}