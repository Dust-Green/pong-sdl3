#pragma once


struct Vector2 {
	float x{ 0.0f };
	float y{ 0.0f };

	//constructors
	Vector2()
		:x{ 0.0f }, y{ 0.0f }
	{

	}
	Vector2(float x, float y)
		:x(x),y(y)
	{

	}

	// rhs = Right Hand Side
	//Addition and Subtraction Operators
	Vector2 operator+(Vector2 const& rhs)
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}
	Vector2 operator-(Vector2 const& rhs)
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}
	//Multiplication and Subtraction
	Vector2 operator*(float rhs)
	{
		return Vector2(x * rhs, y * rhs);
	}
	//Vector2 operator/(Vector2 const& rhs)
	//{

	//}
	//Compound Assignments
	Vector2& operator+=(Vector2 const& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}
};