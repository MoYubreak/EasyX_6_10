#include<graphics.h>
#include<iostream>
using namespace std;

char arr[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'}
};

char pawn = 'X';

void DrawLine()
{
	for (int i = 0; i < 3; i++)
	{
		line(i * 300, 0, i * 300, 900);
		line(0, i * 300, 900, i * 300);
	}
}

void DrawPawn()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (arr[i][j] == 'X')
			{
				line(j * 300, i * 300, (j + 1) * 300, (i + 1) * 300);
				line((j + 1) * 300, i * 300, j * 300, (i + 1) * 300);
			}
			else if(arr[i][j] == 'O')
				circle(j * 300 + 150, i * 300 + 150, 100);
		}
	}
}

void text()
{
	TCHAR str[64];
	_stprintf_s(str, _T("持棋 %c"), pawn);
	settextcolor(RGB(165, 42, 42));
	outtextxy(5, 5, str);
}

bool GameWin(const char& c)
{
	if (arr[0][0] == c && arr[0][1] == c && arr[0][2] == c)
		return true;
	else if (arr[1][0] == c && arr[1][1] == c && arr[1][2] == c)
		return true;
	else if (arr[2][0] == c && arr[2][1] == c && arr[2][2] == c)
		return true;
	else if (arr[0][0] == c && arr[1][0] == c && arr[2][0] == c)
		return true;
	else if (arr[0][1] == c && arr[1][1] == c && arr[2][1] == c)
		return true;
	else if (arr[0][2] == c && arr[1][2] == c && arr[2][2] == c)
		return true;
	else if (arr[0][0] == c && arr[1][1] == c && arr[2][2] == c)
		return true;
	else if (arr[0][2] == c && arr[1][1] == c && arr[2][0] == c)
		return true;
	return false;
}

bool GameDraw()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (arr[i][j] == '-')
				return false;
		}
	}
	return true;
}

int main()
{
	//初始化
	initgraph(900,900);
	bool game = true;
	ExMessage msg = ExMessage();

	BeginBatchDraw();
	while (game)
	{
		//控制输入
		while (peekmessage(&msg))
		{
			//getmessage(&msg, EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN)
			{

				int index_i = msg.y / 300;
				int index_j = msg.x / 300;
				if (arr[index_i][index_j] == '-')
					arr[index_i][index_j] = pawn;
				if (pawn == 'X')
					pawn = 'O';
				else if (pawn == 'O')
					pawn = 'X';
			}
		}
		DrawLine();
		text();
		DrawPawn();
		FlushBatchDraw();
		if (GameWin('X'))
		{
			MessageBox(GetHWnd(), _T("持X者胜利"), _T("结算"), MB_OK);
			game = false;
		}
		else if (GameWin('O'))
		{
			MessageBox(GetHWnd(), _T("持O者失败"), _T("结算"), MB_OK);
			game = false;
		}
		else if (GameDraw())
		{
			MessageBox(GetHWnd(), _T("平局"), _T("结算"), MB_OK);
			game = false;
		}
	}
	
	EndBatchDraw();
	return 0;
}