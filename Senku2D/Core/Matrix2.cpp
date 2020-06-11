#include "Matrix2.h"

Senku2D::Matrix2::Matrix2()
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		Data[i] = 0;
	}
}

Senku2D::Matrix2::Matrix2(const Matrix2& Other)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		Data[i] = Other.Data[i];
	}
}

void Senku2D::Matrix2::operator=(const Matrix2& Mat2)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		Data[i] = Mat2.Data[i];
	}
}

Senku2D::Vector2 Senku2D::Matrix2::operator*(const Vector2& Vec) const
{
	return Vector2(Data[0] * Vec.x + Data[1] * Vec.y, Data[2] * Vec.x + Data[3] * Vec.y);
}

Senku2D::Matrix2 Senku2D::Matrix2::operator*(const Matrix2& Mat2) const
{
	Matrix2 Mat;

	Mat.Data[0] = Data[0] * Mat2.Data[0] + Data[1] * Mat2.Data[2];
	Mat.Data[1] = Data[0] * Mat2.Data[1] + Data[1] * Mat2.Data[3];
	Mat.Data[2] = Data[2] * Mat2.Data[0] + Data[3] * Mat2.Data[2];
	Mat.Data[3] = Data[2] * Mat2.Data[1] + Data[3] * Mat2.Data[3];

	return Mat;
}
