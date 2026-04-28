#include "../include/solar_system.h"

GLuint earthTexture;
GLuint marsTexture;

void loadTextures()
{
glGenTextures(1,&earthTexture);
glBindTexture(GL_TEXTURE_2D,earthTexture);

glTexParameteri(GL_TEXTURE_2D,
GL_TEXTURE_MIN_FILTER,
GL_LINEAR);

glGenTextures(1,&marsTexture);
glBindTexture(GL_TEXTURE_2D,marsTexture);

glTexParameteri(GL_TEXTURE_2D,
GL_TEXTURE_MIN_FILTER,
GL_LINEAR);
}