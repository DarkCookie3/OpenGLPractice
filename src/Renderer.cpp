#include "Renderer.h"
#include "IndexBuffer.h"
#include <iostream>
#include "DecToHex.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char* function, const char* file, int line)
{
    if (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error]: 0x" << DecToHex(error)
            << " " << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;        
}