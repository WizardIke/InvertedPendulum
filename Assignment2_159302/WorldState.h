#ifndef __WORLDSTATE_H__
#define __WORLDSTATE_H__

#include "transform.h"
#include "graphics.h"

extern float WORLD_MAXX, WORLD_MAXY;
extern int fieldX1, fieldY1, fieldX2, fieldY2; //playing field boundaries
extern BoundaryType worldBoundary, deviceBoundary;

struct WorldStateType {

	void init() {
		x = 0.0f;
		x_dot = 0.0f;
		x_double_dot = 0.0f;
		angle = 0.0f;
		angle_dot = 0.0f;
		angle_double_dot = 0.0f;
		F = 0.0f;
	}

	float x;
	float x_dot;
	float x_double_dot;
	float angle;
	float angle_dot;
	float angle_double_dot;

	float const mb = 0.1f;
	float const g = 9.8f;
	float const m = 1.1f; // mass of cart & broom
	float const l = 0.5f;

	float F;
};

void initPendulumWorld();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BEGIN - DYNAMICS OF THE SYSTEM
float calc_angular_acceleration(const WorldStateType& s);

float calc_horizontal_acceleration(const WorldStateType& s);
// END - DYNAMICS OF THE SYSTEM
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif