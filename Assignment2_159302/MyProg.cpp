///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    ARTIFICIAL INTELLIGENCE 159302
//    INVERTED PENDULUM SIMULATION
// 
//	  Description: Inverted pendulum simulation with fuzzy logic engine and animation functions
//
//    Run Parameters: 
//
//    Keys for Operation: 
//
//	  History:  dates of revision
//              April 27, 2017
//              March 3, 2015
//
//    Start-up code by:  Dr. Napoleon Reyes, n.h.reyes@massey.ac.nz
//    					 Computer Science, INMS
//						 Massey University-Albany
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <deque>
#include <set>
#include <vector>


#include "sprites.h" 
#include "graphics.h"
#include "transform.h"
#include "fuzzylogic.h"
#include "WorldState.h"

using namespace std;


/// Global Variables ///////////////////////////////////////////////////////////////////////


bool DEBUG_MODE=false;
char keyPressed[5];


struct DataSetType{
   vector<float> x;
   vector<float> y;
   vector<vector<float> > z; 
};

DataSetType dataSet;

int NUM_OF_DATA_POINTS;

// Function Prototypes ////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
float getKey() {
   
	  float F=0.0;
	
     if(GetAsyncKeyState(VK_LEFT) < 0) {     
        //"LEFT ARROW";
		  F=-7.0;
	  }
	  
	  if(GetAsyncKeyState(VK_RIGHT) < 0) { 
        F=7.0;  
    
        //"RIGHT ARROW"
	  }
	  
	  return F;
}

////////////////////////////////////////////////////////////////////////////////

void drawInvertedPendulumWorld(){
	
	setcolor(WHITE);
	rectangle(xDev(worldBoundary,deviceBoundary,worldBoundary.x1),yDev(worldBoundary,deviceBoundary,worldBoundary.y1),
	          xDev(worldBoundary,deviceBoundary,worldBoundary.x2),yDev(worldBoundary,deviceBoundary,worldBoundary.y2));
   //~ setcolor(YELLOW);
	//~ rectangle(xDev(worldBoundary,deviceBoundary,worldBoundary.x1),yDev(worldBoundary,deviceBoundary,worldBoundary.y2+0.07),
	          //~ xDev(worldBoundary,deviceBoundary,worldBoundary.x2),yDev(worldBoundary,deviceBoundary,worldBoundary.y2));
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	
	setcolor(WHITE);
	outtextxy((int)((deviceBoundary.x1 + deviceBoundary.x2)/2.0f), (int)deviceBoundary.y1 - 3 * textheight("H"),"ARTIFICIAL INTELLIGENCE 159302");
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy((int)((deviceBoundary.x1 + deviceBoundary.x2)/2.0f), (int)deviceBoundary.y1 - 2 * textheight("H"),"INVERTED PENDULUM");
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy((int)((deviceBoundary.x1 + deviceBoundary.x2)/2.0f), (int)deviceBoundary.y1 - textheight("H"),"FUZZY LOGIC CONTROLLER");
	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	outtextxy(((int)deviceBoundary.x2 - textwidth("START-UP CODE by:  n.h.reyes@massey.ac.nz")), (int)deviceBoundary.y2 + textheight("H"),"START-UP CODE by:  n.h.reyes@massey.ac.nz  (C) Massey University 2015");
}

void displayInfo(const WorldStateType& s){
	setcolor(WHITE);
	outtextxy((int)((deviceBoundary.x1 + deviceBoundary.x2)/2.0f), (int)deviceBoundary.y1 - 2 * textheight("H"),"INVERTED PENDULUM");
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy((int)((deviceBoundary.x1 + deviceBoundary.x2)/2.0f), (int)deviceBoundary.y1 - textheight("H"),"FUZZY LOGIC CONTROLLER");
	settextstyle(SMALL_FONT, HORIZ_DIR, 6);
	
	char angleStr[120];
	char xStr[120];
	
	float a=((s.angle*180.0f/3.14f));
	
	if(a > 360.0f){
		a = a / 360.0f;
	}
	
	sprintf(xStr,"x = %4.2f",s.x);
	outtextxy(((int)deviceBoundary.x2 - textwidth("n.h.reyes@massey.ac.nz")), (int)deviceBoundary.y2 - (7*textheight("H")),xStr);
	
	sprintf(angleStr,"angle = %4.2f",a);
	outtextxy(((int)deviceBoundary.x2 - textwidth("n.h.reyes@massey.ac.nz")), (int)deviceBoundary.y2 - (6*textheight("H")),angleStr);
	
	sprintf(angleStr,"F = %4.2f",s.F);
	outtextxy(((int)deviceBoundary.x2 - textwidth("n.h.reyes@massey.ac.nz")), (int)deviceBoundary.y2 - (5*textheight("H")),angleStr);

}


void runInvertedPendulum(FuzzySystem& fuzzySystem){
	
	float inputs[4];
	
	WorldStateType prevState, newState;
	// srand(time(NULL));  // Seed the random number generator
			
    initPendulumWorld();
	
	static bool page;
	
	float const h=0.002f;
	float externalForce=0.0f;
	
	prevState.init();
	newState.init();
	
	//-------------------------------------------------
	//Start at the origin
	//Cart cart(0.0, worldBoundary.y2 + 0.06);
	//Rod rod(0.0, worldBoundary.y2 + 0.06);
	//-------------------------------------------------
	
	//Start somewhere on the left
	//Cart cart(-1.0, worldBoundary.y2 + 0.06);
	Cart cart(-1.0f, worldBoundary.y2 + 0.125f);
	//Rod rod(-1.0, worldBoundary.y2 + 0.06);
	Rod rod(-1.0f, worldBoundary.y2 + 0.125f + 0.35f);
	
	//---------------------------------------------------------------
    //***************************************************************
    //Set the initial angle of the pole with respect to the vertical
	prevState.angle = 45.0f * (3.14f/180.0f);  //initial angle  = 8 degrees	
	prevState.x = 0.0f;
	
	//~ display_All_MF (g_fuzzy_system);
    //~ getch();
		
	while((GetAsyncKeyState(VK_ESCAPE)) == 0 ) 
	{
		
         setactivepage(page);
         cleardevice();
		 drawInvertedPendulumWorld();
	
	     //retrieve inputs
		 inputs[in_theta] = prevState.angle;
		 inputs[in_theta_dot] = prevState.angle_dot;
		 inputs[in_x] = prevState.x;
		 inputs[in_x_dot] = prevState.x_dot;
		
		prevState.F = fuzzySystem.calculateOutput(inputs); //call the fuzzy controller
		 
		 externalForce=0.0f;
		 externalForce = getKey(); //manual operation
		 
		 if(externalForce != 0.0f)
		 	prevState.F = externalForce;
         
         if(DEBUG_MODE){
           cout << "F = " << prevState.F << endl; //for debugging purposes only
         }
		
		 //---------------------------------------------------------------------------
		 // **************************************************************************
		 // BEGIN - DYNAMICS OF THE SYSTEM

		 //Calculate the new state of the world
		 newState.angle_double_dot = calc_angular_acceleration(prevState);
		 newState.angle_dot = prevState.angle_dot + (h * newState.angle_double_dot); 
		 newState.angle = prevState.angle + (h * newState.angle_dot);
		 if (newState.angle > 3.14159265359f)
		 {
			 newState.angle -= 2 * 3.14159265359f;
		 }
		 else if(newState.angle < -3.14159265359f)
		 {
			 newState.angle += 2 * 3.14159265359f;
		 }
		 newState.F = prevState.F;				 
		 newState.x_double_dot = calc_horizontal_acceleration(prevState); 
		 newState.x_dot = prevState.x_dot + (h * newState.x_double_dot);
         newState.x = prevState.x + (h * newState.x_dot);
		 
		 if(DEBUG_MODE){
	         cout << "prevState.angle = " << prevState.angle << endl;
			 cout << "prevState.angle_dot = " << prevState.angle_dot << endl;
			 cout << "prevState.angle_double_dot = " << prevState.angle_double_dot << endl;
			 cout << "prevState.x = " << prevState.x << endl;
			 cout << "prevState.x_dot = " << prevState.x_dot << endl;
			 cout << "prevState.x_double_dot = " << prevState.x_double_dot << endl;
		 }
		 
		 
		 prevState.x = newState.x;		
 		 prevState.angle = newState.angle;
		 prevState.x_dot = newState.x_dot;
		 prevState.angle_dot = newState.angle_dot;		
		 prevState.angle_double_dot = newState.angle_double_dot;
		 prevState.x_double_dot = newState.x_double_dot;
		 //--------------------------	 		 
		 cart.setX(newState.x);
		 rod.setX(newState.x);
		 rod.setAngle(newState.angle);		 
		 cart.draw();
		 rod.draw();
		 // END - DYNAMICS OF THE SYSTEM
		 // **************************************************************************
		 //---------------------------------------------------------------------------
		 displayInfo(newState);
		 
	     setvisualpage(page);
         page = !page;  //switch to another page
         if(mousedown()){
         	//do nothing
         }
   }
}


void generateControlSurface_Angle_vs_Angle_Dot(FuzzySystem& fuzzySystem)
{	
	float inputs[4];
	
	cout << "Generating control surface (Angle vs. Angle_Dot)..." << endl;
	WorldStateType prevState, newState;
	srand((unsigned int)time(NULL));  // Seed the random number generator
			
    initPendulumWorld();
	
	static bool page;
	
	float const h=0.002f;
	
	prevState.init();
	newState.init();
	

	//-------------------------------------------------

	//~ Cart cart(-1.0, worldBoundary.y2 + 0.125);
	//~ Rod rod(-1.0, worldBoundary.y2 + 0.125 + 0.35);
	//-------------------------------------------------
	
	
    float angle_increment;
    float angle_dot_increment;

    float minAngle=0;
    float maxAngle=0;
    float angle=0.0;

    float angle_dot=0.0;
    float minAngleDot=0;
    float maxAngleDot=0;

    NUM_OF_DATA_POINTS=100;

//---------------------------------
    dataSet.x.resize(NUM_OF_DATA_POINTS);
    dataSet.y.resize(NUM_OF_DATA_POINTS);
    dataSet.z.resize(NUM_OF_DATA_POINTS);

    for(int y=0; y < NUM_OF_DATA_POINTS; y++){
       dataSet.z[y].resize(NUM_OF_DATA_POINTS);	
    }
//---------------------------------    
    minAngleDot= -0.3f;
    maxAngleDot=  0.3f;
    angle_dot_increment=(maxAngleDot-minAngleDot)/float(NUM_OF_DATA_POINTS);
    angle_dot=minAngleDot;
//---------------------------------
    minAngle=(-12.0f)*3.14f/180.0f;
    maxAngle=(12.0f)*3.14f/180.0f;
    angle_increment=(maxAngle-minAngle)/float(NUM_OF_DATA_POINTS);   

//---------------------------------
    for(int row=0; row < NUM_OF_DATA_POINTS; row++){
    	 dataSet.y[row] = angle_dot;
         prevState.angle_dot = angle_dot;
         angle=minAngle;

         for(int col=0; col < NUM_OF_DATA_POINTS; col++){
             prevState.x=0.0;
		     prevState.x_dot=0.0;
		     prevState.x_double_dot = 0.0;
		     prevState.angle = angle;
		     prevState.angle_dot = angle_dot;
		     prevState.angle_double_dot = 0.0;
		     prevState.F = 0.0; 


             dataSet.x[col] = angle;
	         prevState.angle = angle;


			 inputs[in_theta] = prevState.angle;
			 inputs[in_theta_dot] = prevState.angle_dot;
			 inputs[in_x] = prevState.x;
			 inputs[in_x_dot] = prevState.x_dot;
			
	         prevState.F = 0.0;  //nothing is done.//fuzzy_system(inputs, g_fuzzy_system);
			
			
			 //---------------------------------------------------------------------------
			 //Calculate the new state of the world
			 //Updating angle
			 
			 newState.angle_double_dot = calc_angular_acceleration(prevState);
			 newState.angle_dot = prevState.angle_dot + (h * newState.angle_double_dot); 
			 newState.angle = prevState.angle + (h * newState.angle_dot);
			 newState.F = prevState.F;
			
			 //Updating x
					 
			 newState.x_double_dot = calc_horizontal_acceleration(prevState); 
			 newState.x_dot = prevState.x_dot + (h * newState.x_double_dot);
	         newState.x = prevState.x + (h * newState.x_dot);

	//Update previous state
			 prevState.x = newState.x;		
	 		 prevState.angle = newState.angle;
			 prevState.x_dot = newState.x_dot;
			 prevState.angle_dot = newState.angle_dot;		
			 prevState.angle_double_dot = newState.angle_double_dot;
			 prevState.x_double_dot = newState.x_double_dot;
			 
			 //--------------------------
			 inputs[in_theta] = prevState.angle;
			 inputs[in_theta_dot] = prevState.angle_dot;
			 inputs[in_x] = prevState.x;
			 inputs[in_x_dot] = prevState.x_dot;
			
			prevState.F = fuzzySystem.calculateOutput(inputs);
			dataSet.z[row][col] = prevState.F; //record Force calculated
			 
	//Set next case to examine; increment data points		 
          angle = angle + angle_increment;    
      }
      angle_dot = angle_dot + angle_dot_increment;		 
   }	
   
   cout << "done collecting data." << endl;
}




void saveDataToFile(string fileName){
	cout << "Saving control surface to file: " << fileName << "..." << endl;
	ofstream myfile;
	myfile.open (fileName, std::ofstream::out | std::ofstream::app);
	
	//Column Header
	for(int col=0; col < NUM_OF_DATA_POINTS; col++){
		if(col == 0){
		    myfile << "0.00, " << dataSet.x[col] << ",";
		} else if (col < (NUM_OF_DATA_POINTS-2)) {
			myfile << dataSet.x[col] << ",";
		} else {
			myfile << dataSet.x[col] << ",";
		}
	}
	myfile << endl;
	for(int row=0; row < NUM_OF_DATA_POINTS; row++){
	  for(int col=0; col < NUM_OF_DATA_POINTS; col++){
		  if(col == 0){			  
			  myfile << dataSet.y[row] << ", " << dataSet.z[row][col] << ","; //with Row header
		  }else if(col < (NUM_OF_DATA_POINTS-2)) {			  
           myfile << dataSet.z[row][col] << ",";
		  } else {
			  myfile << dataSet.z[row][col] << ",";
		  }
     }
	  myfile << endl;
   }
 
   myfile.close();
   cout << "Data set saved (File: " << fileName << ")" << endl;
	
}

void clearDataSet(){
	
	//Column Header
   for(int col=0; col < NUM_OF_DATA_POINTS; col++){
		dataSet.x[col] = 0.0;		    
   }
	
   for(int row=0; row < NUM_OF_DATA_POINTS; row++){
   	  dataSet.y[row] = 0.0;	
	  for(int col=0; col < NUM_OF_DATA_POINTS; col++){		  
		  dataSet.z[row][col] = 0.0;		  
     }	
   }   
   cout << "DataSet cleared." << endl;
	
}


////////////////////////////////////////////////////////////////////////////////////

int main(void) {
	
   int graphDriver = 0,graphMode = 0;
   
   initgraph(&graphDriver, &graphMode, "", 1280, 1024); // Start Window
   FuzzySystem fuzzySystem;
   try{
		runInvertedPendulum(fuzzySystem);
	
		clearDataSet();
		generateControlSurface_Angle_vs_Angle_Dot(fuzzySystem);
		saveDataToFile("data_angle_vs_angle_dot.txt");
		
   }
   catch(...){
    	cout << "Exception caught!\n";
   }
	return 0;
} 

