#ifndef MATERIAL_H
#define MATERIAL_H
#include <ShaderProgram.h>
#include <Texture2D.h>
#include <vector>

class Material {
public:
	Material();
	Material(std::string diff, std::string emis, std::string spec, float shin, bool genMidmap);
	Material(std::string diff, std::string emis, std::string spec, float shin, bool genMidmap, ShaderProgram* shader);
	std::vector<Texture2D>* getTextures() { return &_textures; };

	void render();

	int getShaderProg() { return _shader->prog; }
	
private:

	inline GLint maxTextureUnits()
	{
		static GLint mtu = -1;
		if (mtu == -1)
		{
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mtu);
		}
		return mtu;
	}

	Texture2D getDiff() { return _textures[0]; }
	Texture2D getEmis() { return _textures[1]; }
	Texture2D getSpec() { return _textures[2]; }

	std::vector<Texture2D> _textures;
	float _shininess = 0;
	ShaderProgram* _shader = nullptr;

};
#endif