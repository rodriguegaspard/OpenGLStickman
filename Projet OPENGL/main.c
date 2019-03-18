//gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o  switch_light.o VM_init.o -lm -lGL -lGLU -lglut -no-pie -o test


#include "init.h"
#include "axes.h"
#include "VM_init.h"

GLfloat xrot = 0.0f;   
GLfloat yrot = 0.0f;   
GLfloat z = -5.0f;

GLfloat y_axe = 0.0f;
GLfloat x_axe = 0.0f;
GLfloat z_axe = 0.0f;
GLfloat mode = 0.0f;


GLvoid Modelisation()
{
  // Entre glPushMatrix et glPopMatrix s'écrit la description de la scène.
  glEnable(GL_COLOR_MATERIAL);
  // Gestion de la lumiere
  
  GLfloat position[] = {0.0, 5.0, 0.0, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, position); // Positionnement de la source lumineuse
  
  GLfloat ambiant[] = {0.5f,0.5f,0.5f,1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiant);
  
  GLfloat lightPos[] = {0.5f,0.5f,0.5f,1.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightPos);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); // Activation de la lumiere
  
  VM_init();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  {
    // TORSE
    glPushMatrix();
    {
      glScalef(1.0f,2.0f,1.0f);
      glColor3f(1,0.8,0.3);
      glutSolidCube(0.5);
    }
    glPopMatrix();
    //COU
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
      // TETE
      glPushMatrix();
      {
	glTranslatef(0.0f,0.25f,0.0f);
	glutSolidSphere(0.25f,30,30);
	//Oeil gauche
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
	
	//Oeil droit
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
    
    
    //EPAULE GAUCHE
	glPushMatrix();
	{
	  glTranslatef(0.25f,0.35f,0.0f);
	  glColor3f(1.0f,0.8f,0.3f);
	  glutSolidSphere(0.2f,10,10);	
	  // BRAS GAUCHE
	  glPushMatrix();
	  {
	    glTranslatef(0.25f,0.0f,0.0f);
	    glPushMatrix();
	    glScalef(3.0f,1.0f,1.0f);
	    glutSolidCube(0.16);
	    glPopMatrix();
	    // COUDE GAUCHE
	    glPushMatrix();
	    {
	      glTranslatef(0.24f,0.0f,0.0f);
	      glutSolidSphere(0.15f,10,10);
	      // AVANT-BRAS GAUCHE
	      glPushMatrix();
	      {
		glTranslatef(0.13f,0.0f,0.0f);
		glPushMatrix();
		{
		  glScalef(5.0f,1.0f,1.0f);
		  glutSolidCube(0.12f);
		}
		glPopMatrix();
		//MAIN GAUCHE
		glPushMatrix();
		{
		  glTranslatef(0.31f,0.0f,0.0f);
		  glutSolidSphere(0.12f,10,10);
		}
		glPopMatrix();//FIN MAIN
	      }
	      glPopMatrix();//FIN AVANT-BRAS
	    }
	    glPopMatrix();//FIN COUDE
	  }
	  glPopMatrix();//FIN BRAS
	}
	glPopMatrix(); //FIN EPAULE
  }
  glPopMatrix(); 
  axes();
  glutSwapBuffers();
}

int main(int argc, char **argv) 
{  
  return notre_init(argc, argv, &Modelisation);
}
