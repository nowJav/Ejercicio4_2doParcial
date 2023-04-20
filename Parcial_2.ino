/*const int LRD_PIN = A0; // Pin analógico utilizado para el sensor LRD
const int BOTON_PIN = 2; // Pin digital utilizado para el botón
const int LED_PIN = 6; // Pin digital utilizado para el LED
bool leerSensor = false; // Variable para indicar si se debe leer el sensor

void setup() {
  Serial.begin(9600);
  pinMode(BOTON_PIN, INPUT_PULLUP); // Se establece el pin del botón como entrada con resistencia pull-up interna
  pinMode(LED_PIN, OUTPUT); // Se establece el pin del LED como salida
}

void loop() {
  if (leerSensor) {
    int valor = analogRead(LRD_PIN);
    Serial.println(valor);
    if (valor < 100) { // Si el valor del LRD es menor a 100, se enciende el LED
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
  
  // Se lee el estado del botón y se cambia el valor de la variable leerSensor cuando se presiona el botón
  if (digitalRead(BOTON_PIN) == LOW) {
    delay(50); // Se añade un pequeño retraso para evitar lecturas erróneas debido a rebotes del botón
    leerSensor = !leerSensor;
  }
}*/

const int LRD_PIN = A0; // Pin analógico utilizado para el sensor LRD
const int BOTON_PIN = 2; // Pin digital utilizado para el botón
const int LED_PIN_1 = 6; // Pin digital utilizado para el LED 1
const int LED_PIN_2 = 7; // Pin digital utilizado para el LED 2
const int LED_PIN_3 = 8; // Pin digital utilizado para el LED 3
//const int LED_PIN_4 = 9; // Pin digital utilizado para el LED 4
//const int LED_PIN_5 = 10; // Pin digital utilizado para el LED 5
//const int LED_PIN_6 = 11; // Pin digital utilizado para el LED 6
bool leerSensor = false; // Variable para indicar si se debe leer el sensor
bool ultimaLecturaBoton = false; // Variable para almacenar la última lectura del botón
int ultimoValor = 0; // Variable para almacenar el último valor leído del LRD
bool aumentando = false; // Variable para indicar si la cantidad de luz está aumentando o disminuyendo

void setup() {
  Serial.begin(9600);
  pinMode(BOTON_PIN, INPUT_PULLUP); // Se establece el pin del botón como entrada con resistencia pull-up interna
  pinMode(LED_PIN_1, OUTPUT); // Se establecen los pines de los LEDs como salida
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  //pinMode(LED_PIN_4, OUTPUT);
  //pinMode(LED_PIN_5, OUTPUT);
  //pinMode(LED_PIN_6, OUTPUT);
}

void loop() {
  // Lectura del botón
  bool lecturaBoton = digitalRead(BOTON_PIN);
  if (lecturaBoton != ultimaLecturaBoton && lecturaBoton == LOW) {
    leerSensor = !leerSensor; // Se invierte el estado de la variable leerSensor al presionar el botón
    if (!leerSensor) { // Si se deja de leer el sensor, se apagan todos los LEDs
      digitalWrite(LED_PIN_1, LOW);
      digitalWrite(LED_PIN_2, LOW);
      digitalWrite(LED_PIN_3, LOW);
      //digitalWrite(LED_PIN_4, LOW);
      //digitalWrite(LED_PIN_5, LOW);
      //digitalWrite(LED_PIN_6, LOW);
    }
  }
  ultimaLecturaBoton = lecturaBoton;
  
  // Lectura del sensor y encendido/apagado secuencial de los LEDs
  if (leerSensor) {
    int valor = analogRead(LRD_PIN);
    Serial.println(valor);
    if (valor < ultimoValor) { // Si la cantidad de luz está disminuyendo
      aumentando = false;
    } else if (valor > ultimoValor) { // Si la cantidad de luz está aumentando
      aumentando = true;
    }
    ultimoValor = valor;
    if (valor <= 100) { // Si el valor del LRD es menor a 100, se encienden los 6 LEDs secuencialmente
      if (aumentando) {
        for (int i = 1; i <= 6; i++) {
          digitalWrite(i + 2, HIGH);
          delay(100);
        }
      } else {
        for (int i = 6; i >= 1; i--) {
          digitalWrite(i + 2, LOW);
          delay(10);
        }
      }
    }
  }
}     