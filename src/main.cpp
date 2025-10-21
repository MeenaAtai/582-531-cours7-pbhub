#include <Arduino.h>
#include <FastLED.h>
#include <M5_PbHub.h>
#include <MicroOscSlip.h>

#define BROCHE_ATOM_FIL_BLANC 32 // connecté
#define BROCHE_ATOM_FIL_JAUNE 26 //pixel pour key unit

#define MA_BROCHE_BOUTON 39

#define CANAL_KEY_UNIT 0

// Le nombre 128 entre les < > ci-dessous est le nombre maximal d'octets réservés pour les messages entrants.
// Les messages sortants sont écrits directement sur la sortie et ne nécessitent pas de réservation d'octets supplémentaires.
MicroOscSlip<128> monOsc(&Serial);

M5_PbHub myPbHub;

//CRGB keyPixel;

CRGB pixelAtom;


void setup() {
  // Initialiser FastLED pour contrôler le pixel RGB du M5Stack Key Unit
  //FastLED.addLeds< WS2812, BROCHE_ATOM_FIL_JAUNE , GRB >(&keyPixel, 1);

  // Initialiser FastLED pour contrôler le pixel RGB du M5Stack Atom Unit
  FastLED.addLeds< WS2812, 27 , GRB >(&pixelAtom, 1);

  // initialiser la touche du key unit 
  //pinMode( BROCHE_ATOM_FIL_BLANC , INPUT_PULLUP );

  // initialiser la touche du Atom unit 
  pinMode( MA_BROCHE_BOUTON , INPUT );

  Wire.begin();
  myPbHub.begin();
  myPbHub.setPixelCount( CANAL_KEY_UNIT , 1);

  Serial.begin(115200);

}

void loop() {
  //KEY
  //int maLectureKey = digitalRead( BROCHE_ATOM_FIL_BLANC );
  int maLectureKey = myPbHub.digitalRead( CANAL_KEY_UNIT );
  monOsc.sendInt("/key", maLectureKey);
  
  if ( maLectureKey == 1) { //couleur non appuyé
    //keyPixel = CRGB(0, 0, 0); //noir
    myPbHub.setPixelColor( CANAL_KEY_UNIT , 0 , 0, 0, 0 );
   } else {
    int rouge = random(0,256);
    int vert = random(0,256);
    //keyPixel = CRGB(rouge, vert, 0); //jaune
    myPbHub.setPixelColor( CANAL_KEY_UNIT , 0 , rouge, vert, 0 );
  }

  // INTÉGRÉ - ATOM
  int maLectureBouton = digitalRead( MA_BROCHE_BOUTON );

  if ( maLectureBouton == 1) { //couleur non appuyé
    pixelAtom = CRGB(0, 0, 0); //noir
   } else {
    pixelAtom = CRGB(255, 255, 0); //jaune
  }

  FastLED.show();



  delay(20);
}

