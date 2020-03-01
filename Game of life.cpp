#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <iostream>
#include <queue>

using namespace std;

int fx=2450,fy=1250,sx=50,sy=50,w=15,c;
int mx=(fx)/w;
int my=(fy)/w;

void draw_matrix(int x,int y,int w){
	setcolor(RED);
	for(int i=0;i<=x;i++)
		line(sx+w*i,sy,sx+w*i,sy+w*y);
	for(int i=0;i<=y;i++)
		line(sx,sy+w*i,sx+w*x,sy+w*i);
}

main(){
	int mat[mx][my]={0};
	initwindow(fx+100,fy+100);
	draw_matrix(mx,my,w);
	queue<pair<int,int> > life,death;
	for(int i=0;i<mx;i++){
		for(int j=0;j<my;j++){
			if(rand()%100>60){
				mat[i][j]=1;
				setfillstyle(SOLID_FILL, WHITE);
				floodfill(sx+i*w+1,sy+j*w+1,RED);
			} 
		}
	}
	while(true){
		for(int i=1;i<mx-1;i++){
			for(int j=1;j<my-1;j++){
				c=mat[i-1][j-1]+mat[i-1][j]+mat[i-1][j+1]+mat[i][j+1]+mat[i+1][j+1]+mat[i+1][j]+mat[i+1][j-1]+mat[i][j-1];
				if(mat[i][j]==0 && c==3){
					life.push({i,j});
				}
				if(mat[i][j]==1 && (c>=4 || c<=1)){
					death.push({i,j});
				}
			}
		}
		setfillstyle(SOLID_FILL, WHITE);
		while(!life.empty()){
			mat[life.front().first][life.front().second]=1;
			floodfill(sx+life.front().first*w+1,sy+life.front().second*w+1,RED);
			life.pop();
		}
		setfillstyle(SOLID_FILL, BLACK);
		while(!death.empty()){
			mat[death.front().first][death.front().second]=0;
			floodfill(sx+death.front().first*w+1,sy+death.front().second*w+1,RED);
			death.pop();
		}
		//_sleep(20);
	}
	getch();
	closegraph();
}
