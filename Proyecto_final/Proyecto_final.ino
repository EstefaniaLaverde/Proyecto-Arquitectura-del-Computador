//Estefanía Laverde Becerra
//Girasol artificial

#include <ListLib.h>
#include <Servo.h>

Servo servoMotor;
List<int> datos;

//Variables a usar
const int fotoc=0; //Nombre del pin analógico A0
int valor_fc; //Valor leído por el fotoresistor
int grados; //Grados que se van a escribir en el servo
int mini; //Mínimo elemento en la lista
int min_index=0; //Indice de la lista que indica en qué grado se tomó el dato

void setup() {
  // put your setup code here, to run once:
  servoMotor.attach(9);
  pinMode(fotoc, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int gr=0;
  while(gr<=180){ //Barrido para guardar los datos leídos por la fotoresistencia
    servoMotor.write(gr);
    valor_fc=analogRead(fotoc);

    Serial.println(valor_fc);

    datos.Add(valor_fc);
    gr+=1;
    delay(15);
  }
  Serial.print("Hay ");
  Serial.print(datos.Count());
  Serial.println(" elementos en la lista.");

  mini=datos[0]; //Proceso para guardar el dato más pequeño medido y su correspondiente ángulo
  int i=0;
  while(i<=180){
    Serial.print("Estos son los datos de la lista: ");
    Serial.println(datos[i]);
    if(datos[i]<mini){
      mini=datos[i];
      min_index=i;
    }
    i++;
  }
  Serial.print("El mínimo valor medido fue: ");
  Serial.println(mini);
  Serial.print("El índice del mínimo valor medido es: ");
  Serial.println(min_index);

  grados=min_index;
  Serial.print("Los grados escritos en el servo son: "); //No es necesario hacer una conversión porque la lista tiene 180 elementos y el correspondiente al menor grado es el usado en el servo
  Serial.println(grados);

  servoMotor.write(grados); //Se coloca en la posición de máxima exposición (mínima resistencia
  datos.Clear();

  delay(8000); //Se repite el proceso de barrido cada 6 segundos
}
