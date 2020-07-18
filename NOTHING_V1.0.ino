#define DEATH_INTERVAL 10000
Timer deathTimer;

#define DEATH_SWITCH 500
Timer switchTimer;

enum blinkState {ALIVE, DEAD1, DEAD2};
int blinkState = ALIVE;

byte hue=0;
Timer nextStep;

void setup() {
  // put your setup code here, to run once

}

void loop() {
  switch (blinkState) {
    case ALIVE:
      aliveLoop();
      aliveDisplay;
      break;
    case DEAD1:
      dead1Loop();
      break;
    case DEAD2:
      dead2Loop();
      break;
  }

  buttonPressed();
  buttonSingleClicked();
  buttonDoubleClicked();
  buttonMultiClicked();
  buttonLongPressed();
  setValueSentOnAllFaces(blinkState);

}

void aliveLoop(){
  if(buttonPressed()){
    transitionLoop();
  }
  if(buttonSingleClicked()){
    transitionLoop();
  }
  if(buttonDoubleClicked()){
    transitionLoop();
  }
  if(buttonMultiClicked()){
    transitionLoop();
  }
  if(buttonLongPressed()){
    transitionLoop();
  }
  if(isAlone()){
    blinkState = ALIVE;
  }else {
    transitionLoop();
  }
}

void aliveDisplay(){
if (nextStep.isExpired()) {
    setColor( makeColorHSB( hue , 255 , 255 ) );
    hue++;     
    nextStep.set(40);

  }
}

void dead1Loop(){
  if (deathTimer.isExpired()) {
    blinkState = ALIVE;
  }
  setColorOnFace(RED, 0);
  setColorOnFace(WHITE, 1);
  setColorOnFace(RED, 2);
  setColorOnFace(WHITE, 3);
  setColorOnFace(RED, 4);
  setColorOnFace(WHITE, 5);
  if (switchTimer.isExpired()) {
    switchTimer.set(DEATH_SWITCH);
    blinkState = DEAD2;
  }
}

void dead2Loop(){
  if (deathTimer.isExpired()) {
    blinkState = ALIVE;
  }
  setColorOnFace(WHITE, 0);
  setColorOnFace(RED, 1);
  setColorOnFace(WHITE, 2);
  setColorOnFace(RED, 3);
  setColorOnFace(WHITE, 4);
  setColorOnFace(RED, 5);
  if (switchTimer.isExpired()) {
    switchTimer.set(DEATH_SWITCH);
    blinkState = DEAD1;
  }
}
  
void transitionLoop(){
  deathTimer.set(DEATH_INTERVAL);
  switchTimer.set(DEATH_SWITCH);
  blinkState = DEAD1;
}
