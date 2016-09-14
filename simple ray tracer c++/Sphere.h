#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include <iostream>
#include "Ray.h"
#include "Light.h"
using namespace std;

class Sphere
{
private:
	float xOrigin;
	float yOrigin;
	float zOrigin;
	float xIntersection;
	float yIntersection;
	float zIntersection;
	float radius;
	float A;
	float B;
	float C;
	float t;
	float B4ACRoot;
	float sphereDistance;
	float normalX;
	float normalY;
	float normalZ;
	float sphereDiffuse;
	Vect planeLightray;
	bool testNormal;

public:

	Sphere()
	{
		xOrigin = 0;
		yOrigin = 0;
		zOrigin = 0;
		A = 0;
		B = 0;
		C = 0;
		t = 0;
		B4ACRoot = 0;
		radius = 0;
		sphereDistance = 0;
		xIntersection = 0;
		yIntersection = 0;
		zIntersection = 0;
		normalX = 0;
		normalY = 0;
		normalZ = 0;
		sphereDiffuse = 0;
		planeLightray.setX(0);
		planeLightray.setY(0);
		planeLightray.setZ(0);
		testNormal = false;
	}

	void setSphereOrigin(float x, float y, float z)
	{
		xOrigin = x;
		yOrigin = y;
		zOrigin = z;
	}

	float getXpnt()
	{
		return xOrigin;
	}

	float getYpnt()
	{
		return yOrigin;
	}

	float getZpnt()
	{
		return zOrigin;
	}

	void setRadius(float r)
	{
		radius = r;
	}

	float getRadius()
	{
		return radius;
	}

	float getB4ACRoot()
	{
		return B4ACRoot;
	}

	void findIfRaySphereIntersection(Ray ray)
	{
		A =	((ray.getXdir() * ray.getXdir()) + (ray.getYdir() * ray.getYdir()) + (ray.getZdir() * ray.getZdir()));
		B = ((2 * (ray.getXdir() * ray.getXOrigin())) - (2 * (ray.getXdir() * xOrigin)) + (2 * (ray.getYdir() * ray.getYOrigin())) - (2 * (ray.getYdir() * yOrigin)) + (2 * (ray.getZdir() * ray.getZOrigin())) - (2 * (ray.getZdir() * zOrigin)));
		C = ((ray.getXOrigin() * ray.getXOrigin()) - (2 * ray.getXOrigin() * xOrigin) + (xOrigin * xOrigin) + (ray.getYOrigin() * ray.getYOrigin()) - (2 * ray.getYOrigin() * yOrigin) + (yOrigin * yOrigin) + (ray.getZOrigin() * ray.getZOrigin()) - (2 * ray.getZOrigin() * zOrigin) + (zOrigin * zOrigin) - (radius * radius));
		B4ACRoot = (B * B) - (4 * A * C);
	}

	void findRaySphereIntersectionCoordinates(Ray ray)
	{
		t = ((-1 * B) - (sqrtf(((B * B) - (4 * A * C))))) / (2 * A);
		xIntersection = ray.getXOrigin() + (t * (ray.getXdir()));
		yIntersection = ray.getYOrigin() + (t * (ray.getYdir()));
		zIntersection = ray.getZOrigin() + (t * (ray.getZdir()));
	}

	void findRaySphereDistance(Ray ray)
	{
		sphereDistance = sqrtf(((xIntersection - ray.getXOrigin()) * (xIntersection - ray.getXOrigin())) + ((yIntersection - ray.getYOrigin()) * (yIntersection - ray.getYOrigin())) + ((zIntersection - ray.getZOrigin()) * (zIntersection - ray.getZOrigin())));
	}

	float getDistance()
	{
		return sphereDistance;
	}

	void calculateNormal()
	{
		normalX = (xIntersection - xOrigin) / radius;
		normalY = (yIntersection - yOrigin) / radius;
		normalZ = (zIntersection - zOrigin) / radius;
	}

	void calculateLightray(Light lightray)
	{
		planeLightray.setX(lightray.getXorigin() - xIntersection);
		planeLightray.setY(lightray.getYorigin() - yIntersection);
		planeLightray.setZ(lightray.getZorigin() - zIntersection);
		planeLightray.normalize();
	}

	void calculateDiffuseLight(Light lightray)
	{
		sphereDiffuse = (((planeLightray.getX() * normalX) + (planeLightray.getY() * normalY) + (planeLightray.getZ() * normalZ)) * lightray.getLightIntensity());
	}

	float getDiffuse()
	{
		return sphereDiffuse;
	}
};

#endif


