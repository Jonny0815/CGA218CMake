//
// Created by Benjamin Meyer on 25.12.2020.
//

#ifndef CGA218_TEXTURE2D_H
#define CGA218_TEXTURE2D_H

#include <libheaders.h>
#include <glerror.h>
#include "ShaderProgram.h"


class Texture2D {
private:

    GLuint texid = 0;
    ShaderProgram* shader;

public:

    Texture2D();
    Texture2D(const std::string & path, bool genMipMaps, ShaderProgram* h_shader);

    void setTextureParameters(GLint wrappingType, GLint wrappingMode, GLint filterType, GLint filterMode);
    void setTextureParameters();
    void bind(ShaderProgram* h_shader);
    void useTexture(GLuint tu);

    GLint getTexid() { return texid; }

    
};





#endif //CGA218_TEXTURE2D_H
