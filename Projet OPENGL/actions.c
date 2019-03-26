#include "actions.h"
#include <stdio.h>
#include <math.h>

extern GLfloat xrot;   
extern GLfloat yrot;

extern GLfloat mode;
extern GLfloat x_axe;
extern GLfloat y_axe;
extern GLfloat z_axe;

extern GLfloat player[];
extern GLfloat dummy[];

extern _Bool flashlight;
extern _Bool orbdisco;

GLfloat cuissedroite = -10.0f;
GLfloat cuissegauche = 10.0f;
GLfloat molletdroit =  -6.0f;
GLfloat molletgauche = -6.0f;
GLfloat brasdroit = 10.0f;                                                                                                                      
GLfloat brasgauche = 10.0f;                                                                                                                       
GLfloat avantbrasdroit =  3.0f;                                                                                     
GLfloat avantbrasgauche = 3.0f;
GLfloat bob = 0.01f;
GLfloat moveSpeed = 0.2f;
GLfloat turnSpeed = 20.0f;

GLfloat dummy_cuissedroite = -10.0f; 
GLfloat dummy_cuissegauche = 10.0f;                                                                                                                 
GLfloat dummy_molletdroit =  -6.0f;    
GLfloat dummy_molletgauche = -6.0f;
GLfloat dummy_brasdroit = 10.0f;
GLfloat dummy_brasgauche = 10.0f;
GLfloat dummy_avantbrasdroit =  3.0f;
GLfloat dummy_avantbrasgauche = 3.0f;
GLfloat dummy_bob = 0.01f;
GLfloat dummy_moveSpeed = 0.2f;
GLfloat dummy_turnSpeed = 20.0f;

void moveDummy(_Bool dummyFlash, _Bool dummyOrb) {
  /*ORBE COLOREE*/

  if(!dummyOrb){
    dummy[5] = 0.0f;                                                                                                                      
    dummy[4] = 0.0f;                                                                                                                      
    dummy[7] = 0.0f;                                                                                                                  
    dummy[6]  = 0.0f;
  }
  
  if(!dummyFlash){
    dummy[5] = 0.0f;
    dummy[4] = 0.0f;
    dummy[7] = 0.0f;
    dummy[6]  = 0.0f;
  }
  
  /*WALK CYCLE*/
  
  if((dummy[1] <= -40.0f) || (dummy[1] >= 40.0f)) dummy_cuissedroite = -dummy_cuissedroite;
  if((dummy[0] <= -40.0f) || (dummy[0] >= 40.0f)) dummy_cuissegauche = -dummy_cuissegauche;
  dummy[0] = dummy[0] + dummy_cuissegauche;
  dummy[1] = dummy[1] + dummy_cuissedroite;
  
  if((dummy[3] <= 0.0f) || (dummy[3] >= 24.0f)) dummy_molletdroit = -dummy_molletdroit;                                                   
  if((dummy[2] <= 0.0f) || (dummy[2] >= 24.0f)) dummy_molletgauche = -dummy_molletgauche;
  dummy[2] = dummy[2] + dummy_molletgauche;                                                                                 
  dummy[3] = dummy[3] + dummy_molletdroit;
  
  /*BRAS*/
  
  if(!dummyFlash){
    if((dummy[4] <= -40.0f) || (dummy[4] >= 40.0f)) dummy_brasgauche = -dummy_brasgauche;
    dummy[4] = dummy[4] + dummy_brasgauche;      
    if((dummy[6] <= -12.0f) || (dummy[6] >= 12.0f)) dummy_avantbrasgauche = -dummy_avantbrasgauche;       
    dummy[6] = dummy[6] + dummy_avantbrasgauche;
  }
  else{
    dummy[4] = 0.0f;
    dummy[6] = -30.0f;
  }
  if(!dummyOrb){
    if((dummy[5] <= -40.0f) || (dummy[5] >= 40.0f)) dummy_brasdroit = -dummy_brasdroit;
    dummy[5] = dummy[5] + dummy_brasdroit;
    if((dummy[7] <= -12.0f) || (dummy[7] >= 12.0f)) dummy_avantbrasdroit = -dummy_avantbrasdroit;
    dummy[7] = dummy[7] + dummy_avantbrasdroit;
  }
  else{
    dummy[5] = 0.0f;
    dummy[7] = 90.0f;
  }
  
  if(dummy[8] >= 0.03f) dummy_bob = -dummy_bob;
  if(dummy[8] <= 0.0f) dummy_bob = -dummy_bob;
  dummy[8] = dummy[8] - dummy_bob;
  
  /*MOVING FORWARD*/
  if((dummy[9] + sin(dummy[11]*(M_PI/180))*dummy_moveSpeed > 24.0f || dummy[9] + sin(dummy[11]*(M_PI/180))*dummy_moveSpeed < -24.0f) || (dummy[10] + cos(dummy[11]*(M_PI/180))*dummy_moveSpeed > 24.0f || dummy[10] + cos(dummy[11]*(M_PI/180))*dummy_moveSpeed < -24.0f)) dummy[11] = -dummy[11] + (float)rand()/(float)(RAND_MAX/90) + 180.0f;
  else{
    dummy[10] = dummy[10] + cos(dummy[11]*(M_PI/180))*dummy_moveSpeed;
    dummy[9] = dummy[9] + sin(dummy[11]*(M_PI/180))*dummy_moveSpeed;
  }
}

void touche_pressee(unsigned char key, int x, int y) 
{
  switch (key) {
  case ESCAPE: 
    exit(1);                   	
    break;
      
  case O_MIN:
    /*ORBE COLOREE*/
    orbdisco = !orbdisco;
    player[5] = 0.0f;                                                                                                                       
    player[4] = 0.0f;                                                                                                                      
    player[7] = 0.0f;                                                                                                                  
    player[6]  = 0.0f; 
    break;
      
  case TOUCHE_MIN_L: 
  case TOUCHE_MAJ_L:
    flashlight = !flashlight;
    player[5] = 0.0f;
    player[4] = 0.0f;
    player[7] = 0.0f;
    player[6]  = 0.0f;    
    break;
      
  case Z_MIN:
    /*WALK CYCLE*/
    if((player[1] <= -40.0f) || (player[1] >= 40.0f)) cuissedroite = -cuissedroite;
    if((player[0] <= -40.0f) || (player[0] >= 40.0f)) cuissegauche = -cuissegauche;
    player[0] = player[0] + cuissegauche;
    player[1] = player[1] + cuissedroite;
      
    if((player[3] <= 0.0f) || (player[3] >= 24.0f)) molletdroit = -molletdroit;                                                   
    if((player[2] <= 0.0f) || (player[2] >= 24.0f)) molletgauche = -molletgauche;
    player[2] = player[2] + molletgauche;                                                                                 
    player[3] = player[3] + molletdroit;
      
    /*BRAS*/
      
    if(!flashlight){
      if((player[4] <= -40.0f) || (player[4] >= 40.0f)) brasgauche = -brasgauche;
      player[4] = player[4] + brasgauche;      
      if((player[6] <= -12.0f) || (player[6] >= 12.0f)) avantbrasgauche = -avantbrasgauche;       
      player[6] = player[6] + avantbrasgauche;
    }
    else{
      player[4] = 0.0f;
      player[6] = -30.0f;
    }
      
    if(!orbdisco){
      if((player[5] <= -40.0f) || (player[5] >= 40.0f)) brasdroit = -brasdroit;
      player[5] = player[5] + brasdroit;
      if((player[7] <= -12.0f) || (player[7] >= 12.0f)) avantbrasdroit = -avantbrasdroit;
      player[7] = player[7] + avantbrasdroit;
    }
    else{
      player[5] = 0.0f;
      player[7] = 90.0f;
    }
      
    if(player[8] >= 0.03f) bob = -bob;
    if(player[8] <= 0.0f) bob = -bob;
    player[8] = player[8] - bob;
      
    /*MOVING FORWARD*/
    if((player[9] + sin(player[11]*(M_PI/180))*moveSpeed > 24.0f || player[9] + sin(player[11]*(M_PI/180))*moveSpeed < -24.0f) || (player[10] + cos(player[11]*(M_PI/180))*moveSpeed > 24.0f || player[10] + cos(player[11]*(M_PI/180))*moveSpeed < -24.0f)) printf("Hors-Limites"); /*NE RIEN FAIRE*/
    else
      {
	player[10] = player[10] + cos(player[11]*(M_PI/180))*moveSpeed;
	player[9] = player[9] + sin(player[11]*(M_PI/180))*moveSpeed;
      }
    break;
      
  case D_MIN:
    player[11] = player[11] - turnSpeed;
    break;
      
  case Q_MIN:
    player[11] = player[11] + turnSpeed;
    break;
  }
}


