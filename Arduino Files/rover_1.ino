const int motorIzqPin1 = 2;  // Pin 1 del motor izquierdo
const int motorIzqPin2 = 3;  // Pin 2 del motor izquierdo
const int motorDerPin1 = 4;  // Pin 1 del motor derecho
const int motorDerPin2 = 5;  // Pin 2 del motor derecho

const int DerPWM = 6;
const int IzqPWM = 7;

void setup() {
  // Inicializar pines de los motores
  pinMode(motorIzqPin1, OUTPUT);
  pinMode(motorIzqPin2, OUTPUT);
  pinMode(motorDerPin1, OUTPUT);
  pinMode(motorDerPin2, OUTPUT);
  pinMode(DerPWM, OUTPUT);
  pinMode(IzqPWM, OUTPUT);

  // Inicializar comunicación serial
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int commaIndex = data.indexOf(',');

    if (commaIndex != -1) {
      String valX = data.substring(0, commaIndex);
      String valY = data.substring(commaIndex + 1);

      int posX = valX.toInt();
      int posY = valY.toInt();

      controlGiro(posX);
      controlAvance(posY);
    }
  }
}

void controlGiro(int posX) {
  int velocidad = map(abs(posX), 0, 320, 255, 0);

  if (posX < 0) {
    // Mover hacia la izquierda
    digitalWrite(motorIzqPin1, HIGH);
    digitalWrite(motorIzqPin2, LOW);
    digitalWrite(motorDerPin1, LOW);
    digitalWrite(motorDerPin2, HIGH);
    analogWrite(DerPWM, velocidad);
    analogWrite(IzqPWM, velocidad);
    
  } else {
    // Mover hacia la derecha
    digitalWrite(motorIzqPin1, LOW);
    digitalWrite(motorIzqPin2, HIGH);
    digitalWrite(motorDerPin1, HIGH);
    digitalWrite(motorDerPin2, LOW);
    analogWrite(DerPWM, velocidad);
    analogWrite(IzqPWM, velocidad);
    
  }
}

void controlAvance(int posY) {
  int velocidad = map(abs(posY), 0, 240, 255, 0);

  if (posY < 0) {
    // Mover hacia la izquierda
    digitalWrite(motorIzqPin1, LOW);
    digitalWrite(motorIzqPin2, HIGH);
    digitalWrite(motorDerPin1, LOW);
    digitalWrite(motorDerPin2, HIGH);
    analogWrite(DerPWM, velocidad);
    analogWrite(IzqPWM, velocidad);
    
    
  } else {
    // Mover hacia la derecha
    digitalWrite(motorIzqPin1, HIGH);
    digitalWrite(motorIzqPin2, LOW);
    digitalWrite(motorDerPin1, HIGH);
    digitalWrite(motorDerPin2, LOW);
    analogWrite(DerPWM, velocidad);
    analogWrite(IzqPWM, velocidad);
    
  }
}
