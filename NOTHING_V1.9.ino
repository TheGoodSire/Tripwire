#define COF setColorOnFace
int DI = 10000; int DS = 500; Timer deathT; Timer switchT; Timer nextS;
enum bS {ALIVE, DEAD, SELECT}; byte bS = DEAD; Color selectColors [] = {BLUE, RED, YELLOW};
byte hue = 0; byte dead = 0; byte numN = 0; byte pastN = 0; byte index = 0; byte dice = 0;
void setup() {deathT.set(DS*2); randomize(); hue = random(255);}
void loop() {setValueSentOnAllFaces(bS); numN = 0; FOREACH_FACE(f) {if (!isValueReceivedOnFaceExpired(f)) numN++;}
  if (buttonLongPressed()) {deathT.set(DI); switchT.set(DS*5); index = random(2); dice = random(5); bS = SELECT;} 
  if (bS == ALIVE) { setColor(makeColorHSB(hue,255,255));
    if (buttonPressed() || pastN != numN) {deathT.set(DI); bS = DEAD;}
    if (nextS.isExpired()) {hue++; nextS.set((random(6)+1)*10);}}
  if (bS == DEAD) { setColor(makeColorHSB(hue,255,255)); COF(WHITE, dead); COF(WHITE, dead+2); COF(WHITE, dead+4);
    if (deathT.isExpired()) {pastN = numN; bS = ALIVE;}
    if (switchT.isExpired()) {switchT.set(DS); dead = (dead + 1) % 2;}}
  if (bS == SELECT) { setColor(makeColorHSB(hue,255,255)); if (nextS.isExpired()) {hue+5; nextS.set(3);}
    if (deathT.isExpired()) {pastN = numN; bS = ALIVE;}
    if (switchT.isExpired()) {setColor(selectColors[index]); 
      switch (dice) {  case 0: COF(OFF, 0); case 1: COF(OFF, 1); case 2: COF(OFF, 2);
                       case 3: COF(OFF, 3); case 4: COF(OFF, 4); break;}}}}
