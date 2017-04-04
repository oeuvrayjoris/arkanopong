#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"

Point PointXY(float x, float y) {
	Point myPoint;
	myPoint.x = x;
	myPoint.y = y;
	return myPoint;
}

Vector VectorXY(Point A, Point B) {
	Vector myVector;
	myVector.x = B.x - A.x;
	myVector.y = B.y - A.y;
	return myVector;
}

float Distance(Vector V) {
	return sqrt(pow(V.x,2)+pow(V.y,2));
}

Color3D ColorXY(float red, float green, float blue) {
	Color3D myColor;
	myColor.red = red;
	myColor.green = green;
	myColor.blue = blue;
	return myColor;
}

Point PointPlusVector(Point A, Vector B) {
	Point myPoint;
	myPoint.x = A.x + B.x;
	myPoint.y = A.y + B.y;
	return myPoint;
}

Vector AddVector(Vector A, Vector B) {
	Vector myVector;
	myVector.x = A.x + B.x;
	myVector.y = A.y + B.y;
	return myVector;
}

Vector SubVector(Vector A, Vector B) {
	Vector myVector;
	myVector.x = A.x - B.x;
	myVector.y = A.y - B.y;
	return myVector;
}

Vector MultVector(Vector A, float scalaire) {
	Vector myVector;
	myVector.x = A.x * scalaire;
	myVector.y = A.y * scalaire;
	return myVector;	
}