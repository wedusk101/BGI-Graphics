//assets.h
#pragma once

#ifndef ASSETS__H_
#define ASSETS__H_

#include "primitives.h"
#include "matrix.h"

namespace bgilib
{
	// we intend on defining an inheritance hierarchy for easier code organization, especially for collision detection functions
	typedef struct
	{
		Circle head;
		Rectangle neck;
		Rectangle torso;
		Rectangle rHand;
	   	Rectangle lHand;
		Rectangle rLeg;
		Rectangle lLeg;
	} Humanoid;
    
	
	
	typedef struct
	{
		Point center;
		Line uString;
		Line lString;
		int radius;
		int midy;
	} Bow;
    
    	typedef struct
    	{
       		Point locus;
       		int size;
    	} Arrow;
    
    	typedef struct
    	{
	   	Line vert;
	   	Line horiz;
    	} Target;
	
	typedef struct
	{
		Point tail;
		Point head;
		Point uHead;
		Point lHead;
	}BallArrow;
    
	
	Circle genBall();				//Function to generate coordinates for ball
	void genRods(Rectangle & , Rectangle &);	//Function to generate coordinates for the Rods
     	Humanoid genHumanoid(const Point &); 		//center of the circle constituting the head is passed as argument
     	Rectangle getRectangle(const int &, const int &, const int &, const int &);
	void updateRods(Rectangle &, Rectangle &);

	
     	void genFootball(const Circle &);
     	void genRods(const int &, const int &);
     	//void genGoalPost();
	void genGoalPost(Line &, Line &);
	void drawRods(Rectangle,Rectangle);
	void genFootball(Point &,int &);
	BallArrow genBallArrow(const Point&);			//Function to generate Arrow for ball initially
	void drawBallArrow(BallArrow&);				//Function to draw Arrow for ball
	

	Bow genInitBow();                           	//Function to generate coordinates for the Bow
     	void genBow(Bow &);
     	Arrow genArrow(const int &,Point &);    	//Function to generate coordinates for the Arrow
     	Target genTarget(const Point &);        	//Function to generate coordinates for the Target

	
     	void drawBow(Bow & , const int &);              //Function to draw the Bow - please pass by reference, const or otherwise - this is quite slow as it copies the object
     	void drawArrow(const int &, const Point &);            //Function to draw the Arrow - please pass by reference, const or otherwise - this is quite slow as it copies the object
     	void drawTarget(const Target &);              		//Function to draw the Target - please pass by reference, const or otherwise - this is quite slow as it copies the object
}

#endif
