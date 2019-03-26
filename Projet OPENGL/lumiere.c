#include "lumiere.h"

void initLight(Light *light, int numlight)
{
  glEnable(numlight);
  glLightfv(numlight, GL_AMBIENT, light->amb);
  glLightfv(numlight, GL_DIFFUSE, light->diff);
  glLightfv(numlight, GL_SPECULAR, light->spec);
  if(light->spotExp != 0) glLightf(numlight, GL_SPOT_EXPONENT, light->spotExp);
  if(light->spotCutoff != 0) glLightf(numlight, GL_SPOT_CUTOFF, light->spotCutoff);
  glLightf(numlight, GL_CONSTANT_ATTENUATION, light->atten[0]);
  glLightf(numlight, GL_LINEAR_ATTENUATION, light->atten[1]);
  glLightf(numlight, GL_QUADRATIC_ATTENUATION, light->atten[2]);
}

void spotPos(Light *light, int numlight)
{
  glPushMatrix();
    glLightfv(numlight, GL_POSITION, light->pos);
    glLightfv(numlight, GL_SPOT_DIRECTION, light->spotDir);
  glPopMatrix();
}

void drawLight(Light *light)
{
  glColor4fv(light->diff);
  glPushMatrix();
  {
    glBegin(GL_LINES);
    glVertex3f(light->pos[0], light->pos[1], light->pos[2]);
    glVertex3f(light->spotDir[0], light->spotDir[1], light->spotDir[2]);
    glEnd();
  }
  glPopMatrix();
}
