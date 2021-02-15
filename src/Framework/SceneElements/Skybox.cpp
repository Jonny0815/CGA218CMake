#include "Skybox.h"

Skybox::Skybox(ShaderProgram* h_shader)
{

    
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    std::vector<std::string> faces
    {   "assets/textures/skybox_left.png",
        "assets/textures/skybox_right.png",
        "assets/textures/skybox_top.png",
        "assets/textures/skybox_bottom.png",
        "assets/textures/skybox_front.png",
        "assets/textures/skybox_back.png"};
    texid = loadCubemap(faces);
    shader = h_shader;
}

Skybox::~Skybox()
{
}

void Skybox::render(ShaderProgram* h_shader, Camera* h_cam)
{
    if (shader->prog == h_shader->prog)
    {
        
        glDepthFunc(GL_LEQUAL);
        
          // change depth function so depth test passes when values are equal to depth buffer's content
        //shader->use();

        glm::mat4 view = glm::mat4(glm::mat3(h_cam->getViewMatrix())); // remove translation from the view matrix
        shader->setUniform("view", view, false);
                                 // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0 + shader->getCurrentTU());
        glBindTexture(GL_TEXTURE_CUBE_MAP, texid);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set dept
    }
}

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;

    GLint internalformat;
    GLenum format;
    

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        switch (nrChannels)
        {
        case 1:
            internalformat = GL_R8;
            format = GL_RED;
            break;
        case 2:
            internalformat = GL_RG8;
            format = GL_RG;
            break;
        case 3:
            internalformat = GL_RGB8;
            format = GL_RGB;
            break;
        case 4:
            internalformat = GL_RGBA8;
            format = GL_RGBA;
            break;
        default:
            internalformat = GL_RGB8;
            format = GL_RGB;
            break;
        }
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
