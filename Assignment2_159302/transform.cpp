#include "transform.h"
 
using namespace std;

constexpr float M_PI = 3.14159265358979323846f;  //use M_PI from math.h instead

/////////////////////////////////////////////////////////////////////////////////
// World-to-Device Coordinates Transformation 

int xDev(const BoundaryType &WorldBound,const BoundaryType &DevBound,float xworld)
{
    float xslope,xint;
    
    // if((WorldBound.x2-WorldBound.x1) == 0.0)
      xslope = (DevBound.x2-DevBound.x1)/(WorldBound.x2-WorldBound.x1+.001f);
    // else
      // xslope = (DevBound.x2-DevBound.x1)/(WorldBound.x2-WorldBound.x1);
    xint = DevBound.x1-xslope*WorldBound.x1;

    return (int)ceil(xslope*xworld+xint);
}

int yDev(const BoundaryType &WorldBound,const BoundaryType &DevBound,float yworld)
{
    float yslope,yint;
    
    // if((WorldBound.y2-WorldBound.y1) == 0.0)
       yslope = (DevBound.y2-DevBound.y1)/(WorldBound.y2-WorldBound.y1+.001f);
    // else
       // yslope = (DevBound.y2-DevBound.y1)/(WorldBound.y2-WorldBound.y1);
    yint = DevBound.y1-yslope*WorldBound.y1;

    return (int)ceil(yslope*yworld+yint);
}


float degToRad(float deg) {
	return(deg * M_PI / 180.0f);
}


