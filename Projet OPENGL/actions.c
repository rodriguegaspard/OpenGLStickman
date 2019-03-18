#include "actions.h"

extern GLfloat xrot;   
extern GLfloat yrot;

extern GLfloat mode;
extern GLfloat x_axe;
extern GLfloat y_axe;
extern GLfloat z_axe;

extern blend;
extern light;

void touche_pressee(unsigned char key, int x, int y) 
{
    usleep(100);

    switch (key) {
    case ESCAPE: 
	exit(1);                   	
	break; 

    case TOUCHE_MIN_B: 
    case TOUCHE_MAJ_B: 
     blend =  switch_blend(blend);
      break;

    case TOUCHE_MIN_L: 
    case TOUCHE_MAJ_L: 
      light = switch_light(light);
      break;
    }	
}

