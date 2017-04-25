#ifndef GEOMETRY_H_
#define GEOMETRY_H_

typedef struct Point {
	float x;
	float y;
} Point;

typedef struct Vector {
	float x;
	float y;
} Vector;

typedef struct Color3D {
	float red;
	float green;
	float blue;
} Color3D;

Point PointXY(float x, float y);

Vector VectorXY(Point A, Point B);

float Distance(Vector V);

Color3D ColorXY(float red, float green, float blue);

Point PointPlusVector(Point A, Vector B);

Vector AddVector(Vector A, Vector B);

Vector SubVector(Vector A, Vector B);

Vector MultVector(Vector A, float scalaire);

#endif