## Inclinómetro, ver si la planta ha caido


```cpp
int tiltSwitch = 3; 
int tiltVal; 

void setup ()
{
	Serial.begin(9600);
	pinMode (tiltSwitch, INPUT) ;
}
void loop ()
{
	if(isTilted()){
		Serial.println("ha caido");
	}else{
		Serial.println("no ha caido");
	}
}		

bool isTilted(){
 tiltVal = digitalRead (tiltSwitch) ;

	if (tiltVal == HIGH)
	{
		return true;
	}else
	{
		return false;
	}  
}
```

El funcionamiento es similar a un led, si esta en HIGH tiene corriente y si esta en LOW no tiene,
esto pasa por el contacto que tiene el sensor de mercurio, cuando se inclina se pierde el contacto,
y se apaga.