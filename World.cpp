#include "World.h"

void World::PushCheckMap(std::string tag, CollObjectArr push)
{
	int size = push.size();
	for (int i = 0; i < size; ++i)
	{
		m_colCheckMap[tag].push_back(push[i]);
	}
}

void World::CollisionProcess(CollObject* object, CollObject* check, Point& movepos,DWORD tick)
{
	typedef Collider::CollType Type;
	float deltatime = tick * 0.001f;
	bool isCollide = false;

	std::string objectTag = object->GetTag();
	std::string checkTag = check->GetTag();
	Collider* objectCollider = object->GetCollider();
	Collider* checkCollider = check->GetCollider();
	Vector2 velocity = object->GetVelocity();
	Vector2 force = object->GetForce();
	Type objectColliderType = objectCollider->GetColliderType();
	Type checkColliderType = checkCollider->GetColliderType();

	switch (objectColliderType)
	{
	case Type::Rect:
	{
		Rect movedRect = objectCollider->GetRect();
		switch (checkColliderType)
		{
		case Type::Rect:
		{
			Rect checkRect = checkCollider->GetRect();

			if (movedRect.GetLeft() < checkRect.GetRight() && movedRect.GetRight() > checkRect.GetLeft()
				&& movedRect.GetTop() < checkRect.GetBottom() && movedRect.GetBottom() > checkRect.GetTop())
			{
				if (velocity.y > 0.0f)
				{
					movepos.Y = checkRect.GetTop() - movedRect.Height * 0.5f;
				}
				else if (velocity.y < 0.0f)
				{
					movepos.Y = checkRect.GetBottom() + movedRect.Height * 0.5f;
				}
				else if (velocity.x < 0.0f)
				{
					movepos.X = checkRect.GetRight() + movedRect.Width * 0.5f;
				}
				else if (velocity.x > 0.0f)
				{
					movepos.X = checkRect.GetLeft() - movedRect.Width * 0.5f;
				}
				isCollide = true;
				object->OnCollisionEnter(check);
			}
		}break;
		case Type::Circle:
		{
			Vector2 checkPosition = Vector2(checkCollider->GetPosition().X, checkCollider->GetPosition().Y);
			int checkRadius = checkCollider->GetRadius();
			Vector2 temp = checkPosition;

			if (checkPosition.x < movedRect.GetLeft()) temp.x = movedRect.GetLeft();
			else if (checkPosition.x > movedRect.GetRight()) temp.x = movedRect.GetRight();
			if (checkPosition.y < movedRect.GetTop()) temp.y = movedRect.GetTop();
			else if (checkPosition.y > movedRect.GetBottom()) temp.y = movedRect.GetBottom();
			float distance = Vector2::Distance(checkPosition, temp);

			if (distance < checkRadius)
			{
				// 하지말자 지훈아

				isCollide = true;
				object->OnCollisionEnter(check);
			}
		}break;
		}
	}break;
	case Type::Circle:
	{
		Vector2 movedPosition = Vector2(objectCollider->GetPosition().X, objectCollider->GetPosition().Y);
		int movedRadius = objectCollider->GetRadius();
		switch (checkColliderType)
		{
		case Type::Rect:
		{
			Rect checkRect = checkCollider->GetRect();
			Vector2 temp = movedPosition;
			
			if (movedPosition.x < checkRect.GetLeft()) temp.x = checkRect.GetLeft();
			else if (movedPosition.x > checkRect.GetRight()) temp.x = checkRect.GetRight();
			if (movedPosition.y < checkRect.GetTop()) temp.y = checkRect.GetTop();
			else if (movedPosition.y > checkRect.GetBottom()) temp.y = checkRect.GetBottom();
			float distance = (movedPosition - temp).GetMagnitude();

			if (distance <= movedRadius)
			{
				/*Vector2 checkPosition = Vector2(checkCollider->GetPosition().X, checkCollider->GetPosition().Y);
				float angle = Vector2::Angle(Vector2::Right, (checkPosition - movedPosition));*/

				// 지훈아 나중에 해

				isCollide = true;
				object->OnCollisionEnter(check);
			}
		}break;
		case Type::Circle:
		{
			Vector2 checkPosition = Vector2(checkCollider->GetPosition().X, checkCollider->GetPosition().Y);
			int checkRadius = checkCollider->GetRadius();

			if (Vector2::Distance(movedPosition, checkPosition) < movedRadius + checkRadius)
			{
				Vector2 pos = checkPosition + Vector2::Normalize(checkPosition, movedPosition) * (movedRadius + checkRadius);
				movepos = Point(pos.x, pos.y);

				isCollide = true;
				object->OnCollisionEnter(check);
			}
		}break;
		}
	}break;
	}
}

World* World::GetInstance()
{
	static World instance;

	return &instance;
}

void World::Init()
{
	CollObjectMap::iterator it = m_collObjects.begin();
	for (; it != m_collObjects.end(); it++)
	{
		CollObjectArr arr = it->second;
		std::string tag = it->first;
		if (tag == "platform")
		{
			// check nothing becasue it's not move
			PushCheckMap("player", arr);
			PushCheckMap("prop", arr);
		}
		else if (tag == "moving") // moving platform
		{
			// not use
		}
		else if (tag == "prop")
		{
			PushCheckMap("player", arr);
			PushCheckMap("prop", arr);
		}
		else if (tag == "player")
		{
			PushCheckMap("prop", arr);
		}
		else if (tag == "enemy") // npc
		{
			// not use
		}
		else if (tag == "bullet")
		{
			// not use
		}
		else
		{
			throw "Unknown Tag";
		}
	}
}

void World::FixedUpdate(DWORD tick)
{
	CollObjectMap::iterator it = m_collObjects.begin();
	for(;it != m_collObjects.end(); it++)
	{ 
		std::string tag = it->first;
		int arrSize = it->second.size();
		for (int i = 0; i < arrSize; ++i)
		{
			auto object = it->second[i];
			if (!object->GetActive())
				continue;
			object->FixedUpdate(tick);

			Vector2 velocity = object->GetVelocity() * tick * 0.001f;
			Point movePos = object->GetPosition() + Point(velocity.x, velocity.y);
			object->SetMovedPosition(movePos);
			int otherSize = m_colCheckMap[tag].size();
			for (int j = 0; j < otherSize; ++j)
			{
				auto other = m_colCheckMap[tag][j];
				if (!other->GetActive())
					continue;
				if (object == other)
					continue;
				CollisionProcess(object, other, movePos, tick);
			}
			object->SetMovedPosition(movePos);
		}
	}
}

void World::RegisterCollObject(std::string tag, CollObject* object)
{
	m_collObjects[tag].push_back(object);
}

void World::ClearRegistered()
{
	CollObjectMap::iterator it;
	for (it = m_collObjects.begin(); it != m_collObjects.end(); it++)
	{
		it->second.clear();
	}
	for (it = m_colCheckMap.begin(); it != m_colCheckMap.end(); it++)
	{
		it->second.clear();
	}
	m_collObjects.clear();
	m_colCheckMap.clear();
}
