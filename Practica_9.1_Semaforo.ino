#define sRojo 12
#define sAmarillo 11
#define sVerde 10
#define pRojo 9
#define pVerde 8
#define boton 7
#define potenciometro A0
boolean estadoBoton = false;  
int valorPot = 0;
int tiempoEsperaPot = 10; 
int crossTime = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(sRojo, OUTPUT);
  pinMode(sAmarillo, OUTPUT);
  pinMode(sVerde, OUTPUT);
  pinMode(pRojo, OUTPUT);
  pinMode(pVerde, OUTPUT);
  pinMode(boton, INPUT);
}

void loop() {
  Serial.println(valorPot); 
  valorPot = analogRead(potenciometro);
  digitalWrite (pRojo, HIGH); 
  digitalWrite (sVerde, HIGH); 
  estadoBoton = digitalRead(boton);
  if (estadoBoton == true) {
    esperaPotenciometro();
    secuenciaSemaforo();
  }
}

void secuenciaSemaforo() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(sVerde, LOW);
    delay(1000);
    digitalWrite(sVerde, HIGH);
    delay(1000);
    digitalWrite(sVerde, LOW);
  }
  digitalWrite(sAmarillo, HIGH);
  delay(2500);
  digitalWrite(sAmarillo, LOW);
  digitalWrite(sRojo, HIGH);
  delay(2000);
  digitalWrite(pRojo, LOW);
  digitalWrite(pVerde, HIGH);
  delay(crossTime); 
  secuenciaPeaton();
  digitalWrite(pRojo, HIGH);
  delay(2000);
  digitalWrite(sRojo, LOW);
  digitalWrite(pVerde, LOW);
}

void secuenciaPeaton() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pVerde, LOW);
    delay(1000);
    digitalWrite(pVerde, HIGH);
    delay(1000);
    digitalWrite(pVerde, LOW);
    
  }
}

void esperaPotenciometro() {
  valorPot = valorPot * tiempoEsperaPot; 
  Serial.println(valorPot);
  digitalWrite(sVerde, HIGH); 
  crossTime = map(valorPot, 0, 1023, 10, 25)*100; 
  Serial.println(crossTime);
  delay(crossTime);
}
