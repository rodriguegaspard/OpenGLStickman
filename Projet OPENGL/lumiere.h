#ifndef LUMIERE_H
  #define LUMIERE_H
  #include <math.h>
  #include <GL/glut.h>

  typedef struct lightRec {
    float amb[4];
    float diff[4];
    float spec[4];
    float pos[4];
    float spotDir[3];
    float spotExp;
    float spotCutoff;
    float atten[3];
  } Light;

  void initLight(Light *light, int lt); //Initialise la lumière
  void spotPos(Light *light, int lt); //Paramètres pour un spotlight
  void drawLight(Light *light);// Fonction de debug qui trace une ligne du point d'origine du spot vers sa direction

#endif
