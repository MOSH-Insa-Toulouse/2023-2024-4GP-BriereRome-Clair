#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SoftwareSerial.h>

// definition des pins
// Potar digital 
#define P_SCK 13
#define P_CS  10 
#define P_SI  11 
// Module Bluetooth
#define BT_RX 8
#define BT_TX 7 
#define BT_baudrate 9600
SoftwareSerial BT_Serial(BT_TX, BT_RX); // Tx et Rx du module bt


// Boutons 
#define B_plus  3 
#define B_moins 4 
#define B_ok    2 
#define B_time  300
// Cateurs graphite et flex sensor
#define GR_ADC A0 
#define FS_ADC A1 
// Ecran oled
#define OLED_SDT A4 
#define OLED_SCK A5 

//ECRAN OLED
#define oled_largeur     128
#define oled_hauteur     64
#define brocheResetOLED  -1
#define addI2C_oled      0x3C
int OLED_ok = 0 ;
Adafruit_SSD1306 ecranOLED(oled_largeur,oled_hauteur,&Wire,brocheResetOLED);

// BOUTONS ET SELECTION DU CALIBRE
int read_B_plus;
int last_B_plus_state;
int read_B_moins;
int last_B_moins_state;
int read_B_ok;
int last_B_ok_state;
int milli_B =0;
int Val_select = 1; 
int Val_choisie = 1;
int choix_modifie = 0;

// Potar digital

#define MCP_WRITE 0b00010001
#define P_Rmax  50 // Rmax en kOhm
#define R3      100 // en kOhm
float R_cible = 0 ;
int P_pos = 0 ;

// Capteurs
float GR_val = 0 ;
float FS_val = 0 ;






void boutons(){
  int read_B_plus = digitalRead(B_plus);
  if ((read_B_plus == HIGH) && (millis() - milli_B > B_time)){
      Val_select++ ;
      milli_B = millis();
    }

  int read_B_moins = digitalRead(B_moins);
  if  ((read_B_moins == HIGH) && (millis() - milli_B > B_time)){
      Val_select-- ;
      milli_B = millis();
    }

  int read_B_ok = digitalRead(B_ok);
  if  (read_B_ok == HIGH){
      Val_choisie = Val_select ;
      choix_modifie = 1 ;
  } 
  last_B_plus_state = read_B_plus ;
  last_B_moins_state = read_B_moins ;
  last_B_ok_state = read_B_ok ;
}

void AffichageOLED(int vs, int vc){
    ecranOLED.clearDisplay();
    ecranOLED.setCursor(0,0);
    ecranOLED.print("val select : ");
    ecranOLED.println(vs);
    ecranOLED.print("val choisie : ");
    ecranOLED.println(vc);  
    ecranOLED.display();
}

void SPIWrite(int Val){
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); 
  
  digitalWrite(P_CS, LOW); // SS pin low to select chip
  
  SPI.transfer(MCP_WRITE);        // Send command code
  SPI.transfer(Val);       // Send associated value
  
  digitalWrite(P_CS, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}

void setup() {
  if(ecranOLED.begin(SSD1306_SWITCHCAPVCC, addI2C_oled)) {
    OLED_ok=1;
    ecranOLED.clearDisplay();
    ecranOLED.setTextSize(2);
    ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    ecranOLED.setCursor(0,0);
    ecranOLED.println("OLED OK");
    ecranOLED.display();   
    delay(2000);
    ecranOLED.clearDisplay();
  }

  pinMode (P_SI,INPUT);
  pinMode (BT_TX,INPUT);
  pinMode (B_plus,INPUT);
  pinMode (B_moins,INPUT);
  pinMode (B_ok,INPUT);
  pinMode (P_SI,INPUT);
  pinMode (GR_ADC,INPUT);
  pinMode (FS_ADC,INPUT);

  digitalWrite(P_CS, HIGH); //desactive le chip select du potar
  SPI.begin();
  SPIWrite(1);

  BT_Serial.begin(BT_baudrate);
  //BT_Serial.println("BT ok");

  Serial.begin(9600);
  Serial.println("start");
}

void loop() {
  //Gestion des boutons
  boutons();
  // Gestion de l'OLED
  if (OLED_ok){
    AffichageOLED(Val_select, Val_choisie);
  }

  // Gestion du potar
  /* Mettre le potar à la valeur qui correspond au gain valchoisie si elle a bougé
  G = (R2+R3)/R2 <=> R2 * G = R2+R3 <=> R2(G-1)=R3 <=> R2 = R3/(G-1)*/
  if (choix_modifie){
    R_cible = R3/(Val_choisie-1);
    P_pos = R_cible*256/P_Rmax ;    // pour choisir le gain
    //P_pos = Val_choisie*256/P_Rmax ;  // pour choisir la valeur de la résistance
    P_pos = constrain(P_pos, 0, 255);
    
    SPIWrite(P_pos);
    choix_modifie = 0 ;
  }

  //Mesures
  GR_val=analogRead(GR_ADC);
  FS_val = analogRead(FS_ADC);

  FS_val=map(FS_val,0,1023,0,255);
  GR_val=map(GR_val,0,1023,0,255); 

  //Bluetooth
  BT_Serial.write(FS_val);
  BT_Serial.write(GR_val);
  
  /*Serial.print(FS_val);
  Serial.print("; ");
  Serial.println(GR_val);*/

  delay(40);

}


