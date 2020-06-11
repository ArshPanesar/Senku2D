#include "Matrix3.h"

Senku2D::Matrix3::Matrix3()
{
	for (unsigned int i = 0; i < 9; ++i)
	{
		Data[i] = 0;
	}
}

Senku2D::Matrix3::Matrix3(const Matrix3& Other)
{
	for (unsigned int i = 0; i < 9; ++i)
	{
		Data[i] = Other.Data[i];
	}
}

Senku2D::Matrix3 Senku2D::Matrix3::operator*(const Matrix3& Mat3)
{
	Matrix3 Mat;

	//First Row
	Mat.Data[0] = Data[0] * Mat3.Data[0] + Data[1] * Mat3.Data[3] + Data[2] * Mat3.Data[6];
	Mat.Data[1] = Data[0] * Mat3.Data[1] + Data[1] * Mat3.Data[4] + Data[2] * Mat3.Data[7];
	Mat.Data[2] = Data[0] * Mat3.Data[2] + Data[1] * Mat3.Data[5] + Data[2] * Mat3.Data[8];
	//Second Row
	Mat.Data[3] = Data[3] * Mat3.Data[0] + Data[4] * Mat3.Data[3] + Data[5] * Mat3.Data[6];
	Mat.Data[4] = Data[3] * Mat3.Data[1] + Data[4] * Mat3.Data[4] + Data[5] * Mat3.Data[7];
	Mat.Data[5] = Data[3] * Mat3.Data[2] + Data[4] * Mat3.Data[5] + Data[5] * Mat3.Data[8];
	//Third Row
	Mat.Data[6] = Data[6] * Mat3.Data[0] + Data[7] * Mat3.Data[3] + Data[8] * Mat3.Data[6];
	Mat.Data[7] = Data[6] * Mat3.Data[1] + Data[7] * Mat3.Data[4] + Data[8] * Mat3.Data[7];
	Mat.Data[8] = Data[6] * Mat3.Data[2] + Data[7] * Mat3.Data[5] + Data[8] * Mat3.Data[8];

	return Mat;
}

void Senku2D::Matrix3::operator=(const Matrix3& Mat3)
{
	for (unsigned int i = 0; i < 9; ++i)
	{
		Data[i] = Mat3.Data[i];
	}
}
