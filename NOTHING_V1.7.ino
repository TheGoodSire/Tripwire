#define DEATH_INTERVAL 10000
#define DEATH_SWITCH 500
Timer deathTimer; Timer switchTimer; Timer nextStep;
enum blinkState {ALIVE, DEAD}; byte blinkState = DEAD;
byte hue = 0; byte dead = 0; byte numNeighbors = 0; byte pastNeighbors = 0;
void setup() {deathTimer.set(DEATH_SWITCH*2); randomize(); hue = random(255);}
void loop() {
  numNeighbors = 0; FOREACH_FACE(f) {if (!isValueReceivedOnFaceExpired(f)) numNeighbors++;} 
  if (blinkState == ALIVE) {
    if (buttonPressed() || pastNeighbors != numNeighbors) {deathTimer.set(DEATH_INTERVAL); blinkState = DEAD;}
    if (nextStep.isExpired()) {setColor(makeColorHSB(hue,255,255)); hue++; nextStep.set((random(6)+1)*10);}
  }
  if (blinkState == DEAD) {
    if (deathTimer.isExpired()) pastNeighbors = numNeighbors; blinkState = ALIVE;
    setColor(makeColorHSB(hue,255,255)); setColorOnFace(WHITE, dead); setColorOnFace(WHITE, dead+2); setColorOnFace(WHITE, dead+4);
    if (switchTimer.isExpired()) {switchTimer.set(DEATH_SWITCH); dead = (dead + 1) % 2;}
  }
  setValueSentOnAllFaces(blinkState);
}
