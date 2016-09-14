#ifndef Plane_H
#define Plane_H

#include "Ray.h"
#include "Vector.h"
#include "Light.h"
#include "Sphere.h"
#include <math.h>
#include <iostream>
using namespace std;

class Plane
{
private:
	float pntxIntersection;//intersection point
	float pntyIntersection;
	float pntzIntersection;

	float pointOnPlanex;
	float pointOnPlaney;
	float pointOnPlanez;

	float PlanexNormal;
	float PlaneyNormal;
	float PlanezNormal;

	float planeDistance;

	float t;

	float planeDiffuse;

	Vect planeLightray;

	float A;
	float B;
	float C;
	float B4ACRoot;

public:

	Plane()
	{
		pntxIntersection = 0;
		pntyIntersection = 0;
		pntzIntersection = 0;

		PlanexNormal = 0;
		PlaneyNormal = 0;
		PlanezNormal = 0;

		pointOnPlanex = 0;
		pointOnPlaney = 0;
		pointOnPlanez = 0;

		planeDistance = 0;

		planeLightray.setX(0);
		planeLightray.setY(0);
		planeLightray.setZ(0);

		planeDiffuse = 0;

		t = 0;

		A = 0;
		B = 0;
		C = 0;
		B4ACRoot = 0;
	}

	float getXIntersectionpnt()
	{
		return pntxIntersection;
	}

	float getYIntersectionpnt()
	{
		return pntyIntersection;
	}

	float getZIntersectionpnt()
	{
		return pntzIntersection;
	}

	void setPlaneNormal(float x, float y, float z)
	{
		PlanexNormal = x;
		PlaneyNormal = y;
		PlanezNormal = z;
	}

	void setPointOnPlane(float x, float y, float z)
	{
		pointOnPlanex = x;
		pointOnPlaney = y;
		pointOnPlanez = z;
	}

	float getXNormal()
	{
		return PlanexNormal;
	}

	float getYNormal()
	{
		return PlaneyNormal;
	}

	float getZNormal()
	{
		return PlanezNormal;
	}

	float getplaneT()
	{
		return t;
	}

	void findRayPlaneIntersection(Ray ray)
	{
		t = ((PlanexNormal * (pointOnPlanex - ray.getXOrigin())) + (PlaneyNormal * (pointOnPlaney - ray.getYOrigin())) + (PlanezNormal * (pointOnPlanez - ray.getZOrigin()))) / ((PlanexNormal * ray.getXdir()) + (PlaneyNormal * ray.getYdir()) + (PlanezNormal * ray.getZdir()));
	}

	void findRayPlaneIntersectionCoordinates(Ray ray)
	{
		pntxIntersection = ray.getXOrigin() + (t * (ray.getXdir()));
		pntyIntersection = ray.getYOrigin() + (t * (ray.getYdir()));
		pntzIntersection = ray.getZOrigin() + (t * (ray.getZdir()));
	}

	void findRayPlaneDistance(Ray ray)
	{
		planeDistance = sqrtf((((pntxIntersection - ray.getXOrigin()) * (pntxIntersection - ray.getXOrigin())) + ((pntyIntersection - ray.getYOrigin()) * (pntyIntersection - ray.getYOrigin())) + ((pntzIntersection - ray.getZOrigin()) * (pntzIntersection - ray.getZOrigin()))));
	}

	float getDistance()
	{
		return planeDistance;
	}

	void calculateLightRay(Light lightray)
	{
		planeLightray.setX(lightray.getXorigin() - pntxIntersection);
		planeLightray.setY(lightray.getYorigin() - pntyIntersection);
		planeLightray.setZ(lightray.getZorigin() - pntzIntersection);
		planeLightray.normalize();
	}

	void calculatediffuseLighting(Light lightray)
	{
		planeDiffuse = (((planeLightray.getX() * PlanexNormal) + (planeLightray.getY() * PlaneyNormal) + (planeLightray.getZ() * PlanezNormal)) * lightray.getLightIntensity());
	}

	float getPlaneDiffuse()
	{
		return planeDiffuse;
	}

	void calculateShadowRay(Sphere sphere)
	{
		//A =	((ray.getXdir() * ray.getXdir()) + (ray.getYdir() * ray.getYdir()) + (ray.getZdir() * ray.getZdir()));
		//B = ((2 * (ray.getXdir() * ray.getXOrigin())) - (2 * (ray.getXdir() * xOrigin)) + (2 * (ray.getYdir() * ray.getYOrigin())) - (2 * (ray.getYdir() * yOrigin)) + (2 * (ray.getZdir() * ray.getZOrigin())) - (2 * (ray.getZdir() * zOrigin)));
		//C = ((ray.getXOrigin() * ray.getXOrigin()) - (2 * ray.getXOrigin() * xOrigin) + (xOrigin * xOrigin) + (ray.getYOrigin() * ray.getYOrigin()) - (2 * ray.getYOrigin() * yOrigin) + (yOrigin * yOrigin) + (ray.getZOrigin() * ray.getZOrigin()) - (2 * ray.getZOrigin() * zOrigin) + (zOrigin * zOrigin) - (radius * radius));
		//B4ACRoot = (B * B) - (4 * A * C);

		A = ((planeLightray.getX() * planeLightray.getX()) + (planeLightray.getY() * planeLightray.getY()) + (planeLightray.getZ() * planeLightray.getZ()));
		B = ((2 * (planeLightray.getX() * pntxIntersection)) - (2 * planeLightray.getX() * sphere.getXpnt()) + (2 * planeLightray.getY() * pntyIntersection) - (2 * planeLightray.getY() * sphere.getYpnt()) + (2 * planeLightray.getZ() * pntzIntersection) - (2 * planeLightray.getZ() * sphere.getZpnt()));
		C = ((pntxIntersection * pntxIntersection) - (2 * pntxIntersection * sphere.getXpnt()) + (sphere.getXpnt() * sphere.getXpnt()) + (pntyIntersection * pntyIntersection) - (2 * pntyIntersection * sphere.getYpnt()) + (sphere.getYpnt() * sphere.getYpnt()) + (pntzIntersection * pntzIntersection) - (2 * pntzIntersection * sphere.getZpnt()) + (sphere.getZpnt() * sphere.getZpnt()) - (sphere.getRadius() * sphere.getRadius()));
		B4ACRoot = (B * B) - (4 * A * C);
	}

	float getB4ACRoot()
	{
		return B4ACRoot;
	}

};

#endif