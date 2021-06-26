#pragma once

#include "CollObject.h"

class CollObject;
class Collider
{
private:
	Point m_position;
	Point m_localPosition;

public:
	enum class CollType
	{
		Rect,
		Circle
	};

private:
	CollType m_colltype;
	CollObject* m_collObject;

protected:
	void SetColliderType(CollType type) { m_colltype = type; }

public:
	Collider(CollType type, Point position = Point()) : m_collObject(nullptr) { m_colltype = type; m_position = position; }
	virtual ~Collider(){}

	CollType GetColliderType() { return m_colltype; }
	void SetThisCollObject(CollObject* object) { m_collObject = object; }
	CollObject* GetThisCollObject() { return m_collObject; }
	void SetPosition(Point position) { m_position = position; }
	Point GetPosition() { return m_position; }
	void SetLocalPosition(Point position) { m_localPosition = position; }
	Point GetLocalPosition() { return m_localPosition; }

	virtual void SetCollider(Rect rect = Rect()){}
	virtual void SetCollider(INT radius = 0) {}
	virtual void Draw(Graphics* g) {}

	virtual Rect GetRect() { return Rect(); }
	virtual Size GetSize() { return Size(); }
	virtual INT GetRadius() { return 0; }
};

class ColliderRect : public Collider
{
private:
	Size m_size;

public:
	ColliderRect() : Collider(CollType::Rect) { m_size = Size(); }
	ColliderRect(Size size = Size()) : Collider(CollType::Rect) { m_size = size; }
	virtual ~ColliderRect() {}

	void SetCollider(Size size = Size()) { m_size = size; }
	Size GetSize() { return m_size; }
	Rect GetRect();

	void Draw(Graphics* g);
};

class ColliderCircle : public Collider
{
private:
	INT m_radius;

public:
	ColliderCircle() : Collider(CollType::Circle) { m_radius = 0; }
	ColliderCircle(INT radius = 0) : Collider(CollType::Circle) { m_radius = radius; }
	virtual ~ColliderCircle(){}

	void SetCollider(INT radius = 0) { m_radius = radius; }
	INT GetRadius() { return m_radius; }

	void Draw(Graphics* g);
};