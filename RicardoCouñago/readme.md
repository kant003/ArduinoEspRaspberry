<h1>Activación de la bomba de riego</h1>

Esta parte del proyecto de __cuidado de una planta__ es la encargada de activar la __bomba de riego__ durante un tiempo determinado.

Para ello se conecta la bomba a la placa en el pin especificado y se prepara el código que se explica a continuación.

Tras la definición e inicialización de las variables necesarias se crea la función __activar bomba__. Esta función se encarga de encender la bomba, pero no de controlar el tiempo, ya que esto debe hacerse desde el __loop__ para no bloquear el resto de funcionalidades. Para controlar el tiempo se utiliza la función __millis()__ que cuenta el tiempo transcurrido desde el comienzo del programa y se actualiza constantemente.

Las funciones que necesiten hacer uso de este método, como activar el riego con un botón, lo único que tendrán que hacer es cambiar el valor del booleano __regar__ a __true__ y el del entero __tiempoRiego__ al tiempo deseado en __milisegundos__. La propia función se encarga ya de resetear estos valores a false y 0 respectivamente al terminar el proceso.

Código del programa:

```c
int pinBomba = 14; //Este pin habrá que cambiarlo dependiendo de la placa.
unsigned int inicio=millis();
boolean regar=false; //Cambiar a true para iniciar el riego
unsigned int tiempoRiego=0;  //Tiempo que la bomba estará encendida

void setup() {
  pinMode(pinBomba, OUTPUT); //Definicion del pin en modo Output
}


//Funcion que activa la bomba el tiempo pasado en milisegundos.
void activarBomba(boolean encendido){
  if(encendido){
    digitalWrite(pinBomba, HIGH);
  }else{
    digitalWrite(pinBomba, LOW);
  }
}

void loop() {

  //Este parte del código habrá que ponerla en el loop general
  curtime=millis();
  if(regar && (curtime<tiempoRiego+inicio)){
    activarBomba(true);
  }else{
    regar=false;  //regar se cambia a false pasado el tiempo para que se corte el riego
    tiempoRiego=0;  //se resetea el tiempo a 0
  }
 
}
```