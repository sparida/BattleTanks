//Map Editor for Battle Tanks

#include <allegro.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
BITMAP *bm;
int map[32][24];
int rsf=7; //Random Size Flag
int tchf=1; //Tile Choice Flag, -1-Tank1, -2 -Tank2, 0-Nothing, 1-Solid Barrier Tile, 2-Bomb Tile, 3-Tank1 Flag, 4-Tank2 Flag, 
            //5-Tank1 Base, 6-Tank2 Base, 7-Voretx, 8-Tank Barrier Tile, 9-Horizontal Bomb, 10- Vertical Bomb
int t1ff=1,t2ff=1,t1bf=1,t2bf=1,t1f=1,t2f=1; //Tank 1 & 2 Flag and Base Flags
int tbc[2]={5,2};  //Tank Body Colour
int twc[2]={11,4};  //Tank Wheel Colour
int tww=6;  //Tank Wheel Width
int trc=15; //Tank Turret Colour
char innf[30];
char outf[30];
char finnf[40]="Map Files\\";
char foutf[40]="Map Files\\";
    
void init();
void deinit();
void drawGrid();
void markSquare();
void save();
void refresh();
void rectify(int &,int &);

int main() {
	init();
	drawGrid();

	while (!key[KEY_ESC]) 
    {
          
          vsync();
                       blit(bm,screen,0,0,0,0,SCREEN_W,SCREEN_H);
          markSquare();
		save();
			}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {

	allegro_init();
	set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
	bm=create_bitmap(SCREEN_W,SCREEN_H);
	for(int i=0;i<=31;i++)
{
        for(int j=0;j<=23;j++)
        {
                map[i][j]=0;
        }
              
}
    ifstream i;
    i.open("Data Files\\MSettings.txt",ios::in);
    i>>innf;
    i>>outf;
    strcat(finnf,innf);
    strcat(foutf,outf);
    i.close();
    install_keyboard();
	install_mouse();
	show_mouse(bm);
	set_mouse_range(0,0,640,480);
	/* add other initializations here */
}

void drawGrid()
{
        
     for(int i=0;i<=32;i++)
        {
                line(bm,i*20,0,i*20,480,14);
        }
     for(int i=0;i<=32;i++)
        {
                line(bm,0,i*20,640,i*20,14);
        }  
        
}
          
void deinit() {
	destroy_bitmap(bm);
}
void save()
{
     if(key[KEY_S])
     {
                   ofstream of;
                   of.open(foutf,ios::out);
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       of<<map[i][j]<<"\n";
                      }
                      }
                      of.close();
                      refresh();
                      rest(50);
     }
     else if(key[KEY_O])
     {
                   ifstream inf;
                   inf.open(finnf,ios::in);
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       inf>>map[i][j];
                      }
                      }
                      inf.close();
                      refresh();
                      rest(50);
     }
     
     else if(key[KEY_C])
     {
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       map[i][j]=0;
                      } 
                      }
                      
 
                      refresh();
                      rest(50);
                   }
           
       else if(key[KEY_R])
     {
            int c;
            srand(time(NULL));
            if(rsf<=0)
            rsf=1;             
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       
                       c=rand() % rsf;
                       
                       if(c==0)
                       map[i][j]=1;
                       else
                       map[i][j]=0;
                      } 
                   }
                      clear_keybuf();
                      srand(time(NULL));
                      refresh();
                      rest(30);
     } 
     else if(key[KEY_UP])
     {
          if(rsf>=2)
          rsf--;
          rest(30);
     } 
     else if(key[KEY_DOWN])
     {
          rsf++;
          rest(30);
     }
     else if(key[KEY_T])
     tchf=1;
     else if(key[KEY_B])
     tchf=2;
     else if(key[KEY_H])
     tchf=3;
     else if(key[KEY_J])
     tchf=4;
     else if(key[KEY_K])
     tchf=5;
     else if(key[KEY_L])
     tchf=6;
     else if(key[KEY_V])
     tchf=7;
     else if(key[KEY_Y])
     tchf=8;
     else if(key[KEY_U])
     tchf=9;
     else if(key[KEY_I])
     tchf=10;
     else if(key[KEY_1])
     tchf=-1;
     else if(key[KEY_2])
     tchf=-2;

}
void refresh()
{
     clear_to_color(bm,0);
     drawGrid();
     
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                           int x=10+20*i;
                           int y=10+20*j;
//**************************************************************************************************                           
                       if(map[i][j]==0)
                       {
                                      
                       }
                       else if(map[i][j]==1)
                        {
                            rectfill(bm,x-10,y-10,x+10,y+10,7);
                            rectfill(bm,x-4,y-4,x+4,y+4,8);

                            
                            
                        }
                       else if(map[i][j]==2)
                       {
                            int fg=0;
                            for(int cntr=0;cntr<=10;cntr+=2)
                            {
                            if(fg%2==0)
                            circlefill(bm,x,y,10-cntr,1);
                            else
                            circlefill(bm,x,y,10-cntr,12);
                            
                            fg++;
                            fg=fg%2;
                            }
                            
                       }    
                       else if(map[i][j]==3)
                       {
                            rectfill(bm,x-10,y-10,x+10,y,11);
                            rectfill(bm,x+5,y,x+10,y+10,5);
                       }    
                       else if(map[i][j]==4)
                       {
                            rectfill(bm,x-10,y-10,x+10,y,4);
                            rectfill(bm,x+5,y,x+10,y+10,2);
                       }    
                       else if(map[i][j]==5)
                       { 
                            rect(bm,x-10,y-10,x+10,y+10,11);
                            rect(bm,x-5,y-5,x+5,y+5,5);
                       }    
                       else if(map[i][j]==6)
                       {
                            rect(bm,x-10,y-10,x+10,y+10,4);
                            rect(bm,x-5,y-5,x+5,y+5,2);
                       }    
                        else if(map[i][j]==7)
                       {
                            
                            for(int cntr=0;cntr<=10;cntr+=3)
                            {
                            rect(bm,x-cntr,y-cntr,x+cntr,y+cntr,7);
                            }
                            
                       }
                       else if(map[i][j]==8)
                       {
                            
                            for(int cntr=0;cntr<=10;cntr+=2)
                            {
                            rect(bm,x-cntr,y-cntr,x+cntr,y+cntr,2);
                            }
                            for(int cntr=0;cntr<=10;cntr+=2)
                            {
                            circle(bm,x,y,cntr,2);
                            }
                            
                       }
                       else if(map[i][j]==9)
                       {
                            
                            int points1[6]={x-10,y,x-2,y-10,x-2,y+10};
                            polygon(bm,3,points1,1);
                            int points2[6]={x+10,y,x+2,y-10,x+2,y+10};
                            polygon(bm,3,points2,1);
                            floodfill(bm,x-3,y,1); 
                            floodfill(bm,x+3,y,1);                           
                       }                    
                       else if(map[i][j]==10)
                       {
                            
                            int points1[6]={x,y-10,x-10,y-2,x+10,y-2};
                            polygon(bm,3,points1,1);
                            int points2[6]={x,y+10,x-10,y+2,x+10,y+2};
                            polygon(bm,3,points2,1);
                            floodfill(bm,x,y-3,1); 
                            floodfill(bm,x,y+3,1);                           
                       }                     
                       else if(map[i][j]==-1)
                       {
                            
                            rectfill(bm,x-tww,y-tww,x+tww,y+tww,tbc[0]);
                            rectfill(bm,x-2*tww,y-2*tww,x-tww,y+2*tww,twc[0]);
                            rectfill(bm,x+tww,y-2*tww,x+2*tww,y+2*tww,twc[0]);
                            rectfill(bm,x-1,y-3*tww,x+1,y,trc);                           
                       }                     
                       else if(map[i][j]==-2)
                       {
                            
                            rectfill(bm,x-tww,y-tww,x+tww,y+tww,tbc[1]);
                            rectfill(bm,x-2*tww,y-2*tww,x-tww,y+2*tww,twc[1]);
                            rectfill(bm,x+tww,y-2*tww,x+2*tww,y+2*tww,twc[1]);
                            rectfill(bm,x-1,y-3*tww,x+1,y,trc);                          
                       }                                    
//************************************************************************************************                   
                      } 
                   }
                  
     }

void markSquare()
{
     if(mouse_b & 1)
     {
                int x=mouse_x;
                int y=mouse_y;
                int xi,yj;
                for(int i=0;i<=31;i++)
                {
                        if(x>20*i && x<=20*(i+1))
                        xi=i;
                }
                for(int j=0;j<=23;j++)
                {
                        if(y>20*j && y<=20*(j+1))
                        yj=j;
                }
                rectify(xi,yj);
                if(tchf==0)
                map[xi][yj]=tchf;
                else if(tchf==1 && map[xi][yj]==0)
                map[xi][yj]=tchf;
                else if(tchf==2 && map[xi][yj]==0)
                map[xi][yj]=tchf;
                else if(tchf==7 && map[xi][yj]==0)
                map[xi][yj]=tchf;
                else if(tchf==8 && map[xi][yj]==0)
                map[xi][yj]=tchf;
                else if(tchf==9 && map[xi][yj]==0)
                map[xi][yj]=tchf;
                else if(tchf==10 && map[xi][yj]==0)
                map[xi][yj]=tchf;

                else if(tchf==3 && t1ff==1 && map[xi][yj]==0)
                {
                     map[xi][yj]=tchf;
                     t1ff=0;
                }
                else if(tchf==4 && t2ff==1 && map[xi][yj]==0)
                {
                     map[xi][yj]=tchf;
                     t2ff=0;
                }
                else if(tchf==5 && t1bf==1 && map[xi][yj]==0)
                {
                     map[xi][yj]=tchf;
                     t1bf=0;
                }
                else if(tchf==6 && t2bf==1 && map[xi][yj]==0)
                {
                     map[xi][yj]=tchf;
                     t2bf=0;
                }
                else if(tchf==-1 && t1f==1 && map[xi][yj]==0)
                {
                     map[xi][yj]=tchf;
                     t1f=0;
                }
                else if(tchf==-2 && t2f==1 && map[xi][yj]==0)
                {
                     map[xi][yj]=tchf;
                     t2f=0;
                }
                refresh();
                                
     }
     if(mouse_b & 2)
     {
                int x=mouse_x;
                int y=mouse_y;
                int xi,yj;
                for(int i=0;i<=31;i++)
                {
                        if(x>=20*i && x<=20*(i+1))
                        xi=i;
                }
                for(int i=0;i<=23;i++)
                {
                        if(y>=20*i && y<=20*(i+1))
                        yj=i;
                }
                rectify(xi,yj);
                if(map[xi][yj]==0)
                map[xi][yj]=0;
                else if(map[xi][yj]==1)
                map[xi][yj]=0;
                else if(map[xi][yj]==2)
                map[xi][yj]=0;
                else if(map[xi][yj]==7)
                map[xi][yj]=0;
                else if(map[xi][yj]==8)
                map[xi][yj]=0;
                else if(map[xi][yj]==9)
                map[xi][yj]=0;
                else if(map[xi][yj]==10)
                map[xi][yj]=0;
                else if(map[xi][yj]==3)
                {
                     t1ff=1;
                     map[xi][yj]=0;
                     int x=10+20*xi;
                     int y=10+20*yj;
                     rectfill(bm,x-10,y-10,x+10,y+10,0);
                }
                else if(map[xi][yj]==4)
                {
                     t2ff=1;
                     map[xi][yj]=0;
                     int x=10+20*xi;
                     int y=10+20*yj;
                     rectfill(bm,x-10,y-10,x+10,y+10,0);
                }
                else if(map[xi][yj]==5)
                {
                     t1bf=1;
                     map[xi][yj]=0;
                     int x=10+20*xi;
                     int y=10+20*yj;
                     rectfill(bm,x-10,y-10,x+10,y+10,0);
                }
                else if(map[xi][yj]==6)
                {
                     t2bf=1;
                     map[xi][yj]=0;
                     int x=10+20*xi;
                     int y=10+20*yj;
                     rectfill(bm,x-10,y-10,x+10,y+10,0);
                }
                else if(map[xi][yj]==-1)
                {
                     t1f=1;
                     map[xi][yj]=0;
                     int x=10+20*xi;
                     int y=10+20*yj;
                     rectfill(bm,x-10,y-10,x+10,y+10,0);
                }
                else if(map[xi][yj]==-2)
                {
                     t2f=1;
                     map[xi][yj]=0;
                     int x=10+20*xi;
                     int y=10+20*yj;
                     rectfill(bm,x-10,y-10,x+10,y+10,0);
                }
                refresh();
                               
     }
}
void rectify(int &x,int &y)
{
     if(x<=0)
     x=0;
     if(x>=31)
     x=31;
     if(y<=0)
     y=0;
     if(y>=23)
     y=23;
}
