#ifndef RAY_H
#define RAY_H

#include <math.h>
#include "Vector.h"
#include "Plane.h"
#include <iostream>
using namespace std;

class Ray
{
private:
	float x;
	float y;
	float z;

	float xOrigin;
	float yOrigin;
	float zOrigin;

	float rayxDir;
	float rayyDir;
	float rayzDir;

public:

	Ray()
	{
		x = 0;//x, y, and z values used to calculate ray direction from camera image plane
		y = 0;
		z = 0;

		xOrigin = 0;
		yOrigin = 0;
		zOrigin = 0;

		rayxDir = 0;
		rayyDir = 0;
		rayzDir = 0;
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

	float getXOrigin()
	{
		return xOrigin;
	}

	float getYOrigin()
	{
		return yOrigin;
	}

	float getZOrigin()
	{
		return zOrigin;
	}

	float getXdir()
	{
		return rayxDir;
	}

	float getYdir()
	{
		return rayyDir;
	}

	float getZdir()
	{
		return rayzDir;
	}

	void setOrigin(float ox, float oy, float oz)
	{
		xOrigin = ox;
		yOrigin = oy;
		zOrigin = oz;
	}

	void calculateRayDir()
	{
		rayxDir = x - xOrigin;
		rayyDir = y - yOrigin;
		rayzDir = z - zOrigin;

	}

	void normalize()
	{
		float xUnChanged = rayxDir;
		float yUnChanged = rayyDir;
		float zUnChanged = rayzDir;
		rayxDir = xUnChanged /sqrtf((xUnChanged  * xUnChanged ) + (yUnChanged  * yUnChanged ) + (zUnChanged  * zUnChanged ));
		rayyDir = yUnChanged /sqrtf((xUnChanged  * xUnChanged ) + (yUnChanged  * yUnChanged ) + (zUnChanged  * zUnChanged ));
		rayzDir = zUnChanged /sqrtf((xUnChanged  * xUnChanged ) + (yUnChanged  * yUnChanged ) + (zUnChanged  * zUnChanged ));
	}
};

#endif