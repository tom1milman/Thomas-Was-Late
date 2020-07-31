#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	//Reference to m_Textures
	auto& m = m_s_Instance->m_Textures;

	//find the required key value pair
	auto keyValuePair = m.find(filename);

	//if texture found, return
	if (keyValuePair != m.end())
	{
		return keyValuePair->second;
	}
	//if not found, create key value pair
	//and load the texture into the map
	else
	{
		//create new key value pair
		auto& texture = m[filename];
		//load new texture
		texture.loadFromFile(filename);

		//return new texture
		return texture;
	}
}