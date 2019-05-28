#  Gonzalo Alonso Castro


## Sistema de Configuración de la red WiFi para el ESP32 (compatible con esp8266)

A la hora de desplegar el proyecto en el lugar de destino, se necesita configurar la red WiFI ( nombre de red y contraseña ). Tradicionalmente, al desarroyar aplicaciones con microcontroladores se establecía a través de puerto serie, actualizando el firmware del equipo.

Existe una forma más versátil, haciendo que el microcontrolador genere una red WiFi temporal a la que conectarse cuando no tiene configuración establecida o nos e encuentra la que hay guardada.
La librería _IotWebConf_ nos da esta funcionalidad.

A través de esta librería, se gestiona toda la configuración WiFi, además de integrar el servidor WEB que, más adelante, usaremos en el proyecto

## Cómo añadir funcionalidades

Cada usuario deberá añadir sus ficheros al proyecto teniendo en cuenta varias cosas:

* Cada usuario podrá incormporar código a la función _setup()_ recomendablemente haciendo una llamada a su propio setup

* Se recomienda también que se organice el código del _loop()_, haciendo una llamada a una función propia. Ahí se actualizará continuamente el estado de su sistema, comporbaciones, etc.

* Se debe evitar esperas activas. Esto es, no usar *delay()*. En su lugar, se debe realizar temporizaciones tomando el tiempo actual ( usando ```unsigned long miTemp = millis()```) y comprobar si se ha superado el tiempo deseado de este modo:

		if( millis() > miTemp + DELAY)
		
## Configurar entorno Arduino para ESP32

El Arduino no tiene soporte de serie para ESP32.
Para poder usarlo, instalaremos la librería / compilador de este microcontrolador. Se necesita Python para instalarlo.
Descargalo de [Python2.7](https://www.python.org/downloads/release/python-2715/)
Instala el Python, con valores predeterminados.
Luego instalamos el [GIT](https://git-scm.com/download/win)
Terinamos con la librería de hardware ESP32, usando el GIT. Abre la ventana de comandos, accede a ~/Documentos/Arduino/hardware y clona el repo GIT:

		git clone https://github.com/espressif/arduino-esp32.git

Al terminar, asegurate de que la carpera que has descargado tiene una subcarpeta ```espressif\esp32\tools``` de modo que quede en tu carpeta de usaurio ```~\Documents\Arduino\hardware\espressif\esp32\tools```

Para terminar entra en esa carpeta, ejecuta get.exe. Al terminar estará instalado. Reinicia el Arduino y ya puedes usarlo.

[Fuente](https://www.prometec.net/instalando-esp32/)
