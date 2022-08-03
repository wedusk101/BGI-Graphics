/**********************************************************************************************************************

The following code define functions used to generate different assets (football,rod,bow,arrow etc.) for the Football 
and the Archery game. The piece of code has following components and dependencies.

                                            **********************************************
For the Football Game:

genRectangle()  - Returns coordinates of Rectangle - This function is  used to generate the coordinates of Rectangle.

genBall() - Returns center and radius of Ball - This function is used to generate the coordinates of the circle 
which will be used to draw a Ball. The coordinates are generated with respect to the resolution of the window.

genRods() - Returns void - This function is used to generate the coordinates of the up and down Rods with respect
to the resolution of the window.

genFootball() - Returns void - This function is used to draw the Football on the screen.

drawRods() - Returns void - This function is used to draw the 2 Rods.

updateRods() - Returns void - This function is used to generated updated coordinates values of Rods.

genGoalPost() - Returns void - This function is used to generate the coordinates of the Goal Post and draw it on the
screen.

genBallArrow() - Returns the coordinate of Arrow on ball used to aim. - This function is used to generate the
initial coordinates of the Arrow on Ball which will be used for aiming.

drawBallArrow() - Returns void - This function is used to draw the Arrow on screen from the points generated
from "genBallArrow()".


                                            **********************************************

For the Archery Game:

genInitBow() - Return the initial coordinates of Bow - This function is used to generate the coordinates for 
the Bow at the start of game play.

genBow() - Returns void - This function is used to generate new coordinates of the Bow during the game play.

drawBow() - Returns void - This function is used to draw Bow on the screen.

genArrow() - Returns Arrow size and its point of origin - This function is used to generate Arrow’s 
size and its coordinate of origin.

drawArrow() - Returns void - This function is used to draw the Arrow on the screen.

genTarget() - Return the coordinate of the Target - This function is used to generate coordinates of Target.

drawTarget() - Return void - This function is used to draw Target on screen.


**********************************************************************************************************************/





#include "assets.h"
#include "graphics.h"
#include "matrix.h"
#include <cstdio>

namespace bgilib
{
	Rectangle getRectangle(const int &topLeftX, const int &topLeftY, const int &bottomRightX, const int &bottomRightY)
	{
		Rectangle rect;
		rect.tL.x = topLeftX;
		rect.tL.y = topLeftY;
		rect.bR.x = bottomRightX;
		rect.bR.y = bottomRightY;
		rect.center.x = (topLeftX + bottomRightX) / 2; // potential overflow bug
		rect.center.y = (topLeftY + bottomRightY) / 2;
		rect.width = bottomRightX - topLeftX;
		rect.height = bottomRightY - topLeftY;
		return rect;
	}

/**********************************************ASSETS FOR FOOTBALL PROJECT***************************************************/	
	Circle genBall()
	{
		Circle ball;
		int xMax, yMax;
		xMax = getmaxx();
		yMax = getmaxy();
		ball.center.x = xMax / 8;
		ball.center.y = (yMax - 40);
		ball.radius = 25;
		return ball;
	}
	void genRods(Rectangle &upRod , Rectangle &downRod)
	{
		int xMax, yMax;
		xMax = getmaxx();
		yMax = getmaxy();

		/*Coordinates for Up Rod*/
		upRod.tL.x = xMax/2;
		upRod.tL.y = 0;
		upRod.bR.y = yMax * 5/16;
		upRod.bR.x = upRod.tL.x + (xMax * 3 / 80);//UPPER ROD POSITIONING
		upRod.width = upRod.bR.x-upRod.tL.x;
		upRod.height = upRod.bR.y - upRod.tL.y;
		upRod.center = midPoint(upRod.bR, upRod.tL);

		/*Coordiantes for Down rod*/
		downRod.tL.x = upRod.tL.x;
		downRod.bR.x = upRod.bR.x;
		downRod.bR.y = yMax;
		downRod.tL.y = upRod.bR.y + 300;//LOWER ROD POSITIONING
		downRod.width = downRod.bR.x - downRod.tL.x;
		downRod.height = downRod.bR.y - downRod.tL.y;//WIDTH AND HEIGHT OF RODS
		downRod.center = midPoint(downRod.bR, downRod.tL);//MIDPOINT OF RODS
	}

	Humanoid genHumanoid(const Point &p)
	{
		//restraints to be included to make sure the object is within the window limits
		Humanoid h1;
		int x, y, r;

		//head
		h1.head.center.x = p.x;
		h1.head.center.y = p.y;
		h1.head.radius = 40;
		circle(h1.head.center.x, h1.head.center.y, h1.head.radius);

		x = h1.head.center.x;
		y = h1.head.center.y;
		r = h1.head.radius;

		//neck
		h1.neck.tL.x = x - (r / 3);
		h1.neck.tL.y = y + r - 4;
		h1.neck.bR.x = x + (r / 3);
		h1.neck.bR.y = y + r + 20 - 4;
		rectangle(h1.neck.tL.x, h1.neck.tL.y, h1.neck.bR.x, h1.neck.bR.y);

		//torso
		h1.torso.tL.x = x - r;
		h1.torso.tL.y = y + r + 20 - 4;
		h1.torso.bR.x = x + r;
		h1.torso.bR.y = y + r + 20 + (2 * r + 20) - 4;
		rectangle(h1.torso.tL.x, h1.torso.tL.y, h1.torso.bR.x, h1.torso.bR.y);

		//rHand;
		//lHand;
		//rLeg;
		//lLeg;

		return h1; // returning reference to the humanoid type object generated by the function
	}
	
	void genFootball(Point &center,int &radius)
    	{

    	Point poly1,poly2,poly3,poly4,poly5,poly6;
        setcolor(15); // Light Red
	circle(center.x, center.y,radius); //Circle drawn

	poly1.x=center.x-8;
	poly1.y=center.y-(radius-1);
	poly2.x=center.x-4;
	poly2.y=center.y-(radius-8);
	poly3.x=center.x+4;
	poly3.y=center.y-(radius-8);
	poly4.x=center.x+8;
	poly4.y=center.y-(radius-1);
	int polygon2[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon2);

	poly1.x=center.x+(radius-1);
	poly1.y=center.y-8;
	poly2.x=center.x+(radius-8);
	poly2.y=center.y-4;
	poly3.x=center.x+(radius-8);
	poly3.y=center.y+4;
	poly4.x=center.x+(radius-1);
	poly4.y=center.y+8;

	int polygon3[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon3);


    	poly1.x=center.x-(radius-1);
	poly1.y=center.y-8;
	poly2.x=center.x-(radius-8);
	poly2.y=center.y-4;
	poly3.x=center.x-(radius-8);
	poly3.y=center.y+4;
	poly4.x=center.x-(radius-1);
	poly4.y=center.y+8;

	int polygon4[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon4);

    	poly1.x=center.x-8;
	poly1.y=center.y+(radius-1);
	poly2.x=center.x-4;
	poly2.y=center.y+(radius-8);
	poly3.x=center.x+4;
	poly3.y=center.y+(radius-8);
	poly4.x=center.x+8;
	poly4.y=center.y+(radius-1);
	int polygon5[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon5);

    	setfillstyle(SOLID_FILL,LIGHTGRAY);
	floodfill(center.x, center.y,15);

    	poly1.x=center.x-4;
	poly1.y=center.y-8;
	poly2.x=center.x+4;
	poly2.y=center.y-8;
	poly3.x=center.x+8;
	poly3.y=center.y;
	poly4.x=center.x+4;
	poly4.y=center.y+8;
	poly5.x=center.x-4;
	poly5.y=center.y+8;
	poly6.x=center.x-8;
	poly6.y=center.y;
	int polygon[14]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y,poly5.x,poly5.y,poly6.x,poly6.y,poly1.x,poly1.y};
	drawpoly(7,polygon);

	setfillstyle(SOLID_FILL,RED);
	floodfill(center.x, center.y,15);
	setlinestyle(0,0,1);

    }

	void drawRods(Rectangle upRod,Rectangle downRod)
	{
        	rectangle(upRod.tL.x,upRod.tL.y,upRod.bR.x,upRod.bR.y);
        	rectangle(downRod.tL.x,downRod.tL.y,downRod.bR.x,downRod.bR.y);
	}
	void genRods(const int &X, const int &Y)
	{
        	setcolor(15);
			bgilib :: Rectangle rod1,rod2;
    		rod1.tL.x = X;
        	rod1.tL.y = 0;
        	rod1.bR.y = Y;
        	rod1.bR.x = rod1.tL.x+50;
        	rod2.tL.x = rod1.tL.x;
        	rod2.bR.x = rod1.bR.x;
        	rod2.bR.y = getmaxy();
        	rod2.tL.y = rod1.bR.y+100;
        	rectangle(rod1.tL.x,rod1.tL.y,rod1.bR.x,rod1.bR.y);
        	rectangle(rod2.tL.x,rod2.tL.y,rod2.bR.x,rod2.bR.y);
	}
	void updateRods(Rectangle &upRod, Rectangle &downRod)
	{
		int xMax, yMax;
		xMax = getmaxx();
		yMax = getmaxy();

		/*Coordinates for Up Rod*/
		upRod.tL.y = 0;
		upRod.bR.x = upRod.tL.x + (xMax * 3 / 80);//UPPER ROD POSITIONING
		upRod.width = upRod.bR.x - upRod.tL.x;
		upRod.height = upRod.bR.y - upRod.tL.y;
		upRod.center = midPoint(upRod.bR, upRod.tL);

		/*Coordiantes for Down rod*/
		downRod.tL.x = upRod.tL.x;
		downRod.bR.x = upRod.bR.x;
		downRod.bR.y = yMax;
		downRod.tL.y = upRod.bR.y + 300;//LOWER ROD POSITIONING
		downRod.width = downRod.bR.x - downRod.tL.x;
		downRod.height = downRod.bR.y - downRod.tL.y;//WIDTH AND HEIGHT OF RODS
		downRod.center = midPoint(downRod.bR, downRod.tL);//MIDPOINT OF RODS
	}


	void genGoalPost(Line &top, Line &reaR)
	{

		//primitives::Line top,reaR,bottom,front;
		bgilib::Line bottom, front;
		int xMax=getmaxx();
		int yMax=getmaxy();
		top.src.x=xMax*2/3;
		top.src.y=yMax*1/4;
		top.dst.x=xMax*5/6;
		top.dst.y=yMax*1/4;
		front.src.x=xMax*2/3;
		front.src.y=yMax*1/4;
		front.dst.x=xMax*2/3;
		front.dst.y=yMax;
		reaR.src.x=xMax*5/6;
		reaR.src.y=yMax*1/4;
		reaR.dst.x=xMax;
		reaR.dst.y=yMax*3/4;
		bottom.src.x=xMax*2/3;
		bottom.src.y=yMax;
		bottom.dst.x=xMax;
		bottom.dst.y=yMax;

		setlinestyle(0,0,25);
		line(top.src.x,top.src.y,top.dst.x,top.dst.y);//top bar//
		setlinestyle(0,0,20);
		line(reaR.src.x,reaR.src.y,reaR.dst.x,reaR.dst.y);//rear post//
		setlinestyle(0,0,20);
		line(front.src.x,front.src.y,front.dst.x,front.dst.y);//front post//
		setlinestyle(0,0,20);
		line(bottom.src.x,bottom.src.y,bottom.dst.x,bottom.dst.y);//bottom//
		setfillstyle(HATCH_FILL,WHITE);
		floodfill((xMax*2/3)+30,(yMax*1/4)+20,WHITE);
		setlinestyle(0,0,1);
	}
	BallArrow genBallArrow(const Point &origin)				//Function to generate Arrow for ball initially
	{
		BallArrow b_arrow;
		int xMax = getmaxx();
		b_arrow.tail = origin;
		b_arrow.head.x = b_arrow.tail.x + (xMax / 18);
		b_arrow.head.y = b_arrow.tail.y;
		return b_arrow;
	}
	void drawBallArrow(BallArrow &b_arrow)					//Function to draw Arrow for ball
	{
		Point p;							//Point which will be rotated to draw arrow head

		/*Finding out the midpoint between the midpoint of tail and head and head */
		p.x = (b_arrow.tail.x + b_arrow.head.x) / 2;
		p.y = (b_arrow.tail.y + b_arrow.head.y) / 2;
		p.x = (p.x + b_arrow.head.x) / 2;
		p.y = (p.y + b_arrow.head.y) / 2;

		b_arrow.uHead = getRotatedPoint(p, 0.785, b_arrow.head.x, b_arrow.head.y);
		b_arrow.lHead = getRotatedPoint(p, -0.785, b_arrow.head.x, b_arrow.head.y);
		
		setlinestyle(0, 0, 2);
		line(b_arrow.head.x, b_arrow.head.y, b_arrow.tail.x, b_arrow.tail.y);
		line(b_arrow.uHead.x, b_arrow.uHead.y, b_arrow.head.x, b_arrow.head.y);
		line(b_arrow.lHead.x, b_arrow.lHead.y, b_arrow.head.x, b_arrow.head.y);
		line(b_arrow.lHead.x, b_arrow.lHead.y, b_arrow.uHead.x, b_arrow.uHead.y);
	}
	
	
/***********************************************ASSETS FOR ARCHERY PROJECT**************************************************/

	
	
	Bow genInitBow()							//Generates coordinates for bow before the gameplay
	{
		Bow bow;
		int xMax = getmaxx();
		int yMax = getmaxy();

		bow.radius = xMax / 16;
		bow.center.x = bow.radius / 3;
	 	bow.center.y = yMax / 2;
        	setcolor(WHITE);
        	setlinestyle(0 , 0 , 7);             //set line style function is not for arcs but the thickness parameter works successfully
        	struct arccoordstype arcinfo;
		arc(bow.center.x , bow.center.y , 290 , 70 , bow.radius);
	 	getarccoords(&arcinfo);              //fetching the endpoints of the last drawn arc
        	bow.midy = ( arcinfo.ystart + 5 + arcinfo.yend - 5 ) / 2;

       	 	/*co-ordinates for upper part of the string*/

        	bow.uString.src.x = arcinfo.xstart;
       		bow.uString.src.y = arcinfo.ystart+5;
        	bow.uString.dst.x = arcinfo.xstart;
        	bow.uString.dst.y = bow.midy;

       		//co-ordinates for lower part of the string
        	bow.lString.src.x = arcinfo.xend;
        	bow.lString.src.y = bow.midy+1;
        	bow.lString.dst.x = arcinfo.xend;
       		bow.lString.dst.y = arcinfo.yend-4;
		return bow;
	}
	
	void genBow(Bow &bow)							//Generates the coordinates for the bow during the gameplay
	{

		setcolor(WHITE);
		struct arccoordstype arcinfo;
		setlinestyle(0, 0, 7);             //set line style function is not for arcs but the thickness parameter works successfully
		arc(bow.center.x, bow.center.y, 290, 70, bow.radius);
		getarccoords(&arcinfo);              //fetching the endpoints of the last drawn arc
		bow.midy = (arcinfo.ystart + 5 + arcinfo.yend - 5) / 2;

		/*co-ordinates for upper part of the string*/

		bow.uString.src.x = arcinfo.xstart;
		bow.uString.src.y = arcinfo.ystart + 5;
		bow.uString.dst.x = arcinfo.xstart;
		bow.uString.dst.y = bow.midy;

		//co-ordinates for lower part of the string
		bow.lString.src.x = arcinfo.xend;
		bow.lString.src.y = bow.midy;
		bow.lString.dst.x = arcinfo.xend;
		bow.lString.dst.y = arcinfo.yend - 4;
	}
	void drawBow(Bow &bow , const int &flag)						// Draw bow according to the coordinates generated
	{

        	setcolor(12);
        	setlinestyle(0 , 0 , 8);
        	arc(bow.center.x , bow.center.y , 350 , 10 , bow.radius - 1);
        	arc(bow.center.x , bow.center.y , 350 , 10 , bow.radius - 2);
        	arc(bow.center.x , bow.center.y , 350 , 10 , bow.radius - 3);
        	arc(bow.center.x , bow.center.y , 350 , 10 , bow.radius + 3);
        	arc(bow.center.x , bow.center.y , 350 , 10 , bow.radius + 2);
        	arc(bow.center.x , bow.center.y , 350 , 10 , bow.radius + 1);

        	setlinestyle(0 , 0 , 3);

		if (flag == 1)    //if a bow is stretched
		{	/*Function call for a stretched bow.*/
			int trans = (bow.radius / 3) * (-1);
			translatePoint(bow.uString.dst, trans, 0);
			translatePoint(bow.lString.src, trans, 0);
		}
        	line(bow.uString.src.x , bow.uString.src.y , bow.uString.dst.x , bow.uString.dst.y);
        	line(bow.lString.src.x , bow.lString.src.y , bow.lString.dst.x , bow.lString.dst.y);
	}
	Arrow genArrow(const int &bowRadius,Point &origin)  //if arrow is to be aligned with the bow send origin = bow center
	{
        	Arrow arrow;
		arrow.locus = origin;
        	arrow.size = bowRadius * 3 / 20;
        	return arrow;                 //returning reference to the Arrow type object generated by the function
	}
	
	void drawArrow(const int &size, const Point &origin)
	{
		int tail_size;
        	setlinestyle(0 , 0 , 3);
       		setcolor(WHITE);
       		moveto(origin.x , origin.y);                                   //https://www.cs.colorado.edu/~main/bgi/doc/moveto.html
       		linerel(10 * size, 0);     //linerel(int dx,int dy)      //https://www.cs.colorado.edu/~main/bgi/doc/linerel.html

       		//head part of the arrow

       		linerel(-2 * size , -1 * size + 1);
		linerel(0 , 2 * size - 1);
       		linerel(2 * size , -1 * size);

       		//tail part of the arrow

       		moveto(origin.x + 3 , origin.y);
       		tail_size = size - 3;

       		linerel(-2 * tail_size, -1 * tail_size + 1);
       		linerel(0 , 2 * tail_size - 1);
       		linerel(2 * tail_size, -1 * tail_size);
    }
	
	Target genTarget(const Point &targetCenter)
	{
	    	Target targ;
	    	int xMax = getmaxx();
	    	int yMax = getmaxy();
	   	targ.horiz.src.x = xMax - xMax/30;
        	targ.horiz.src.y = targetCenter.y;
        	targ.horiz.dst.x = targ.horiz.src.x + xMax / 30;
        	targ.horiz.dst.y = targ.horiz.src.y;

	    	targ.vert.src.x = targ.horiz.src.x;
        	targ.vert.src.y = targ.horiz.src.y - yMax / 8;
        	targ.vert.dst.x = targ.horiz.src.x;
        	targ.vert.dst.y = targ.horiz.src.y + yMax / 8;
        	return targ;
	}
	
    	void drawTarget(const Target &targ) // consider sending as const reference if this function isn't a mutator
    	{
        	setlinestyle(0,0,6);
        	line(targ.vert.src.x,targ.vert.src.y,targ.vert.dst.x,targ.vert.dst.y);
        	setlinestyle(0,0,7);
        	line(targ.horiz.src.x,targ.horiz.src.y,targ.horiz.dst.x,targ.horiz.dst.y);
        	setlinestyle(0,0,4);
        	arc(targ.horiz.src.x,targ.horiz.src.y,90,270,14);
    	}

}

/* int main()                  // test football
{
    initwindow(480,480);
    primitives::Circle ball;
    std::cout << "Please enter the coordinates for the initial position of the ball (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	std::cout << "Please enter the radius of the ball." << std::endl;
	std::cin >> ball.radius;
    football(ball);
	system("pause");
}
/*int main()                    //test humanoid
{
    initwindow(480,480);
    primitives::Humanoid h1;
    primitives::Point temp;
    printf(" enter x,y \n");
    scanf("%d%d",&temp.x,&temp.y);
    h1 = primitives::genHumanoid(temp);
    getch();
}*/

/*int main()                    //Test Target
{
    initwindow(800,480);
    primitives::Point tar;
    primitives::Target targ1;
    tar.x = 710;
    tar.y = 40;
    targ1 = genTarget(tar);
    drawTarget(targ1);
}
*/
