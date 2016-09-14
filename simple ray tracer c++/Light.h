#ifndef LIGHT_H
#define LIGHT_H

#include <math.h>
#include "Plane.h"
using namespace std;

class Light
{
private:
	int xOrigin;
	int yOrigin;
	int zOrigin;
	float lightIntensity;

public:
	Light()
	{
		xOrigin = 0;
		yOrigin = 0;
		zOrigin = 0;
		lightIntensity = 0;
	}

	void setLightPosition(int x, int y, int z)
	{
		xOrigin = x;
		yOrigin = y;
		zOrigin = z;
	}

	void setLightIntensity(float i)
	{
		lightIntensity = i;
	}

	int getXorigin()
	{
		return xOrigin;
	}

	int getYorigin()
	{
		return yOrigin;
	}

	int getZorigin()
	{
		return zOrigin;
	}

	float getLightIntensity()
	{
		return lightIntensity;
	}
};

#endif
