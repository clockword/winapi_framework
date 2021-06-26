#include "ResourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
	static ResourceManager instance;

	return &instance;
}

Image *ResourceManager::LoadImage_(std::string name)
{
	if (m_img.find(name) == m_img.end())
	{
		std::string path = "./Resource/Image/" + name + ".png";

		WCHAR pathfile[MAX_PATH];
		MultiByteToWideChar(CP_ACP, NULL, path.data(), -1, pathfile, MAX_PATH);

		m_img[name] = Image::FromFile(pathfile);
	}

	return GetImage(name);
}

Image *ResourceManager::GetImage(std::string key)
{
	try
	{
		if (m_img.find(key) == m_img.end())
			throw "not found Image from key";
	}
	catch(const char* ch)
	{
		printf("%s", ch);
		return nullptr;
	}
	
	return m_img[key];
}

void ResourceManager::DeleteImages()
{
	std::map<std::string, Image*>::iterator it;
	for (it = m_img.begin(); it != m_img.end();)
	{
		Image* img = (it++)->second;
		delete img;
	}
	m_img.clear();
}

