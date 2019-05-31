# Practicas de Raspberry Pi

## Como práctica de Entornos y Sistemas, me propongo instalar un servidor HTTL sobre la Raspberry Pi

Me he dicidido a usar [Nginx](https://www.nginx.com/) porque es un servidor ligero, que usa mucha menos memoria que el omnipresente Apache. Ha sido concevido como un sucesor de los servidores tradicionales buscando la máxima potencia y mucha funcionalidad.
Permite crear Hosts Virtuales, para que múltiples usuarios puedan conpartir la misma instalación, y se puede configurar certificados de seguridad, pasarelas [CGI](https://es.wikipedia.org/wiki/Interfaz_de_entrada_com%C3%BAn) y mucho más.

## Instalación

Empezamos instalando el servidor. Afortunadamente, los paquetes están directamente disponibles en los repositorios de Raspbian.

		sudo apt update
		sudo apt upgrade
		sudo apt install nginx

De este modo actualizamos la base de datos de paquetes disponibles en los servidores. Luego actualizamos y, por último, instalamos Ngnix. Ahora toca configurar un servidor Virtual

Para ello, crearemos una carpeta para el proyecto

		sudo mkdir /var/www/zalo

Damos permisos de acceso a la carpeta:

		sudo chmod 777 /var/www/zalo

Así el servidor podrá acceder al directorio y podremos modificar datos sin ser superusuario. Ahora crearemos los archivos de la página web. Yo usaré scp para copiar desde mi PC al servidor. [SCP](https://en.wikipedia.org/wiki/Secure_copy) permite copiar ficheros entre equipos usando túneles ssh. Muy cómodo, casi como usar cp!!

		scp -r c:\usuarios\zalo\Documentos\wev\* pi@10.101.3.200:/var/www/zalo

Este comando copia los datos de mi carpeta ~\Documentos\web de mi PC a la carpeta /var/www/zalo del servidor.

Ahora nos disponemos a configurar el servidor Nginx para que _sirva_ nuestra página. Hacemos una copia de la configuración por defecto:

		sudo cp /etc/nginx/sites-available/{default,zalo}

Ahora editamos la configuración para adaptarla a nuestras necesidades. Lo dejaremos así:

		server {
		        listen 82 default;
		        listen [::]:82;

		        server_name zalo.local;

		        root /var/www/zalo;
		        index index.html;

		        location / {
		                try_files $uri $uri/ =404;
		        }
		}

Hacemos un test de la configuración así:

		sudo nginx -t

Todo OK? Seguimos!

Ahora solo queda habilitar la configuración y reiniciar el servidor


		sudo ln -s /etc/nginx/sites-available/zalo /etc/nginx/sites-enabled
		sudo service nginx restart

Probamos a cargar la página. Simplemente haz click en [este enlace](http://cebem2019a.ddns.net:82/) y verás la página que he creado. Permite cargar un fichero de video local y verlo en el navegador. No se carga en el servidor, para no saturarlo. Sirve como ejemplo de video incrustado en HTML también.

