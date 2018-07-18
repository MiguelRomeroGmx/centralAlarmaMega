#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
#include <Keypad.h>

int estado;
int control = 0;
int buzzer = 15;
int posicion=0;    // necesaria para la clave
int cursor= 6 ;      // posicion inicial de la clave en el LCD
int clave=0;       // para el LCD
const byte Filas = 4;          //KeyPad de 4 filas
const byte Cols = 4;           //y 4 columnas
char letra = '0';
byte Pins_Filas[] = {7, 6, 5, 4};     //Pines Arduino para las filas.
byte Pins_Cols[] = { 3, 2, 1, 0};     // Pines Arduino para las columnas.
     
     char Teclas [ Filas ][ Cols ] =
          {
              {'1','2','3','A'},
              {'4','5','6','B'},
              {'7','8','9','C'},
              {'*','0','#','D'}
          };
     Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

char codigoSecreto[4] = {'1','2','3','4'};

void setup() {
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16,INPUT);
  pinMode(17,INPUT);
  pinMode(18,INPUT);
  pinMode(19,INPUT);
  lcd.begin(16, 2);           // Fijamos el numero de caracteres y filas
  lcd.print(" ALARMA CENTRAL");
  tone(buzzer,500);     
  delay(100);
  noTone(buzzer);
  tone(buzzer,600);     
  delay(100);
  noTone(buzzer);
  tone(buzzer,800);     
  delay(100);
  noTone(buzzer);
  lcd.setCursor(0, 1);
  lcd.print(" SISTEMA LISTO");
  delay(1000);
  lcd.clear();
}

void loop() {
  
  digitalWrite(14, HIGH);
  delay(200);
  char pulsacion = Teclado1.getKey();  
      if (pulsacion == 'A'){
        tone(buzzer,350);
        delay(50);
        noTone(buzzer);
        contrasena(); 
          }
      else {
      lcd.setCursor(0, 0);
      lcd.print("ESPERANDO ACCION");
      }
  }  

 void contrasena() { 
  lcd.setCursor(0, 0);
  lcd.print("INTRODUCIR CLAVE");
  for(int control = 0; control <= 40; control++){
  delay(200);
  
    char pulsacion = Teclado1.getKey() ;    
      if (pulsacion != 0)  {  
          lcd.setCursor(0, 1);
          //lcd.print("Clave:"); 
          if (pulsacion != 'A' && pulsacion != 'B' && pulsacion != 'C' && pulsacion != 'D' && clave==0){
              letra = pulsacion;
              tone(buzzer,350); 
              lcd.setCursor(cursor,1);
              lcd.print(pulsacion);
              delay(50);
              noTone(buzzer);
              cursor++;
              
              if (pulsacion == codigoSecreto[posicion])
                  posicion ++; // aumentamos posicion si es correcto el digito
                  
                  if (posicion == 4){
                              
                      delay(200);                           
                      tone(buzzer,500);
                      delay(100);
                      noTone(buzzer);
                      tone(buzzer,600);
                      delay(100);
                      noTone(buzzer);
                      tone(buzzer,800);
                      delay(100);
                      noTone(buzzer); 
                      lcd.clear(); 
                      control = 50; 
                      clave_correcta();
                          
                  }
                      
                      if(cursor > 9){
                          cursor = 6;     // lo volvemos a colocar al inicio
                          posicion = 0; 
                          lcd.setCursor(6,0);
                          //lcd.print(" "); 
                         

                         if(clave==0)  {       // comprobamos que no hemos acertado
                              lcd.setCursor(0,0);      
                              lcd.print("CLAVE INCORRECTA "); 
                              tone(buzzer,70,500); // para generar
                              delay(250); // tono de error
                              noTone(buzzer);
                              delay(1000);
                              lcd.clear();
                              control = 50;
                              loop();
                          } 
                      }
                  }   
        }
  }
  lcd.clear();
  posicion = 0;
  clave = 0;
  //pulsacion = '0';
  cursor = 6;
  control = 50;
  loop();
}


void clave_correcta(){
  clave = 1;
  cursor = 6; 
  lcd.setCursor(0,0);      
  lcd.print(" CLAVE CORRECTA "); 
  delay(1000);
  lcd.clear();
  control = 50;
  posicion = 0;
  clave = 0;
  loop();
  
}

void alarma_activa(){

if(digitalRead(16)==HIGH || digitalRead(17)==HIGH || digitalRead(18)==HIGH || digitalRead(19)==HIGH){
  lcd.setCursor(0, 0);
  lcd.print("   ACTIVACION");
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  delay(500);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  delay(100);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  delay(500);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  delay(100);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  delay(500);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  delay(100);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  delay(500);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  delay(100);
  lcd.clear();
                                  
} 
 
 return;


  
}

