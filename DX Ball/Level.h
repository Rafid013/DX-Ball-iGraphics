#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define row 12
#define column 12
#define windowx 1350
#define windowy 760
#define block_starty ((windowy/2))
#define block_startx (200)
#define block_endx (windowx - block_startx)
#define pad_starty 10
#define pad_endy 25
#define pad_centery ((pad_starty + pad_endy) / 2)
#define PI 3.14159265
#define SWAP(a,b) {\
		a = a ^ b;\
		b = a ^ b;\
		a = a ^ b;\
}
#define boundary_w 50
#define START_PAGE_STARTX 100 //
#define START_PAGE_STARTY 100 //  //start page bars
#define START_PAGE_LENGTH 300 //
#define START_PAGE_HEIGHT 100 //



void DrawBlocks(); void ball_reflect(); void ballmove(); void level2(); void level1_blocks(); void level_blocks();
void Draw_Ball(int, int, int); void Draw_Pad(int, int, int); void Boundary(); void level1(); void Break_Blocks();
void level_clear(); void level2_blocks(); void level3_blocks(); void level3(); void level4_blocks(); void level4();
void level5_blocks(); void level5(); void level(); int level_check(); void start_page(); void calltime();
void quit_bar(); void high_scores(); void help(); void show_score(); void ShowPower(int); void inputHOF();
void isPowerFunc(); int PowerCaught(); void PowerMove(); void power_call(); void draw_life(); void interval();
void updateHOF(); void inputPage(); void showHOF(); void credit(); 

double pad_centerx = (windowx / 2);
double l_pad = 150; //length of pad
double radius = 9.9;
double ball_centerx = pad_centerx;
double ball_centery = pad_endy + radius;
double Second;
int ballstate = 0; //ball moves or not
double ball_angle;
double dx, dy; //speed of the ball
int pad_speed = 35;
int score;
const double h = (((windowy / 2) - 80) / row); // //height & width of blocks and column
const double w = ((windowx - 2 * block_startx) / column); //
int page_no, quit_bar_show;
int level_called; //whether the level was called
int power, life = 3;
int thru_block, fireball, ball_magnet;
double powx, powy;
int isPower, showpower;
double pow_speed = 5; //speed of the power blocks
int TextInput;
char NameInput[20];
double NameStartx, NameStarty;
int paused, update, won;
int brick_break_sound;
int dynamite;
int play_intro;

typedef struct 
{
	double bottomleftx;
	double bottomlefty;
	double toprightx;
	double toprighty;
} vertex;

typedef struct
{
	int red;
	int green;
	int blue;
} colour;

typedef struct
{
	int block_pos; //for determining which blocks to draw
	vertex point;
	colour color;
} block;

block blocks[row][column];

typedef struct
{
	int score;
	char name[20];
} HOF;

HOF hof[11];


int cmp(const void* a, const void* b)
{
	int c = ((HOF*)a) -> score;
	int d = ((HOF*)b) -> score;
	return d - c;
}

void inputHOF()
{
	int i = 0;
	FILE *fp = NULL;
	fp = fopen("Hof.txt", "r");
	while(fscanf(fp, "%s %d", hof[i].name, &hof[i].score) != EOF) ++i;
	fclose(fp);
}

void updateHOF()
{
	int i;
	hof[10].score = score;
	strcpy(hof[10].name, NameInput);
	qsort(hof, 11, sizeof(HOF), cmp);
		FILE *fp;
	fp = fopen("Hof.txt", "w");
	for (i = 0; i < 10; i++)
	{
		fprintf(fp, "%s %d\n", hof[i].name, hof[i].score);
	}
	fclose(fp);
	for (i = 0; i < 20; ++i)
		NameInput[i] = '\0';
	update = 0;
	score = 0;
}

void showHOF()
{
	int i;
	char num[50];
	char c[10];
	NameStartx = 375;
	NameStarty = windowy - 209;
	for (i = 0; i < 10; i++)
	{
		iSetColor(128, 128, 128);
		sprintf(c, "%d.", i + 1);
		iText(NameStartx, NameStarty, c);
		iText(NameStartx + 30, NameStarty, hof[i].name);
		sprintf(num, "%06d", hof[i].score);
		iText(NameStartx + 350, NameStarty, num);
		NameStarty -= 30;
	}
}


void level1_blocks()
{
	int i, j, red, green, blue;
	red = 255;
	green = 0;
	blue = 0;
	for (i = 0; i < row; ++i)
	{
		SWAP(red, blue);
		SWAP(red, green);
		for (j = 0; j < column; ++j)
		{
			if (i != 0 && j != 0 && i != (row - 1) && j != (column - 1))
			{
				blocks[i][j].block_pos = 1;
				blocks[i][j].color.red = red;
				blocks[i][j].color.green = green;
				blocks[i][j].color.blue = blue;
			}
			SWAP(red, blue);
			SWAP(red, green);
		}
	}
}

void level_blocks()
{
	int i, j;
	double b_l_x, b_l_y;
	b_l_x = block_startx;
	b_l_y = block_starty;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < column; ++j)
		{
			blocks[i][j].point.bottomleftx = b_l_x;
			blocks[i][j].point.bottomlefty = b_l_y;
			blocks[i][j].point.toprightx = b_l_x + w;
			blocks[i][j].point.toprighty = b_l_y + h;
			b_l_x += w;
		}
		b_l_y += h;
		b_l_x = block_startx;
	}
}

void level_clear()
{
	int i, j;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < column; ++j)
		{
			blocks[i][j].block_pos = 0;
			blocks[i][j].color.red = 0;
			blocks[i][j].color.green = 0;
			blocks[i][j].color.blue = 0;
		}
	}
}


void level2_blocks()
{
	int i, j;
	int red = 0, green = 0, blue = 255;
	int a = row - 1;
	int b = column - 1;
	for (j = 0; j < column; ++j)
	{
		blocks[0][j].block_pos = 1;
		blocks[0][j].color.red = red;
		blocks[0][j].color.green = green;
		blocks[0][j].color.blue = blue;
		blocks[a][j].block_pos = 1;
		blocks[a][j].color.red = red;
		blocks[a][j].color.green = blue;
		blocks[a][j].color.blue = green;
		SWAP(green, blue);
	}
	for (i = 1; i < row; ++i)
	{
		blocks[i][0].block_pos = 1;
		blocks[i][0].color.red = red;
		blocks[i][0].color.green = blue;
		blocks[i][0].color.blue = green;
		blocks[i][b].block_pos = 1;
		blocks[i][b].color.red = red;
		blocks[i][b].color.green = green;
		blocks[i][b].color.blue = blue;
		SWAP(green, blue);
	}
	a = a - 1;
	for (j = 1; j < b; ++j)
	{
		blocks[1][j].block_pos = 2;
		blocks[a][j].block_pos = 2;
	}
	a = row - 3;
	b = column - 5;
	int c = b + 1;
	for (i = 3; i < a; ++i)
	{
		blocks[i][3].block_pos = 1;
		blocks[i][3].color.red = 153;
		
		blocks[i][4].block_pos = 1;
		blocks[i][4].color.red = 153;
		
		blocks[i][b].block_pos = 1;
		blocks[i][b].color.red = 153;
		
		blocks[i][c].block_pos = 1;
		blocks[i][c].color.red = 153;
		
	}
}

void level1()
{
	iShowBMP(0, 0, "Background1.bmp");
	DrawBlocks();
	Draw_Pad(255, 255, 255);
	Boundary();
	if(!fireball)
	Draw_Ball(153, 51, 255);
	else Draw_Ball(255,127,39);

}

void level2()
{
	iShowBMP(0, 0, "Background2.bmp");
	DrawBlocks();
	Draw_Pad(255, 255, 255);
	Boundary();
	if(!fireball)
	Draw_Ball(153, 51, 255);
	else Draw_Ball(255,127,39);
}


void level4_blocks()
{
	int i;
	blocks[row - 6][column - 1].block_pos = blocks[row - 6][0].block_pos = 3;
	blocks[row - 6][column - 1].color.red = blocks[row - 6][0].color.red = 255;
	blocks[row - 6][column - 1].color.green = blocks[row - 6][0].color.green = 100;
	for (i = row - 5; i > row - 10; --i)
	{
		blocks[i][column - 2].block_pos = blocks[i][1].block_pos = 3;
		blocks[i][column - 2].color.red = blocks[i][1].color.red = 255;
		blocks[i][column - 2].color.green = blocks[i][1].color.green = 100;
	}
	for (i = 4; i < row; ++i)
	{
		blocks[i][column - 4].block_pos = blocks[i][3].block_pos = 3;
		blocks[i][column - 4].color.red = blocks[i][3].color.red = 200;
	}
	for (i = 3; i < row - 1; ++i)
	{
		blocks[i][column - 5].block_pos = blocks[i][4].block_pos = 1;
		if (i == 9) blocks[i][column - 5].color.blue = blocks[i][4].color.blue = 255;
		else if (i == 8)
		{
			blocks[i][column - 5].color.red = blocks[i][4].color.red = 51;
			blocks[i][column - 5].color.green = blocks[i][4].color.green = 153;
			blocks[i][column - 5].color.blue = blocks[i][4].color.blue = 255;
		}
		else if (i == 6 || i == 5 || i == 4)
		{
			blocks[i][column - 5].color.red = blocks[i][4].color.red = 128;
			blocks[i][column - 5].color.green = blocks[i][4].color.green = 128;
			blocks[i][column - 5].color.blue = blocks[i][4].color.blue = 128;
		}
		else blocks[i][column - 5].color.red = blocks[i][4].color.red = 150;
	}
	for (i = 2; i < row; ++i)
	{
		blocks[i][column - 6].block_pos = blocks[i][5].block_pos = 1;
		if (!(i == 3 || i == 4 || i == 5 || i == row - 1 || i == row - 2 || i == row - 3))
		{
			blocks[i][column - 6].color.red = blocks[i][5].color.red = 128;
			blocks[i][column - 6].color.green = blocks[i][5].color.green = 128;
			blocks[i][column - 6].color.blue = blocks[i][5].color.blue = 128;
		}
		else blocks[i][column - 6].color.red = blocks[i][5].color.red = 120;
	}
}


void level4()
{
	iShowBMP(0, 0, "Background4.bmp");
	DrawBlocks();
	Draw_Pad(255, 255, 255);
	Boundary();
	if(!fireball)
	Draw_Ball(153, 51, 255);
	else Draw_Ball(255,127,39);
}

void level5_blocks()
{
	int i, j, a = column - 6, b, c, d;
	for (i = 0; i < 2; i++)
	{
		for (j = 5; j <= a; j++)
		{
			blocks[i][j].block_pos = 4;
			blocks[i][j].color.red = 26;
			blocks[i][j].color.blue = 255;
		}
	}
	a = column - 1;
	b = column - 3;
	c = column - 5;
	d = column - 6;
	for (i = 2; i < 5; i++)
	{
		for (j = 1; j <= a; j++)
		{
			if (j == 2 || j == b)
			{
				blocks[i][j].block_pos = 4;
				blocks[i][j].color.red = 160; //color of gun
				blocks[i][j].color.green = 160;
				blocks[i][j].color.blue = 160;
			}
			else if (j == 4 || j == c)
			{
				blocks[i][j].block_pos = 4;
				blocks[i][j].color.red = 26;  //color of outer surface
				blocks[i][j].color.blue = 255;
			}
			else if (j == 5 || j == d)
			{
				blocks[i][j].block_pos = 1;
				blocks[i][j].color.red = 153; //color of inner surface
				blocks[i][j].color.green = 51;
				blocks[i][j].color.blue = 255;
			}
		}
	}

	a = 3;
	b = column - 4;
	for (i = 5; i < row - 3; i++)
	{
		for (j = a; j <= b; j++)
		{
			if (j == a || j == b)
			{
				blocks[i][j].block_pos = 4;
				blocks[i][j].color.red = 26;
				blocks[i][j].color.blue = 255;
			}
			else
			{
				blocks[i][j].block_pos = 1;
				blocks[i][j].color.red = 153;
				blocks[i][j].color.green = 51;
				blocks[i][j].color.blue = 255;
			}

		}
		a--;
		b++;
	}
	blocks[5][column - 3].block_pos = blocks[5][2].block_pos = 4;
	blocks[5][column - 3].color.red = blocks[5][2].color.red = 160; //color of gun
	blocks[5][column - 3].color.green = blocks[5][2].color.green = 160;
	blocks[5][column - 3].color.blue = blocks[5][2].color.blue = 160;
	a = 3;
	b = column - 4;
	for (j = a; j <= b; j++)
	{
		blocks[i][j].block_pos = 1;
		blocks[i][j].color.red = 153; //color of inner surface
		blocks[i][j].color.green = 51;
		blocks[i][j].color.blue = 255;
	}
	a = 4; 
	b = column - 5;
	c = row - 2;
	for (j = a; j <= b; j++)
	{
		int _c = c + 1;
		blocks[c][j].block_pos = 1;
		blocks[c][j].color.red = 255; //color of inner engine
		blocks[c][j].color.green = 128;
		blocks[_c][j].block_pos = 1;
		blocks[_c][j].color.red = 255; //color of inner engine
		blocks[_c][j].color.green = 128;
	}
}

void level5()
{
	iShowBMP(0, 0, "Background5.bmp");
	DrawBlocks();
	Draw_Pad(255, 255, 255);
	Boundary();
	if(!fireball)
	Draw_Ball(153, 51, 255);
	else Draw_Ball(255,127,39);
}

void level3()
{
	iShowBMP(0, 0, "Background3.bmp");
	DrawBlocks();
	Draw_Pad(255, 255, 255);
	Boundary();
	if(!fireball)
	Draw_Ball(153, 51, 255);
	else Draw_Ball(255,127,39);
}


void interval()
{
	iShowBMP(0, 0, "LevelUp.bmp");
}


int level_check()
{
	int i, j;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < column; ++j)
		{
			if (blocks[i][j].block_pos > 0) return 0;
		}
	}
	return 1;
}

void level()
{
	if (page_no == 0)
	{
		if(!play_intro)
		{
			PlaySound("POL-treasure-castle-short.wav",NULL,SND_ASYNC);
			play_intro=1;
		}
		start_page();
		if (quit_bar_show) quit_bar();
	}
	else if (page_no == 1)
	{
		if (!level_called)
		{
			level1_blocks(); //so that it doesn't draw the same blocks after breaking
			level_called = 1;
			won = 0;
		}
		level1();
		show_score();
		if (level_check())
		{
			showpower = 0;
			level_called = 0;
			l_pad = 150;
			thru_block = 0;
			fireball = 0;
			ball_magnet = 0;
			page_no = -3;
			level_clear();
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
			ballstate = 0;
			score += 100;
		}
		if (quit_bar_show) quit_bar();
	}
	else if (page_no == 2)
	{
		if (!level_called)
		{
			level2_blocks();
			level_called = 1;
		}
		level2();
		show_score();
		if (level_check())
		{
			showpower = 0;
			level_called = 0;
			l_pad = 150;
			thru_block = 0;
			fireball = 0;
			ball_magnet = 0;
			page_no = -4;
			level_clear();
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
			ballstate = 0;
			score += 200;
		}
		if (quit_bar_show) quit_bar();
	}
	else if (page_no == 3)
	{
		if (!level_called)
		{
			level3_blocks();
			level_called = 1;
		}
		if (quit_bar_show) quit_bar();
		level3();
		show_score();
		if (level_check())
		{
			showpower = 0;
			level_called = 0;
			l_pad = 150;
			thru_block = 0;
			fireball = 0;
			ball_magnet = 0;
			page_no = -5;
			level_clear();
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
			ballstate = 0;
			score += 300;
		}
		if (quit_bar_show) quit_bar();
	}
	else if (page_no == 4)
	{
		if (!level_called)
		{
			level4_blocks();
			level_called = 1;
		}
		level4();
		show_score();
		if (level_check())
		{
			showpower = 0;
			level_called = 0;
			l_pad = 150;
			thru_block = 0;
			fireball = 0;
			ball_magnet = 0;
			page_no = -6;
			level_clear();
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
			ballstate = 0;
			score += 400;
		}
		if (quit_bar_show) quit_bar();
	}
	else if (page_no == 5)
	{
		if (!level_called)
		{
			level5_blocks();
			level_called = 1;
		}
		level5();
		show_score();
		if (level_check())
		{
			PlaySound("Win.wav",NULL,SND_ASYNC);
			showpower = 0;
			level_called = 0;
			l_pad = 150;
			thru_block = 0;
			fireball = 0;
			ball_magnet = 0;
			score += 500;
			won = 1;
			page_no = -7;
			TextInput = 1;
			level_clear();
			pad_centerx = (windowx / 2);
			ball_centerx = pad_centerx;
			ball_centery = pad_endy + radius;
			ballstate = 0;
		}
		if (quit_bar_show) quit_bar();
	}
	else if (page_no == -1)
	{
		help();
		if(!play_intro)
		{
			PlaySound("POL-treasure-castle-short.wav",NULL,SND_ASYNC);
			play_intro=1;
		}
	}
	else if (page_no == -2)
	{
		high_scores();
		if(!play_intro)
		{
			PlaySound("POL-treasure-castle-short.wav",NULL,SND_ASYNC);
			play_intro=1;
		}
	}
	else if (page_no == -7)
	{
		inputPage();
	}
	else if(page_no == -8)
	{
		credit();
		if(!play_intro)
		{
			PlaySound("POL-treasure-castle-short.wav",NULL,SND_ASYNC);
			play_intro=1;
		}
	}
	else interval();
}

void level3_blocks()
{
	int i, j, a, b, c, d;
	i = row - 1;
	for (j = 0; j < column; ++j)
	{
		if ((j < 5 && !(j % 2)) || (j > 6 && j % 2))
		{
			blocks[0][j].block_pos = blocks[i][j].block_pos = 3;
			blocks[0][j].color.red = blocks[i][j].color.red = 255;
			blocks[0][j].color.green = blocks[i][j].color.green = 153;
			blocks[0][j].color.blue = blocks[i][j].color.blue = 51; //color of visible boundary
		}
		else blocks[0][j].block_pos = blocks[i][j].block_pos = 2;
	}
	j = column - 1;
	a = row - 2;
	for (i = 2; i < a; i++)
	{
		if ((i < 5 && !(i % 2)) || (i > 6 && i % 2))
		{
			blocks[i][0].block_pos = blocks[i][j].block_pos = 3;
			blocks[i][0].color.red = blocks[i][j].color.red = 255;
			blocks[i][0].color.green = blocks[i][j].color.green = 153;
			blocks[i][0].color.blue = blocks[i][j].color.blue = 51; //color of visible boundary
		}
		else blocks[i][j].block_pos = blocks[i][0].block_pos = 2;
	}
	i = row - 3;
	a = column - 2;
	b = column - 4;
	c = b + 1;
	d = b - 1;
	for (j = 2; j < a; j++)
	{
		blocks[2][j].block_pos = blocks[i][j].block_pos = 1;
		if (j == 2 || j == 3 || j == b || j == c)
		{
			blocks[2][j].color.red = blocks[i][j].color.red = 255;
			blocks[2][j].color.green = blocks[i][j].color.green = 255;
		}
		else if (j == 4 || j == d)
		{
			blocks[2][j].color.red = blocks[i][j].color.red = 76;
			blocks[2][j].color.blue = blocks[i][j].color.blue = 153;
		}
		else
		{
			blocks[2][j].color.red = blocks[i][j].color.red = 255;
			blocks[2][j].color.green = blocks[i][j].color.green = 128;
		}
	}
	i = row - 4;
	for (j = 2; j < a; j++)
	{
		blocks[3][j].block_pos = blocks[i][j].block_pos = 1;
		if (j == 2 || j == c)
		{
			blocks[3][j].color.red = blocks[i][j].color.red = 255;
			blocks[3][j].color.green = blocks[i][j].color.green = 255;
		}
		else if (j == 3 || j == b)
		{
			blocks[3][j].color.red = blocks[i][j].color.red = 76;
			blocks[3][j].color.blue = blocks[i][j].color.blue = 153;
		}
		else if (j == 4 || j == d)
		{
			blocks[3][j].color.red = blocks[i][j].color.red = 255;
			blocks[3][j].color.green = blocks[i][j].color.green = 128;
		}
		else
		{
			blocks[3][j].color.green = blocks[i][j].color.green = 102;
			blocks[3][j].color.blue = blocks[i][j].color.blue = 204;
		}
	}
	i = row - 5;
	for (j = 2; j < a; j++)
	{
		blocks[4][j].block_pos = blocks[i][j].block_pos = 1;
		if (j == 2 || j == c)
		{
			blocks[4][j].color.red = blocks[i][j].color.red = 76;
			blocks[4][j].color.blue = blocks[i][j].color.blue = 153;
		}
		else if (j == 3 || j == b)
		{
			blocks[4][j].color.red = blocks[i][j].color.red = 255;
			blocks[4][j].color.green = blocks[i][j].color.green = 128;
		}
		else if (j == 4 || j == d)
		{
			blocks[4][j].color.green = blocks[i][j].color.green = 102;
			blocks[4][j].color.blue = blocks[i][j].color.blue = 204;
		}
		else
		{
			blocks[4][j].color.red = blocks[i][j].color.red = 255;
			blocks[4][j].color.blue = blocks[i][j].color.blue = 127;
		}
	}
	i = row - 6;
	for (j = 2; j < a; j++)
	{
		blocks[i][j].block_pos = blocks[5][j].block_pos = 1;
		if (j == 2 || j == c)
		{
			blocks[5][j].color.red = blocks[i][j].color.red = 255;
			blocks[5][j].color.green = blocks[i][j].color.green = 128;
		}
		else if (j == 3 || j == b)
		{
			blocks[5][j].color.green = blocks[i][j].color.green = 102;
			blocks[5][j].color.blue = blocks[i][j].color.blue = 204;
		}
		else if (j == 4 || j == d)
		{
			blocks[5][j].color.red = blocks[i][j].color.red  = 255;
			blocks[5][j].color.blue = blocks[i][j].color.blue = 127;
		}
		else
		{
			blocks[5][j].color.red = blocks[i][j].color.red = 102;
			blocks[5][j].color.blue = blocks[i][j].color.blue = 102;
		}
	}
}


void start_page()
{
	int a = windowx - START_PAGE_STARTX - START_PAGE_LENGTH;
	int b = windowy - START_PAGE_STARTY - START_PAGE_HEIGHT;
	iShowBMP(0, 0, "STARTPAGE.bmp");
	iShowBMP2(START_PAGE_STARTX, b, "Play.bmp", 255);
	iShowBMP2(a, START_PAGE_STARTY, "Quit.bmp", 255);
	iShowBMP2(START_PAGE_STARTX+425,b, "CreditMenu.bmp", 255);
	iShowBMP2(a, b, "Instructions.bmp", 255);
	iShowBMP2(START_PAGE_STARTX, START_PAGE_STARTY, "HighScores.bmp", 255);
}


void help()
{
	iShowBMP(0, 0, "Help.bmp");
}

void high_scores()
{
	inputHOF();
	if (update) updateHOF();
	iShowBMP(0, 0, "HighScoresPage.bmp");
	showHOF();
}

void inputPage()
{
	if (won)
	{
		iShowBMP(0, 0, "Winner.bmp");
		iSetColor(0, 255, 0);
		iText(475, 450, "ENTER YOUR NAME");
		iRectangle(475, 380, 400, 30);
		iSetColor(255, 255, 255);
		iText(480, 385, NameInput);
	}
	else
	{
		iShowBMP(0, 0, "GameOver.bmp");
		iSetColor(255, 0, 0);
		iText(475, 180, "ENTER YOUR NAME");
		iRectangle(475, 110, 400, 30);
		iSetColor(255, 255, 255);
		iText(480, 115, NameInput);
	}
	
}
void credit()
{
	iShowBMP(0, 0, "Credit.bmp");
}