#include "Game.h"
#include "GameObject.h"

#include "Level.h" 

#include "ResourceManager.h"
#include "InputManager.h"
#include "DijkstraPath.h"
#include "AStarPath.h"
#include "World.h"

Level::Level(Game* game, std::string name) : m_game(game), m_name(name)
{
}

Level::~Level()
{
}

void Level::Init()
{
	for (const auto& pair : m_obj)
	{
		pair.second->Init();
	}

	World::GetInstance()->Init();
}

void Level::Update(Graphics* g, DWORD tick)
{
	for (const auto& pair : m_obj)
	{
		GameObject* const obj = pair.second;
		if (obj->GetActive())
			obj->Update(g, tick);
	}
}

void Level::Load()
{
	Unload();

	FILE* fp = nullptr;

	std::string path = "./Resource/Level/" + m_name + ".txt";
	fp = fopen(path.c_str(), "rt");

	while (true)
	{
		int key, posX, posY;
		std::string name;
		std::string tag;

		char ch_name[255] = { 0, };
		char ch_tag[255] = { 0, };
		fscanf(fp, "%d %s %s %d %d", &key, ch_tag, ch_name, &posX, &posY);
		name = ch_name;
		tag = ch_tag;
		if (name == "End")
			break;
		std::string type = name.substr(0, 2);
		std::string img = name.substr(3);
		if (type == "bg")
		{
			m_obj[key] = new GameObject();
		}
		else if (type == "bt")
		{
			m_obj[key] = new Button();
			InputManager::GetInstance()->RegisterButton(static_cast<Button*>(m_obj[key]));
		}
		else if (type == "co")
		{
			m_obj[key] = new CollObject();
			World::GetInstance()->RegisterCollObject(tag, static_cast<CollObject*>(m_obj[key]));
		}
		else if (type == "tb")
		{
			m_obj[key] = new TextBox();
			InputManager::GetInstance()->RegisterTextBox(static_cast<TextBox*>(m_obj[key]));
		}
		else if (type == "tx")
		{
			m_obj[key] = new Text();
		}
		else if (type == "dp")
		{
			m_obj[key] = new DijkstraPath();
		}
		else if (type == "ap")
		{
			m_obj[key] = new AStarPath();
		}

		m_obj[key]->SetFile(img);
		m_obj[key]->SetImage(ResourceManager::GetInstance()->LoadImage_(img));
		m_obj[key]->SetTag(tag);
		m_obj[key]->SetName(img);
		m_obj[key]->SetCollider(img);
		m_obj[key]->SetPosition(posX, posY);
		m_obj[key]->SetLevel(this);

		m_obj[key]->LoadExtra();
	}

	fclose(fp);
}

void Level::Unload()
{
	World::GetInstance()->ClearRegistered();
	InputManager::GetInstance()->ClearRegistered();
	for (auto& pair : m_obj)
	{
		delete pair.second;
	}
	m_obj.clear();
}

template<class T>
T Level::AddGameobject(int index)
{
	GameObject* obj = dynamic_cast<GameObject*>(new T());
	if (obj) m_obj.insert({ index, obj });
	return obj;
}