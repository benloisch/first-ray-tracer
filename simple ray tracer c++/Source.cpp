#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Vector.h"
#include "Camera.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
using namespace std;
//1920 x 1080 is considered 'full' HD

const int width = 1366;
const int height = 768;

double aWidth = width;
double aHeight = height;

double aspectRatio = 0;
//angle in RADIANS
double angle = (3.14159265 / 2);//90 degree fov

double pixelxNormalized = 0;
double pixelyNormalized = 0;

double pixelCamerax = 0;
double pixelCameray = 0;

double tvalue = 0;

int testPrimeNumberx = 0;
int testPrimeNumberz = 0;

int pixelr[width][height] = {0};
int pixelg[width][height] = {0};
int pixelb[width][height] = {0};

void saveFile(int pixelR[width][height], int pixelG[width][height], int pixelB[width][height])
{
	ofstream file;
	string swidth;
	string sheight;
	ostringstream convertwidth;
	ostringstream convertheight;

	convertwidth << width;
	convertheight << height;

	swidth = convertwidth.str();
	sheight = convertheight.str();

	file.open("imagefile.ppm");
	file << "P3\n" << swidth << " " << sheight << "\n 255\n";
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			file << pixelR[j][i] << " " << pixelG[j][i] << " " << pixelB[j][i] << " ";
		}
		file << "\n";
	}

	file.close();
}

int main() 
 {
	float ambient = 0.2;
	Camera cam(5, 5, -5, 5, 0, 10);
	cam.CreateCamMatrix();

	Vect findXY(0, 0, 1);

	Ray mainRay;

	Sphere mainWorldSphere;
	mainWorldSphere.setRadius(1);
	mainWorldSphere.setSphereOrigin(5, 3, -2);

	Plane mainWorldPlane;
	mainWorldPlane.setPlaneNormal(0, 1, 0);
	mainWorldPlane.setPointOnPlane(0, 0, 0);

	Light Light;
	Light.setLightIntensity(7);
	Light.setLightPosition(-3, 11, -2);

	mainRay.setOrigin(cam.getxOrigin(), cam.getyOrigin(), cam.getzOrigin());

	aspectRatio = aWidth / aHeight;
	
	int xwidth = 0;
	int yheight = 0;

	for(int i = 0; i < height; i++)
	{
		yheight++;
		for(int j = 0; j < width; j++)
		{
			xwidth++;
			
			pixelxNormalized = (xwidth + 0.5) / width;
			pixelyNormalized = (yheight + 0.5) / height;
			
			pixelCamerax = ((2 * pixelxNormalized) - 1) * aspectRatio * tanf(angle / 2);
			pixelCameray = (1 - (2 * pixelyNormalized)) * tanf(angle / 2);
		
			findXY.setX(pixelCamerax);
			findXY.setY(pixelCameray);
			findXY.setZ(1);
			cam.multiplyVectorbyCamMatrix(findXY);

			mainRay.setX(findXY.getX());
			mainRay.setY(findXY.getY());
			mainRay.setZ(findXY.getZ());

			mainRay.calculateRayDir();
			mainRay.normalize();
			//mainRay direction is now calculated
		
			mainWorldPlane.findRayPlaneIntersection(mainRay);
			mainWorldPlane.findRayPlaneIntersectionCoordinates(mainRay);
			mainWorldPlane.findRayPlaneDistance(mainRay);
			mainWorldPlane.calculateLightRay(Light);
			mainWorldPlane.calculatediffuseLighting(Light);
			mainWorldPlane.calculateShadowRay(mainWorldSphere);

			mainWorldSphere.findIfRaySphereIntersection(mainRay);
			mainWorldSphere.findRaySphereIntersectionCoordinates(mainRay);
			mainWorldSphere.findRaySphereDistance(mainRay);
			mainWorldSphere.calculateNormal();
			mainWorldSphere.calculateLightray(Light);
			mainWorldSphere.calculateDiffuseLight(Light);

			if(mainWorldPlane.getplaneT() >= 0)
			{
				pixelr[j][i] = 255;
				pixelg[j][i] = 255;
				pixelb[j][i] = 255;
				
				mainWorldPlane.getplaneT();
				testPrimeNumberz = mainWorldPlane.getZIntersectionpnt();
				testPrimeNumberx = mainWorldPlane.getXIntersectionpnt();

				if(testPrimeNumberz % 2 == 0 && testPrimeNumberx % 2 == 0)
				{
					pixelr[j][i] = 0;
					pixelg[j][i] = 0;
					pixelb[j][i] = 0;
				}
				
				if(testPrimeNumberz % 2 != 0 && testPrimeNumberx % 2 != 0)
				{
					pixelr[j][i] = 0;
					pixelg[j][i] = 0;
					pixelb[j][i] = 0;
				}	

				if(testPrimeNumberx == 0 || testPrimeNumberz == 0)
				{
					pixelr[j][i] = 255;
					pixelg[j][i] = 255;
					pixelb[j][i] = 255;
				}	

				pixelr[j][i] *= ambient;
				pixelg[j][i] *= ambient;
				pixelb[j][i] *= ambient;

				pixelr[j][i] *= mainWorldPlane.getPlaneDiffuse();
				pixelg[j][i] *= mainWorldPlane.getPlaneDiffuse();
				pixelb[j][i] *= mainWorldPlane.getPlaneDiffuse();

				if(mainWorldPlane.getB4ACRoot() >= 0)
				{
					pixelr[j][i] *= ambient;
					pixelg[j][i] *= ambient;
					pixelb[j][i] *= ambient;
				}
			}
			
			if(mainWorldPlane.getplaneT() < 0)
			{
				pixelr[j][i] = 50;
				pixelg[j][i] = 50;
				pixelb[j][i] = 50;
			}

			if(mainWorldSphere.getB4ACRoot() >= 0)
			{
				if(mainWorldPlane.getDistance() > mainWorldSphere.getDistance())
				{
					pixelr[j][i] = 255;
					pixelg[j][i] = 0;
					pixelb[j][i] = 0;

					pixelr[j][i] *= ambient;
					pixelg[j][i] *= ambient;
					pixelb[j][i] *= ambient;
					
					if(mainWorldSphere.getDiffuse() >= 0)
					{
						pixelr[j][i] = 255;
						pixelg[j][i] = 0;
						pixelb[j][i] = 0;
						
						if((pixelr[j][i] * mainWorldSphere.getDiffuse() * ambient) > (pixelr[j][i] * ambient))
						{
							pixelr[j][i] *= mainWorldSphere.getDiffuse() * ambient;
						}
						else
						{
							pixelr[j][i] *= ambient;
						}
						
						if((pixelg[j][i] * mainWorldSphere.getDiffuse() * ambient) > (pixelr[j][i] * ambient))
						{
							pixelg[j][i] *= mainWorldSphere.getDiffuse() * ambient;
						}
						else
						{
							pixelg[j][i] *= ambient;
						}

						if((pixelb[j][i] * mainWorldSphere.getDiffuse() * ambient) > (pixelb[j][i] * ambient))
						{
							pixelb[j][i] *= mainWorldSphere.getDiffuse() * ambient;
						}
						else
						{
							pixelb[j][i] *= ambient;
						}
					}
				}
			}

			if(pixelr[j][i] > 255)
				pixelr[j][i] = 255;

			if(pixelg[j][i] > 255)
				pixelg[j][i] = 255;

			if(pixelb[j][i] > 255)
				pixelb[j][i] = 255;

			if(pixelxNormalized > 1)
				xwidth = 0;
		}
	}
	saveFile(pixelr, pixelg, pixelb);
	
	system("PAUSE");
	 return 0;
 }

