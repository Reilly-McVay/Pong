#include "iostream"
#include "sfwdraw.h"
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sfw;

//Random function P1
int random(int min, int max)
{
	return min + rand() % (max - min);
}

//Random function P2
int d(int Sides)
{
	int Roll = 0;
	return Roll = rand() % Sides + 1;
}

struct Player
{
	float y;
	int Score;
};

int main()
{
	srand(time(0));	
	initContext(1000, 800, "Pong");
	Player P[2] { 0,0 };	
	
	//Ball x direction (0 = left , 1 = right)
	int a = (d(2) - 1);

	GO:
	//Ball y direction (2 = up, 0 = straight, 1 = down) 
	int b = 0;

	//Ball y Velocity (1-4) 
	int c = 0;
	
	//Reset Player positions after each score
	P[0].y = 0;
	P[1].y = 0;

	float x = 500, y = 400;
	while (stepContext())
	{
		
		//Game court
		drawLine(70, 100, 70, 700);
		drawLine(930, 100, 930, 700);
		drawLine(500, 100, 500, 700);
		drawLine(70, 100, 930, 100);
		drawLine(70, 700, 930, 700);
		drawCircle(500, 400, 75);

		//Left Player Score
		switch (P[0].Score)
		{
		case 1:
			drawLine(70, 30, 70, 70);
			break;
		case 2:
			drawLine(70, 30, 70, 70);
			drawLine(85, 30, 85, 70);
			break;
		case 3:
			drawLine(70, 30, 70, 70);
			drawLine(85, 30, 85, 70);
			drawLine(100, 30, 100, 70);
			break;
		case 4:
			drawLine(70, 30, 70, 70);
			drawLine(85, 30, 85, 70);
			drawLine(100, 30, 100, 70);
			drawLine(115, 30, 115, 70);
			break;
		case 5:
			drawLine(70, 30, 70, 70);
			drawLine(85, 30, 85, 70);
			drawLine(100, 30, 100, 70);
			drawLine(115, 30, 115, 70);
			drawLine(55, 30, 130, 70);
			break;
		}
		
		//Right Player Score
		switch (P[1].Score)
		{
		case 1:
			drawLine(930, 30, 930, 70);
			break;
		case 2:
			drawLine(930, 30, 930, 70);
			drawLine(915, 30, 915, 70);
			break;
		case 3:
			drawLine(930, 30, 930, 70);
			drawLine(915, 30, 915, 70);
			drawLine(900, 30, 900, 70);
			break;
		case 4:
			drawLine(930, 30, 930, 70);
			drawLine(915, 30, 915, 70);
			drawLine(900, 30, 900, 70);
			drawLine(885, 30, 885, 70);
			break;
		case 5:
			drawLine(930, 30, 930, 70);
			drawLine(915, 30, 915, 70);
			drawLine(900, 30, 900, 70);
			drawLine(885, 30, 885, 70);
			drawLine(870, 30, 945, 70);
			break;
		}

		//End game when a player reaches 5 points
		if ((P[0].Score == 5) || (P[1].Score == 5))
		{
			system("pause");
			break;
		}

		//Ball
		drawCircle(x, y, 25);

		//Left Player
		drawLine(60, P[0].y + 350, 60, P[0].y + 450);
		drawLine(70, P[0].y + 350, 60, P[0].y + 350);
		drawLine(70, P[0].y + 350, 70, P[0].y + 450);
		drawLine(70, P[0].y + 450, 60, P[0].y + 450);

		//Right Player 
		drawLine(940, P[1].y + 350, 940, P[1].y + 450);
		drawLine(930, P[1].y + 350, 940, P[1].y + 350);
		drawLine(930, P[1].y + 350, 930, P[1].y + 450);
		drawLine(930, P[1].y + 450, 940, P[1].y + 450);

		//Left Player controlls
		if (getKey('s') && P[0].y <= 250) { P[0].y += (200 * getDeltaTime()); }
		if (getKey('w') && P[0].y >= -250) { P[0].y -= (200 * getDeltaTime()); }

		//Right Player controlls
		if (getKey('l') && P[1].y <= 250) { P[1].y += (200 * getDeltaTime()); }
		if (getKey('o') && P[1].y >= -250) { P[1].y -= (200 * getDeltaTime()); }

		cout << getDeltaTime() << endl;
		
		//when ball collides with Left Player boarder
		if (x <= 100) 
		{
			if ((P[0].y >= (y - 460)) && (P[0].y <= (y - 340)))
			{
				a = 1;
				c = d(4);
				if (P[0].y > (y - 410))
				{
					c = d(4);
					b = 2;
				}
				if (P[0].y < (y - 390))
				{
					
					b = 1;
				}
				if ((P[0].y >= (y - 410)) && (P[0].y <= (y - 390)))
				{
					b = 0;
				}
			}
			else
			{
				++P[1].Score;
				a = 0;
				goto GO;
			}
		}

		//when ball collides with Right Player boarder
		if (x >= 900)
		{
			if ((P[1].y >= (y - 460)) && (P[1].y <= (y - 340)))
			{
				a = 0;
				if (P[1].y > (y - 410))
				{
					b = 2;
					c = d(4);
				}
				if (P[1].y < (y - 390))
				{
					b = 1;
					c = d(4);
				}
				if ((P[1].y >= (y - 410)) && (P[1].y <= (y - 390)))
				{
					b = 0;
				}
			}
			else
			{
				++P[0].Score;
				a = 1;
				goto GO;
			}
		}

		//when ball collides with top
		if (y <= 125) {b = 1;}

		//when ball collides with bottom
		if (y >= 675) {b = 2;}

		//Ball goes Right or Left depending on 'x'
		//Ball goes Up, Down, or Straight depending on 'b'
		switch (a)
		{
		case 0:
			x -= 300 * getDeltaTime();
			if (b == 2) { y -= ((c * 100) * getDeltaTime()); }
			if (b == 0) { y += 0; }
			if (b == 1) { y += ((c * 100) * getDeltaTime()); }
			break;

		case 1:
			x += 300 * getDeltaTime();
			if (b == 2) { y -= ((c * 100) * getDeltaTime()); }
			if (b == 0) { y += 0; }
			if (b == 1) { y += ((c * 100) * getDeltaTime()); }
			break;
		}
		
		
	}
	termContext();
}