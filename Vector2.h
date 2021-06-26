#pragma once
class Vector2
{
public:
	float x;
	float y;

	static const Vector2 Zero;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& vec);
	Vector2(Vector2 begin, Vector2 end);
	virtual ~Vector2();

	Vector2& operator = (const Vector2 vec);
	Vector2& operator = (const float scalar);
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;
	Vector2 operator + (const Vector2& vec) const;
	Vector2 operator - (const Vector2& vec) const;
	Vector2 operator * (const Vector2& vec) const;
	Vector2 operator * (const float scalar) const;
	Vector2 operator / (const Vector2& vec) const;
	Vector2 operator / (const float scalar) const;
	Vector2 operator - () const;
	Vector2& operator += (const Vector2& vec);
	Vector2& operator += (const float scalar);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator -= (const float scalar);
	Vector2& operator *= (const Vector2& vec);
	Vector2& operator *= (const float scalar);
	Vector2& operator /= (const Vector2& vec);
	Vector2& operator /= (const float scalar);

	float GetMagnitude();
	float GetSqrMagnitude();
	Vector2 GetNormalized();
	void Normalize();
	Vector2 GetReverse();

	static float Dot(Vector2 lhs, Vector2 rhs);
	static Vector2 Lerp(Vector2 a, Vector2 b, float t);
	static float Angle(Vector2 from, Vector2 to);
	static Vector2 Rotate(Vector2 vec, float rotation);
	static float Distance(Vector2 vec1, Vector2 vec2);
	static Vector2 Normalize(Vector2 begin, Vector2 end);
	static Vector2 Normalize(Vector2 vec);
	static Vector2 Reflection(Vector2 vec, Vector2 mirror);
	static float Cross(Vector2 lhs, Vector2 rhs);
};

