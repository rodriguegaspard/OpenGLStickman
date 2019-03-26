#include "init.h"
#include "ppm.h"
#include "axes.h"
#include "lumiere.h"
#include "VM_init.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLfloat xrot = 0.0f;   
GLfloat yrot = 0.0f;   
GLfloat z = -5.0f;

/*GLfloat y_axe = 0.0f;
  GLfloat x_axe = 0.0f;
  GLfloat z_axe = 0.0f;
  GLfloat mode = 0.0f;*/

GLfloat player[] = {
  0.0f, //Angle cuisse gauche 0
  0.0f, //Angle cuisse droite 1
  0.0f, //Angle mollet gauche 2
  0.0f, //Angle mollet droit 3
  0.0f, //Angle bras gauche 4
  0.0f, //Angle bras droit 5
  0.0f, //Angle avant-bras gauche 6
  0.0f, //Angle avant-bras droit 7
  0.0f, //Bobbing 8
  0.0f, //Déplacement x 9
  0.0f, //Déplacement z 10
  0.0f, //Angle de tour 11
};

GLfloat dummy[] = {
  0.0f, //Angle cuisse gauche 0
  0.0f, //Angle cuisse droite 1                                                                                                                     
  0.0f, //Angle mollet gauche 2                                                                                                                     
  0.0f, //Angle mollet droit 3                                                                                                                      
  0.0f, //Angle bras gauche 4                                                                                                                       
  0.0f, //Angle bras droit 5                                                                                                                        
  0.0f, //Angle avant-bras gauche 6                                                                                                                 
  0.0f, //Angle avant-bras droit 7                                                                                                                  
  0.0f, //Bobbing 8                                                                                                                                 
  0.0f, //Déplacement x 9                                                                                                                           
  0.0f, //Déplacement z 10                                                                                                                          
  0.0f, //Angle de tour 11 
};

/*SKYBOX*/
GLfloat sky_size = 50.0f;
TEXTURE_STRUCT * texture;

_Bool flashlight = 0;
_Bool orbdisco = 0;

float randFloat(int a){
  return (float)rand()/(float)(RAND_MAX/a);
}

/*LAMPE TORCHE*/
GLfloat modelAmb[4] = {0.2, 0.2, 0.2, 1.0};

Light spot[] =
  {
    {
      {10.0, 10.0, 10.0, 1.0},  /* ambient */
      {1.0, 1.0, 1.0, 1.0},  /* diffuse */
      {0.4, 0.4, 0.0, 1.0},  /* specular */
      {0.0, 0.0, 0.5, 1.0},  /* position */
      {1.0, 0.0, 7.0},   /* direction */
      50.0,
      60.0,             /* exponent, cutoff */
      {1.0, 0.5, 0.2},    /* attenuation */
    }
  };


/*ORBE DISCO*/

Light colororb[] =
  {
    {                                                                                                                                               
      {1.0, 1.0, 1.0, 1.0},  /* ambient */                                                                                                      
      {1.0, 1.0, 1.0, 1.0},  /* diffuse */                                                                                                          
      {0.4, 0.4, 0.4, 1.0},  /* specular */                                                                                                         
      {0.0, 0.15, 0.25, 1.0},  /* position */  
      {0.0, 0.0, 0.0},   /* direction */                   
      00.0,                                                                                                                                         
      00.0,             /* exponent, cutoff */                                                                                                      
      {1.0, 0.5, 0.2},    /* attenuation */                                                                                                         
    }   
  };


/* SOL */
static void drawPlane(int w, int h)
{
  int i, j;
  float dw = 1.0 / w;
  float dh = 1.0 / h;

  glPushMatrix();
  glRotatef(-90.0, 1, 0, 0);
  glScalef(50.0, 50.0, 1.0);
  glTranslatef(-0.5, -0.5, -1.7);
    
  glNormal3f(0.0, 0.0, 1.0);
  for (j = 0; j < h*10; ++j) {
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= w*10; ++i) {
      glVertex2f(dw * i/10, dh * (j + 1)/10);
      glVertex2f(dw * i/10, dh * j/10);
    }
    glEnd();
  }
  glPopMatrix();
}

void bonhomme(GLfloat man[], _Bool isPlayer, int l1, int l2, _Bool flash, _Bool orb){
  
  srand((unsigned) time(NULL));
  
  glPushMatrix();
  {
    /* TORSE */
    glTranslatef(man[9],0.0f,man[10]);
    glRotatef(man[11],0.0f,1.0f,0.0f);
    glTranslatef(0.0f,man[8],0.0f);
    glColor3f(1,0.8,0.3);
    glPushMatrix();
    {
      glScalef(1.0f,2.0f,1.0f);    
      glutSolidCube(0.5);
    }
    glPopMatrix();
    /*COU*/
    glPushMatrix();
    {	
      glTranslatef(0.0f,0.6f,0.0f);
      glColor3f(1,0.8,0.3);
      glPushMatrix();
      {
	glScalef(1.0f,2.0f,1.0f);	
	glutSolidCube(0.2);
      }
      glPopMatrix();
      /*TETE*/
      glPushMatrix();
      {
	glTranslatef(0.0f,0.25f,0.0f);
	glutSolidSphere(0.25f,30,30);
	/*OEIL GAUCHE*/
	glPushMatrix();
	{
	  glTranslatef(0.2f,0.0f,0.1f);
	  glColor3f(1.0f,1.0f,1.0f);
	  glutSolidSphere(0.1f,10,10);
	  glPushMatrix();
	  {	
	    glTranslatef(0.055f,0.0f,0.0f);
	    glColor3f(0.0f,0.0f,0.0f);
	    glutSolidSphere(0.05f,10,10);
	  }
	  glPopMatrix();
	}
	glPopMatrix();
	  
	/*OEIL DROIT*/
	glPushMatrix();
	{
	  glTranslatef(-0.2f,0.0f,0.1f);
	  glColor3f(1.0f,1.0f,1.0f);
	  glutSolidSphere(0.1f,10,10);
	  glPushMatrix();
	  {	
	    glTranslatef(-0.055f,0.0f,0.0f);
	    glColor3f(0.0f,0.0f,0.0f);
	    glutSolidSphere(0.05f,10,10);
	  }
	  glPopMatrix();
	}
	glPopMatrix();
      }
      glPopMatrix();
    }
    glPopMatrix();
    
    /*EPAULE GAUCHE*/                                                  
    glPushMatrix();                                                        
    {                                                                      
      glTranslatef(0.25f,0.35f,0.0f);                                     
      glColor3f(1.0f,0.8f,0.3f);                                           
      glutSolidSphere(0.2f,10,10);                                         
      /*BRAS GAUCHE*/                                                       
      glPushMatrix();                                                      
      {                                                                    
	glRotatef(man[4],0.0f,1.0f,0.0f);                        
	glRotatef(-70.0f,0.0f,0.0f,1.0f);              
	glTranslatef(0.25f,0.0f,0.0f);
	glPushMatrix();
	glScalef(3.0f,1.0f,1.0f);
	glutSolidCube(0.16);
	glPopMatrix();
	/*COUDE GAUCHE*/
	glPushMatrix();
	{
	  glTranslatef(0.24f,0.0f,0.0f);
	  glutSolidSphere(0.15f,10,10);
	  /*AVANT-BRAS GAUCHE*/
	  glPushMatrix();
	  {
	    glRotatef(man[6], 0.0f, 1.0f, 0.0f);
	    glTranslatef(0.13f,0.0f,0.0f);
	    glPushMatrix();
	    {
	      glScalef(5.0f,1.0f,1.0f);
	      glutSolidCube(0.12f);
	    }
	    glPopMatrix();
	    /*MAIN GAUCHE*/
	    glPushMatrix();
	    {
	      glTranslatef(0.31f,0.0f,0.0f);
	      glutSolidSphere(0.12f,10,10);
	      glPushMatrix();
	      {
		if(flash && isPlayer) {
		  glColor3f(0.2f,0.2f,0.2f);
		  glRotatef(30.0f,0.0f,1.0f,0.0f);
		  glTranslatef(0.0f,0.0f,0.1f);
		  glRotatef(-20.0f,0.0f,0.0f,1.0f);  
		  glPushMatrix();
		  {
		    glScalef(1.2f,1.2f,4.0f);
		    glutSolidCube(0.12); /*LAMPE-TORCHE (CORPS)*/
		  }
		  glPopMatrix();
		  glPushMatrix();
		  {
		    glColor3f(1.0f,1.0f,1.0f);
		    glTranslatef(0.0f,0.0f,0.25f);
		    //LIGHT
		    Light *light = &spot[0]; 
		    initLight(light, l1);
		    spotPos(light, l1);
		    glutSolidSphere(0.09f,10,10); /*AMPOULE*/
		    glPushMatrix(); /*PYRAMIDE*/
		    {
		      glRotatef(-90.0f,1.0f,0.0f,0.0f);
		      glTranslatef(0.0f,0.05f,0.0f);
		      glColor3f(0.2f,0.2f,0.2f);
		      glScalef(0.15f,0.15f,0.15f);
		      glBegin(GL_TRIANGLES);
		      /*DEVANT*/
		      glVertex3f( 0.0f, 1.0f, 0.0f);
		      glVertex3f(-1.0f, -1.0f, 1.0f);
		      glVertex3f(1.0f, -1.0f, 1.0f);
		      /*DROITE*/
		      glVertex3f(0.0f, 1.0f, 0.0f);
		      glVertex3f(1.0f, -1.0f, 1.0f);
		      glVertex3f(1.0f, -1.0f, -1.0f);
		      /*DERRIERE*/
		      glVertex3f(0.0f, 1.0f, 0.0f);
		      glVertex3f(1.0f, -1.0f, -1.0f);
		      glVertex3f(-1.0f, -1.0f, -1.0f);
		      /*GAUCHE*/
		      glVertex3f( 0.0f, 1.0f, 0.0f);
		      glVertex3f(-1.0f,-1.0f,-1.0f);
		      glVertex3f(-1.0f,-1.0f, 1.0f);
		      glEnd();      
		    }
		    glPopMatrix();/*FIN PYRAMIDE LAMPE*/
		  }
		  glPopMatrix();/*FIN AMPOULE*/
		}
		else {
		  glDisable(l1);
		}
	      }
	      glPopMatrix();/*FIN LAMPE*/
	    }
	    glPopMatrix();/*FIN MAIN*/
	  }
	  glPopMatrix();/*FIN AVANT-BRAS*/
	}
	glPopMatrix();/*FIN COUDE*/
      }
      glPopMatrix();/*FIN BRAS*/
    }
    glPopMatrix(); /*FIN EPAULE*/
      
    /*EPAULE DROITE*/
    glPushMatrix();
    {
      glTranslatef(-0.25f,0.35f,0.0f);
      glColor3f(1.0f,0.8f,0.3f);
      glutSolidSphere(0.2f,10,10);	
      /*BRAS DROIT*/
      glPushMatrix();
      {
	glRotatef(man[5],0.0f,1.0f,0.0f);  
	glRotatef(70.0f,0.0f,0.0f,1.0f); 
	glTranslatef(-0.25f,0.0f,0.0f);
	glPushMatrix();
	glScalef(3.0f,1.0f,1.0f);
	glutSolidCube(0.16);
	glPopMatrix();
	/*COUDE DROIT*/
	glPushMatrix();
	{
	  glTranslatef(-0.24f,0.0f,0.0f);
	  glutSolidSphere(0.15f,10,10);
	  /*AVANT-BRAS DROIT*/
	  glPushMatrix();
	  {
	    glRotatef(man[7],0.0f,1.0f,0.0f);  
	    glTranslatef(-0.13f,0.0f,0.0f);
	    glPushMatrix();
	    {
	      glScalef(5.0f,1.0f,1.0f);
	      glutSolidCube(0.12f);
	    }
	    glPopMatrix();
	    /*MAIN DROITE*/
	    glPushMatrix();
	    {
	      glTranslatef(-0.31f,0.0f,0.0f);
	      glutSolidSphere(0.12f,10,10);
	      glPushMatrix();
	      {
		if(orb && isPlayer){ /*ORBE DISCO*/
		  GLfloat randR = randFloat(1);
		  GLfloat randG = randFloat(1);
		  GLfloat randB = randFloat(1);
		  
		  glColor3f(randR,randG,randB);
		  glTranslatef(0.0f,0.15f,0.25f+(man[8]*2));
		  /*LIGHT*/
		  Light *light2 = &colororb[0];                                                                                                     
		  initLight(light2, l2);
		  spotPos(light2, l2);
		  light2->pos[3] = light2->pos[3]+(man[8]*2);
		  
		  light2->amb[0] = randR;
		  light2->amb[1] = randG;
		  light2->amb[2] = randB;

		  light2->diff[0] = randR;
		  light2->diff[1] = randG;
		  light2->diff[2] = randB; 
		  
		  glutSolidSphere(0.13f,10,10);
		}
		else glDisable(l2);
	      }
	      glPopMatrix();
	    }
	    glPopMatrix();/*FIN MAIN*/
	  }
	  glPopMatrix();/*FIN AVANT-BRAS*/
	}
	glPopMatrix();/*FIN COUDE*/
      }
      glPopMatrix();/*FIN BRAS*/
    }
    glPopMatrix(); /*FIN EPAULE*/
    
    
    /*HANCHE GAUCHE*/
    glPushMatrix();
    {
      glTranslatef(0.2f,-0.35f,0.0f);
      glColor3f(1.0f,0.8f,0.3f);
      glutSolidSphere(0.2f,10,10);	
      /*CUISSE GAUCHE*/
      glPushMatrix();
      {
	glRotatef(man[0],1.0f,0.0f,0.0f);
	glTranslatef(0.0f,-0.25f,0.0f);
	glPushMatrix();
	glScalef(1.0f,4.0f,1.0f);
	glutSolidCube(0.2);
	glPopMatrix();
	/* GENOU GAUCHE*/
	glPushMatrix();
	{
	  glTranslatef(0.0f,-0.35f,0.0f);
	  glutSolidSphere(0.17f,10,10);
	  /*MOLLET GAUCHE*/
	  glPushMatrix();
	  {
	    glRotatef(man[2],1.0f,0.0f,0.0f);  
	    glTranslatef(0.0f,-0.3f,0.0f);
	    glPushMatrix();
	    {
	      glScalef(1.0f,6.0f,1.0f);
	      glutSolidCube(0.16f);
	    }
	    glPopMatrix();
	    /*PIED GAUCHE*/
	    glPushMatrix();
	    {
	      glTranslatef(0.0f,-0.4f,0.0f);
	      glutSolidSphere(0.14f,10,10);
	    }
	    glPopMatrix();/*FIN PIED*/
	  }
	  glPopMatrix();/*FIN MOLLET*/
	}
	glPopMatrix();/*FIN GENOU*/
      }
      glPopMatrix();/*FIN CUISSE*/
    }
    glPopMatrix(); /*FIN HANCHE*/
    
    /*HANCHE DROITE*/
    glPushMatrix();
    {
      glTranslatef(-0.2f,-0.35f,0.0f);
      glColor3f(1.0f,0.8f,0.3f);
      glutSolidSphere(0.2f,10,10);	
      /*CUISSE DROITE*/
      glPushMatrix();
      {
	glRotatef(man[1],1.0f,0.0f,0.0f); 
	glTranslatef(0.0f,-0.25f,0.0f);
	glPushMatrix();
	glScalef(1.0f,4.0f,1.0f);
	glutSolidCube(0.2);
	glPopMatrix();
	/*GENOU DROIT*/
	glPushMatrix();
	{
	  glTranslatef(0.0f,-0.35f,0.0f);
	  glutSolidSphere(0.17f,10,10);
	  /*MOLLET DROIT*/
	  glPushMatrix();
	  {
	    glRotatef(man[3],1.0f,0.0f,0.0f);  
	    glTranslatef(0.0f,-0.3f,0.0f);
	    glPushMatrix();
	    {
	      glScalef(1.0f,6.0f,1.0f);
	      glutSolidCube(0.16f);
	    }
	    glPopMatrix();
	    /*PIED DROIT*/
	    glPushMatrix();
	    {
	      glTranslatef(0.0f,-0.4f,0.0f);
	      glutSolidSphere(0.14f,10,10);
	    }
	    glPopMatrix();/*FIN PIED*/
	  }
	  glPopMatrix();/*FIN MOLLET*/
	}
	glPopMatrix();/*FIN GENOU*/
      }
      glPopMatrix();/*FIN CUISSE*/
    }
    glPopMatrix(); /*FIN HANCHE*/    
  }
  glPopMatrix();
}

GLvoid Modelisation()
{ 
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
   
  VM_init();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gluLookAt(player[9] + sin((player[11]+180)*(M_PI/180)),0.0f,player[10]+cos((player[11]+180)*(M_PI/180)),player[9],0.0f,player[10],0.0f,2.0f,0.0f);
  glPushMatrix();
  {
    glPushMatrix(); /*SKY BOX*/
    {
      glEnable(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
      glTexImage2D(GL_TEXTURE_2D,
		   0,
		   GL_RGB,
		   texture->width,
		   texture->height,
		   0,
		   GL_RGB,
		   GL_UNSIGNED_BYTE,
		   texture->data);
    
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
      glBegin(GL_QUADS);
      glTexCoord2i(0.0, 0.0);	    glVertex3f(-sky_size, -sky_size, -sky_size);    
      glTexCoord2i(10.0, 0.0);    glVertex3f( sky_size, -sky_size, -sky_size);    
      glTexCoord2i(10.0, 10.0);   glVertex3f( sky_size,  sky_size, -sky_size);   
      glTexCoord2i(0.0, 10.0);    glVertex3f(-sky_size,  sky_size, -sky_size);  
      glEnd();
    
      glBegin(GL_QUADS);
      glTexCoord2i(0.0, 0.0);	    glVertex3f(-sky_size, -sky_size, -sky_size);    
      glTexCoord2i(10.0, 0.0);    glVertex3f( sky_size, -sky_size, -sky_size);    
      glTexCoord2i(10.0, 10.0);   glVertex3f( sky_size,  -sky_size, sky_size);   
      glTexCoord2i(0.0, 10.0);    glVertex3f(-sky_size,  -sky_size, sky_size);  
      glEnd();
		
      glBegin(GL_QUADS);
      glTexCoord2i(0.0, 0.0);	    glVertex3f(-sky_size, -sky_size, -sky_size);    
      glTexCoord2i(10.0, 0.0);    glVertex3f(-sky_size, sky_size, -sky_size);    
      glTexCoord2i(10.0, 10.0);   glVertex3f(-sky_size, sky_size,  sky_size);   
      glTexCoord2i(0.0, 10.0);    glVertex3f(-sky_size, -sky_size, sky_size);  
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2i(0.0, 0.0);	    glVertex3f(-sky_size, -sky_size, sky_size);    
      glTexCoord2i(10.0, 0.0);    glVertex3f( sky_size, -sky_size, sky_size);    
      glTexCoord2i(10.0, 10.0);   glVertex3f( sky_size,  sky_size, sky_size);   
      glTexCoord2i(0.0, 10.0);    glVertex3f(-sky_size,  sky_size, sky_size);  
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2i(0.0, 0.0);	    glVertex3f(-sky_size, sky_size, -sky_size);    
      glTexCoord2i(10.0, 0.0);    glVertex3f( sky_size, sky_size, -sky_size);    
      glTexCoord2i(10.0, 10.0);   glVertex3f( sky_size,  sky_size, sky_size);   
      glTexCoord2i(0.0, 10.0);    glVertex3f(-sky_size,  sky_size, sky_size);  
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2i(0.0, 0.0);	    glVertex3f(sky_size, -sky_size, -sky_size);    
      glTexCoord2i(10.0, 0.0);    glVertex3f(sky_size, sky_size, -sky_size);    
      glTexCoord2i(10.0, 10.0);   glVertex3f(sky_size, sky_size,  sky_size);   
      glTexCoord2i(0.0, 10.0);    glVertex3f(sky_size, -sky_size, sky_size);  
      glEnd();
      
      glDisable(GL_TEXTURE_2D);
    }/* SOL */
    glPopMatrix();
    drawPlane(25,25);
  }
  glPopMatrix();

  bonhomme(player,1,GL_LIGHT0,GL_LIGHT1,flashlight,orbdisco);
  bonhomme(dummy,1,GL_LIGHT2,GL_LIGHT3,1,1);
  moveDummy(1,1);
  glutSwapBuffers();
}

int main(int argc, char **argv) 
{ 
  texture = readPpm("sky.ppm");
  return notre_init(argc, argv, &Modelisation);
}
