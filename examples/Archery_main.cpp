/****************************************************************************************************************************
The following code implements the Archery game. This piece of code has the following components:

loadLeaderBoard() - Returns void - read leader board object player data from <DBA.DAT> and load it into object <best>.

PlaySound() - Returns bool - Plays audio track(for main menu, game play etc).

genInitBow() - Return the initial coordinates of Bow - This function is used to generate the coordinates for the Bow at the
start of game play.

genArrow() - Returns Arrow size and its point of origin - This function is used to generate Arrow’s size and its coordinate
of origin.

genTarget() - Return the coordinate of the Target - This function is used to generate coordinates of Target.

drawBow() - Returns void - This function is used to draw Bow on the screen.

drawArrow() - Returns void - This function is used to draw the Arrow on the screen.

drawTarget() - Return void - This function is used to draw Target on screen.

GetAsyncKeyState() – Returns bool – Starts the game when the SPACE key is tapped.

ismouseclick() -  Returns bool – This function is used to capture mouse click events. Here left click of mouse.

swapbuffers() – Returns void – This function is used to swap the front and the back buffer.

shockwave() – Returns void – This function is used to generate waves of pixel when the arrow hits the target.
*****************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "assets.h"
#include "fx.h"
#include "leaderboard.h"

#define TRUE 1
#define FALSE 0

int main()                    
{
	int xMax = 0, yMax = 0;
	std::string name;
	std::cout << "Please enter the desired resolution." << std::endl;
	std::cout << "Please enter the width, followed by the height in pixels." << std::endl;
	std::cin >> xMax >> yMax;
	std::cin.get();	
	initwindow(xMax, yMax, "Archery");
	xMax = getmaxx();
	yMax = getmaxy();
	int y_inc = 1,target_inc = 0, lives = 3;
	int score = 0, addScore = 0, lastScore = 0;		// Variable for scoring
	int division = 0;					// Variable to divide the target into fixed no. of zones.
	int target_flag = FALSE;				//Variable to set flag true or false for target movement.
	bool flag = false, mainMenu = false;
	std::string points;					// for displaying the score
	std::string earnedPoint;				// for displaying the current earned point
	std::string livesStr;
	std::string top;
	bgilib::Point arrowHitPos;				//Point Variable to store the arrow position.

	/**object declarations**/
	bgilib::Bow bow;                             
	bgilib::Arrow arrow;       
	bgilib::Target target;	

	// std::vector<Leaderboard> list;
	Leaderboard best;	
	
	while (1) // Main game loop
	{
		cleardevice();		
		if (!mainMenu)
		{
			try
			{
				loadLeaderBoard("saves/DBA.DAT", best); // loads profile data
			}
			catch (std::exception &err)
			{
				std::cout << err.what() << std::endl;
				std::cout << "Error occured while loading player data!" << std::endl;
			}
			PlaySound(TEXT("media/menu.wav"), NULL, SND_ASYNC|SND_LOOP);
			mainMenu = true;			
			std::cout << "Please enter your player avatar name." << std::endl;
			std::getline(std::cin, name);
		}
		// displayLeaderBoard(best); // debugging
		char *avatarName = new char[name.length() + 1];
		strcpy(avatarName, name.c_str());
		Leaderboard profile(avatarName);
		score = 0, addScore = 0, lastScore = 0, division = 0, lives = 3, profile.topScore = 0;
		flag = false;

		bow = bgilib::genInitBow();                             //By default a stretched bow.
		arrow = bgilib::genArrow(bow.radius, bow.center);        //scaled in accordance to bow radius origin at bow.center
		target = bgilib::genTarget(bow.center);

		drawBow(bow, TRUE);
		drawArrow(arrow.size, bow.center);
		drawTarget(target);
		outtextxy(xMax / 2 - 75, yMax / 2, "Press Space to Play!");
		outtextxy(xMax / 2 - 75, yMax / 2 + 25, "Left click mouse to shoot arrows.");
		if (GetAsyncKeyState(VK_SPACE))
		{
			PlaySound(TEXT("media/whistle.wav"), NULL, SND_ASYNC);
			delay(1000);
			flag = true;
		}
		while (flag && lives != 0)                 // gameplay loop
		{
			cleardevice();
			if ((bow.center.y - (bow.radius + 10)) <= 5)             //bound checking for bow  (upper screen) 
				y_inc = 1;
			if ((bow.center.y + bow.radius + 10) >= (yMax - 5))     //bound checking for bow  (lower screen)
				y_inc = -1;

			bow.center.y += y_inc;            			//bow translation by modifying bow center
			genBow(bow);                      			// regenerating the co-ordinates in response to modified Bow center
			drawBow(bow, TRUE);
			drawArrow(arrow.size, bow.center);
			
			/*Target Translation*/
			if (score > 20 && target_flag == FALSE)
			{
				target_inc = 1;
				target_flag = TRUE;
			}
			if (target.vert.dst.y + 10 > yMax)                  	//bound checking for target  (upper screen) 
				target_inc = -1;
			if (target.vert.src.y + 10 < 0)           		//bound checking for target  (lower screen)
				target_inc = 1;
			target.horiz.src.y += target_inc;
			target = bgilib::genTarget(target.horiz.src);
			
			drawTarget(target);

			/**Score Display**/
			points = std::to_string(score);
			const char *pstr = points.c_str();
			livesStr = std::to_string(lives);
			const char *plives = livesStr.c_str();
			outtextxy(xMax - 170, 50, "Points: ");
			outtextxy(xMax - 100, 50, (char*)pstr); // displays the current score 

			earnedPoint = std::to_string(lastScore);
			const char *pstrAdd = earnedPoint.c_str();
			outtextxy(xMax - 248, 70, "Last Point Earned :");
			outtextxy(xMax - 100, 70, (char*)pstrAdd); // displays the current earned score

			outtextxy(xMax - 168, 90, "Lives :");
			outtextxy(xMax - 100, 90, (char*)plives);

			arrow.locus.x = bow.center.x;
			arrow.locus.y = bow.center.y;



			if (ismouseclick(WM_LBUTTONDOWN))                    //occurrence of event is checked
			{
				PlaySound(TEXT("media/arrow_release.wav"), NULL, SND_ASYNC);
				while (arrow.locus.x + (8 * arrow.size) <= target.vert.src.x)
				{
					cleardevice();
					arrow.locus.x = arrow.locus.x + 5;
					genBow(bow);
					drawBow(bow, FALSE);
					drawArrow(arrow.size, arrow.locus);
					drawTarget(target);
					points = std::to_string(score);
					const char *pstr = points.c_str();
					outtextxy(xMax - 170, 50, "Points: ");
					outtextxy(xMax - 100, 50, (char*)pstr); // displays the current score 

					earnedPoint = std::to_string(lastScore);
					const char *pstrAdd = earnedPoint.c_str();
					outtextxy(xMax - 248, 70, "Last Point Earned :");
					outtextxy(xMax - 100, 70, (char*)pstrAdd); // displays the current earned score

					outtextxy(xMax - 168, 90, "Lives :");
					outtextxy(xMax - 100, 90, (char*)plives); // displays the no. of lives left
					swapbuffers();
				}
				clearmouseclick(WM_LBUTTONDOWN);    //event is released

				PlaySound(TEXT("media/target_hit.wav"), NULL, SND_ASYNC);
				arrowHitPos = arrow.locus;		//Stores the final position of the array
				division = (target.horiz.src.y - target.vert.src.y) / 4;  //Divide the target into 4 zones for scoring

				if (arrowHitPos.y < target.vert.src.y || arrowHitPos.y > target.vert.dst.y)		//If arrow doesn't hit the target
				{
					lastScore = 0;
					--lives;
				}
				else
				{
					if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + division))		//If the arrow hits the upper first divided zone of the target
					{
						outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+1");
						arrowHitPos.x += 9 * arrow.size;
						shockWave(arrowHitPos, 20, 50);
						swapbuffers();
						lastScore = addScore = 1;
						--lives;
					}
					else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - division))		//If the arrow hits the lower first divided zone of the target
					{
						outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+1");
						arrowHitPos.x += 9 * arrow.size;
						shockWave(arrowHitPos, 20, 50);
						swapbuffers();
						lastScore = addScore = 1;
						--lives;
					}
					else if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + 2 * division))//If the arrow hits the upper second divided zone of the target
					{
						outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+3");
						arrowHitPos.x += 9 * arrow.size;
						shockWave(arrowHitPos, 20, 50);
						swapbuffers();
						lastScore = addScore = 3;
						--lives;
					}
					else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - 2 * division))	//If the arrow hits the lower second divided zone of the target
					{
						outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+3");
						arrowHitPos.x += 9 * arrow.size;
						shockWave(arrowHitPos, 20, 50);
						swapbuffers();
						lastScore = addScore = 3;
						--lives;
					}
					else if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + 3 * division))//If the arrow hits the upper third divided zone of the target
					{
						outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+5");
						arrowHitPos.x += 9 * arrow.size;
						shockWave(arrowHitPos, 20, 50);
						swapbuffers();
						lastScore = addScore = 5;
						--lives;
					}
					else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - 3 * division))	//If the arrow hits the lower third divided zone of the target
					{
						outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+5");
						arrowHitPos.x += 9 * arrow.size;
						shockWave(arrowHitPos, 20, 50);
						swapbuffers();
						lastScore = addScore = 5;
						--lives;
					}
					else //If the arrow hits the center
					{
						outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+7");
						outtextxy(arrowHitPos.x - 50, arrowHitPos.y, "BULLSEYE !!");
						shockWave(target.horiz.src, 20, 50);
						swapbuffers();
						lastScore = addScore = 7;
						if(lives<3)
							++lives;
						PlaySound(TEXT("media/crowd.wav"), NULL, SND_ASYNC);
					}
				}
				score += addScore;
				addScore = 0;
				target.horiz.src.y = rand() % (yMax - 75 - static_cast<int>(yMax / 8)) + static_cast<int>(yMax / 8);
				target = bgilib::genTarget(target.horiz.src);
				delay(700);
			}
			swapbuffers();
		}

		if (lives == 0) // scoring and leader board - WIP
		{					
			outtextxy(xMax / 2 - 75, yMax / 2, "Game Over!");
			outtextxy(xMax / 2 - 75, yMax / 2 + 20, "Top Score is ");
			profile.topScore = score;				
			
			// list.push_back(profile);
			if (profile.topScore > best.topScore)
			{
				best = profile;
				try
				{
					saveLeaderBoard("saves/DBA.DAT", best); // save profile data
				}
				catch (std::exception &err)
				{
					std::cout << err.what() << std::endl;
					std::cout << "Error occured while saving score!" << std::endl;
				}				
			}
			top = std::to_string(best.topScore);
			const char *ptop = top.c_str();
			outtextxy(xMax / 2 + 25, yMax / 2 + 20, (char*)ptop);
			outtextxy(xMax / 2 - 75, yMax / 2 + 40, "Player name: ");
			outtextxy(xMax / 2 + 25, yMax / 2 + 40, best.playerName);
			mainMenu = false;
			swapbuffers();
			delay(3000);
			delete[] avatarName;
		}
		swapbuffers();
	}
	closegraph();
	return 0;
}