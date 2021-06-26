#pragma once

#include <Windows.h>
#include <map>
#include <string>

//gdiplus must need to include Windows.h
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

static class ResourceManager sealed
{
private:
	typedef std::map<std::string, Image*> ImageMap;
	ImageMap m_img;

public:
	static ResourceManager* GetInstance();

private:
	ResourceManager() {}

	ResourceManager(ResourceManager&);
	ResourceManager& operator=(ResourceManager&);

public:
	Image* LoadImage_(std::string name);
	Image* GetImage(std::string key);
	void DeleteImages();
};

