#include <iostream>
#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
#include "matrix.h"
#include "assets.h"

int main()
{

    	const double acceleration = 0.0, stepSize = 0.5; // arbitrary acceleration value - for g take 9.8
	double theta = 0.0;


	primitives :: Point locus, nextPoint,arrowHead,arrowTail;
	primitives :: Circle ball;
	primitives :: AABB ballBB, prevBB, upRodBB, downRodBB,prevupRodBB,prevdownRodBB;
	primitives :: Rectangle upRod,downRod;
	//std::cout << "Please enter the coordinates for the next point along the path of the ball (x,y)." << std::endl;
	//std::cin >> nextPoint.x >> nextPoint.y; // the closer this point is to the center of the ball, the lower the velocity and vice versa

	initwindow(1366, 750, "First Sample");
	setcolor(12); // Light Red

	int xMax = getmaxx(), yMax = getmaxy();
	while(1)
    	{
		ball = primitives::genBall();//BALL POSITIONING AND RADIUS
		arrowTail.x=ball.center.x;
		arrowTail.y=ball.center.y;
		arrowHead.x=arrowTail.x+70;
		arrowHead.y=arrowTail.y;		//ARROW POSITIONING
		
		primitives::genRods(upRod,downRod);

		ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius); // binds the axis aligned bounding box to the ball for the first time
		upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);
		downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);

    		prevupRodBB=upRodBB; prevdownRodBB=downRodBB;
		primitives :: genFootball(ball.center,ball.radius);
		primitives :: drawRods(upRod,downRod);
		primitives :: genGoalPost();
		//primitives :: drawArrowFootball(arrowHead,arrowTail);
		//primitives :: arrowMovement(arrowHead,arrowTail);
		//arrowHead.x=300;arrowHead.y=300;arrowTail.x=350;arrowTail.y=300;
		double deg=-0.78539;
    		double state=0.01;
	    	double radius=sqrt(pow((arrowHead.x-arrowTail.x),2)+pow((arrowHead.y-arrowTail.y),2));
                while(!ismouseclick(WM_LBUTTONDOWN))
                {
			delay(33);
			cleardevice();
                        if(deg<=-1.57079 || deg>=0)
				state*=-1;
			//double degree= deg*3.1415920/180;
			primitives :: genFootball(ball.center,ball.radius);
                        primitives :: drawRods(upRod,downRod);
                        primitives :: genGoalPost();
			setlinestyle(0,0,1);
			arrowHead.x=arrowTail.x+ static_cast<int>(radius*cos(deg));
			arrowHead.y=arrowTail.y+ static_cast<int>(radius*sin(deg));
			line(arrowHead.x,arrowHead.y,arrowTail.x,arrowTail.y);
			deg+=state;
			swapbuffers();
		}
		outtextxy(100,100,"Nikal Gya");
		clearmouseclick(WM_LBUTTONDOWN);
    		nextPoint=arrowHead;
    		//primitives :: drawArrowFootball(arrowHead,arrowTail);
		ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius); // binds the axis aligned bounding box to the ball for the first time
		upRodBB = updateAABB(upRod.center,upRod.width,upRod.height);
		downRodBB = updateAABB(downRod.center,downRod.width,downRod.height);
		while (!ismouseclick(WM_LBUTTONDOWN)) // check this
		{
			//line(l.src.x, l.src.y, l.dst.x, l.dst.y); for testing collisions
                        outtextxy(100,200,"Ghus Gya");
			cleardevice();
			locus = getNextPositionVerlet(ball.center, nextPoint, acceleration, stepSize, theta); // locus is the next position of the center of the ball along the direction of motion
			genFootball(locus, ball.radius); // primary draw call for the ball
			primitives :: drawRods(upRod,downRod);;
        		primitives :: genGoalPost();
			
			prevBB = ballBB; // backs up the ball's bounding box
			prevupRodBB=upRodBB; prevdownRodBB=downRodBB;

			ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius); // updates the axis aligned bounding box for the ball with every iteration
        		if (primitives :: collideCircleScreen(ball, ballBB, prevBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
				genFootball(locus, ball.radius);
				primitives :: drawRods(upRod,downRod);
            			primitives :: genGoalPost();
			}
			if (collideCircleRectangle(ball, upRod, ballBB, prevBB, upRodBB, prevupRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
		    		genFootball(locus, ball.radius);
				primitives :: drawRods(upRod,downRod);
            			primitives :: genGoalPost();
			}
			if (collideCircleRectangle(ball, downRod, ballBB, prevBB, downRodBB, prevdownRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
		    		genFootball(locus, ball.radius);
				primitives :: drawRods(upRod,downRod);
            			primitives :: genGoalPost();
			}
			swapbuffers();
		}
		clearmouseclick(WM_LBUTTONDOWN);
		swapbuffers();
	}

 	//   genGoalPost();
	std::cout << "X = " << xMax << " Y = " << yMax << std::endl; // for debugging


    	system("pause");
    	closegraph();
	return 0;
}
