#include "iGraphics.h"
#include <math.h>
#include <stdlib.h>
#include "Level.h"

void draw_life()
{
	double life_dx = windowx - block_startx - 45;  //10x10 is the size of bmp. we are obtaining the left bottom point
	double life_dy = windowy - 45;
	double border;
	int i;
	for (i = 1; i <= life; i++)
	{
		if (page_no >= 1)
		{
			if (life >= 3)
			{
				//iShowBMP2(life_dx, life_dy, "ballGreen.bmp", 0); //show green colored bmp
				iSetColor(0, 255, 0);
				iFilledCircle(life_dx, life_dy, 12.5);
				iSetColor(0, 0, 0);
				for (border = 0; border <= 2; border += 0.1)
				{
					iCircle(life_dx, life_dy, 12.5 - border);
				}
				life_dx -= 30; //there is 5 pixel difference between two lives //life dy is always same
			}
			else if (life >= 2)
			{
				//iShowBMP2(life_dx, life_dy, "ballBlue.bmp", 255); //show bmp of color near to red
				iSetColor(0, 0, 255);
				iFilledCircle(life_dx, life_dy, 12.5);
				iSetColor(0, 0, 0);
				for (border = 0; border <= 2; border += 0.1)
				{
					iCircle(life_dx, life_dy, 12.5 - border);
				}
				life_dx -= 30; //there is 5 pixel difference between two lives //life dy is always same
			}
			else
			{
				//iShowBMP2(life_dx, life_dy, "ballRed.bmp", 0); //show bmp of red colour
				iSetColor(255, 0, 0);
				iFilledCircle(life_dx, life_dy, 12.5);
				iSetColor(0, 0, 0);
				for (border = 0; border <= 2; border += 0.1)
				{
					iCircle(life_dx, life_dy, 12.5 - border);
				}
				life_dx -= 30; //there is 5 pixel difference between two lives //life dy is always same
			}
		}
	}
}

void isPowerFunc()
{
	isPower = 1;
}

void ShowPower(int x)
{
	char image_name[7];
	sprintf(image_name, "%d.bmp", x);
	iShowBMP(powx, powy, image_name);
}


void PowerMove()
{
	powy -= pow_speed;
	if (PowerCaught()) power_call();
}

int PowerCaught()
{
	if (powx > pad_centerx - (l_pad / 2) - 10 && powx + 35 < pad_centerx + (l_pad / 2) + 10)
	{
		if (powy <= pad_starty)
		{
			powx = powy = 0;
			return 1;
		}
	}
	if (powy + 35 < 0) showpower = powx = powy = 0;
	return 0;
}

void quit_bar()
{
	int a = (windowx - 400) / 2;
	int b = (windowy - 200) / 2;
	if (page_no > 0)
	{
		iShowBMP(a, b, "QuitBarLevel.bmp");
	}
	if (!page_no)
	{
		iShowBMP(a, b, "QuitBarMainMenu.bmp");
	}
}


void show_score()
{
	char scr[6];
	sprintf(scr, "%d", score);
	iSetColor(255, 255, 255);
	iText(block_startx + 50, windowy - 50, scr);
}


void power_call()
{
	int i, j;
	switch (power)
	{
	case 1: 
		PlaySound("Power.wav",NULL,SND_ASYNC);
		if (l_pad < 300)
		l_pad += 50;
		score += 50;
		break;
	case 2:
		PlaySound("Power.wav",NULL,SND_ASYNC);
		if (l_pad >= 100)
		l_pad -= 50;
		score -= 10;
		break;
	case 3:
		PlaySound("Power.wav",NULL,SND_ASYNC); 
		l_pad = 50;
		score -= 30;
		break;
	case 4:
		PlaySound("Power.wav",NULL,SND_ASYNC); 
		if (life < 5) life++;
		score += 60;
		break;
	case 5:
		--life;
		if(life<=0)  PlaySound("Lose.wav",NULL,SND_ASYNC);
		else PlaySound("Byeball.wav",NULL,SND_ASYNC);
		score -= 20;
		if (life)
		{
			ballstate = 0;
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
		}
		else
		{
			page_no = -7;
			TextInput = 1;
			showpower = 0;
			level_called = 0;
			level_clear();
		}
		l_pad = 150;
		thru_block = 0;
		fireball = 0;
		ball_magnet = 0;
		break;
	case 6: 
		PlaySound("Power.wav",NULL,SND_ASYNC);
		if (dx > 0 && dx < 25) dx += 1.5;
		else if (dx<0 && dx>-25) dx -= 1.5;
		if (dy > 0 && dy < 25) dy += 1.5;
		else if (dy<0 && dy>-25) dy -= 1.5;
		score -= 15;
		break;
	case 7:
		PlaySound("Power.wav",NULL,SND_ASYNC);
		if (dx > 8) dx -= 1.5;
		else if (dx < -8) dx += 1.5;
		if (dy > 8) dy -= 1.5;
		else if (dy < -8) dy += 1.5;
		score += 15;
		break;
	case 8: level_clear();
		break;
	case 9:
		PlaySound("Power.wav",NULL,SND_ASYNC);
		thru_block = 1;
		score += 10;
		break;
	case 10:
		PlaySound("Power.wav",NULL,SND_ASYNC);
		fireball = 1;
		score += 20;
		break;
	case 11:
	    dynamite=1;
		score += 100;
		i = rand() % 12;
		j = rand() % 12;
		blocks[i][j].block_pos = blocks[i][j - 1].block_pos = blocks[i][j + 1].block_pos = 0;
		blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = blocks[i - 1][j + 1].block_pos = 0;
		blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = blocks[i + 1][j + 1].block_pos = 0;
		PlaySound("Bang.wav",NULL,SND_ASYNC);
		dynamite=0;
		break;
	case 0:
		PlaySound("Power.wav",NULL,SND_ASYNC);
		ball_magnet = 1;
		score += 50;
		break;
	}
	showpower = 0;
}



void Break_Blocks()
{
	int i, j;
	double a = ball_centerx + radius; //
	double b = ball_centery + radius; //
	double c = ball_centerx - radius; //   //for reflection and breaking blocks
	double d = ball_centery - radius; //
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < column; ++j)
		{
			if (blocks[i][j].block_pos > 0)
			{
				brick_break_sound=0;
				if (ball_centerx >= blocks[i][j].point.bottomleftx && ball_centerx <= blocks[i][j].point.toprightx)
				{
					if (b >= blocks[i][j].point.bottomlefty && d <= blocks[i][j].point.toprighty)
					{
						if (blocks[i][j].color.red == 0 && blocks[i][j].color.green == 0 && blocks[i][j].color.blue == 0)
						{
							blocks[i][j].color.red = 255;
							blocks[i][j].color.green = 255;
							blocks[i][j].color.blue = 255;
							if(!brick_break_sound&& !thru_block && !fireball && !dynamite)
							{
								PlaySound("Effect.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
						}
						blocks[i][j].block_pos--;
						if (!thru_block) dy = -dy;
						if(thru_block) 
						{
							score+=30;
							if(!brick_break_sound && !dynamite)
							{
								PlaySound("Tank.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
						}
						if (fireball)
						{
							score+=25;
							if(!brick_break_sound && !dynamite)
							{
								PlaySound("Fireball.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
							if (!(i == 0 || i == row || j == 0 || j == column))
							{
								blocks[i][j].block_pos = blocks[i][j - 1].block_pos = blocks[i][j + 1].block_pos = 0;
								blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = blocks[i - 1][j + 1].block_pos = 0;
								blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = blocks[i + 1][j + 1].block_pos = 0;
							}
							if (i == 0)
							{
								if (j == 0)
								{
									blocks[i][j].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i + 1][j].block_pos = blocks[i + 1][j + 1].block_pos = 0;
								}
								else if (j == column)
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = 0;
									blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = 0;
								}
								else
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = blocks[i + 1][j + 1].block_pos = 0;
								}
							}
							else if (i == row)
							{
								if (j == 0)
								{
									blocks[i][j].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i - 1][j].block_pos = blocks[i - 1][j + 1].block_pos = 0;
								}
								if (j == column)
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = 0;
									blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = 0;
								}
								else
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = blocks[i - 1][j + 1].block_pos = 0;
								}
							}
							else if (j == 0)
							{
								blocks[i][j].block_pos = blocks[i][j + 1].block_pos = 0;
								blocks[i + 1][j].block_pos = blocks[i + 1][j + 1].block_pos = 0;
								blocks[i - 1][j].block_pos = blocks[i - 1][j + 1].block_pos = 0;
							}
							else if (j == column)
							{
								blocks[i][j].block_pos = blocks[i][j - 1].block_pos = 0;
								blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = 0;
								blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = 0;
							}
						}
						if(!brick_break_sound && !dynamite)
						{
							if(blocks[i][j].block_pos > 0)
							{
								PlaySound("Effect.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
							else
							{
								PlaySound("Simple.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
						}
						if (isPower)
						{
							power = rand() % 12;
							showpower = 1;
							isPower = 0;
							powx = blocks[i][j].point.bottomleftx;
							powy = blocks[i][j].point.bottomlefty;
						}
						score += 10;
					}
				}
				else if (ball_centery >= blocks[i][j].point.bottomlefty && ball_centery <= blocks[i][j].point.toprighty)
				{
					if (a >= blocks[i][j].point.bottomleftx && c <= blocks[i][j].point.toprightx)
					{
						if (blocks[i][j].color.red == 0 && blocks[i][j].color.green == 0 && blocks[i][j].color.blue == 0)
						{
							blocks[i][j].color.red = 255;
							blocks[i][j].color.green = 255;
							blocks[i][j].color.blue = 255;
							if(!brick_break_sound&& !thru_block && !fireball && !dynamite)
							{
								PlaySound("Effect.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
						}
						blocks[i][j].block_pos--;
						if (!thru_block) dx = -dx;
						if(thru_block)
						{
							score+=30;
							if(!brick_break_sound && !dynamite)
							{
								PlaySound("Tank.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
						}
						if (fireball)
						{
							score+=25;
							if(!brick_break_sound && !dynamite)
							{
								PlaySound("Fireball.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
							if (!(i == 0 || i == row || j == 0 || j == column))
							{
								blocks[i][j].block_pos = blocks[i][j - 1].block_pos = blocks[i][j + 1].block_pos = 0;
								blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = blocks[i - 1][j + 1].block_pos = 0;
								blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = blocks[i + 1][j + 1].block_pos = 0;
							}
							if (i == 0)
							{
								if (j == 0)
								{
									blocks[i][j].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i + 1][j].block_pos = blocks[i + 1][j + 1].block_pos = 0;
								}
								else if (j == column)
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = 0;
									blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = 0;
								}
								else
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = blocks[i + 1][j + 1].block_pos = 0;
								}
							}
							else if (i == row)
							{
								if (j == 0)
								{
									blocks[i][j].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i - 1][j].block_pos = blocks[i - 1][j + 1].block_pos = 0;
								}
								if (j == column)
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = 0;
									blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = 0;
								}
								else
								{
									blocks[i][j].block_pos = blocks[i][j - 1].block_pos = blocks[i][j + 1].block_pos = 0;
									blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = blocks[i - 1][j + 1].block_pos = 0;
								}
							}
							else if (j == 0)
							{
								blocks[i][j].block_pos = blocks[i][j + 1].block_pos = 0;
								blocks[i + 1][j].block_pos = blocks[i + 1][j + 1].block_pos = 0;
								blocks[i - 1][j].block_pos = blocks[i - 1][j + 1].block_pos = 0;
							}
							else if (j == column)
							{
								blocks[i][j].block_pos = blocks[i][j - 1].block_pos = 0;
								blocks[i + 1][j].block_pos = blocks[i + 1][j - 1].block_pos = 0;
								blocks[i - 1][j].block_pos = blocks[i - 1][j - 1].block_pos = 0;
							}
						}
						if(!brick_break_sound && !dynamite)
						{
							if(blocks[i][j].block_pos > 0)
							{
								PlaySound("Effect.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
							else
							{
								PlaySound("Simple.wav",NULL,SND_ASYNC);
								brick_break_sound=1;
							}
						}
						if (isPower)
						{
							power = rand() % 12;
							showpower = 1;
							isPower = 0;
							powx = blocks[i][j].point.bottomleftx;
							powy = blocks[i][j].point.bottomlefty;
						}
						score += 10;
					}
				}
			}
		}
	}
}



void ball_reflect()
{
	double a = ball_centerx - radius;//
	double b = ball_centerx + radius;//
	double c = pad_centerx - l_pad / 2 - 10;//  //for various reflection checkings
	double d = pad_centerx + l_pad / 2 + 10;//
	double e = ball_centery - radius;//
	double f = ball_centery + radius;//
	double l_pad_1_3 = l_pad / 3;
	if (b > block_endx && f > windowy)
	{
		dx = -dx;
		dy = -dy;
		PlaySound("Wall.wav",NULL,SND_ASYNC);
	}
	else if (a < block_startx && f > windowy)
	{
		dx = -dx;
		dy = -dy;
		PlaySound("Wall.wav",NULL,SND_ASYNC);
	}
	else if (a < block_startx || b > block_endx)
	{
		dx = -dx;
		PlaySound("Wall.wav",NULL,SND_ASYNC);
	}
	else if (f >= windowy)
	{
		dy = -dy;
		PlaySound("Wall.wav",NULL,SND_ASYNC);
	}
	else if (f > block_starty)
	{
		Break_Blocks();
	}
	else if (b >= c + l_pad_1_3 && a <= d - l_pad_1_3)
	{
		if (e < pad_endy)
		{
			PlaySound("Pad.wav",NULL,SND_ASYNC);
			if(!ball_magnet) dy = -dy;
			else
			{
				ballstate = 0;
				ball_centery = pad_endy + radius;
			}
		}
	}
	else if (b >= c && a <= c + l_pad_1_3)
	{
		if (e < pad_endy)
		{
			PlaySound("Pad.wav",NULL,SND_ASYNC);
			if (!ball_magnet)
			{
				dy = -dy;
				dx = -fabs(dx);
			}
			else
			{
				ballstate = 0;
				ball_centery = pad_endy + radius;
			}
		}
	}
	else if (b >= d - l_pad_1_3 && a <= d)
	{
		if (e < pad_endy)
		{
			PlaySound("Pad.wav",NULL,SND_ASYNC);
			if (!ball_magnet)
			{
				dy = -dy;
				dx = fabs(dx);
			}
			else
			{
				ballstate = 0;
				ball_centery = pad_endy + radius;
			}
		}
	}
	else if (f < 0)
	{
		--life;
		if(life<=0) PlaySound("Lose.wav",NULL,SND_ASYNC);
		else PlaySound("Byeball.wav",NULL,SND_ASYNC);
		if (life)
		{
			ballstate = 0;
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
		}
		else
		{
			page_no = -7;
			TextInput = 1;
			level_called = 0;
			level_clear();
		}
		l_pad = 150;
		thru_block = 0;
		fireball = 0;
		showpower = 0;
		ball_magnet = 0;
	}
}


void ballmove()
{
	if (ballstate == 1)
	{
		ball_centerx += dx;
		ball_centery += dy;
		ball_reflect();
	}
}

void DrawBlocks()
{
	int i, j;
	double border;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < column; ++j)
		{
			if (blocks[i][j].block_pos > 0)
			{
				iSetColor(blocks[i][j].color.red, blocks[i][j].color.green, blocks[i][j].color.blue);
				iFilledRectangle(blocks[i][j].point.bottomleftx, blocks[i][j].point.bottomlefty, w, h);
				iSetColor(0, 0, 0);
				for (border = 0; border <= 2; border += 0.1)
				{
					iRectangle(blocks[i][j].point.bottomleftx + border, blocks[i][j].point.bottomlefty + border, w - 2 * border, h - 2 * border);
				}
			}
		}
	}
}

void Draw_Ball(int r, int g, int b)
{
	iSetColor(r, g, b);
	iFilledCircle(ball_centerx, ball_centery, radius);
	iSetColor(0, 0, 0);
	iCircle(ball_centerx, ball_centery, radius);
}


void Draw_Pad(int r, int g, int b)
{
	double pad_arrx[] = { pad_centerx - (l_pad / 2), pad_centerx - (l_pad / 2) - 10,
	pad_centerx - (l_pad / 2),pad_centerx + (l_pad / 2),
	pad_centerx + (l_pad / 2) + 10,
	pad_centerx + (l_pad / 2),pad_centerx - (l_pad / 2) };
	double pad_arry[] = { pad_starty,pad_centery,pad_endy,pad_starty,pad_centery,pad_endy,pad_endy };
	iSetColor(r, g, b);
	iFilledPolygon(pad_arrx, pad_arry, 7);
}

void Boundary()
{
	iSetColor(255, 255, 255);
	iFilledRectangle(block_startx - boundary_w, 0, boundary_w, windowy);
	iFilledRectangle(windowx - block_startx, 0, boundary_w, windowy);
}


void iDraw()
{
	iClear();
	level();
	if (showpower) ShowPower(power);
	if (page_no > 0) draw_life();
	iSetColor(255, 255, 255);
	if (paused && page_no > 0) iText(20, 20, "Paused");
}


void iMouseMove(int mx, int my)
{

}


void iMouse(int button, int state, int mx, int my)
{
	double a = START_PAGE_STARTX;
	double b = START_PAGE_STARTY;
	double c = START_PAGE_LENGTH;
	double d = START_PAGE_HEIGHT;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		play_intro=0;
		PlaySound("Click.wav",NULL,SND_ASYNC);
		if (mx > a && mx < a + c && my > b && my < b + d && !page_no)
		{
			page_no = -2;
		}
		if (mx > a && mx < a + c && my > windowy - b - d && my < windowy - b && !page_no)
		{
			level_clear();
			life=3;
			ballstate = 0;
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
			score=0;
			l_pad=150;
	        level_called=0;
			page_no = 1;
		}
		if (mx > windowx - a - c && mx < windowx - a && my > b && my < b + d && !page_no)
		{
			quit_bar_show = 1;
		}
		if (mx > windowx - a - c && mx < windowx - a && my > windowy - b - d && my < windowy - b && !page_no)
		{
			page_no = -1;
		}
		if (mx > 0 && my > 0 && mx < windowx && my < windowy && page_no <= -3 && page_no > -7)
		{
			page_no = (-page_no) - 1;
		}
		if (mx > a + c + 125 && mx < a + c + 425 && my > windowy - b - d && my < windowy - b && !page_no)
		{
			page_no = -8;
		}
	}
}


void iKeyboard(unsigned char key)
{
	if (!TextInput)
	{
		if (key == 's' && !ballstate && page_no > 0)
		{
			double a = ball_centerx - radius;
			double b = ball_centerx + radius;
			double c = pad_centerx - l_pad / 2 - 10;
			double d = pad_centerx + l_pad / 2 + 10;
			double l_pad_1_3 = l_pad / 3;
			dx = dy = 10;
			if (b >= c + l_pad_1_3 && a <= d - l_pad_1_3)
			{
				ball_angle = ((rand() % 10 + 60)*PI) / 180;
				dx = dx*cos(ball_angle);
				dy = dy*sin(ball_angle);
				ballstate = 1;
			}
			else if (b >= l_pad_1_3 && a <= c + l_pad_1_3)
			{
				ball_angle = ((rand() % 10 + 35)*PI) / 180;
				dx = -dx*cos(ball_angle);
				dy = dy*sin(ball_angle);
				ballstate = 1;
			}
			else if (b >= d - l_pad_1_3 && a <= d)
			{
				ball_angle = ((rand() % 10 + 35)*PI) / 180;
				dx = dx*cos(ball_angle);
				dy = dy*sin(ball_angle);
				ballstate = 1;
			}
		}
		if (key == 'p')
		{
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			pad_speed = 0;
			//level_clear();
			paused = 1;
		}
		if (key == 'r')
		{
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
			paused = 0;
			pad_speed = 35;
		}
		if (key == 27)
		{
			if (page_no == -1 || page_no == -2 || page_no==-8)
			{
				play_intro=0;
				page_no = 0;
			}
			else
			{
				iPauseTimer(0);
				iPauseTimer(1);
				iPauseTimer(2);
				pad_speed=0;
				quit_bar_show = 1;
			}
		}
		if ((key == 'y' || key == 'Y') && quit_bar_show)
		{
			if (page_no > 0)
			{
				page_no = 0;
				play_intro = 0;
				quit_bar_show = 0;
				score = 0;
				paused = 0;
				iResumeTimer(0);
				iResumeTimer(1);
				iResumeTimer(2);
				level_clear();
				pad_speed = 35;
				ballstate = 0;
				pad_centerx = (windowx / 2);
				ball_centerx = pad_centerx;
				ball_centery = pad_endy + radius;
				level_called = 0;
				showpower = 0;
			}
			else if (!page_no) exit(0);
		}
		if ((key == 'n' || key == 'N') && quit_bar_show)
		{
			quit_bar_show = 0;
			pad_speed = 35;
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
	}
	else
	{
		static int i = 0;
		if(key == '\r' || i == 25)
		{
			TextInput = 0;
			update = 1;
			page_no = -2;
			i = 0;
		}
		else if (key == 8 && i > 0)
		{
			NameInput[--i] = '\0';
		}
		else
		{
			NameInput[i] = key;
			++i;
		}
	}
}


void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_LEFT)
	{
		int f = (pad_centerx - l_pad / 2 - 10); //left point of the pad
		if(f - block_startx >= pad_speed) 
		{
			pad_centerx -= pad_speed;
			if (ballstate == 0) ball_centerx -= pad_speed;
		}
		else if (f - block_startx < pad_speed && f - block_startx > 0)
		{
			pad_centerx -= f - block_startx;
			if (ballstate == 0) ball_centerx -= f - block_startx;
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		int f = (pad_centerx + l_pad / 2 + 10); //right point of the pad
		if (block_endx - f >= pad_speed)
		{
			pad_centerx += pad_speed;
			if (ballstate == 0) ball_centerx += pad_speed;
		}
		else if (block_endx - f> 0 && block_endx - f < pad_speed)
		{
			pad_centerx += block_endx - f;
			if (ballstate == 0) ball_centerx += block_endx - f;
		}
	}
}


int main()
{
	level_blocks();
	iSetTimer(1, ballmove);
	iSetTimer(15000, isPowerFunc);
	iSetTimer(1, PowerMove);
	iInitialize(windowx, windowy, "DX BALL");
	return 0;
}

