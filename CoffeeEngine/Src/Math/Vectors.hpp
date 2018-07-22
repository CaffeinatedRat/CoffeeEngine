//--------------------------------------------------------------------------------------
// Description: Common vectors and other primitives.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _VECTOR3_MATH_H_
#define _VECTOR3_MATH_H_

namespace CoffeeEngine
{
	namespace Math
	{
		struct Vector3
		{
			float _x, _y, _z;
			Vector3() noexcept : _x(0.0f), _y(0.0f), _z(0.0f) {};
			Vector3(float x, float y, float z) noexcept : _x(x), _y(y), _z(z) {};
			Vector3(const Vector3& vector) noexcept : _x(vector._x), _y(vector._y), _z(vector._z) {};
			Vector3(Vector3&& vector) noexcept : _x(vector._x), _y(vector._y), _z(vector._z)
			{
				vector._x = vector._y = vector._z = 0.0f;
			};

			Vector3& operator=(Vector3&& vector) noexcept = default;
			Vector3& operator=(const Vector3& vector) noexcept = default;
		};

		struct Vector4
		{
			float _x, _y, _z, _w;
			Vector4() noexcept : _x(0.0f), _y(0.0f), _z(0.0f), _w(1.0f) {};
			Vector4(float x, float y, float z, float w) noexcept : _x(x), _y(y), _z(z), _w(w) {};
			Vector4(const Vector4& vector) noexcept : _x(vector._x), _y(vector._y), _z(vector._z), _w(vector._w) {};
			Vector4(Vector4&& vector) noexcept : _x(vector._x), _y(vector._y), _z(vector._z), _w(vector._w)
			{
				vector._x = vector._y = vector._z = 0.0f;
				vector._w = 1.0f;
			};

			Vector4& operator=(Vector4&& vector) noexcept = default;
			Vector4& operator=(const Vector4& vector) noexcept = default;
		};
	}
}

#endif
