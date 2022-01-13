#include "HX711.h" 
//Este programa permite calibrar la báscula. 
//Se utiliza para determinar el factor de calibración.

//Antes de ejecutar el programa la balanza no debe estar cargada con ningún peso.

//Cableado al ESP32CAM
const int Pin_DT = 4;
const int Pin_SCK = 2; 

//Obtención del factor de conversión para convertir valor de lectura en un valor con unidades de peso.

void setup() {
  Serial.begin(115200);
  balanza.begin(Pin_DT, Pin_SCK);
  Serial.print("Lectura del valor del ADC:t");
  Serial.println(balanza.read());
  Serial.println("No ponga ningún objeto sobre la balanza");
  Serial.println("Destarando...");
  balanza.set_scale(335597.8); //La escala por defecto es 1
  balanza.tare(20);  //El peso actual es considerado Tara.
  Serial.println("Coloque sobre la balanza un peso conocido:");
}

void loop() {

  Serial.print("Valor de lectura: Kg");
  Serial.println(balanza.get_value(10),0);
  delay(100);
}
