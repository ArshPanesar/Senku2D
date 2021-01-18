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

Senku2D::Matrix2 Senku2D::Matrix2::GetInverse(const Matrix2& Mat2)
{
	Matrix2 Mat;

	Real Det = GetDeterminant(Mat2);

	Real Temp0 = Mat.Data[0];
	Mat.Data[0] = Mat2.Data[3];
	Mat.Data[1] = -Mat2.Data[1];
	Mat.Data[2] = -Mat2.Data[2];
	Mat.Data[3] = Temp0;

	if (Det != 0)
	{
		Mat *= ((Real)1 / Det);
	}

	return Mat;
}

Senku2D::Matrix2 Senku2D::Matrix2::GetTranspose(const Matrix2& Mat2)
{
	Matrix2 Mat;

	Mat.Data[0] = Mat2.Data[0];
	Real Temp1 = Mat.Data[1];
	Mat.Data[1] = Mat2.Data[2];
	Mat.Data[2] = Temp1;
	Mat.Data[3] = Mat2.Data[3];

	return Mat;
}

void Senku2D::Matrix2::Invert()
{
	*this = GetInverse(*this);
}

void Senku2D::Matrix2::Transpose()
{
	*this = GetTranspose(*this);
}

Senku2D::Real Senku2D::Matrix2::GetDeterminant(const Matrix2& Mat2)
{
	return(Mat2.Data[0] * Mat2.Data[3] - Mat2.Data[1] * Mat2.Data[2]);
}

Senku2D::Real Senku2D::Matrix2::Determinant() const
{
	return(GetDeterminant(*this));
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

Senku2D::Matrix2 Senku2D::Matrix2::operator*(const Real& Num)
{
	Matrix2 Mat;

	Mat = *this;

	for (unsigned int i = 0; i < 4; ++i)
	{
		Mat.Data[i] *= Num;
	}

	return Mat;
}

void Senku2D::Matrix2::operator*=(const Real& Num)
{
	*this = *this * Num;
}
