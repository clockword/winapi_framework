#define _USE_MATH_DEFINES
#include "Vector2.h"
#include <cmath>

const Vector2 Vector2::Up = Vector2(0.0f, -1.0f);
const Vector2 Vector2::Down = Vector2(0.0f, 1.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}


Vector2::Vector2(Vector2 begin, Vector2 end)
{
	Vector2 vec = end - begin;
	this->x = vec.x;
	this->y = vec.y;
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2 vec)
{
	x = vec.x;
	y = vec.y;

	return *this;
}

Vector2& Vector2::operator=(const float scalar)
{
	x = scalar;
	y = scalar;

	return *this;
}

bool Vector2::operator==(const Vector2& vec) const
{
	return (x == vec.x && y == vec.y);
}

bool Vector2::operator!=(const Vector2& vec) const
{
	return (x != vec.x || y != vec.y);
}

Vector2 Vector2::operator+(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x + vec.x;
	rVec.y = y + vec.y;

	return rVec;
}

Vector2 Vector2::operator-(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x - vec.x;
	rVec.y = y - vec.y;

	return rVec;
}

Vector2 Vector2::operator*(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x * vec.x;
	rVec.y = y * vec.y;

	return rVec;
}

Vector2 Vector2::operator*(const float scalar) const
{
	Vector2 rVec;

	rVec.x = x * scalar;
	rVec.y = y * scalar;

	return rVec;
}

Vector2 Vector2::operator/(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x / vec.x;
	rVec.y = y / vec.y;

	return rVec;
}

Vector2 Vector2::operator/(const float scalar) const
{
	Vector2 rVec;
	float v = 1.0f / scalar;

	rVec.x = x * v;
	rVec.y = y * v;

	return rVec;
}

Vector2 Vector2::operator-() const
{
	Vector2 rVec;

	rVec.x = -x;
	rVec.y = -y;

	return rVec;
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2& Vector2::operator+=(const float scalar)
{
	x += scalar;
	y += scalar;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2& Vector2::operator-=(const float scalar)
{
	x -= scalar;
	y -= scalar;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

Vector2& Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

Vector2& Vector2::operator/=(const float scalar)
{
	float v = 1.0f / scalar;

	x *= v;
	y *= v;

	return *this;
}

float Vector2::GetMagnitude()
{
	if (x == 0.0f && y == 0.0f)
		return 0.0f;
	else if (x == 0.0f)
		return y > 0 ? y : -y;
	else if (y == 0.0f)
		return x > 0 ? x : -x;
	return sqrtf(x * x + y * y);
}

float Vector2::GetSqrMagnitude()
{
	if (x == 0.0f && y == 0.0f)
		return 0.0f;
	else if (x == 0.0f)
		return y * y;
	else if (y == 0.0f)
		return x * x;
	return x * x + y * y;
}

Vector2 Vector2::GetNormalized()
{
	if (*this == Vector2::Zero)
		return Vector2::Zero;

	Vector2 temp(*this);

	temp.Normalize();

	return temp;
}

void Vector2::Normalize()
{
	float magnitude = GetMagnitude();
	if (magnitude == 0.0f)
		return;

	x /= GetMagnitude();
	y /= GetMagnitude();
}

Vector2 Vector2::GetReverse()
{
	return (Vector2::Zero - (*this));
}

float Vector2::Dot(Vector2 lhs, Vector2 rhs)
{
	if (lhs.x == 0.0f && rhs.x == 0.0f)
		return lhs.y * rhs.y;
	else if (lhs.y == 0.0f && rhs.y == 0.0f)
		return lhs.x * rhs.x;
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t = 0.5f)
{
	return a * (1.0f - t) + b * t;
}

float Vector2::Angle(Vector2 from, Vector2 to)
{
	if (from.GetNormalized() == to.GetNormalized())
		return 0.0f;
	if (from.GetNormalized().GetReverse() == to.GetNormalized())
		return 180.0f;
	if (Cross(from, to) < 0)
		return -(1 - acosf(Dot(from, to) / from.GetMagnitude() / to.GetMagnitude()) / M_PI) * 180.0f;
	else
		return (1 - acosf(Dot(from, to) / from.GetMagnitude() / to.GetMagnitude()) / M_PI) * 180.0f;
}

Vector2 Vector2::Rotate(Vector2 vec, float rotation)
{
	float rot = rotation * M_PI / 180.0f;

	float x = vec.x * cos(rot) - vec.y * sin(rot);
	float y = -vec.x * sin(rot) - vec.y * cos(rot);
	if (fmod(rotation, 360.0f) == 0.0f || fmod(rotation, 180.0f) == 0.0f) x = 0.0f;
	if (fmod(rotation, 360.0f) == 0.0f) y = -1.0f;
	else if (fmod(rotation, 180.0f) == 0.0f) y = 1.0f;
	else if (fmod(rotation, 90.0f) == 0.0f) y = 0.0f;

	return Vector2(x, y);
}

float Vector2::Distance(Vector2 vec1, Vector2 vec2)
{
	return (vec1 - vec2).GetMagnitude();
}

Vector2 Vector2::Normalize(Vector2 begin, Vector2 end)
{
	return (end - begin).GetNormalized();
}

float Vector2::Cross(Vector2 lhs, Vector2 rhs)
{
	return lhs.x * rhs.y - lhs.y * rhs.x;
}

Vector2 Vector2::Reflection(Vector2 vec, Vector2 mirror)
{
	return vec - (mirror.GetNormalized() * 2.0f * Vector2::Dot(vec, mirror.GetNormalized()));
}

Vector2 Vector2::Normalize(Vector2 vec)
{
	return vec.GetNormalized();
}
