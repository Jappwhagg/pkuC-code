#include<iostream>
#include<time.h>
#include<Windows.h>

using namespace std;

int value[9][9]{ 0 };
bool unchangable[9][9]{ 0 };

void sort(int);
void backsort(int);
bool Check(int, int, int);
void Print(void);

void backsort(int n)
{
	int x = n / 9;
	int y = n % 9;
	for (int i = y + 1;i < 9;i++)
	{
		if (unchangable[x][i] == false)value[x][i] = 0;
	}
	for (int i = x + 1;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			if (unchangable[i][j] == false)value[i][j] = 0;
		}
	}
	if (unchangable[x][y] == true)
	{
		backsort(n - 1);
		return;
	}
	int flag = 0;
	for (int i = value[x][y] + 1;i <= 9;i++)
	{
		if (Check(x, y, i))
		{
			flag = 1;
			value[x][y] = i;
			break;
		}
	}
	if (flag == 0)
	{
		backsort(n - 1);
		return;
	}
	else
	{
		sort(n + 1);
		return;
	}
}

void sort(int n)
{
	if (n > 80)return;
	
	int x = n / 9;
	int y = n % 9;
	if (unchangable[x][y] == true)
	{
		sort(n + 1);
		return;
	}
	int flag = 0;
	for (int i = 1;i <= 9;i++)
	{
		if (Check(x, y, i))
		{
			flag = 1;
			value[x][y] = i;
			break;
		}
	}
	if (flag == 0)
	{
		backsort(n - 1);
		return;
	}
	else
	{
		sort(n + 1);
		return;
	}
}

bool Check(int x, int y, int v)
{
	for (int i = 0;i < 9;i++)
	{
		if (y != i)
		{
			if (value[x][i] == v)return false;
		}
	}
	for (int i = 0;i < 9;i++)
	{
		if (x != i)
		{
			if (value[i][y] == v)return false;
		}
	}
	int X = x / 3;
	int Y = y / 3;
	for (int i = X * 3;i < X * 3 + 3;i++)
	{
		for (int j = Y * 3;j < Y * 3 + 3;j++)
		{
			if (i != x || j != y)
			{
				if (value[i][j] == v)return false;
			}
		}
	}
	return true;
}

void Print()
{
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			if (j % 3 == 0) cout << ' ';
			if (j < 8 && j % 3 != 2) cout << value[i][j] << ' ';
			else cout << value[i][j];
			if (j % 3 == 2 && j != 8) cout << "│";
		}
		if (i % 3 == 2 && i != 8)
		{
			cout << endl;
			cout << "──────┼──────┼──────";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	clock_t start, end;
begin:
	memset(unchangable, false, sizeof(unchangable));
	memset(value, 0, sizeof(value));
	cout << "请输入要解的数独：" << endl;
	cout << "输入请形如下例：" << endl;
	cout << "────────────────" << endl;
	cout << "8 0 0 0 0 0 0 0 0\n0 0 3 6 0 0 0 0 0\n0 7 0 0 9 0 2 0 0\n0 5 0 0 0 7 0 0 0\n0 0 0 0 4 5 7 0 0\n0 0 0 1 0 0 0 3 0\n0 0 1 0 0 0 0 6 8\n0 0 8 5 0 0 0 1 0\n0 9 0 0 0 0 4 0 0";
	cout << endl;
	cout << "────────────────" << endl;
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			cin >> value[i][j];
			if (value[i][j] != 0)
			{
				unchangable[i][j] = true;
			}
		}
	}
	start = clock();
	cout << endl;
	sort(0);
	Print();
	end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC;
	cout << "用时：" << time << 's' << endl;
	cout << "────────────────" << endl;
	cout << "输入1再解一个，输入0结束程序：" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)goto begin;
	return 0;
}