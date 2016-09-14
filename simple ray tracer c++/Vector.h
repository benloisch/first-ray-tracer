#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
using namespace std;

class Vect
{
private:
	float x;
	float y;
	float z;

public:

	Vect()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vect(float setX, float setY, float setZ): x(setX), y(setY), z(setZ)
	{
	
	}

	void setX(float sX)
	{
		x = sX;
	}

	void setY(float sY)
	{
		y = sY;
	}

	void setZ(float sZ)
	{
		z = sZ;
	}

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	float getZ()
	{
		return z;
	}

	void normalize()
	{
		float xUnChanged = x;
		float yUnChanged = y;
		float zUnChanged = z;
		x = xUnChanged /sqrtf((xUnChanged  * xUnChanged ) + (yUnChanged  * yUnChanged ) + (zUnChanged  * zUnChanged ));
		y = yUnChanged /sqrtf((xUnChanged  * xUnChanged ) + (yUnChanged  * yUnChanged ) + (zUnChanged  * zUnChanged ));
		z = zUnChanged /sqrtf((xUnChanged  * xUnChanged ) + (yUnChanged  * yUnChanged ) + (zUnChanged  * zUnChanged ));
	}

	void displayVectorToConsole()
	{
		cout << x << " " << y << " " << z << endl;
	}
};

#endif