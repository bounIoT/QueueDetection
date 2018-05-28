
#define ag_ismi "CMPE_IOT"
#define ag_sifresi "cmpeiot123"
//IP of aws server to be connected
#define IP "13.59.189.137"

//define distance which will be used to estimate if a spot is full or empty
const int dist = 100;
//define pins to be connected to arduino
const int trigPin1 = 12;
const int echoPin1 = 11;
const int trigPin2 = 4;
const int echoPin2 = 3;

int val = 0 ;

// defines variables
long duration;
int distance;
int doluluk ;
void setup() {
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
pinMode(pir1, INPUT);     // declare sensor as input
pinMode(pir2, INPUT);     // declare sensor as input

Serial.begin(115200);
//using AT protocol to send and receive data
  Serial.println("AT");

  delay(3000);

  if(Serial.find("OK")) {
    Serial.println("AT+CWMODE=1");
    delay(2000);
    String baglantiKomutu = String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    Serial.println(baglantiKomutu);
    
    delay(5000);
  }
}
void loop() {
  	//these counters are used to reduce error
	//10 measurements are made from ultrasonic sensor
	//if at least 4 of them show that the spot is full
	//doluluk value changes
   int counter1 = 0 ;
   int counter2 = 0 ;
	
  for(int i=0 ; i<10 ; i++){
   	//someoneUnder1 gets value from the sensor that is in front of line
    if(someoneUnder1()<dist)
    counter1++;
	//someoneUnder1 gets value from the sensor that is at the back of the line
    if(someoneUnder2()<dist)
    counter2++;
    delay(1000);
  }


if(counter2>4)
doluluk = 3; 			//doluluk 3 represents that queue is full
else if(counter1>4)
doluluk = 2;			//doluluk 2 represents that queue is half empty
else
doluluk = 1 ;			//doluluk 1 represents that queue is empty


delay(2000);

 doluluk_yolla(doluluk);
  
  delay(6000);

}

int someoneUnder1(){
  digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin1, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance1: ");
Serial.println(distance);

return distance;

}

int someoneUnder2(){
  digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin2, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance2: ");
Serial.println(distance);

return distance;

}

void doluluk_yolla(int doluluk) {
  Serial.println(String("AT+CIPSTART=\"TCP\",\"")+IP+"\",5044");
  
  delay(1000);
  if(Serial.find("Error")){
    Serial.println("serial error");
    return;
  }

  String komut2 = "POST /command/";
  komut2 += doluluk;
  komut2 += "\r\n\r\n";
  

  delay(3000);
  
  Serial.print("AT+CIPSEND=");                 
  
  Serial.println(komut2.length()+2);       
 delay(1000);
 
 if(Serial.find(">")){                         
  
   Serial.print(komut2);
  
 }
 else {
  Serial.println("AT+CIPCLOSE");
 }
}
