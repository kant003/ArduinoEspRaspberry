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