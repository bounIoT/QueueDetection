// defines pins numbers
#define ag_ismi "CMPE_IOT"
#define ag_sifresi "cmpeiot123"
#define IP "13.59.189.137"

const int dist = 100;
const int trigPin1 = 12;
const int echoPin1 = 11;
const int trigPin2 = 4;
const int echoPin2 = 3;

const int pir1= 6;
const int pir2 = 7;
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
  
   int counter1 = 0 ;
   int counter2 = 0 ;
  for(int i=0 ; i<10 ; i++){
   
    if(someoneUnder1()<dist)
    counter1++;

    if(someoneUnder2()<dist)
    counter2++;
    delay(1000);
  }
if(counter2>4)
doluluk = 3;
else if(counter1>4)
doluluk = 2;
else
doluluk = 1 ;


delay(2000);

 doluluk_yolla(doluluk);
  
  delay(6000);

/*

 val = digitalRead(pir1);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    Serial.println("Motion1 started!");
  } else {
    
      Serial.println("Motion1 ended!");
      
    }
  delay(1000);

  val = digitalRead(pir2);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    Serial.println("Motion2 started!");
  } else {
    
      Serial.println("Motion2 ended!");
      
    }
  delay(1000);

*/
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

  String yollanacakKomut = "GET /update?key=GZAP4V3BETISUW8D&field1=";
  String komut2 = "POST /command/";
  //yollanacakKomut += (int(doluluk));
  yollanacakKomut += doluluk;
  yollanacakKomut += "\r\n\r\n";
  komut2 += doluluk;
  komut2 += "\r\n\r\n";
  

  delay(3000);
  
  Serial.print("AT+CIPSEND=");                 
  
  Serial.println(komut2.length()+2);       
 delay(1000);
 
 if(Serial.find(">")){                         
  
   Serial.print(komut2);
  
 //  Serial.print("\r\n\r\n");
 }
 else {
  Serial.println("AT+CIPCLOSE");
 }
}

