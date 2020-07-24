#define DEATH_INTERVAL 10000
#define DEATH_SWITCH 500
Timer deathTimer; Timer switchTimer; Timer nextStep;
enum blinkState {ALIVE, DEAD, SELECT}; byte blinkState = DEAD;
byte hue = 0; byte dead = 0; byte numNeighbors = 0; byte pastNeighbors = 0; byte index = 0; byte dice = 0;
Color selectColors [3] = {BLUE, RED, YELLOW};
void setup() {deathTimer.set(DEATH_SWITCH*2); randomize(); hue = random(255);}
void loop() {
  numNeighbors = 0; FOREACH_FACE(f) {if (!isValueReceivedOnFaceExpired(f)) numNeighbors++;}
  if (buttonLongPressed()) {deathTimer.set(DEATH_INTERVAL); switchTimer.set(2500); index = random(2); dice = random(5); blinkState = SELECT;} 
  if (blinkState == ALIVE) {
    if (buttonPressed() || pastNeighbors != numNeighbors) {deathTimer.set(DEATH_INTERVAL); blinkState = DEAD;}
    if (nextStep.isExpired()) {setColor(makeColorHSB(hue,255,255)); hue++; nextStep.set((random(6)+1)*10);}
  }
  if (blinkState == DEAD) {
    if (deathTimer.isExpired()) {pastNeighbors = numNeighbors; blinkState = ALIVE;}
    setColor(makeColorHSB(hue,255,255)); setColorOnFace(WHITE, dead); setColorOnFace(WHITE, dead+2); setColorOnFace(WHITE, dead+4);
    if (switchTimer.isExpired()) {switchTimer.set(DEATH_SWITCH); dead = (dead + 1) % 2;}
  }
  if (blinkState == SELECT) {
    if (nextStep.isExpired()) {setColor(makeColorHSB(hue,255,255)); hue++; nextStep.set(3);}
    if (switchTimer.isExpired()) {setColor(selectColors[index]); 
      if (dice == 0 || dice == 1 || dice == 2 || dice == 3 || dice == 4) {setColorOnFace(OFF, 5);}
      if (dice == 0 || dice == 1 || dice == 2 || dice == 3) {setColorOnFace(OFF, 4);}
      if (dice == 0 || dice == 1 || dice == 2) {setColorOnFace(OFF, 3);}
      if (dice == 0 || dice == 1) {setColorOnFace(OFF, 2);}
      if (dice == 0) {setColorOnFace(OFF, 1);}
    }
    if (deathTimer.isExpired()) {pastNeighbors = numNeighbors; blinkState = ALIVE;}
  }
  setValueSentOnAllFaces(blinkState);
}
