/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIX_VECTOR3_H
#define VIX_VECTOR3_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_math.h>
#include <cassert>

namespace Vixen {

	class VIX_API Vector3
	{
	public:
		float x;
		float y;
		float z;
	public:

		inline Vector3()
			: x(0), y(0), z(0)
		{

		}

		inline Vector3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
		{

		}



		///*operators*/

		inline bool operator== (const Vector3& rhs)
		{
			return ( x == rhs.x &&
				     y == rhs.y &&
				     z == rhs.z );
		}

		inline bool operator!= (const Vector3& rhs)
		{
			return !(*this == rhs);
		}

        inline Vector3 add(const Vector3& rhs) const
        {
            return *this + rhs;
        }

		inline Vector3 operator + (const Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		inline Vector3 operator + (const float scalar) const
		{
			return Vector3(x + scalar, y + scalar, z + scalar);
		}

        inline Vector3 sub(const Vector3& rhs) const
        {
            return *this - rhs;
        }

		inline Vector3 operator - (const Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		inline Vector3 operator - (const float scalar) const
		{
			return Vector3(x - scalar, y - scalar, z - scalar);
		}

		inline Vector3 operator * (const Vector3& rhs) const
		{
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

        inline Vector3 mul(const float scalar) const
        {
            return *this * scalar;
        }

		inline Vector3 operator * (const float scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		inline Vector3 operator / (const Vector3& rhs) const
		{
			return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		inline Vector3 operator / (const float scalar) const
		{
			assert(scalar != 0.0f);

			float invScalar = 1.0f / scalar;
			return Vector3(x * invScalar, y * invScalar, z * invScalar);
		}

		inline Vector3& operator += (const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		inline Vector3& operator += (const float scalar)
		{
			x += scalar;
			y += scalar;
			z += scalar;

			return *this;
		}

		inline Vector3& operator -= (const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		inline Vector3& operator -= (const float scalar)
		{
			x -= scalar;
			y -= scalar;
			z -= scalar;

			return *this;
		}

		inline Vector3& operator *= (const Vector3& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		inline Vector3& operator *= (const float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		inline Vector3& operator /= (const Vector3& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;

			return *this;
		}

		inline Vector3& operator /= (const float scalar)
		{
			assert(scalar != 0.0f);

			float invScalar = 1.0f / scalar;
			x *= invScalar;
			y *= invScalar;
			z *= invScalar;

			return *this;
		}

		inline float Length()
		{
			return sqrt(x * x + y * y + z * z);
		}

		inline float LengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		inline float Distance(const Vector3& other) const
		{
			return (*this - other).Length();
		}

		inline float Dot(const Vector3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		inline float normalise()
		{
			float len = Length();

			if(len > 0.0f)
			{
				float lenInv = 1.0f / len;
				x *= lenInv;
				y *= lenInv;
				z *= lenInv;
			}

			return len;
		}

		inline Vector3 Normalize() const
		{
			Vector3 ret = *this;
			ret.normalise();
			return ret;
		}

		inline float Angle(const Vector3& other) const
		{
			Vector3 v1 = *this;
			Vector3 v2 = other;
			v1.normalise();
			v2.normalise();

			float angle = acos(v1.Dot(v2));

			return angle;
		}

		inline Vector3 Cross(const Vector3& other) const
		{
			float newX = y * other.z - other.y * z;
			float newY = -(x * other.z - other.x * z);
			float newZ =  x * other.y - other.x * y;
			return Vector3(newX, newY, newZ);
		}

		inline float X()
		{
			return x;
		}

		inline float Y()
		{
			return y;
		}

		inline float Z()
		{
			return z;
		}

		//constants
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Right;
		static const Vector3 Left;
		static const Vector3 Forward;
		static const Vector3 Backward;


		UString         ToString() const;
        std::string     ToStdString() const;

		inline VIX_API friend UOStream& operator <<
			(UOStream& o, const Vector3& v)
		{
			o << "Vector3 [ "
				<< v.ToString()
				<< " ]";
			return o;
		}

	};


	inline UString Vector3::ToString() const
	{
		USStream ss;
		ss <<  std::fixed
			<< std::setprecision(3)
			<< "X=" << x << " "
			<< "Y=" << y << " "
			<< "Z=" << z;

		return ss.str();
	}

    inline std::string Vector3::ToStdString() const
    {
        std::stringstream ss;
        ss << std::fixed
            << std::setprecision(3)
            << "X=" << x << " "
            << "Y=" << y << " "
            << "Z=" << z;

        return ss.str();
    }
}

#endif
