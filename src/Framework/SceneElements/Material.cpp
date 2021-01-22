#include "Material.h"

Material::Material()
{
}

Material::Material(std::string diff, std::string emis, std::string spec, float shin, bool genMidmap, ShaderProgram* shader)
{
	_textures.push_back(Texture2D(diff, genMidmap, shader));
	_textures.push_back(Texture2D(emis, genMidmap, shader));
	_textures.push_back(Texture2D(spec, genMidmap, shader));
	_shininess = shin;
	_shader = shader;

	getSpec().setTextureParameters();
	getDiff().setTextureParameters();
	getEmis().setTextureParameters();
}

void Material::render()
{	
	if (_shader->getCurrentTU() >= maxTextureUnits())
	{
		_shader->resetTU();
	}
	_shader->getFreeTU();
	getEmis().useTexture(_shader->getCurrentTU());
	_shader->setUniform("matEmissive", (GLint)_shader->getCurrentTU());
	_shader->getFreeTU();
	getDiff().useTexture(_shader->getCurrentTU());
	_shader->setUniform("matDiffuse", (GLint)_shader->getCurrentTU());
	_shader->getFreeTU();
	getSpec().useTexture(_shader->getCurrentTU());
	_shader->setUniform("matSpecular", (GLint)_shader->getCurrentTU());
	
}
