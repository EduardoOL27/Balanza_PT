#include "HX711.h" 
//Este programa permite calibrar la báscula. 
//Se utiliza para determinar el factor de calibración.

//Antes de ejecutar el programa la balanza no debe estar cargada con ningún peso.

//Cableado al ESP32CAM
const int Pin_DT1 = 4;
const int Pin_SCK1 = 2; 
const int Pin_DT2 = 14;
const int Pin_SCK2 = 15;
const int Pin_DT3 = 13;
const int Pin_SCK3 = 12;

int piezas1P;
int piezas2P;
float Cable;
const int interruptor1P = 0.136; //peso por unidad en gramos. 
const int interruptor2P = 0.272; //peso por unidad en gramos.
const int Cablethw = 0;

HX711 balanza1;
HX711 balanza2;
HX711 balanza3;

//Obtención del factor de conversión para convertir valor de lectura en un valor con unidades de peso.

void setup() {
  Serial.begin(115200);
  balanza1.begin(Pin_DT1, Pin_SCK1);
  balanza2.begin(Pin_DT2, Pin_SCK2);
  balanza3.begin(Pin_DT3, Pin_SCK3);
  Serial.print("Lectura del valor del ADC: Kg");
  Serial.println(balanza1.read());
  Serial.println(balanza2.read());
  Serial.println(balanza3.read());
  Serial.println("No ponga ningún objeto sobre la balanza");
  Serial.println("Destarando...");
  balanza1.set_scale(243196.7814); //La escala por defecto es 1
  balanza2.set_scale(246630.719); //La escala por defecto es 1
  balanza3.set_scale(); //La escala por defecto es 1
  balanza1.tare(20);  //El peso actual es considerado Tara.
  balanza2.tare(20);  //El peso actual es considerado Tara.
  balanza3.tare(20);  //El peso actual es considerado Tara.
  Serial.println("Coloque sobre la balanza un peso conocido:");
}

void loop() {

if (balanza1.wait_ready_timeout(1000)) {
    float peso1 = balanza1.get_units(20);
    piezas1P = peso1 / interruptor1P;
      Serial.println("La bascula 1 tiene: ");
      Serial.print(piezas1P);
      Serial.println(" Unidades");
} else {
    Serial.println("HX711 no encontrado.");
    delay(2000);
}
  
if (balanza2.wait_ready_timeout(1000)) {
    float peso2 = balanza2.get_units(20);
    piezas2P = peso2 / interruptor2P;
      Serial.println("La bascula 2 tiene: ");
      Serial.print(piezas2P);
      Serial.println(" Unidades");
} else {
    //Serial.println("HX711 no encontrado.");
    //delay(2000);
}

//if (balanza3.wait_ready_timeout(1000)) {
    //float peso3 = balanza3.get_units(20);
    //Cable = peso3 / Cablethw;
      //Serial.println("La bascula 3 tiene: ");
      //Serial.print(Cable,2);
      //Serial.println(" Metros");
//} else {
    //Serial.println("HX711 no encontrado.");
    //delay(2000);
//}
}
