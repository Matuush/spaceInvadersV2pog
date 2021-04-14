#include "MaxMatrix.h"

#define JOY_X A1
#define JOY_Y A2
#define DIN 9
#define CS 10
#define CLK 11
MaxMatrix disp = MaxMatrix(DIN, CS, CLK, 1);

// Projectile
unsigned int bulletCount = 0;
unsigned int bulletX[8] = {0, 0, 0, 0, 0, 0, 0, 0}, bulletY[8] = {6, 6, 6, 6, 6, 6, 6, 6};
#define newBullet(x) {bulletX[bulletCount] = x; bulletCount++;}
#define setBullet(i, ii) {bulletX[(i)] = bulletX[(ii)], bulletY[(i)] = bulletY[(ii)];}
#define resetBullet(i) {bulletCount--; \
  for(unsigned int ii = i; ii < bulletCount - 1; ii++) {setBullet(ii, ii+1);} \
  bulletY[bulletCount] = 6;}
#define movBullet(i) {if(bulletY[i] == 0) {resetBullet(i)} else bulletY[i]--;}
#define movBullets() {for(unsigned int i = 0; i < bulletCount; i++) {movBullet(i)}}

// Ship
unsigned int shipX = 3, shipLife = 3;
const unsigned int shipY = 7;
#define shoot() {newBullet(shipX);}
#define mov() {unsigned int joy = analogRead(JOY_X); shipX = joy < 200 ? (shipX > 0 ? shipX - 1 : 7) : (joy > 800 ? (shipX < 7 ? shipX + 1 : 0) : shipX);}

// Enemy
unsigned int enemyCount = 0;
unsigned int enemyX[8] = {0, 0, 0, 0, 0, 0, 0, 0}, enemyY[8] = {6, 6, 6, 6, 6, 6, 6, 6};
#define newEnemy(x) {enemyX[enemyCount] = x; enemyCount++;}
#define setEnemy(i, ii) {enemyX[(i)] = enemyX[(ii)], enemyY[(i)] = enemyY[(ii)];}
#define resetEnemy(i) {enemyCount--; \
  for(unsigned int ii = i; ii < enemyCount - 1; ii++) {setEnemy(ii, ii+1);} \
  enemyY[enemyCount] = 6;}
#define movEnemy(i) {if(enemyY[i] == 7) {resetEnemy(i)} else enemyY[i]++;}
#define movEnemies() {for(unsigned int i = 0; i < enemyCount; i++) {movEnemy(i)}}

// Visual
#define prtShip() {disp.setDot(shipX, shipY, true); disp.setDot(shipX, shipY - 1, true); disp.setDot(shipX - 1, shipY, true); disp.setDot(shipX + 1, shipY, true);}
#define prtBullet(i) {disp.setDot(bulletX[i], bulletY[i], true);}
#define prtBullets() {for(unsigned int i = 0; i < bulletCount; i++) prtBullet(i);}
#define prtEnemy(i) {disp.setDot(enemyX[i], enemyY[i], true);}
#define prtEnemy() {for(unsigned int i = 0; i < enemyCount; i++) prtEnemy(i);}
#define prtArr(vjecY, vjecX) {Serial.print(vjecY[0]); Serial.print(vjecY[1]); Serial.print(vjecY[2]); Serial.print(vjecY[3]); Serial.print(vjecY[4]); Serial.print(vjecY[5]); Serial.print(vjecY[6]); Serial.println(vjecY[7]);\
  Serial.print(vjecX[0]); Serial.print(vjecX[1]); Serial.print(vjecX[2]); Serial.print(vjecX[3]); Serial.print(vjecX[4]); Serial.print(vjecX[5]); Serial.print(vjecX[6]); Serial.println(vjecX[7]);}

// uhhh general
unsigned int score = 0, highScore = 0;
#define reset() score = 0, shipX = 3, shipLife = 3;

// UHHHHHHHHH
void setup() {
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  disp.init();
  disp.setIntensity(0.5);
  Serial.begin(9600);
}

unsigned long time = 0;
void loop() {
  time++;
    mov();
    movBullets();
    if(time % 4 == 0 && analogRead(JOY_Y) < 200) shoot();

  disp.clear();
  prtShip();
  prtBullets();

  if(score > highScore) highScore = score;
  if(shipLife <= 0) reset();
  delay(100);
}
