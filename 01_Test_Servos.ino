#include <Servo.h>

// ========================================================================================================
// DERECHO: Arriba, Abajo, Medio (0,90,180)
// IZQUIERDO: Arriba, Abajo, Medio (180,90,0)
// DOS: Arriba, Abajo, Medio  (180,0)  (0,180)   (90,90)
// ========================================================================================================

Servo brazo_i;  // crea el objeto servo
Servo brazo_d;  // crea el objeto servo

const int retardo=10;

int pos_i=180;    // posicion actual brazo izquierdo
int pos_d=0;    // posicion actual brazo derecho

const int servo_i=3;    // se mueve al derecho 180-0
const int servo_d=2;    // esta montado al reves => se mueve al reves 0-180

// ========================================================================================================
// SETUP
// ========================================================================================================
void setup() {
   brazo_i.attach(servo_i);  // vincula el servo al pin digital 2
   brazo_d.attach(servo_d);  // vincula el servo al pin digital 3

   brazo_d.write(pos_d);    
   brazo_i.write(pos_i);    

   Serial.begin(9600);  //iniciamos el puerto serie
   Serial.println("Servos preparados. Comandos: a,s,d,f,g,h,j,k.");
}

// ========================================================================================================
// BUCLE
// ========================================================================================================
void loop() {


  // Espera a que se ingrese un comando por el monitor serial
  while (!Serial.available()) {}

  // Lee el comando ingresado
  char comando = Serial.read();

  // Realiza una acción en función del comando recibido
  switch (comando) {
    case 'q': Serial.println("derecho arriba");     derecho_arriba();     break;
    case 'w': Serial.println("derecho medio");      derecho_medio();      break;
    case 'e': Serial.println("derecho abajo");      derecho_abajo();      break;
    case 'a': Serial.println("izquierdo arriba");   izquierdo_arriba();   break;
    case 's': Serial.println("izquierdo medio");    izquierdo_medio();    break;
    case 'd': Serial.println("izquierdo abajo");    izquierdo_abajo();    break;
    case 'z': Serial.println("dos arriba");         dos_arriba();         break;
    case 'x': Serial.println("dos medio");          dos_medio();          break;
    case 'c': Serial.println("dos abajo");          dos_abajo();          break;
    default:  Serial.println("Comando inválido");   break;
  }
 
}


// ========================================================================================================
// ========================================================================================================
void mueve_servo(int servo, int pos_final)
{
  int inc=1;
  int pos_inicial= pos_d;

  if (servo==servo_i) pos_inicial= pos_i;

  if (pos_final!=pos_inicial)
  {
    if (pos_final<pos_inicial) inc=-1;
    for (int pos = pos_inicial; pos !=pos_final; pos += inc) 
    {
      if (servo==servo_i) brazo_i.write(pos);              
      else brazo_d.write(pos);              
      delay(retardo);                       
    }
  }

  if (servo==servo_i) pos_i= pos_final;
  else pos_d= pos_final;
}

void derecho_arriba() {    mueve_servo(servo_d,180); }
void derecho_abajo()  {  mueve_servo(servo_d,0);  }
void derecho_medio() {   mueve_servo(servo_d,90); }
void izquierdo_arriba() {  mueve_servo(servo_i,0);  }
void izquierdo_abajo() {  mueve_servo(servo_i,180);  }
void izquierdo_medio() {  mueve_servo(servo_i,90);  }

void dos_servos(int pos_final_d, int pos_final_i)
{
  int inc_d=1;
  int inc_i=1;

  if (pos_d<pos_final_d) inc_d=1;
  else inc_d=-1;

  if (pos_i<pos_final_i) inc_i=1;
  else inc_i=-1;

  while (pos_d!=pos_final_d && pos_i!=pos_final_i)
  {
     if (pos_d==pos_final_d) inc_d=0;
     if (pos_i==pos_final_i) inc_i=0;
    
    pos_d += inc_d;
    pos_i += inc_i;

    brazo_d.write(pos_d);    
    brazo_i.write(pos_i);    
    delay(retardo);
  }
}

void dos_arriba() { dos_servos(180,0);}
void dos_abajo()  {dos_servos(0,180);}
void dos_medio()  {dos_servos(90,90);}