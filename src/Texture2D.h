#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int ID;
    // texture image dimensions
    unsigned int Width, Height; // width and height of loaded image in pixels
    // texture Format
    unsigned int Internal_Format; 
    unsigned int Image_Format; 
    // texture configuration
    unsigned int Wrap_S;
    unsigned int Wrap_T;
    unsigned int Filter_Min; 
    unsigned int Filter_Max; 
    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;
};

#endif