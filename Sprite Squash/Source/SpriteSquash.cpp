#include <allegro.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
BITMAP *bm;
int map[32][24],tmap[24][24],tmap2[24][24];
int tchf=1;
int pw=2; 
char innf[30];
char outf[30];
void init();
void deinit();
void drawGrid();
void markSquare();
void save();
void refresh();
void rectify(int &,int &);
void drawSpr(int,int);
int main(int argc, char *argv[]) 
{
	init();
	drawGrid();
	line(bm,310,0,310,480,5);
 line(bm,0,230,640,230,5);          
ifstream sd;
sd.open("Settings\\Settings.txt",ios::in);
sd>>innf;
sd>>outf;
sd.close();
cout<<innf<<endl<<outf<<endl;
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
                   of.open(outf,ios::out);
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       of<<map[i][j]<<"\n";
                      }
                      }
                      of<<pw<<"\n";
                      of.close();
                      refresh();
                      rest(75);
     }
     else if(key[KEY_O])
     {
                   ifstream inf;
                   inf.open(innf,ios::in);
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       inf>>map[i][j];
                      }
                      }
                      inf.close();
                      refresh();
                      rest(75);
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
                      rest(75);
     }
     

   else if(key[KEY_UP])
     {
           for(int i=0;i<=31;i++)
                      {
                            map[i][23]=map[i][0];  
                      } 
           for(int i=0;i<=31;i++)
                      {
                   for(int j=0;j<=22;j++)
                         {
                            map[i][j]=map[i][j+1];
                         }
                      
                      }
                      refresh();
                      rest(75);
     }
      else if(key[KEY_DOWN])
     {
                  
           for(int i=0;i<=31;i++)
                      {
                            map[i][0]=map[i][23];  
                      } 
           for(int i=0;i<=31;i++)
                      {
                   for(int j=23;j>=1;j--)
                         {
                            map[i][j]=map[i][j-1];
                         }
                      
                      }
                      refresh();
                      rest(75);
     }
      else if(key[KEY_LEFT])
     {
                  for(int j=0;j<=23;j++)
                      {
                            map[31][j]=map[0][j];  
                      } 
           for(int i=0;i<=30;i++)
                      {
                   for(int j=0;j<=23;j++)
                         {
                            map[i][j]=map[i+1][j];
                         }
                      
                      }
                      refresh();
                      rest(75);
     }
     
      else if(key[KEY_RIGHT])
     {
                   for(int j=0;j<=23;j++)
                      {
                            map[0][j]=map[31][j];  
                      } 
           for(int i=31;i>=1;i--)
                      {
                   for(int j=0;j<=23;j++)
                         {
                            map[i][j]=map[i-1][j];
                         }
                      
                      }
                      refresh();
                      rest(75);
     }
     
     
     else if(key[KEY_V])
     {
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       tmap[i][j]=map[i][23-j];
                      } 
                      }
                      
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       map[i][j]=tmap[i][j];
                      } 
                      }
                      refresh();
                      rest(75);
     }
     
     
    else if(key[KEY_B])
     {
                    for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       tmap[i][j]=map[31-i][j];
                      } 
                      }
                      
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       map[i][j]=tmap[i][j];
                      } 
                      }

                      refresh();
                      rest(75);
     }
     
     
     else if(key[KEY_N])
     {
                    for(int i=4;i<=27;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       tmap[i-4][j]=map[i][j];
                      } 
                      }
                   
                   
                      
                   for(int i=0;i<=23;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       tmap2[j][23-i]=tmap[i][j];
                      } 
                      }
                      for(int i=4;i<=27;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       map[i][j]=tmap2[i-4][j];
                      } 
                      }

                      refresh();
                      rest(75);
     }
     
     else if(key[KEY_0])
     tchf=0;
     else if(key[KEY_1])
     tchf=1;
     else if(key[KEY_2])
     tchf=2;
     else if(key[KEY_3])
     tchf=3;
     else if(key[KEY_4])
     tchf=4;
     else if(key[KEY_5])
     tchf=5;
     else if(key[KEY_6])
     tchf=6;
     else if(key[KEY_7])
     tchf=7;
     else if(key[KEY_8])
     tchf=8;
     else if(key[KEY_9])
     tchf=9;
     else if(key[KEY_Q])
     tchf=10;
     else if(key[KEY_W])
     tchf=11;
     else if(key[KEY_E])
     tchf=12;
     else if(key[KEY_R])
     tchf=13;
     else if(key[KEY_T])
     tchf=14;
     else if(key[KEY_Y])
     tchf=15;
     else if(key[KEY_Z])
     {
     pw++;
     rest(75);
     }
     else if(key[KEY_X])
     {
     if(pw>1)
     pw--;
     rest(75);
     }
     
     
    
}

void refresh()
{
     clear_to_color(bm,0);
     
     
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                           int x=10+20*i;
                           int y=10+20*j;
//**************************************************************************************************                           
                       if(map[i][j]==0)
                       {
                                      rectfill(bm,x-10,y-10,x+10,y+10,0);
                       }
                       else
                       {                         
                        rectfill(bm,x-10,y-10,x+10,y+10,map[i][j]);
                        }
                       
//************************************************************************************************                   
                      } 
                   }
                   drawGrid();
        line(bm,310,0,310,480,5);
        line(bm,0,230,640,230,5);
        drawSpr(70,70);          
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
                map[xi][yj]=tchf;
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
                map[xi][yj]=0;
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
void drawSpr(int xc,int yc)
{
   
   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                           int x=(i-16)*pw;
                           int y=(j-12)*pw;
                           x=x+xc+3;
                           y=y+yc+3;
                           rectfill(bm,x-pw/2,y-pw/2,x+pw/2,y+pw/2,map[i][j]);
                      }
                   }
 
    
}
