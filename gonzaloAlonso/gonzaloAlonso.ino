/* Camptive portal: Permite configurar la WIFI del microcontrolador sin necesidad
 * de conectarlo al PC. El dispositivo se puede desplegar en el lugar de destino. 
 * Mediante un movil o otro equipo WIFI se accede a la WEb que el Esp genera.
 * Ahí se insertarán los datos de conexión. A partir de entonces se conectará automáticamente
 * al reiniciar el equipo. Pulsado un boton ( definido como CONFIG_PIN ) se fuerza a mostrar
 * la página de configuración de nuevo, para cambiar los datos. Si no se encuentra la red WIFI
 * guardada tras 30s, se muestra la página de configuración.
 * Bibliografía: https://github.com/prampec/IotWebConf/blob/master/examples/IotWebConf01Minimal/IotWebConf01Minimal.ino
 * */
#include <IotWebConf.h>
#define IOTWEBCONF_DEFAULT_AP_MODE_TIMEOUT_MS 5000
#define CONFIG_PIN 15

// El nombre de la red WIFI para acceder a la configuración
const char thingName[] = "testThing";

// Contraseña por defecto
const char wifiInitialApPassword[] = "smartthing";

// Instanciamos Objetos básicos
DNSServer dnsServer;
WebServer server(80);
IPAddress apIP(8, 8, 8, 8);
IPAddress netMsk(255, 255, 255, 0);
IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword );


//***** Variables de cada alumno ******//
// Manuel Dauzon
unsigned long delayLED;
boolean encenderLED ;
#define DELAY_LED 5000
#define PIN_RIEGO 16


/**
 * Codigo de iniciacion
 */
void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");

  // Configuramos el PIN para forzar la página de configuración
  iotWebConf.setConfigPin(CONFIG_PIN);

  // Magia para que al terminar de configurarse se reinicie en modo cliente y todo funciona OK
  iotWebConf.setConfigSavedCallback([]{
    Serial.println("Config SAVED");
    // Reset System
    ESP.restart();
    });

  // Borra la configuracion si presionamos RESET al arrancar
  if (( digitalRead( CONFIG_PIN ) == LOW ) ||(iotWebConf.init() == false)) {
    iotWebConf.resetWifiAuthInfo();
    Serial.println("CONFIG DELETED");
    WiFi.softAPConfig(apIP, apIP, netMsk);
    server.on("/", handleRootConfig);
  }
  else {
    // Arranque en modo normal. Carga la página ROOT
    server.on("/", handleRoot);  
  }

  
  /* Manejadores de páginas. Cada una se cargará al poner su URL
   * Ejemplo:
   * 192.168.4.1/ledOn >> muesrta la página generada con la funciona handleLedOn
   * 192.168.4.1/ >> Es la página principal, ROOT, antes configurada
   */
  server.on("/ledOn", handleLedOn);
  server.on("/config", []{iotWebConf.handleConfig(); });
  server.onNotFound([](){ iotWebConf.handleNotFound(); });

  Serial.println("Ready.");

  // Si debes establecer variables, llama a tu setup desde aquí
  setupEjemplo();
  
}



/* Es imperativo no bloquear este proceso.
 * Las llamadas a delay() están PROHIBIDAS !!!
 * Usar comprobaciones de tiempo usando millis()
 * 
 * CADA USUARIO debe añadir aquí el procedimiento loop propio
 */
void loop() 
{
  // mantiene el servicio DNS, HTTP y captivePortal
  iotWebConf.doLoop();
  loopEjemplo();
}



// Establecemos el pin como salida, y estado inicial
void setupEjemplo() {
  pinMode(PIN_RIEGO, OUTPUT);
  encenderLED = false;  
}


/**
 * Se ejecuta cada loop
 * Comprueba si el booleano correspondiente se ha activado, indicando que se debe realizar
 * la funcion. Despues del tiempo establecido se apaga
 */
void loopEjemplo() {
  // Manuel Dauzon
  if (encenderLED) {      // Solo se cumprueba se han activado el boton
    unsigned long curTime = millis();   // Leemos el tiempo actuali
    if ( curTime > (delayLED + DELAY_LED)) { // Ha pasado el período de temporización ?
      digitalWrite( PIN_RIEGO, LOW);
      encenderLED = false;
      Serial.println( "SET LED ON" );
    }
  } 
}



/**
 * Maneja las peticiones a la página ROOT
 */
void handleRootConfig()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }

  String s = "<!DOCTYPE html>";
  s += "<html lang='en'>";
  s += "<head><meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'/>";
  s += "<style>body {margin:0; padding; font-size: 30px;}a {background-color: #F39;padding: 21px;display: block;color: black;text-decoration: none;text-align: center;}</style>";
  s += "<title>IotWebConf 01 Minimal</title></head><body>";
  s += "<div>Smart Plant Controller</div>";
  s += "<div>Accede a  <a href='config'>configuraci&oacute;n </a> para establecer la red WiFi de tu local</div>";
  s += "</body></html>";

  server.send(200, "text/html", s);
}


/**
 * Página principal
 * En ella se debería mostrar los botones que activan cada uno de
 * las funciones de cada participante
 */
void handleRoot()
{
  String response = "";
  // the content of the HTTP response follows the header:
  response = "<html lang='en'><head>";
  response += "<style type='text/css'>div {padding: 50px;}a {font-size: 50px;background-color: #50ff50;margin: 50px;padding: 20px;text-decoration: none;color: black;border-radius: 5px;}</style>";
  response += "</head><body><div>";
  //response += "<a href='/H'>REGAR PLANTA</a>";
  response += "<a href='/ledOn'>LED ON</a>";
  response += "</div></body></html>";

  server.send(200, "text/html", response );
}


/** 
 * Ejemplo de manejador de peticion de usuario 
 * cada vez que el usuario pincha en un enlace de la WEB principal,
 * se activa la funcion regisitrada al mismo
 */
void handleLedOn()
{
  // Se activa la variable que marca el inicio
  encenderLED = true;
  // Si hay temporización, guardar time actual
  delayLED = millis();

  // Mensaje por puerto serie
  Serial.println( "SET LED ON" );
  // Activa el PIN
  digitalWrite( PIN_RIEGO, HIGH);

  // Vuelve a mostrar la página principal
  handleRoot();
}
