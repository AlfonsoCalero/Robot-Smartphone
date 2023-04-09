// ========================================================================================================
// SETUP
// ========================================================================================================
void setup() {
  Serial.begin(9600);  //iniciamos el puerto serie

  setup_servos();
  setup_motores();
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
    // BRAZOS
    case 'q': Serial.println("brazo derecho arriba");     derecho_arriba();     break;
    case 'w': Serial.println("brazo derecho medio");      derecho_medio();      break;
    case 'e': Serial.println("brazo derecho abajo");      derecho_abajo();      break;
    case 'a': Serial.println("brazo izquierdo arriba");   izquierdo_arriba();   break;
    case 's': Serial.println("brazo izquierdo medio");    izquierdo_medio();    break;
    case 'd': Serial.println("izquierdo abajo");          izquierdo_abajo();    break;
    case 'z': Serial.println("dos brazos arriba");         dos_arriba();        break;
    case 'x': Serial.println("dos brazos medio");          dos_medio();         break;
    case 'c': Serial.println("dos brazos abajo");          dos_abajo();         break;
    // MOTORES
    case 'o': Serial.println("Adelante");                 Adelante(1);          break;
    case 'l': Serial.println("Atras");                    Atras(1);             break;
    case 'k': Serial.println("Derecha");                  Derecha(1);           break;
    case 'l': Serial.println("Izquierda");                Izquierda(1);         break;
    default:  Serial.println("Comando inválido");         break;
  }
  
}
