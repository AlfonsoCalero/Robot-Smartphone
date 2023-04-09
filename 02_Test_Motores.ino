//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MOTORES Motor paso a paso 28BYJ-48 con Arduino y driver ULN2003
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//definicion de pins
const int motorPin1 = 4;    // 28BYJ48 In1
const int motorPin2 = 5;    // 28BYJ48 In2
const int motorPin3 = 6;   // 28BYJ48 In3
const int motorPin4 = 7;   // 28BYJ48 In4

const int motorPin5 = 8;    // 28BYJ48 In1
const int motorPin6 = 9;    // 28BYJ48 In2
const int motorPin7 = 10;   // 28BYJ48 In3
const int motorPin8 = 11;   // 28BYJ48 In4

//definicion variables
int motorSpeed = 1200;   //variable para fijar la velocidad
int stepCounter_d = 0;     // contador para los pasos
int stepCounter_i = 0;     // contador para los pasos
int stepsPerRev = 4076;  // pasos para una vuelta completa

//tablas con la secuencia de encendido (descomentar la que necesiteis)
//secuencia 1-fase
//const int numSteps = 4;
//const int stepsLookup[4] = { B1000, B0100, B0010, B0001 };

//secuencia 2-fases
//const int numSteps = 4;
//const int stepsLookup[4] = { B1100, B0110, B0011, B1001 };

//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

// ========================================================================================================
// SETUP
// ========================================================================================================
void setup()
{
  //declarar pines como salida
  // MOTOR 1
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  // MOTOR 2
  pinMode(motorPin5, OUTPUT);
  pinMode(motorPin6, OUTPUT);
  pinMode(motorPin7, OUTPUT);
  pinMode(motorPin8, OUTPUT);

  Serial.begin(9600);  //iniciamos el puerto serie
  Serial.println("Servos preparados. Comandos: w,z,d,a,s.");
}

// ========================================================================================================
// BUCLE
// ========================================================================================================
void loop()
{
  // Espera a que se ingrese un comando por el monitor serial
  while (!Serial.available()) {}

  // Lee el comando ingresado
  char comando = Serial.read();

  // Realiza una acción en función del comando recibido
  switch (comando) {
    case 'w': Serial.println("Adelante");         Adelante(1);  break;
    case 's': Serial.println("Atras");            Atras(1);     break;
    case 'd': Serial.println("Derecha");          Derecha(1);    break;
    case 'a': Serial.println("Izquierda");        Izquierda(1);  break;
    default:  Serial.println("Comando inválido"); break;
  }
}

// ========================================================================================================
// Adelante
// ========================================================================================================
void Adelante(int iNumeroVueltas)
{
  for (int i = 0; i < stepsPerRev * iNumeroVueltas; i++)
  {
    clockwise_d();
    clockwise_i();
    delayMicroseconds(motorSpeed);
  }
}

// ========================================================================================================
// Atras
// ========================================================================================================
void Atras(int iNumeroVueltas)
{
  for (int i = 0; i < stepsPerRev * iNumeroVueltas; i++)
  {
    anticlockwise_d();
    anticlockwise_i();
    delayMicroseconds(motorSpeed);
  }
}

// ========================================================================================================
// Izquierda
// ========================================================================================================
void Izquierda(int iNumeroVueltas)
{
  for (int i = 0; i < stepsPerRev * iNumeroVueltas; i++)
  {
    clockwise_d();
    anticlockwise_i();
    delayMicroseconds(motorSpeed);
  }
}

// ========================================================================================================
// Derecha
// ========================================================================================================
void Derecha(int iNumeroVueltas)
{
  for (int i = 0; i < stepsPerRev * iNumeroVueltas; i++)
  {
    anticlockwise_d();
    clockwise_i();
    delayMicroseconds(motorSpeed);
  }
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// FUNCIONES DE BAJO NIVEL
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void clockwise_i()
{
  stepCounter_i++;
  if (stepCounter_i >= numSteps) stepCounter_i = 0;
  setOutput_i(stepCounter_i);
}

void clockwise_d()
{
  stepCounter_d--;
  if (stepCounter_d < 0) stepCounter_d = numSteps - 1;
  setOutput_d(stepCounter_d);
}

void anticlockwise_i()
{
  stepCounter_i--;
  if (stepCounter_i < 0) stepCounter_i = numSteps - 1;
  setOutput_i(stepCounter_i);
}

void anticlockwise_d()
{
  stepCounter_d++;
  if (stepCounter_d >= numSteps) stepCounter_d = 0;
  setOutput_d(stepCounter_d);
}

void setOutput_d(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}

void setOutput_i(int step)
{
  digitalWrite(motorPin5, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin6, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin7, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin8, bitRead(stepsLookup[step], 3));
}

