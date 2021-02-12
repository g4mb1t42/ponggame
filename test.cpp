#include <iostream>
#include <windows.h>
using namespace std;
int genislik = 30;
int yukseklik = 20;
bool oyuncu = false;
bool yukari = false;
bool sekme = false;
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
class Ekran
{
public:
	Ekran(int x, int y) {
		ShowConsoleCursor(false);
		screenx = x;
		screeny = y;
		for (int i = 0; i < screeny; i++)
		{
			for (int j = 0; j < screenx; j++)
			{
				if (j == 0)
				{
					screen[j][i] = 'I';
				}
				else if (i == 0 || i == screeny - 1)
				{
					screen[j][i] = '-';
				}
				else
				{
					screen[j][i] = ' ';
				}
			}
			cout << endl;
		}
	}
	void addChar(int x, int y, char c)
	{
		if (x != 0 && y != 0 && y != screeny - 1 )
		{
			screen[x][y] = c;
		}
	}
	void moveChar(int x, int y, char c, int r, int l, int pospx, int pospy)
	{
		if (x != 0  && y != 0 && y != screeny - 1 && x + r != 0  && y + l != screeny - 1 && y + l != 0 && oyuncu == false)
		{
			screen[x][y] = ' ';
			screen[x + r][y + l] = c;
		}
		else if (x != screenx - 1 && x + r != screenx - 1 && oyuncu == false)
		{
			if (sekme == true)
			{
				screen[pospx + 1][pospy] = ' ';
				screen[pospx + 1][pospy + 1] = ' ';
				screen[pospx + 1][pospy - 1] = ' ';
			}
			screen[x][y] = ' ';
			screen[x + r][y + l] = c;
		}
		else
		{
		
			if (yukari == false && y != 1)
			{
				screen[x][y - 2] = ' ';
				screen[x][y + 1] = c;
				screen[x][y] = c;
				screen[x][y - 1] = c;
			}
			else if(yukari == true && y != screeny - 1)
			{
				screen[x][y + 2] = ' ';
				screen[x][y - 1] = c;
				screen[x][y] = c;
				screen[x][y + 1] = c;
			}
			
		}
	}
	void drawScreen()
	{
		system("cls");
		for (int i = 0; i < screeny; i++)
		{
			for (int j = 0; j < screenx; j++)
			{
				cout << screen[j][i] << ' ';
			}
			cout << endl;
		}
	}
private:
	char screen[100][100];
	int screenx;
	int screeny;

};
int main()
{
	Ekran ekran(genislik, yukseklik);
	ekran.addChar(1, 1, 'o');
	ekran.addChar(genislik - 1, yukseklik / 2, '|');
	int posx = 1;
	int posy = 1;
	int pospx = genislik - 1;
	int pospy = yukseklik / 2;
	int yatay = 1;
	int dusey = 1;
	while (true)
	{
		sekme = false;
		oyuncu = false;
		ekran.moveChar(posx, posy, 'o', yatay, dusey, pospx, pospy);
		posx = posx + yatay;
		posy = posy + dusey;
		if (pospy == yukseklik)
		{
			pospy == yukseklik - 1;
		}
		if (pospy == 0)
		{
			pospy == 1;
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{

				yukari = false;
				oyuncu = true;
				ekran.moveChar(pospx, pospy, '|', yatay, dusey, pospx, pospy);
				pospy++;
	
		}
		if (GetAsyncKeyState(VK_UP) < 0)
		{
	
				yukari = true;
				oyuncu = true;
				ekran.moveChar(pospx, pospy, '|', yatay, dusey, pospx , pospy);
				pospy--;

		
		}
		if(posx == 1 && yatay == -1){
		     yatay = yatay * -1;
		}
		if(posx == genislik - 1 && yatay == 1)
		{
			if((posx == pospx) && (posy == pospy || posy == pospy + 1 || posy == pospy - 1))
			{
				yatay = yatay * -1;
				pospx == yukseklik - 2;
				sekme = true;
				ekran.moveChar(posx, posy, 'o', yatay, dusey, pospx, pospy);

			}
			else
			{
				system("cls");
				cout << "Kaybettin \n";
				break;
			}
			
			
		}
		if ((posy == 1 && dusey == -1) || (posy == yukseklik - 2 && dusey == 1)) 
		{
			dusey = dusey * -1;
		}
		ekran.drawScreen();
		Sleep(002);
	}
	system("pause");
	return 0;
}