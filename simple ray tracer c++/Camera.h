#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include <iostream>
using namespace std;

class Camera
{
private:
	float CameraMatrix[4][4];
	Vect lookAt;
	Vect lookAtVec;
	float camX;
	float camY;
	float camZ;

public:
	
	Camera()
	{
		camX = 0;
		camY = 0;
		camZ = 0;
		lookAt.setX(0);
		lookAt.setY(0);
		lookAt.setZ(0);
	}

	Camera(float cX, float cY, float cZ, float lookatX, float lookatY, float lookatZ): camX(cX), camY(cY), camZ(cZ)
	{
		lookAt.setX(lookatX);
		lookAt.setY(lookatY);
		lookAt.setZ(lookatZ);
	}

	void CreateCamMatrix()
	{
		Vect right;
		Vect up;
		Vect forward;
		//Cross Product is
		//Cx = AyBz - AzBy
		//Cy = AzBx - AxBz
		//Cz = AxBy - AyBx

		//First find camera positive z axis of cam by (lookAt.xyz - camOrigin)
		lookAtVec.setX(lookAt.getX() - camX);
		lookAtVec.setY(lookAt.getY() - camY);
		lookAtVec.setZ(lookAt.getZ() - camZ);
		
		//Calculate the right vector (x axis) by taking cross product of world 'up'(0, 1, 0) and lookat vector
		right.setX((1 * lookAtVec.getZ()) - (0 * lookAtVec.getY()));
		right.setY((0 * lookAtVec.getX()) - (0 * lookAtVec.getZ()));
		right.setZ((0 * lookAtVec.getY()) - (1 * lookAtVec.getX()));

		//Calculate camera up vector (y axis) by taking the cross product of lookat vector and right(just above) vector

		up.setX((lookAtVec.getY() * right.getZ()) - (lookAtVec.getZ() * right.getY()));
		up.setY((lookAtVec.getZ() * right.getX()) - (lookAtVec.getX() * right.getZ()));
		up.setZ((lookAtVec.getX() * right.getY()) - (lookAtVec.getY() * right.getX()));

		//Last, calculate forward vector (positive z axis) which is just the lookat vector

		forward.setX(lookAtVec.getX());
		forward.setY(lookAtVec.getY());
		forward.setZ(lookAtVec.getZ());

		//Now, to make the camera transformation matrix, everything must be normalized

		right.normalize();
		up.normalize();
		forward.normalize();

		//Now, setup the camera matrix
		//right, up, and forward represent the camera's x, y, and z axis
		//the translation of the camera is the camera's origin in world space

		CameraMatrix[0][0] = right.getX();
		CameraMatrix[0][1] = right.getY();
		CameraMatrix[0][2] = right.getZ();
		CameraMatrix[0][3] = 0;

		CameraMatrix[1][0] = up.getX();
		CameraMatrix[1][1] = up.getY();
		CameraMatrix[1][2] = up.getZ();
		CameraMatrix[1][3] = 0;

		CameraMatrix[2][0] = forward.getX();
		CameraMatrix[2][1] = forward.getY();
		CameraMatrix[2][2] = forward.getZ();
		CameraMatrix[2][3] = 0;

		CameraMatrix[3][0] = camX;
		CameraMatrix[3][1] = camY;
		CameraMatrix[3][2] = camZ;
		CameraMatrix[3][3] = 1;	
	}

	void displayMatrixtoConsole()
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				cout << CameraMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	void multiplyVectorbyCamMatrix(Vect &vec)
	{
		float vecXunChanged = vec.getX();
		float vecYunChanged = vec.getY();
		float vecZunChanged = vec.getZ();

		vec.setX((vecXunChanged * CameraMatrix[0][0]) + (vecYunChanged  * CameraMatrix[1][0]) + (vecZunChanged * CameraMatrix[2][0]) + (1 * CameraMatrix[3][0]));
		vec.setY((vecXunChanged * CameraMatrix[0][1]) + (vecYunChanged  * CameraMatrix[1][1]) + (vecZunChanged * CameraMatrix[2][1]) + (1 * CameraMatrix[3][1]));
		vec.setZ((vecXunChanged * CameraMatrix[0][2]) + (vecYunChanged  * CameraMatrix[1][2]) + (vecZunChanged * CameraMatrix[2][2]) + (1 * CameraMatrix[3][2]));
	}

	float getxOrigin()
	{
		return camX;
	}

	float getyOrigin()
	{
		return camY;
	}

	float getzOrigin()
	{
		return camZ;
	}
};

#endif