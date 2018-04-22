#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <cmath>
#include <algorithm>

using namespace std;

///The graphic interface for the game
void draw(){
    outtextxy(280,30,"BATTLESHIPS");
    outtextxy(140,60,"PLAYER 1");
    outtextxy(440,60,"PLAYER 2");
    int j=250;
    int k=1;
    for(int i=0;i<=250;i+=25)
    {
        line(50,100+i,300,100+i);
        line(350,100+i,600,100+i);
        line(50+i,100,50+i,100+j);
        line(350+i,100,350+i,100+j);
        if(i<=225){
            switch(k){
                case 1: outtextxy(40,104+i,"1"); outtextxy(340,104+i,"1"); outtextxy(60+i,84,"1"); outtextxy(360+i,84,"1"); break;
                case 2: outtextxy(40,104+i,"2"); outtextxy(340,104+i,"2"); outtextxy(60+i,84,"2"); outtextxy(360+i,84,"2"); break;
                case 3: outtextxy(40,104+i,"3"); outtextxy(340,104+i,"3"); outtextxy(60+i,84,"3"); outtextxy(360+i,84,"3"); break;
                case 4: outtextxy(40,104+i,"4"); outtextxy(340,104+i,"4"); outtextxy(60+i,84,"4"); outtextxy(360+i,84,"4"); break;
                case 5: outtextxy(40,104+i,"5"); outtextxy(340,104+i,"5"); outtextxy(60+i,84,"5"); outtextxy(360+i,84,"5"); break;
                case 6: outtextxy(40,104+i,"6"); outtextxy(340,104+i,"6"); outtextxy(60+i,84,"6"); outtextxy(360+i,84,"6"); break;
                case 7: outtextxy(40,104+i,"7"); outtextxy(340,104+i,"7"); outtextxy(60+i,84,"7"); outtextxy(360+i,84,"7"); break;
                case 8: outtextxy(40,104+i,"8"); outtextxy(340,104+i,"8"); outtextxy(60+i,84,"8"); outtextxy(360+i,84,"8"); break;
                case 9: outtextxy(40,104+i,"9"); outtextxy(340,104+i,"9"); outtextxy(60+i,84,"9"); outtextxy(360+i,84,"9"); break;
                case 10: outtextxy(30,104+i,"10"); outtextxy(330,104+i,"10"); outtextxy(56+i,84,"10"); outtextxy(356+i,84,"10"); break;
            }
            k++;
        }
    }
}

///The matrix for each player containing each ship
int matrixp1[11][11] = { { 0 } }, matrixp2[11][11] = { { 0 } };

struct ship {
	int x1=0, x2=0, y1=0, y2=0;
	int size;
};

///Function to get the coordinates for a ship
void takeCoordinates(ship &ship) {
	if (ship.size > 1)
	{
		cout << "Write the coordinates for the ship of size " << ship.size << " ( (x1,y1) , (x2,y2) ) : ";
		cin >> ship.x1 >> ship.y1 >> ship.x2 >> ship.y2;
	}
	else {
		cout << "Write the coordinates for the ship of size " << ship.size << " ( (x1,y1) ) : ";
		cin >> ship.x1 >> ship.y1;
		ship.x2 = ship.x1;
		ship.y2 = ship.y1;
	}
}

///Function to check if the given coordinates are correct ( if they are in the matrix and if they do not overrun other ships )
int checkCoordinates(ship ship, int p) {
	int absx = abs(ship.x1 - ship.x2) + 1;
	int absy = abs(ship.y1 - ship.y2) + 1;
	if ((absx == 1 && absy != ship.size) || (absx == ship.size && absy != 1))
	{
		cout << "The values are incorrect! They do not match the size of the ship! Try again!" << endl;
		return 0;
	}
	if (ship.x1 > 10 || ship.x2 > 10 || ship.y1 > 10 || ship.y2 > 10 || ship.x1 < 0 || ship.x2 < 0 || ship.y1 < 0 || ship.y2 < 0)
	{
		cout << "The values are incorect! They must be greater than 0 and lower than 11! Try again!" << endl;
		return 0;
	}
	int maxx = max(ship.x1, ship.x2);
	int maxy = max(ship.y1, ship.y2);
	int minx = min(ship.x1, ship.x2);
	int miny = min(ship.y1, ship.y2);
	for (int i = minx; i <= maxx; i++)
		for (int j = miny; j <= maxy; j++) {
			if(p==1)
				if (matrixp1[j][i] == 1)
				{
					cout << "There is already a ship! Try again!";
					return 0;
				}
			if (p == 2)
				if (matrixp2[j][i] == 1)
				{
					cout << "There is already a ship! Try again!";
					return 0;
				}
		}
	return 1;
}

///Function to place the ship into the matrix if it has free space
void placeShip(ship ship, int matrix[11][11]) {
	if (ship.size == 1) {
		matrix[ship.y1][ship.x1] = 1;
	}
	else {
		int maxx = max(ship.x1, ship.x2);
		int maxy = max(ship.y1, ship.y2);
		int minx = min(ship.x1, ship.x2);
		int miny = min(ship.y1, ship.y2);
		for (int i = minx; i <= maxx; i++)
			for (int j = miny; j <= maxy; j++)
			{
				matrix[j][i] = 1;
			}
	}
}

///Function that verifies if the matrix of a player has no more ships in it
int checkFinished(int matrix[11][11]) {
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			if (matrix[i][j] == 1)
				return 0;
		}
	}
	return 1;
}

///Functoion that verifies if the bomb hits a ship or not
void checkHit(int x, int y, int matrix[11][11], int p) {
	if (matrix[x][y] == 1)
    {
        ///X PE MATRICE PE DESEN
        if(p==1){
            setcolor(4);
            int y1 = 100;
            y1 += 25*(x-1);
            int x1 = 50;
            x1 += 25*(y-1);
            line(x1, y1, x1+25, y1+25);
            line(x1+25, y1, x1, y1+25);
        }
        else{
            int y1 = 100;
            y1 += 25*(x-1);
            int x1 = 350;
            x1 += 25*(y-1);
            setcolor(4);
            line(x1, y1, x1+25, y1+25);
            line(x1+25, y1, x1, y1+25);
        }
        cout<<"Your bomb hit a ship!"<<endl;
    }
	else if(matrix[x][y]==0)
    {
        ///O PEMATRICE IN DESEN
        if(p==1){
            setcolor(9);
            int y1 = 100;
            y1 += 25*(x-1);
            int x1 = 50;
            x1 += 25*(y-1);
            circle(x1+12.5,y1+12.5,12);
        }
        else{
            int y1 = 100;
            y1 += 25*(x-1);
            int x1 = 350;
            x1 += 25*(y-1);
            setcolor(9);
            circle(x1+12.5,y1+12.5,12);
        }
        cout<<"You missed!"<<endl;
    }
    matrix[x][y]=-1;
}

int main(){
    int gm,gd;
    gd=DETECT;
    initgraph(&gd, &gm,"");
    draw();
    int p=1;
    ///The introduction and validation of data
    ///The matrices are being filled with the ships
    while (true) {
		ship ship;
		cout<<"Welcome to BattleShips!"<<endl;
		cout<<"Player "<<p<<" : "<<endl;
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 0; j < i; j++)
			{
				ship.size = 5 - i;
				takeCoordinates(ship);
				int ok;
				ok = checkCoordinates(ship,p);
				if (ok == 1) {
					if (p == 1)
						placeShip(ship, matrixp1);
					if (p == 2)
						placeShip(ship, matrixp2);
				}
				else j--;
			}
		}
		system("cls");
		p++;
		if (p == 3)
			break;
	}
	p = 1;
	cout<<"Welcome to BattleShips!"<<endl;
	///The game begins
	///Each player takes turns in order to drop a bomb on the other player's map
	while (true) {
		int x, y;
		cout << "Player "<< p <<" has to choose where he wants to drop the bomb!"<<endl;
		cout << "Select the point you want to deploy the bomb (x,y) : ";
		cin >> x >> y;
		if(x>0 && y>0 && x<11 && y<11)
		{
		    if (p == 1)
            {
                if(matrixp2[y][x]== - 1){
                    cout<<"You have already dropped a bomb at that place! Try a different one!"<<endl;
                }
                else{
                    checkHit(y, x, matrixp2, p);
                    p = 2;
                }
            }
            else
            {
                if(matrixp1[y][x]== - 1){
                    cout<<"You have already dropped a bomb at that place! Try a different one!"<<endl;
                }
                else{
                    checkHit(y, x, matrixp1, p);
                    p = 1;
                }
            }
		}
		else{
            cout<<"The values do not match. They have to be greater than and lower than 11!";
		}
        ///The game finishes when one player's map is left out without ships
		if (checkFinished(matrixp1) == 1) {
			cout << "Player 2 has won! Congratulations!";
			break;
		}
		if (checkFinished(matrixp2) == 1) {
			cout << "Player 1 has won! Congratulations!";
			break;
		}
		cout<<endl;
	}
	///Sleep so the graphic will stay 15 more secs on the screen
    Sleep(15000);
    closegraph();
    return 0;
}
