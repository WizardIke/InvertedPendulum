#include "WorldState.h"

float WORLD_MAXX, WORLD_MAXY;
int fieldX1, fieldY1, fieldX2, fieldY2; //playing field boundaries
BoundaryType worldBoundary, deviceBoundary;

void initPendulumWorld() {

	//widescreen
	fieldX1 = getmaxx() / 10;
	fieldX2 = getmaxx() - (getmaxx() / 10);
	fieldY1 = getmaxy() / 9;
	fieldY2 = getmaxy() - (getmaxy() / 9);


	worldBoundary.x1 = -2.4f;
	//worldBoundary.y1 = 1.2;
	worldBoundary.y1 = 3.0f;
	worldBoundary.x2 = 2.4f;
	worldBoundary.y2 = -0.4f;

	deviceBoundary.x1 = (float)fieldX1;
	deviceBoundary.y1 = (float)fieldY1;
	deviceBoundary.x2 = (float)fieldX2;
	deviceBoundary.y2 = (float)fieldY2;

	WORLD_MAXX = worldBoundary.x2 - worldBoundary.x1;
	WORLD_MAXY = worldBoundary.y2 - worldBoundary.y1;

}

float calc_angular_acceleration(const WorldStateType& s) {
	float a_double_dot = 0.0;
	float numerator = 0.0;
	float denominator = 0.0;

	numerator = (s.m * s.g * (float)sin(s.angle) - ((float)cos(s.angle) * (s.F + ((s.mb) * s.l * s.angle_dot * s.angle_dot * (float)sin(s.angle)))));
	denominator = (((4 / 3)*s.m * s.l) - (s.mb * s.l * (float)cos(s.angle) * (float)cos(s.angle)));
	if (numerator == 0.0 || denominator == 0.0) {
		a_double_dot = 0.0;
	}
	else {
		a_double_dot = numerator / denominator;
	}

	return a_double_dot;
}

float calc_horizontal_acceleration(const WorldStateType& s) {
	float x_double_dot = 0.0;
	float numerator = 0.0;


	numerator = (s.F + s.mb * s.l * (s.angle_dot * s.angle_dot)* (float)sin(s.angle) - s.angle_double_dot * (float)cos(s.angle));
	if (numerator == 0.0) {
		x_double_dot = 0.0;
	}
	else {
		x_double_dot = numerator / s.m;
	}
	return x_double_dot;
}