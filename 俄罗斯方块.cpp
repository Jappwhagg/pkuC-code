#include<iostream>
#include<time.h>
#include<random>
#include<conio.h>
#include<Windows.h>
#include<cstring>
#include<iomanip>

struct Point {
	int x;
	int y;
};

const int BW(10);
const int BH(20);
const int HomeX(3);
const int HomeY(0);
bool Board[BW][BH];
int sharp;
int x, y;

Point Form[19][4]{
	//条形
	{{0,0},{1,0},{2,0},{3,0}},
	{{0,0},{0,1},{0,2},{0,3}},
	//方形
	{{0,0},{0,1},{1,0},{1,1}},
	//L形
	{{0,1},{1,1},{2,1},{2,0}},
	{{0,0},{1,0},{1,1},{1,2}},
	{{0,0},{1,0},{2,0},{0,1}},
	{{0,0},{0,1},{0,2},{1,2}},
	//镜像L形
	{{0,0},{0,1},{1,1},{2,1}},
	{{0,2},{1,0},{1,1},{1,2}},
	{{0,0},{1,0},{2,0},{2,1}},
	{{0,0},{0,1},{0,2},{1,0}},
	//T形
	{{0,1},{1,0},{1,1},{2,1}},
	{{0,1},{1,0},{1,1},{1,2}},
	{{0,1},{1,1},{1,2},{2,1}},
	{{1,0},{1,1},{1,2},{2,1}},
	//Z形
	{{0,0},{1,0},{1,1},{2,1}},
	{{0,1},{0,2},{1,0},{1,1}},
	//镜像Z形
	{{0,1},{1,0},{1,1},{2,0}},
	{{0,0},{0,1},{1,1},{1,2}}
};

using namespace std;

void AddGraph();
void ShowGraph();
void ClearGraph();
void ShowOrClear(bool, const string&);
void FillStr(int X, int Y, const string&);
void LineClear();
void Drop();
bool Drop_CD();
void Left();
bool Left_CD();
void Right();
bool Right_CD();
void Rotate();
bool Rotate_CD(int);
void Initialize();
void Run();
Point TransPosition(Point);

void AddGraph()
{
	sharp = rand() % 19;
	x = HomeX;
	y = HomeY;
	ShowGraph();
}

void ShowGraph()
{
	ShowOrClear(true, "■");
}

void ClearGraph()
{
	ShowOrClear(false, "  ");
}

void ShowOrClear(bool exist, const string& fill)
{
	for (int i = 0;i < 4;i++)
	{
		Point Pixel = TransPosition(Form[sharp][i]);
		if (Board[Pixel.x][Pixel.y] == exist)
		{
			cout << "GAME OVER";
			system("pause");
			Run();
		}
		Board[Pixel.x][Pixel.y] = exist;
		FillStr(Pixel.x, Pixel.y, fill);
	}
}

void FillStr(int X, int Y, const string& fill)
{
	COORD coord;
	coord.X = X * 2 + 2;
	coord.Y = Y + 1;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHandle, coord);
	cout << fill;
}

void FrameFillStr(int X, int Y, const string& fill)
{
	COORD coord;
	coord.X = X * 2;
	coord.Y = Y;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHandle, coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << fill;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void LineClear()
{
	int JudgeY = BH - 1;
	while (JudgeY >= 0)
	{
		int cnt = 0;
		for (int i = 0;i < BW;i++)
		{
			if (Board[i][JudgeY])
			{
				cnt++;
			}
		}
		if (cnt != BW)
		{
			JudgeY--;
		}
		else
		{
			for (int i = 0;i < BW;i++)
			{
				Board[i][JudgeY] = false;
				FillStr(i, JudgeY, "  ");
			}
			for (int j = JudgeY;j >= 0;j--)
			{
				for (int i = BW - 1;i >= 0;i--)
				{
					if (Board[i][j])
					{
						Board[i][j] = false;
						FillStr(i, j, "  ");
						Board[i][j+1] = true;
						FillStr(i, j + 1, "■");
					}
				}
			}
		}
	}
}

void Drop()
{
	if (!Drop_CD())
	{
		ClearGraph();
		y++;
		ShowGraph();
	}
	else
	{
		LineClear();
		AddGraph();
	}
}

bool Drop_CD()
{
	for (int i = 0;i < 4;i++)
	{
		bool Point_CD = true;
		Point Pixel0 = TransPosition(Form[sharp][i]);
		if (Pixel0.y > BH - 2)
		{
			return true;
		}
		for (int j = 0;j < 4;j++)
		{
			Point Pixel1 = TransPosition(Form[sharp][j]);
			if (Pixel0.x == Pixel1.x && Pixel0.y < Pixel1.y)
			{
				Point_CD = false;
				break;
			}
		}
		if (Point_CD && Board[Pixel0.x][Pixel0.y + 1])
		{
			return true;
		}
	}
	return false;
}

void Left()
{
	if (!Left_CD())
	{
		ClearGraph();
		x--;
		ShowGraph();
	}
}

bool Left_CD()
{
	for (int i = 0;i < 4;i++)
	{
		bool Point_CD = true;
		Point Pixel0 = TransPosition(Form[sharp][i]);
		if (Pixel0.x < 1)
		{
			return true;
		}
		for (int j = 0;j < 4;j++)
		{
			Point Pixel1 = TransPosition(Form[sharp][j]);
			if (Pixel0.y == Pixel1.y && Pixel0.x > Pixel1.x)
			{
				Point_CD = false;
				break;
			}
		}
		if (Point_CD && Board[Pixel0.x - 1][Pixel0.y])
		{
			return true;
		}
	}
	return false;
}

void Right()
{
	if (!Right_CD())
	{
		ClearGraph();
		x++;
		ShowGraph();
	}
}

bool Right_CD()
{
	for (int i = 0;i < 4;i++)
	{
		bool Point_CD = true;
		Point Pixel0 = TransPosition(Form[sharp][i]);
		if (Pixel0.x > BW - 2)
		{
			return true;
		}
		for (int j = 0;j < 4;j++)
		{
			Point Pixel1 = TransPosition(Form[sharp][j]);
			if (Pixel0.y == Pixel1.y && Pixel0.x < Pixel1.x)
			{
				Point_CD = false;
				break;
			}
		}
		if (Point_CD && Board[Pixel0.x + 1][Pixel0.y])
		{
			return true;
		}
	}
	return false;
}

void Rotate()
{
	int Nextsharp = sharp;
	if (sharp == 6 || sharp == 10 || sharp == 14)
	{
		Nextsharp -= 3;
	}
	else if (sharp == 1 || sharp == 16 || sharp == 18)
	{
		Nextsharp -= 1;
	}
	else if (sharp == 2)
	{
		Nextsharp = sharp;
	}
	else
	{
		Nextsharp += 1;
	}
	if (!Rotate_CD(Nextsharp))
	{
		ClearGraph();
		sharp = Nextsharp;
		ShowGraph();
	}
}

bool Rotate_CD(int Nextsharp)
{
	for (int i = 0;i < 4;i++)
	{
		bool Point_CD = true;
		Point Pixel0 = TransPosition(Form[Nextsharp][i]);
		if (Pixel0.x<0 || Pixel0.x>BW - 1 || Pixel0.y > BH - 1)
		{
			return true;
		}
		for (int j = 0;j < 4;j++)
		{
			Point Pixel1 = TransPosition(Form[sharp][j]);
			if (Pixel0.x == Pixel1.x && Pixel0.y == Pixel1.y)
			{
				Point_CD = false;
				break;
			}
		}
		if (Point_CD && Board[Pixel0.x][Pixel0.y])
		{
			return true;
		}
	}
	return false;
}

void Initialize()
{
	system("cls");
	for (int i = 0;i < 12;i++)
	{
		FrameFillStr(i, 0, "■");
		FrameFillStr(i, 21, "■");
	}
	for (int i = 1;i < 21;i++)
	{
		FrameFillStr(0, i, "■");
		FrameFillStr(11, i, "■");
	}
	memset(Board, false, sizeof(Board));

	AddGraph();
}

void Run()
{
	Initialize();
	int time = 0;
	while (true)
	{
		Sleep(1);
		if (time++ > 300)
		{
			Drop();
			time = 0;
		}
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				switch (_getch())
				{
				case 72://上键
					Rotate();
					break;
				case 80://下键
					Drop();
					break;
				case 75://左键
					Left();
					break;
				case 77:
					Right();
					break;
				}
			}
			else if (ch == 32)
			{
				system("pause");
			}
		}
	}
}

Point TransPosition(Point p)
{
	return { x + p.x,y + p.y };
}

int main()
{
	srand(int(time(0)));
	Run();
	return 0;
}