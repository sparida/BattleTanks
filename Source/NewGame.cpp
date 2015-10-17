/*
The following is a computer game for the CBSE Class 12 computer science project.
The game is titled 'Battle Tanks' and at present is in its fifth version.
The game uses basic graphics, keyboard controls & implements logic and gameplay via c++.
****************************************************************************************************************************************** //
*/

#include <cstdlib>
#include <iostream>
#include <allegro.h>
#include <fstream>
#include <cmath>
#define MAXPS 500
#define MAXPR 100
using namespace std;
BITMAP *bm;
SAMPLE *s;
MIDI *m; 
int pscnt=0; //Particle System Count
int bw=7;   //Border Width
int bc=5;   //Border Colour
int bg=0;   //Background Colour
int tbc[2]={5,2};  //Tank Body Colour
int twc[2]={11,4};  //Tank Wheel Colour
int tcbc=12;   //Tank Critical Body Colour
int tcwc=13;   //Tank Critical Wheel Colour
int tww=6;  //Tank Wheel Width
int trc=15; //Tank Turret Colour
int bs=3;   //Bullet Size
int blc=12; //Bullet Colour
int bsd=14; //Bullet Speed
int ts=5;   //Tank Speed
int gs=30;  //Game Speed
int t1blc=-1;//Player1 Bullet Counter
int t2blc=-1;//Player2 Bullet Counter
int t1blcnt=0;//Player1 Bullet Count
int t2blcnt=0;//Player2 Bullet Count
int t1f=1,t2f=1;//Player Movement Flags 
int t1x=380,t1y=380,t1d=1,t2x=40,t2y=40,t2d=1; //Tank Location Specifiers
int fnb=5;   //Number Of Hits Required For Death
int map[32][24];   //Tile Map Array
int winner=0;     //Winner Flag
int t1hc=0,t2hc=0; //Tank 1 & 2 Hit Counts
int tbes=3; //Tile Bomb Explosion Size
int tbct=2; //Tile Bomb Count
int tbncnt=2; //Time Bomb Count
int tsm[2]={0,0},t1sm=0,t2sm=0; //Tank Shadow Mode Flags
int GameOver=0;   //Game Flag
int mch,sch,sv; //Music Choice, Sound Choice & Sound Volume
int puc=1; //Power Ups Choice 
int lmc=0; //Land Mine Count
int hvbcnt=0; //Horizontal & Vertical Bomb Count
int f1a=0,f2a=0,b1a=0,b2a=0;// Tank 1 & 2 Flag and Base Alive Counters
int t1fx=-10,t1fy=-10,t1bx=-10,t1by=-10, //Tank1 Flag & Base Coordinates 
t2fx=-10,t2fy=-10,t2bx=-10,t2by=-10; //Tank2 Flag & Base Coordinates
int vcnt=0; //Vortex Count
int vmax=10; // Maximum Vortex Count
int ttnf,ttyf; //ttn flag, tty flag(Class PowerUps)
int hgf=1;  //High Graphics Flag
char mapn[50];
char mapnf[50]="Map Files\\";
char ma[25][50]=  //Music Array
{
"01.Metallica-Enter Sandman.mid",
"01.Metallica-Fuel.mid",
"1sweet_child.mid",
"2wewill.mid",
"slipknot_duality.mid",
"ozzy_osbourne_crazy_train.mid",
"nirvana_smells_like_teen_spirit.mid",
"DC_-_Back_In_Black.mid",
"Learn_To_Fly.mid",
"04.Metallica-Fade To Black.mid",
"All_Along_The_Watchtower.mid",
"boulevard-of-broken-dreams.mid",
"Brain_Stew.mid",
"Californication.mid",
"Crawling.mid",
"Hotel_California.mid",
"Kashmir.mid",
"Killing_In_The_Name_Of.mid",
"Last_Resort.mid",
"One_Step_Closer.mid",
"Pardon_Me.mid",
"Scar_Tissue.mid",
"StairwayToHeaven.mid",
"Sweet_Home_Alabama.mid",
"Voodoo_Child.mid"
};

long sec=0;
void tim()
{
     sec++;
}
END_OF_FUNCTION(tim);     
void initialize();
void deinitialize(); 
void boundary();
void moveTank();
void checkHit();
void checkFlagWin(int);
void explosion(int,int);
void rectify(int&,int&);
void drawTank(int,int,int,int);
void drawBullet(int,int);
void detectTankTileCollision(int,int,int,int);
void playSound(int);
void scoreStatus();
void initSprites(char *);
void drawBarriers();
void drawPowers();
//****************************************ParticleSystem**************************************
typedef struct
{
float x,y,lx,ly;
float vx,vy,lvx,lvy;
float ax,ay,lax,lay;
int cl,lcl;
float r,lr;
int isAlive; 
}PARTICLE; 
class ParticleSys
{
      
      float bx,by;
      PARTICLE p[MAXPR];
      long starttime;
      long endtime;
      long curtime;
      int effectType;
      int isAlive;
      int NOP;
      float p1,p2,p3;
      int p4;
      public:
      ParticleSys()
      {
                   for(int i=0;i<MAXPR;i++)
                   p[i].isAlive=0;
                   
                   isAlive=0;
                   starttime=0;
                   endtime=1;
                   curtime=0;
                   NOP=MAXPR;
      }       
             void checkAlive();
             void displayParticles();
             void startParticleSystem(float,float,int,int,int,float,float,float,int);//x,y,type,time,numofpar,para1-4
             void pursueEffect();
             void randomShow();
             void initCrackerBurst();
             void crackerBurst();
             void whiteMist();
             void endEffect();
             void initSpiral();
             void spiralField();
           
}ps[MAXPS];

void ParticleSys::displayParticles()
{
if(isAlive==1)
{     
for(int i=0;i<MAXPR;i++)
{
        if(p[i].isAlive==1)
        putpixel(bm,(int)p[i].x,(int)p[i].y,p[i].cl);
}
}     
}


void ParticleSys::startParticleSystem(float x, float y, int n,int t,int num, float p1t,float p2t, float p3t,int p4t)
{
bx=x;
by=y;

NOP=num;
if(NOP>MAXPR)
NOP=MAXPR;

for(int i=0;i<NOP;i++)
{
p[i].r=1;
p[i].isAlive=1;
p[i].x=bx;
p[i].y=by;
}

effectType=n;
isAlive=1; 
starttime=sec;
endtime=sec+t;    
curtime=starttime;

p1=p1t;
p2=p2t;
p3=p3t;
p4=p4t;

if(effectType==2)
initCrackerBurst();

if(effectType==4)
initSpiral();

}

void ParticleSys::pursueEffect()
{
     if(effectType==1)
     randomShow();
     
     else if(effectType==2)
     crackerBurst();
     
     else if(effectType==3)
     whiteMist();
     
     else if(effectType==4)
     spiralField();
}

void ParticleSys::endEffect()
{
     isAlive=0;
     for(int i=0;i<MAXPR;i++)
     p[i].isAlive=0;
}

void ParticleSys::checkAlive()
{
    curtime=sec;
    if(curtime<=endtime)
    {
    if(isAlive==1)
    {                          
    pursueEffect();
    }
    }
    
    else
    {
    endEffect();
    }
}

void ParticleSys::randomShow()
{
int xr,yr;     
float k=p1;
float dx,dy;
for(int i=0;i<NOP;i++)
{
 p[i].lx=p[i].x;
 p[i].ly=p[i].y;       
}
for(int i=0;i<NOP;i++)
{
 xr=(rand()% 11) -5;
 yr=(rand()% 11) -5;
 dx=xr/k;
 dy=yr/k;
 p[i].x=p[i].x+dx;
 p[i].y=p[i].y+dy;
 p[i].cl=(rand()% 16);
 
} 
int ca[2]={4,6};
int ca1[2]={5,11};
int ca2[2]={2,4};
int r,c;
switch(p4)
{
          case 0:
          displayParticles();
          break;
          case 1:
          for(int i=0;i<NOP/2;i++)
          {
          line(bm,(int)p[i].x,(int)p[i].y,(int)p[NOP-1-i].x,(int)p[NOP-1-i].y,p[i].cl);        
          }
          break;
          case 2:
          for(int i=0;i<NOP;i++)
          {     
                r=(rand()%3)+1;
                c=(rand()%2);
                circle(bm,(int)p[i].x,(int)p[i].y,r,ca[c]);
          }
          break;
          case 3:
          for(int i=0;i<NOP;i++)
          {
                  c=(rand()%2);
                  p[i].cl=ca1[c];
          }
          displayParticles();       
          break;
          case 4:
          for(int i=0;i<NOP;i++)
          {
                  c=(rand()%2);
                  p[i].cl=ca2[c];
          }
          displayParticles();       
          break;
               
          default:
          displayParticles();
          break;
}
}
void ParticleSys::initCrackerBurst()
{
    
     int dir;
     float v0=p1;
     float vth;
     for(int i=0;i<NOP;i++)
     {
     dir=(rand()% 360)+1;   
     vth=(3.14/180.0)*dir;
     p[i].vx=v0*cos(vth);
     p[i].vy=v0*sin(vth);
     p[i].cl=p4;    
     }
}
void ParticleSys::crackerBurst()
{
     float df=p2;
     float dt=p3;
     float K=0.1;
for(int i=0;i<NOP;i++)
{
p[i].vx=p[i].vx/df;
p[i].vy=p[i].vy/df;
float dx=p[i].vx*dt;
float dy=p[i].vy*dt;
dx*=K;
dy*=K;
p[i].x=p[i].x+dx;
p[i].y=p[i].y+dy;
}
displayParticles();     
}
void ParticleSys::whiteMist()
{
     
int xr,yr;     
float k=p1;
float dx,dy;
float range=20.0;
int col[5]={1,11,13,12,10};
for(int i=0;i<NOP;i++)
{
 p[i].lx=p[i].x;
 p[i].ly=p[i].y;       
}

for(int i=0;i<NOP;i++)
{
 xr=(rand()% 11) -5;
 yr=(rand()% 11) -5;
 dx=xr/k;
 dy=yr/k;
 p[i].x=p[i].x+dx;
 p[i].y=p[i].y+dy;
 int ct=(rand()% 5);
 p[i].cl=col[ct];
 p[i].r=(rand()% 2) +1;
 
}
for(int i=0;i<NOP;i++)
{
        circlefill(bm,(int)p[i].x,(int)p[i].y,(int)p[i].r,(int)p[i].cl);
}
}

void ParticleSys::initSpiral()
{
     int dir;
     float th;
     float r0=p1;
     float v0=p2;
     float df=p3;
     for(int i=0;i<NOP;i++)
     {
     dir=(rand()% 360)+1;   
     th=(3.14/180.0)*dir;
     p[i].x=bx+(r0*cos(th));
     p[i].y=by+(-r0*sin(th));
     p[i].vx=(-v0*cos(th));
     p[i].vy=(v0*sin(th));
     p[i].cl=p4;
     }
}
void ParticleSys::spiralField()
{
     float df=p3;
     float dt=0.5;
     float K=0.1;
for(int i=0;i<NOP;i++)
{
p[i].vx=p[i].vx*df;
p[i].vy=p[i].vy*df;
float dx=p[i].vx*dt;
float dy=p[i].vy*dt;
dx*=K;
dy*=K;
p[i].x=p[i].x+dx;
p[i].y=p[i].y+dy;
}
displayParticles();
}

//***********************************************************************************************
//*******************************************************SPRITESQUASH***************************************************

class MySprite
{
      public:
      int map[32][24];
      int pw;
      void initSpr(char *n)
      {     
                   ifstream in;
                   in.open(n,ios::in);
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                           in>>map[i][j];
                      }
                   }
                   in>>pw;
                   in.close();

      }
      public:
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
                           if(map[i][j]!=0)
                           rectfill(bm,x-pw/2,y-pw/2,x+pw/2,y+pw/2,map[i][j]);
                      }
                   }
       }
      
};
      
MySprite T1Up;
MySprite T1Down;
MySprite T1Left;
MySprite T1Right;
MySprite T2Up;
MySprite T2Down;
MySprite T2Left;
MySprite T2Right;
MySprite BulletS,BulletS2;
MySprite TB1S,TB2S;
MySprite MUp,MDown,MLeft,MRight;
MySprite BarrierS,LandMineS,QBarrierS,HBombS,VBombS,VortexS,T1FlagS,T2FlagS,T1GLS,T2GLS;
MySprite ShieldS,AntiShieldS,CannonS,EnergyS,MissileS,BarrierBombS,AtomizerS,TimeBombS;
void initSprites()
{
T1Up.initSpr("Sprites\\T1\\TUp.txt");
T1Down.initSpr("Sprites\\T1\\TDown.txt");
T1Left.initSpr("Sprites\\T1\\TLeft.txt");
T1Right.initSpr("Sprites\\T1\\TRight.txt");
T2Up.initSpr("Sprites\\T2\\TUp.txt");
T2Down.initSpr("Sprites\\T2\\TDown.txt");
T2Left.initSpr("Sprites\\T2\\TLeft.txt");
T2Right.initSpr("Sprites\\T2\\TRight.txt");
BulletS.initSpr("Sprites\\Tiles\\Bullet.txt");
BulletS2.initSpr("Sprites\\Tiles\\Bullet2.txt");
BarrierS.initSpr("Sprites\\Tiles\\Barrier.txt");
QBarrierS.initSpr("Sprites\\Tiles\\QBarrier.txt");
LandMineS.initSpr("Sprites\\Tiles\\LandMine.txt");
HBombS.initSpr("Sprites\\Tiles\\HBomb.txt");
VBombS.initSpr("Sprites\\Tiles\\VBomb.txt");
TB1S.initSpr("Sprites\\Tiles\\TB1.txt");
TB2S.initSpr("Sprites\\Tiles\\TB2.txt");
VortexS.initSpr("Sprites\\Tiles\\Vortex.txt");
T1FlagS.initSpr("Sprites\\Tiles\\T1Flag.txt");
T2FlagS.initSpr("Sprites\\Tiles\\T2Flag.txt");
T1GLS.initSpr("Sprites\\Tiles\\T1GL.txt");
T2GLS.initSpr("Sprites\\Tiles\\T2GL.txt");
MUp.initSpr("Sprites\\Missile\\MUp.txt");
MDown.initSpr("Sprites\\Missile\\MDown.txt");
MRight.initSpr("Sprites\\Missile\\MRight.txt");
MLeft.initSpr("Sprites\\Missile\\MLeft.txt");
ShieldS.initSpr("Sprites\\PowerUps\\Shield.txt");
AntiShieldS.initSpr("Sprites\\PowerUps\\AntiShield.txt");
CannonS.initSpr("Sprites\\PowerUps\\Cannon.txt");
EnergyS.initSpr("Sprites\\PowerUps\\Energy.txt");
BarrierBombS.initSpr("Sprites\\PowerUps\\BarrierBomb.txt");
MissileS.initSpr("Sprites\\PowerUps\\Missile.txt");
AtomizerS.initSpr("Sprites\\PowerUps\\Atomizer.txt");
TimeBombS.initSpr("Sprites\\PowerUps\\TimeBomb.txt");
}
//**********************************************************************************************************************


class HitMan
{
       int t1aq,t1dq,t2aq,t2dq;
       int ht;
       public:
       HitMan()
       {
        t1aq=0;
        t2aq=0;
        t1dq=1;
        t2dq=1;     
       }
       void attack(int,int);
       void qdefault();
       void setQuotients(int,int,int,int);
}HM;

void HitMan::qdefault()
{
t1aq=0;
t2aq=0;
t1dq=1;
t2dq=1;     
}
void HitMan::setQuotients(int a1,int d1,int a2,int d2)
{
t1aq=a1;
t2aq=a2;
t1dq=d1;
t2dq=d2;
}
void HitMan::attack(int a,int d)
{
     
if(a==1)
{
t1hc+=t1aq;                
}
else if(a==2)
{
t2hc+=t2aq;                
}
if(d==1)
{
t1hc+=t1dq;                
}
else if(d==2)
{
t2hc+=t2dq;                
}
}


class PowerUps
{      
      int trigger;
      int triggertime;
      int x,y;
      int isAlive;
      int changeflag;
      public:
      int ttn; //Trigger Tank Number
      int tty; //Energy-1, BarrierBomb-2, Shield-3, AntiShield-4, Cannon-5, Missile-6, Atomizer-7, TimeBomb-8 
      void displayPU();
      void triggerTim();
      void checkContact();
      void powerUp();
      PowerUps()
      {
                trigger=0;
                ttn=0;
                tty=1;
                triggertime=20;
                changeflag=1;
                }
}PU;
void PowerUps::displayPU()
{
     if(isAlive==1)
     {
     switch(tty)
     {
                case 1:
                     EnergyS.drawSpr(x,y);
                     break;
                case 2:
                     BarrierBombS.drawSpr(x,y);
                     break;
                case 3:
                     ShieldS.drawSpr(x,y);
                     break;
                case 4:
                     AntiShieldS.drawSpr(x,y);
                     break;
                case 5:
                     CannonS.drawSpr(x,y);
                     break;
                case 6:
                     MissileS.drawSpr(x,y);
                     break;
                case 7:
                     AtomizerS.drawSpr(x,y);
                     break;
                case 8:
                     TimeBombS.drawSpr(x,y);
                     break;
 
     }
     }
     checkContact();
}


void PowerUps::triggerTim()
{
     if((sec%15)==(14))
     {
                                           isAlive=1;
                                           ttn=0;
                                           ttnf=ttn;
                                           if(changeflag==1)
                                           {
                                           int xr=(rand()% 600) +1;
                                           int yr=(rand()% 450) +1;
                                           int ty=(rand()% 8) +1;
                                           ty=(((ty+2)%8)+1);
                                           x=xr;
                                           y=yr;
                                           tty=ty;
                                           ttyf=tty;
                                           playSound(9);
                                           changeflag=0;
                                           }
                                           HM.qdefault();
                                           displayPU();  
     }
     if((sec%15)==(13))
     changeflag=1;
}
void PowerUps::checkContact()
{
     if(isAlive==1)
     {
                      int a=t1x-x;
                      int b=t1y-y;
                      float xd=pow(a,2.0);
                      float yd=pow(b,2.0);
                      float r=sqrt(xd+yd);
                      if(r<=13.0)
                      {
                      ttn++;
                      ttnf=ttn;
                      isAlive=0;
                      }
                      a=t2x-x;
                      b=t2y-y;
                      xd=pow(a,2.0);
                      yd=pow(b,2.0);
                      r=sqrt(xd+yd);
                      if(r<=13.0)
                      {
                      ttn+=2;
                      ttnf=ttn;
                      isAlive=0;
                      }
     if(ttn!=0)
     powerUp();
     
     }
}

     
     
     
class Bullet
{
      public:
             int x,y,d,flag,bmf;
             void initBullet(int a,int b,int c)
             {          
                        playSound(1);
                        x=a;
                        y=b;
                        d=c;
                        flag=1;
                        bmf=1;
             }
             void drawBullet(int a,int b)
             {
            if(hgf==1)
            {      
			if(bmf==1)
			{
                        BulletS.drawSpr(a-1,b-1);
                        bmf=2;  
             }
                        else
			{
                        BulletS2.drawSpr(a-1,b-1);
                        bmf=1;  
             }
             }
             
             else
             {
                 circlefill(bm,a,b,bs,blc);
             }
               
             }

             void moveBullet()
             {
     if(d==1 && y>=bw)
     y-=bsd;
     if(d==2 && x<=640-bw)
     x+=bsd;
     if(d==3 && y<=480-bw)
     y+=bsd;
     if(d==4 && x>=bw)
     x-=bsd;
     if(d==1 && y<bw)
     flag=0;
     if(d==2 && x>640-bw)
     flag=0;
     if(d==3 && y>480-bw)
     flag=0;
     if(d==4 && x<bw)
     flag=0;
     
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                      float xd;
                      xd=pow(a-x,2.0);
                      float yd;
                      yd=pow(b-y,2.0);
                      float r;
                      r=sqrt(xd+yd);
                      if(map[i][j]==1 && r<=13.0)
                      {
                      
                      if(flag==1)
                      {
                      circle(screen,a,b,10,4);
                      playSound(2);
                      }
                      flag=0;
                      }
                      
              }
      }
     if(flag!=0)
     {
                drawBullet(x,y);
     }
  }
}; 
Bullet b1[7],b2[7];
//******************************************************************************



class TileBomb
{
      public:
      int x,y;
      int alive;
      TileBomb()
      {
                alive=1;
      }
      void explode(int n,int t)
{
     if(t==1)
     {
     x=t1x;
     y=t1y;
     }
     else if(t==2)
     {
     x=t2x;
     y=t2y;
     }
     alive=0;
     
      ps[pscnt].startParticleSystem(x,y,1,3,100,1.3,0.0,0.0,2);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
       removeTiles();
}
      
      
      
      void removeTiles()
      {
           
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
                
                int xr=(rand()% tbes) +1;
                int yr=(rand()% tbes) +1;
                 for(int i=0;i<=xr;i++)
                {
                        for(int j=0;j<=yr;j++)
                        {
                           int a,b,m,n;
                           a=xi+i;
                           b=yj+j;
                           m=xi-i;
                           n=yj-j;
                           rectify(a,b);
                           rectify(m,n);
                           if(map[a][b]!=3 && map[a][b]!=4 && map[a][b]!=5 && map[a][b]!=6)
                           { 
                           map[a][b]=0;
                           }
                           if(map[m][n]!=3 && map[m][n]!=4 && map[m][n]!=5 && map[m][n]!=6)
                           { 
                           map[m][n]=0;
                           }
                        }
                }
           
           
           
      }

};
TileBomb t1b[10],t2b[10];

class LandMine
{
      public:
      int x,y;//Row, Column
      int alive,flag;
      LandMine()
      {
                flag=0;
                
                alive=0;
      }
      void drawMine();
      void testCollision();
      void explode();
      void removeTilesTanks();
      
      
}lm[300];
class HVBomb
{
      public:
      int x,y;//Row, Column
      int alive,flag;
      int type; //1-Horizontal 2-Vertical
      HVBomb()
      {
                flag=0;
                
                alive=0;
      }
      void drawMine();
      void testCollision();
      void explode();
      void removeTilesTanks();
      
      
}hvb[300];


class TimeBomb
{
      public:
      int x,y;//Actual Coordinates
      int alive,flag,ani,cntrt,nt;
      int eflag;
      int starttime,curtime;
      TimeBomb()
      {
                flag=0;
                ani=0;
                alive=0;
                cntrt=0;
                eflag=0;
      }
      void initBomb(int,int,int);
      void drawBomb();
      void testActivation();
      void explode();
      void removeTilesTanks();
      
      
}t1tb[10],t2tb[10];
class Missile
{
      public:
             int x,y,d,flag,m;
             Missile()
             {
                      flag=0;
             }
             void initMissile(int a,int b,int c,int e)
             {          
                        playSound(8);
                        x=a;
                        y=b;
                        d=c;
                        flag=1;
                        m=e;
             }
             void drawMissile()
             {
                  if(hgf==1)
                  {
                        if(d==1)
                        {
                                MUp.drawSpr(x-1,y-1);
                        }
                        else if(d==2)
                        {
                                MRight.drawSpr(x-1,y-1);
                        }
                        else if(d==3)
                        {
                                MDown.drawSpr(x-1,y-1);
                        }
                        else if(d==4)
                        {
                                MLeft.drawSpr(x-1,y-1);
                        }
                  }
                  
                  else
                  {
                      
                        if(d==1)
                        {
                                rectfill(bm,x-5,y-5,x+5,y+10,7);
                                rectfill(bm,x-5,y-10,x+5,y-5,12);
                        }
                        else if(d==2)
                        {
                                rectfill(bm,x-10,y-5,x+5,y+5,7);
                                rectfill(bm,x+5,y-5,x+10,y+5,12);
                        }
                        else if(d==3)
                        {
                                rectfill(bm,x-5,y-10,x+5,y+5,7);
                                rectfill(bm,x-5,y+5,x+5,y+10,12);
                        }
                        else if(d==4)
                        {
                                rectfill(bm,x-5,y-5,x+10,y+5,7);
                                rectfill(bm,x-10,y-5,x-5,y+5,12);
                        }
                  }
             }

             void moveMissile()
             {
                  if(flag==1)
                  {
     if(d==1 && y>=bw)
     y-=bsd/2;
     if(d==2 && x<=640-bw)
     x+=bsd/2;
     if(d==3 && y<=480-bw)
     y+=bsd/2;
     if(d==4 && x>=bw)
     x-=bsd/2;
     if(d==1 && y<bw)
     flag=2;
     if(d==2 && x>640-bw)
     flag=2;
     if(d==3 && y>480-bw)
     flag=2;
     if(d==4 && x<bw)
     flag=2;
     }
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      if(flag==1 && (map[i][j]==1 || map[i][j]==2 || map[i][j]==9 || map[i][j]==10))
                      {
                      int a=10+20*i;
                      int b=10+20*j;
                      float xd=pow(a-x,2.0);
                      float yd=pow(b-y,2.0);
                      float r=sqrt(xd+yd);
                      if(r<=13.0)
                      {
                      explode();
                      flag==2;
                      }
                      }
                      
                      
                      
              }
      }
     //888888888888888888888888888888888888888888888888888888888888888888888888

if(m==2)
{
                      int k=x-t1x;
                      int l=y-t1y;
                      float xd=k*k;
                      float yd=l*l;
                      float r=sqrt(xd+yd);
             if(flag==1 && r<=13.0)
             {
             flag=2;
             playSound(2);
             t1hc+=5;
             }

}
else if(m==1)
{
                      int k=x-t2x;
                      int l=y-t2y;
                      float xd=k*k;
                      float yd=l*l;
                      float r=sqrt(xd+yd);
             if(flag==1 && r<=13.0)
             {
             flag=2;
             playSound(2);
             t2hc+=5;
             }

}
     //*********************************************************************** 
      
      
      
      
     if(flag==1)
     {
                drawMissile();
     }
  }
  void explode()
  {
      
      int a=x;
      int b=y;
      int n=3;
      ps[pscnt].startParticleSystem(x,y,1,3,100,0.5,0.0,0.0,0);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }

     ps[pscnt].startParticleSystem(x,y,3,5,100,0.5,0.0,0.0,0);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
     ps[pscnt].startParticleSystem(x,y,3,5,100,0.5,0.0,0.0,0);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
      ps[pscnt].startParticleSystem(x,y,2,5,100,50,1.01,0.5,1);
      pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                       
      ps[pscnt].startParticleSystem(x,y,2,5,100,50,1.015,0.5,12);
      pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
      ps[pscnt].startParticleSystem(x,y,2,5,100,50,1.02,0.5,13);
      pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
       flag=2;
       playSound(5);
       removeTilesTanks();
  }
  void removeTilesTanks()
  {
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
                
                int xr=tbes+4;
                int yr=tbes+4;
                 for(int i=0;i<=xr;i++)
                {
                        for(int j=0;j<=yr;j++)
                        {
                           int a,b,m,n,q,w,o,p,t1r,t1c,t2r,t2c;
                           for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }
                           
                           a=xi+i;
                           b=yj+j;
                           m=xi-i;
                           n=yj-j;
                           q=xi+i;
                           w=yj-j;
                           o=xi-i;
                           p=yj+j;
                           rectify(a,b);
                           rectify(m,n);
                           rectify(o,p);
                           rectify(q,w);
                        
                           if(a==t1r && b==t1c && ((a+b)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(a==t2r && b==t2c && ((a+b)% 5)!=0)
                           {
                                     t2hc+=4;
                           }
                           if(m==t1r && n==t1c && ((m+n)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(m==t2r && n==t2c && ((m+n)%5)!=0)
                           {
                                     
                                     t2hc+=4;
                           }
                           if(o==t1r && p==t1c && ((o+p)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(o==t2r && p==t2c && ((o+p)%5)!=0)
                           {
                                     t2hc+=4;
                           }
                           if(q==t1r && w==t1c && ((q+w)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(q==t2r && w==t2c && ((q+w)%5)!=0)
                           {
                                     t2hc+=4;
                           }
                           
                           
                           
                            
                           if(map[a][b]==2 || map[m][n]==2 || map[o][p]==2 || map[q][w]==2 || map[a][b]==9 || map[m][n]==9 || map[o][p]==9 || map[q][w]==9 || map[a][b]==10 || map[m][n]==10 || map[o][p]==10 || map[q][w]==10)
                           {
                                           int count;
                                           for(count=0;count<lmc;count++)
                                           {
                                              if(lm[count].x==a && lm[count].y==b)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;
                                              }
                                              if(lm[count].x==m && lm[count].y==n)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;  
                                              }
                                           
                                           if(lm[count].x==o && lm[count].y==p)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;  
                                              }
                                           
                                           if(lm[count].x==q && lm[count].y==w)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;  
                                              }
                                           }
                                           for(count=0;count<hvbcnt;count++)
                                           {
                                              if(hvb[count].x==a && hvb[count].y==b)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;
                                              }
                                              if(hvb[count].x==m && hvb[count].y==n)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;  
                                              }
                                           
                                           if(hvb[count].x==o && hvb[count].y==p)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;  
                                              }
                                           
                                           if(hvb[count].x==q && hvb[count].y==w)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;  
                                              }
                                           }
                                           
                           }
                           if(map[a][b]!=3 && map[a][b]!=4 && map[a][b]!=5 && map[a][b]!=6)
                           { 
                           map[a][b]=0;
                           }
                           if(map[m][n]!=3 && map[m][n]!=4 && map[m][n]!=5 && map[m][n]!=6)
                           { 
                           map[m][n]=0;
                           }
                           if(map[o][p]!=3 && map[o][p]!=4 && map[o][p]!=5 && map[o][p]!=6)
                           { 
                           map[o][p]=0;
                           }
                           if(map[q][w]!=3 && map[q][w]!=4 && map[q][w]!=5 && map[q][w]!=6)
                           { 
                           map[q][w]=0;
                           }
                                    
                        }
                }

}      
}; 
Missile m1,m2;


class Flags
{     
      public:
      int f1pu,f2pu,flag; //Flag Pick-Up 
      int f1dp,f2dp; //Flag Drop Off
      Flags()
      {
             f1pu=0;
             f2pu=0;
             f1dp=0;
             f2dp=0;
             flag=0;
      }
      void drawFlagsBase()
      {
           if(hgf==1)
           {
           T1GLS.drawSpr(t1bx-1,t1by-1);
           T2GLS.drawSpr(t2bx-1,t2by-1);
           }
           else
           {
           rect(bm,t1bx-10,t1by-10,t1bx+10,t1by+10,11);
           rect(bm,t1bx-5,t1by-5,t1bx+5,t1by+5,5);
           rect(bm,t2bx-10,t2by-10,t2bx+10,t2by+10,4);
           rect(bm,t2bx-5,t2by-5,t2bx+5,t2by+5,2);
           }
           
           if(f1a==1 && f1pu!=1)
           {
             int x=t1fx;
             int y=t1fy;
             if(hgf==1)
             {
             T1FlagS.drawSpr(x-1,y-1);
             }
             else
             {
             rectfill(bm,x-10,y-10,x+10,y,11);
             rectfill(bm,x+5,y,x+10,y+10,5);
             } 

           }
           if(f2a==1 && f2pu!=1)
           {
             int x=t2fx;
             int y=t2fy;
             if(hgf==1)
             {
             T2FlagS.drawSpr(x-1,y-1);
             }
             else
             {
             rectfill(bm,x-10,y-10,x+10,y,4);
             rectfill(bm,x+5,y,x+10,y+10,2);
             }  

           }
                 
      }           
      
      void carryFlag(int n)
      {
           if(n==1)
           {
                    float xd=pow(t1x-t2fx,2.0);
                    float yd=pow(t1y-t2fy,2.0);
                    float r=sqrt(xd+yd);
                   if(f2a==1 && r<=13.0)
                   {
                             f2pu=1;
                             t1sm=0;
                             playSound(6);
                             ps[pscnt].startParticleSystem(t1x,t1y,2,3,100,10,1.01,0.5,tbc[1]);
                             pscnt++;
                             if(pscnt>=MAXPS)
                             {
                             pscnt=0;
                             }
                             ps[pscnt].startParticleSystem(t1x,t1y,2,3,100,10,1.01,0.5,twc[1]);
                             pscnt++;
                             if(pscnt>=MAXPS)
                             {
                             pscnt=0;
                             }
                   }
           }
           if(n==2)
           {
                    float xd=pow(t2x-t1fx,2.0);
                    float yd=pow(t2y-t1fy,2.0);
                    float r=sqrt(xd+yd);
                   if(f1a==1 && r<=13.0)
                   {
                             f1pu=1;
                             t2sm=0;
                             playSound(6);
                             ps[pscnt].startParticleSystem(t2x,t2y,2,3,100,10,1.01,0.5,tbc[0]);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                       ps[pscnt].startParticleSystem(t2x,t2y,2,3,100,10,1.01,0.5,twc[0]);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                   }
           }
      }
      
      void dropFlag(int n)
      {
           if(n==1)
           {
                   if(f2pu==1)
                   {
                              f2pu=0;
                              t2fx=t1x;
                              t2fy=t1y;
                              flag=1;
                              playSound(6);
                   }
           }
           
           if(n==2)
           {
                   if(f1pu==1)
                   {
                              f1pu=0;
                              t1fx=t2x;
                              t1fy=t2y;
                              flag=2;
                              playSound(6);
                   }
           }
           if(flag!=0)
           {
           checkFlagWin(flag);
           flag=0;
           }
      }
      
}f;
//*****************************************************************************************************

class Vortex
{
      public:
      int r,c;
      int alive;
      Vortex()
      {
             alive=0;
      }
      void drawVortex();
      void stillAlive();
      void testPresence(int);
      void teleport(int);
} v[10];

void Vortex::drawVortex()
{
if(alive==1)
{
     int x=10+20*r;
     int y=10+20*c;
     if(hgf==1)
     {
     VortexS.drawSpr(x-1,y-1);
     }
     else
     {
         for(int cntr=0;cntr<=10;cntr+=3)
                            {
                            rect(bm,x-cntr,y-cntr,x+cntr,y+cntr,7);
                            }
     }
     
}
}
void Vortex::stillAlive()
{
     if(map[r][c]!=7)
     alive=0;
}

void Vortex::testPresence(int n)
{
     int flag=0;
     if(alive==1)
     {
             int t1r,t1c,t2r,t2c;
             for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }   
                             
                           if(n==1)
                             {
                             if(alive==1 && r==t1r && c==t1c)
                           {
                                     flag=1;
                           }
                           }
                           else if(n==2)
                           {
                           if(alive==1 && r==t2r && c==t2c)
                           {
                                     flag=1;
                           }
                           }
          
     if(flag==1)
     {
      
      teleport(n);
     }
  
                 
                 
  
}   
}

void Vortex::teleport(int n)
{
     
     
     
     int i=rand() % (vcnt+1);
     if(v[i].alive==1 && v[i].r!=r && v[i].c!=c )
     {
     if(n==1)
     {
             int a=v[i].r;
             int b=v[i].c;
             t1x=10+20*a;
             t1y=10+20*b;
             playSound(7);
             ps[pscnt].startParticleSystem(t1x,t1y,1,3,100,2.0,0.0,0.0,3);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
     }
     else if(n==2)
     {
             int a=v[i].r;
             int b=v[i].c;
             t2x=10+20*a;
             t2y=10+20*b;
             playSound(7);
             ps[pscnt].startParticleSystem(t2x,t2y,1,3,100,2.0,0.0,0.0,4);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
     }
     }
      
     
}



int main(int argc, char *argv[])
{
    initialize();
    boundary();
    while(!key[KEY_ESC] && GameOver!=1)
   { 
                       clear(bm);
                       moveTank();
                       vsync();
                       blit(bm,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                       
   }
   destroy_bitmap(bm);
   destroy_sample(s);
   destroy_midi(m);
   clear(screen);
   textout_ex(screen,font,"Game Over",270,195,7,0);
   rest(3000);
   ofstream of;
   of.open("Data Files\\Final Score.txt",ios::out);
   of<<winner<<"\n";
   of<<t1hc<<"\n";
   of<<t2hc<<"\n";
   of<<t1blcnt<<"\n";
   of<<t2blcnt<<"\n";
   of.close();
   allegro_exit();
   return EXIT_SUCCESS;
}
END_OF_MAIN()

void initialize()
{
    allegro_init();
    initSprites();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_gfx_mode(GFX_AUTODETECT,640,480,0,0);
    bm=create_bitmap(SCREEN_W,SCREEN_H);
     install_keyboard();
     install_timer();
     ifstream i;
                      i.open("Data Files\\Settings.txt",ios::in);
                      i>>mch;
                      i>>sch;
                      i>>sv;
                      i>>gs;
                      i>>fnb;
                      i>>mapn;
                      i>>puc;
                      i>>hgf;
                      i.close();
    ifstream inf;
    strcat(mapnf,mapn);
    inf.open(mapnf,ios::in);
                   for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                       inf>>map[i][j];
                       if(map[i][j]==2)
                       {
                                       if(lmc>=300)
                                       {
                                       }
                                       else
                                       {
                                           lm[lmc].alive=1;
                                           lm[lmc].x=i;
                                           lm[lmc].y=j;
                                       }
                                       lmc++;   
                       }
                       if(map[i][j]==3)
                       {
                                       t1fx=10+20*i;
                                       t1fy=10+20*j;
                                       f1a=1;
                       }
                       if(map[i][j]==4)
                       {
                                       t2fx=10+20*i;
                                       t2fy=10+20*j;
                                       f2a=1;
                       }
                       if(map[i][j]==5)
                       {
                                       t1bx=10+20*i;
                                       t1by=10+20*j;
                                       b1a=1;
                       }
                       if(map[i][j]==6)
                       {
                                       t2bx=10+20*i;
                                       t2by=10+20*j;
                                       b2a=1;
                       }
                        if(map[i][j]==7)
                       {               if(vcnt<=vmax)
                                       {
                                       v[vcnt].r=i;
                                       v[vcnt].c=j;
                                       v[vcnt].alive=1;
                                       vcnt++;
                                       }
                       }
                       if(map[i][j]==8)
                       {               
                                       map[i][j]=8;
                       }
                       if(map[i][j]==9 || map[i][j]==10)
                       {               
                                       if(hvbcnt>=300)
                                       {
                                       }
                                       else
                                       {
                                           hvb[hvbcnt].alive=1;
                                           hvb[hvbcnt].x=i;
                                           hvb[hvbcnt].y=j;
                                           if(map[i][j]==9)
                                           hvb[hvbcnt].type=1;
                                           else if(map[i][j]==10)
                                           hvb[hvbcnt].type=2;
                                       }
                                       hvbcnt++;
                       }
                       if(map[i][j]==-1)
                       {               
                                       map[i][j]=0;
                                       t1x=10+20*i;
                                       t1y=10+20*j;
                       }
                       if(map[i][j]==-2)
                       {               
                                       map[i][j]=0;
                                       t2x=10+20*i;
                                       t2y=10+20*j;
                       } 

                       
                      }
                      }
                      inf.close();
                      
           if(mch==1)
           {
             
           int decider=rand()%(25);
           char maf[200]="Sound Files\\MIDI Songs\\";
           strcat(maf,ma[decider]);
           m=load_midi(maf);
           play_midi(m,1); 
           }  
           srand(time(NULL));
           LOCK_VARIABLE(sec);
	       LOCK_FUNCTION(tim);
	       install_int_ex(tim,BPS_TO_TIMER(1));
	       
 rest(50);
}

void deinitialize()
{
     
     destroy_bitmap(bm);
     destroy_midi(m);
     remove_sound();
}
void boundary()
{
    rectfill(bm,0,0,640,480,bg);
    rectfill(bm,0,0,bw,480,bc);
    rectfill(bm,0,0,640,bw,bc);
    rectfill(bm,640-bw,0,640,480,bc);
    rectfill(bm,0,480-bw,640,480,bc);                  
   }

void drawTank(int a,int b,int d,int t)
{
     int cn;
     if(t==1)
     cn=0;
     else if(t==2)
     cn=1;
     if(hgf==1)
     {  
     if(d==1 && cn==0)
     {
              T1Up.drawSpr(a,b);
     }
     else if(d==2 && cn==0)
     {
              T1Right.drawSpr(a,b);
     }
     else if(d==3 && cn==0)
     {
              T1Down.drawSpr(a,b);
     }
     else if(d==4 && cn==0)
     {
              T1Left.drawSpr(a,b);
     }
     
     
     if(d==1 && cn==1)
     {
              T2Up.drawSpr(a,b);
     }
     else if(d==2 && cn==1)
     {
              T2Right.drawSpr(a,b);
     }
     else if(d==3 && cn==1)
     {
              T2Down.drawSpr(a,b);
     }
     else if(d==4 && cn==1)
     {
              T2Left.drawSpr(a,b);
     }
     }
     else
     {
         if(d==1 || d==3)
     {
              rectfill(bm,a-tww,b-tww,a+tww,b+tww,tbc[cn]);
              rectfill(bm,a-2*tww,b-2*tww,a-tww,b+2*tww,twc[cn]);
              rectfill(bm,a+tww,b-2*tww,a+2*tww,b+2*tww,twc[cn]);
     }
     else if(d==2 || d==4)
     {
              rectfill(bm,a-tww,b-tww,a+tww,b+tww,tbc[cn]);
              rectfill(bm,a-2*tww,b-2*tww,a+2*tww,b-tww,twc[cn]);
              rectfill(bm,a-2*tww,b+tww,a+2*tww,b+2*tww,twc[cn]);
     }
     switch(d)
     {
                        case 1:
                             rectfill(bm,a-1,b-3*tww,a+1,b,trc);
                             break;
                        case 2:
                             rectfill(bm,a,b-1,a+3*tww,b+1,trc);
                             break;
                        case 3:
                             rectfill(bm,a-1,b,a+1,b+3*tww,trc);
                             break;
                        case 4:
                             rectfill(bm,a-3*tww,b-1,a,b+1,trc);
                             break;
     }
     }
     drawPowers();
                                        
}


/**************************************************************************************************/
void moveTank()
{
       t1f=1;
       t2f=1;
       if(ttnf==1 && ttyf==7)
       {
                  t1f=1;
       }
       if(key[KEY_UP])
   {
                  detectTankTileCollision(t1x,t1y,1,t2d);
                  if(t1y>=bw && t1f==1)
                  t1y-=ts;
                  t1d=1;
   }
   if(key[KEY_RIGHT])
   {
                  detectTankTileCollision(t1x,t1y,2,t2d);
                  if(t1x<=640-bw && t1f==1)
                  t1x+=ts;
                  t1d=2;
   }
   if(key[KEY_DOWN])
   {
                  detectTankTileCollision(t1x,t1y,3,t2d);
                  if(t1y<=480-bw && t1f==1)
                  t1y+=ts;
                  t1d=3;
   }
   if(key[KEY_LEFT])
   {
                  detectTankTileCollision(t1x,t1y,4,t2d);
                  if(t1x>=bw && t1f==1)
                  t1x-=ts;
                  t1d=4;
   }
   
   if(key[KEY_W])
   {
                  detectTankTileCollision(t2x,t2y,t1d,1);                 
                  if(t2y>=bw && t2f==1)
                  t2y-=ts;
                  t2d=1;
   }
   if(key[KEY_D])
   {
                  detectTankTileCollision(t2x,t2y,t1d,2);
                  if(t2x<=640-bw && t2f==1)
                  t2x+=ts;
                  t2d=2;
   }
   if(key[KEY_S])
   {
                  detectTankTileCollision(t2x,t2y,t1d,3);
                  if(t2y<=480-bw && t2f==1)
                  t2y+=ts;
                  t2d=3;
   }
   if(key[KEY_A])
   {
                  detectTankTileCollision(t2x,t2y,t1d,4);
                  if(t2x>=bw && t2f==1)
                  t2x-=ts;
                  t2d=4;
   }
   if(key[KEY_ENTER])
   { 
                     if(t1sm==0)
                     {
                     //rest(40);
                     t1blc++;
                     if(t1blc>=7)
                     t1blc=0;
                     t1blcnt++;
                     b1[t1blc].initBullet(t1x,t1y,t1d);
                     }
   }
   if(key[KEY_SPACE])
   { 
                     if(t2sm==0)
                     {
                     //rest(40);
                     t2blc++;
                     if(t2blc>=7)
                     t2blc=0;
                     t2blcnt++;
                     b2[t2blc].initBullet(t2x,t2y,t2d);
                     }
   }
   
   if(key[KEY_P] && key[KEY_RSHIFT])
   {
                  int bflag=1;
                  for(int cntr=0;cntr<=tbncnt-1;cntr++)
                  {
                          if(t1tb[cntr].alive==0 && bflag==1 && t1tb[cntr].eflag==0)
                          {
                          t1tb[cntr].initBomb(t1x,t1y,1);
                          playSound(12);
                          
                          
                          bflag=0;
                          }
                  }
   }
   else if(key[KEY_P])
   {
                  int bflag=1;
                  for(int cntr=0;cntr<=tbct-1;cntr++)
                  {
                          if(t1b[cntr].alive==1 && bflag==1)
                          {
                          t1b[cntr].explode(3,1);
                          playSound(4);
                          t1b[cntr].alive=0;
                          bflag=0;
                          }
                          
                  }
                  
   }
   
    if(key[KEY_X] && key[KEY_LSHIFT])
   {
                  int bflag=1;
                  for(int cntr=0;cntr<=tbncnt-1;cntr++)
                  {
                          if(t2tb[cntr].alive==0 && bflag==1 &&  t2tb[cntr].eflag!=1)
                          {
                          t2tb[cntr].initBomb(t2x,t2y,2);
                          playSound(12);
                          
                          bflag=0;
                          }
                  }
   }
   else if(key[KEY_X])
   {
                  int bflag=1;
                  for(int cntr=0;cntr<=tbct-1;cntr++)
                  {
                          if(t2b[cntr].alive==1 && bflag==1)
                          {
                          t2b[cntr].explode(3,2);
                          playSound(4);
                          t2b[cntr].alive=0;
                          bflag=0;
                          }
                  }
   }
    if(key[KEY_RSHIFT] && key[KEY_O])
   {
                     rest(20);
                     if(t1sm==0 && f.f2pu!=1)
                     {
                     t1sm=1;
                     playSound(3);
                     t1hc+=2;
                     }
                     else if(t1sm==1)
                     {
                     t1sm=0;     
                     playSound(3);
                     }
   }                 
    
   if(key[KEY_LSHIFT] && key[KEY_C])
   {
                     rest(20);
                     if(t2sm==0 && f.f1pu!=1)
                     {
                     t2sm=1;
                     playSound(3);
                     t2hc+=2;
                     }
                     else if(t2sm==1)
                     {
                     t2sm=0;
                     playSound(3);     
                     }
   }                 
   
   if(key[KEY_U])
   {
                f.carryFlag(1); 
                 
   }
   if(key[KEY_I])
   {
                f.dropFlag(1); 
                 
   }
   if(key[KEY_V])
   {
                f.carryFlag(2); 
                 
   }
   if(key[KEY_B])
   {
                f.dropFlag(2); 
                 
   }
   if(key[KEY_F])
   {
                
                for(int i=0;i<vcnt;i++)
                v[i].testPresence(2); 
                 
   }
   if(key[KEY_L])
   {
                for(int i=0;i<vcnt;i++)
                v[i].testPresence(1);  
                 
   }
   
   if(key[KEY_ENTER] && key[KEY_RSHIFT])
   { 
                     if(m1.flag==0)
                     {
                     m1.initMissile(t1x,t1y,t1d,1);
                     }
   }
   
   if(key[KEY_SPACE] && key[KEY_LSHIFT])
   { 
                     if(m2.flag==0)
                     {
                     m2.initMissile(t2x,t2y,t2d,2);
                     }
   }
   
   
   rest(gs);
   boundary();
   for(int i=0;i<=6;i++)
   b1[i].moveBullet();
   for(int i=0;i<=6;i++)
   b2[i].moveBullet();
   drawBarriers();
      if(t1sm!=1)
   {               
   drawTank(t1x,t1y,t1d,1);
   }
   if(t2sm!=1)
   {
   drawTank(t2x,t2y,t2d,2);
   }
   for(int ctr=0;ctr<lmc;ctr++)
   {
           lm[ctr].drawMine();
           lm[ctr].testCollision();
   }
   for(int ctr=0;ctr<=tbncnt-1;ctr++)
   {
           t1tb[ctr].drawBomb();
           t1tb[ctr].testActivation();
           t2tb[ctr].drawBomb();
           t2tb[ctr].testActivation();
   }
    for(int ctr=0;ctr<vcnt;ctr++)
   {
           v[ctr].stillAlive();
           v[ctr].drawVortex();
   }
   for(int ctr=0;ctr<hvbcnt;ctr++)
   {
           hvb[ctr].drawMine();
           hvb[ctr].testCollision();
   }

   f.drawFlagsBase();
   m1.moveMissile();
   m2.moveMissile();
   if(puc==1)
   {
   PU.triggerTim();
   PU.displayPU();
   }
   for(int i=0;i<MAXPS;i++)
     {        
             ps[i].checkAlive();
     }     
   checkHit();
   scoreStatus();
}
void drawBarriers()
{
     for(int i=0;i<=31;i++)
                   {
                   for(int j=0;j<=23;j++)
                      {
                           int x=10+20*i;
                           int y=10+20*j;
                       if(map[i][j]==1)
                        {              
                                      if(hgf==1)
                                      {
                                       BarrierS.drawSpr(x-1,y-1);
                                       }
                                       else
                                       {
                                       rectfill(bm,x-10,y-10,x+10,y+10,7);
                                       rectfill(bm,x-4,y-4,x+4,y+4,8);
                                       }
                        }
                        else if(map[i][j]==8)
                        {              
                                      if(hgf==1)
                                      {
                                       QBarrierS.drawSpr(x-1,y-1);
                                       }
                                       else
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
                        }
                      } 
                   }
}         
void detectTankTileCollision(int x,int y,int d1,int d2)
{
  
    if(d1==1)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                      if((map[i][j]==1 || map[i][j]==8)&& t1y<=b+10 && t1y>=b+5 && t1x>=a-10 && t1x<=a+10)
                      {
                      t1f=0;
                      circlefill(screen,a,b,10,13);
                      }
              }
      }
    }  
    
    if(d1==2)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                       if((map[i][j]==1 || map[i][j]==8) && t1x>=a-10 && t1x<=a-5 && t1y>=b-10 && t1y<=b+10)
                      {
                                       circlefill(screen,a,b,10,13);
                      t1f=0;
                      }
              }
      }
    }  
    
    if(d1==3)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                      if((map[i][j]==1 || map[i][j]==8) && t1y>=b-10 && t1y<=b-5 && t1x>=a-10 &&t1x<=a+10)
                      {
                                      circlefill(screen,a,b,10,13);
                      t1f=0;
                      }
              }
      }
    }  
    
    if(d1==4)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                      if((map[i][j]==1 || map[i][j]==8) && t1x<=a+10 && t1x>=a+5 && t1y>=b-10 && t1y<=b+10)
                      {
                                      circlefill(screen,a,b,10,13);
                      t1f=0;
                      }
              }
      }
    }        
    
    
    if(d2==1)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                      if((map[i][j]==1 || map[i][j]==8) && t2y<=b+10 && t2y>=b+5 && t2x>=a-10 && t2x<=a+10)
                      {
                      t2f=0;
                      circlefill(screen,a,b,10,13);
                      }
              }
      }
    }  
    
    if(d2==2)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                       if((map[i][j]==1 || map[i][j]==8) && t2x>=a-10 && t2x<=a-5 && t2y>=b-10 && t2y<=b+10)
                      {
                                       circlefill(screen,a,b,10,13);
                      t2f=0;
                      }
              }
      }
    }  
    
    if(d2==3)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                      if((map[i][j]==1 || map[i][j]==8) && t2y>=b-10 && t2y<=b-5 && t2x>=a-10 &&t2x<=a+10)
                      {
                                      circlefill(screen,a,b,10,13);
                      t2f=0;
                      }
              }
      }
    }  
    
    if(d2==4)
    {
      for(int i=0;i<=31;i++)
      {
              for(int j=0;j<=23;j++)
              {
                      int a=10+20*i;
                      int b=10+20*j;
                      if((map[i][j]==1 || map[i][j]==8) && t2x<=a+10 && t2x>=a+5 && t2y>=b-10 && t2y<=b+10)
                      {
                                      circlefill(screen,a,b,10,13);
                      t2f=0;
                      }
              }
      }
    }   
    
    if(ttnf==1 && ttyf==7)
       {
                  t1f=1;
       }
    if(ttnf==2 && ttyf==7)
       {
                  t2f=1;
       }     
}

void checkHit()
{
    
     
     for(int i=0;i<=6;i++)
     {
                      int k=b2[i].x-t1x;
                      int l=b2[i].y-t1y;
                      float xd=k*k;
                      float yd=l*l;
                      float r=sqrt(xd+yd);
             if(b2[i].flag!=0 && r<=13.0)
             {
             b2[i].flag=0;
             playSound(2);
             HM.attack(2,1);
             }
     }       
             if(t1hc>=fnb-1)
             {
             tbc[0]=tcbc;               
             twc[0]=tcwc;
             }
             else
             {
             tbc[0]=5;               
             twc[0]=11;
             }
             if(t1hc>=fnb)
             {
                          scoreStatus();
                          vsync();
                       blit(bm,screen,0,0,0,0,SCREEN_W,SCREEN_H);
             winner=2;
             GameOver=1;
             playSound(5);
             explosion(4,1);
             } 
           
     for(int i=0;i<=6;i++)
     {
                      int k=b1[i].x-t2x;
                      int l=b1[i].y-t2y;
                      float xd=k*k;
                      float yd=l*l;
                      float r=sqrt(xd+yd);
             if(b1[i].flag!=0 && r<=13.0)
             {
             b1[i].flag=0;
             playSound(2);
             HM.attack(1,2);
             }
     }
             if(t2hc>=fnb-1)
             {
             tbc[1]=tcbc;               
             twc[1]=tcwc;
             }
             else
             {
             tbc[1]=2;               
             twc[1]=4;
             }
             if(t2hc>=fnb)
             {
                          scoreStatus();
                          vsync();
                       blit(bm,screen,0,0,0,0,SCREEN_W,SCREEN_H);
             winner=1;
             GameOver=1;
             playSound(5);
             explosion(4,2);
             }
}


void checkFlagWin(int n)
{
     if(n==1)
     {       float xt=t2fx-t1bx;
             float yt=t2fy-t1by; 
             float xd=pow(xt,2);
             float yd=pow(yt,2);
             float r=sqrt(xd+yd);
             if(r<=10.0)
             {
             winner=1;
             GameOver=1;
             playSound(5);
             explosion(4,2);
             }          
     }
     
     else if(n==2)
     {       float xt=t1fx-t2bx;
             float yt=t1fy-t2by;
             float xd=pow(xt,2);
             float yd=pow(yt,2);
             float r=sqrt(xd+yd);
             if(r<=10.0)
             {
             winner=2;
             GameOver=1;
             playSound(5);
             explosion(4,1);
 
             }          
     }
}




//******************************************************************************************
void explosion(int n,int t)
{
     int x,y;
     if(t==1)
     {
     x=t1x;
     y=t1y;
     }
     else if(t==2)
     {
     x=t2x;
     y=t2y;
     }
     
     for(int c=0;c<=n*10;c++)
     {
             int ch=rand() % 2;
             if(ch==0)
             {
                      int s=(rand() % n) +1;
                      s=s*10;
                      int xe=rand()%n;
                      int ye=rand()%n;
                      int cr=rand()%15;
                      circlefill(screen,x+xe,y+ye,s,cr);
                      rest(185);
             } 
             else if(ch==1)
             {
                      int s=(rand() % n) +1;
                      s=s*10;
                      int xe=rand()%n;
                      int ye=rand()%n;
                      int cr=rand()%15;
                      rectfill(screen,x-s+xe,y-s+ye,x+s-xe,y+s-ye,cr);
                      rest(185);
             }        
       
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

void playSound(int ch)
{
     if(ch==1)
     {
              //Play Bullet Firing Sound
              if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\FireBullet.wav");
              play_sample(s,sv-15,128,1000,0);
              }
     }
     else if(ch==2)
     {
          //Play bullet colliding with tank sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\HitTank.wav");
              play_sample(s,sv,128,1000,0);
              }
     }
     else if(ch==3)
     {
          //Initiate/End shadow mode sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\ShadowMode.wav");
              play_sample(s,sv,128,1000,0);
              }
     }
     else if(ch==4)
     {
          //Explosion Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\Bomb.wav");
              play_sample(s,sv,128,1000,0);
              }
     }
     else if(ch==5)
     {
          //Final Explosion Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\FinalExplosion.wav");
              play_sample(s,sv,128,1000,0);
              }
      }
      
      else if(ch==6)
     {
          //Flag Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\Flag.wav");
              play_sample(s,sv,128,1000,0);
              }
      }
       else if(ch==7)
     {
          //Vortex Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\Vortex.wav");
              play_sample(s,sv,128,500,0);
              }
      }
      
      else if(ch==8)
     {
          //Missile Initiation Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\Missile.wav");
              play_sample(s,sv,128,500,0);
              }
      }
      else if(ch==9)
     {
          //Power Up Available Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\PowerUpAvailable.wav");
              play_sample(s,sv,128,500,0);
              }
      }
      else if(ch==10)
     {
          //Powered Up Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\PoweredUp.wav");
              play_sample(s,sv,128,500,0);
              }
      }
      else if(ch==11)
     {
          //Pip Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\Pip.wav");
              play_sample(s,sv,60,250,0);
              }
      }
      else if(ch==12)
     {
          //Bomb Initilization Sound
          if(sch==1)
              {
              s=load_sample("Sound Files\\WAV SFX\\BombInit.wav");
              play_sample(s,sv,128,500,0);
              }
      }

     
}

void scoreStatus()
{
     rect(bm,0,0,640,bw,0);
   
                    int t1sl=t2hc*(320-7)/fnb;
                    int t2sl=t1hc*(320-7)/fnb;
                    t1sl=313-t1sl;
                    t2sl=313-t2sl;
                    rectfill(bm,7,0,7+t1sl,bw,4);
                    rectfill(bm,633-t2sl,0,633,bw,11);
                    textprintf_ex(bm, font, 0, 0, makecol(100,100,200),
                    -1, "%d", fnb-t2hc);
   textprintf_ex(bm, font, 627, 0, makecol(100,100,200),
                    -1, "%d", fnb-t1hc);   
}

void PowerUps::powerUp()     
{    
     playSound(10);
     if(ttn==1)
     {
     switch(tty)
     {
                case 1:
                     if(t1hc>0 && t1hc!=1)
                     {
                     t1hc-=2;
                     }
                     else if(t1hc==1)
                     {
                     t1hc-=1;
                     }
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,4);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 2:
                     for(int cntr=0;cntr<=tbct-1;cntr++)
                     {
                          t1b[cntr].alive=1;
                          
                     }
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,3);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 3:
                     HM.setQuotients(0,0,0,1);
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,2);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                     
                case 4:
                     HM.setQuotients(0,1,1,1);
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,11);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 5:
                     HM.setQuotients(0,1,0,2);
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,6);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 6:
                     m1.flag=0;
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,5);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 7:
                     t1f=1;
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,6);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 8:
                     for(int c=0;c<=tbncnt-1;c++)
                     {
                               t1tb[c].alive=0;
                               t1tb[c].flag=0;
                               t1tb[c].eflag=0;
                     }
                     ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,2);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                       ps[pscnt].startParticleSystem(t1x,t1y,2,2,100,10,1.01,0.5,1);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;    
                         
     }
     }
     if(ttn==2)
     {
     switch(tty)
     {
                case 1:

                     if(t2hc>0 && t2hc!=1)
                     {
                     t2hc-=2;
                     }
                     else if(t2hc==1)
                     {
                     t2hc-=1;
                     }
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,4);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 2:
                     for(int cntr=0;cntr<=tbct-1;cntr++)
                     {
                          t2b[cntr].alive=1;
                          
                     }
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,3);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 3:
                     HM.setQuotients(0,1,0,0);
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,3);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 4:
                     HM.setQuotients(1,1,0,1);
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,1);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 5:
                     HM.setQuotients(0,2,0,1);
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,6);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 6:
                     m2.flag=0;
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,5);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 7:
                     t2f=1;
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,6);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;
                case 8:
                     for(int c=0;c<=tbncnt-1;c++)
                     {
                     t2tb[c].alive=0;
                     t2tb[c].flag=0;
                     t2tb[c].eflag=0;
                     }
                     ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,2);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                       ps[pscnt].startParticleSystem(t2x,t2y,2,2,100,10,1.01,0.5,1);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
                     break;

     }
     }
}
void drawPowers()
{
     if(ttnf==1)
     {
     switch(ttyf)
     {
                case 1:
                     break;
                case 2:
                     break;
                case 3:
                     if(hgf==1)
                     circle(bm,t1x-1,t1y-1,20,2);
                     else
                     circle(bm,t1x,t1y,20,2);
                     break;
                case 4:
                     if(hgf==1)
                     circle(bm,t1x-1,t1y-1,20,1);
                     else
                     circle(bm,t1x,t1y,20,1);
                     break;
                case 5:
                     if(hgf==1)
                     {
                     circlefill(bm,t1x-1,t1y-1,5,6);
                     }
                     else
                     {
                     circlefill(bm,t1x,t1y,5,6);
                     for(int i=0;i<=6;i++)
                     {
                     if(b1[i].flag==1)
                     circlefill(bm,b1[i].x,b1[i].y,bs,6);
                     }
                     }
                     break;
                case 6:
                     break;
                case 7:
                     rect(bm,t1x-10,t1y-10,t1x+10,t1y+10,6);
                     break;

     }
     }
     if(ttnf==2)
     {
     switch(ttyf)
     {
                case 1:
                     break;
                case 2:
                     break;
                case 3:
                     if(hgf==1)
                     circle(bm,t2x-1,t2y-1,20,2);
                     else
                     circle(bm,t2x,t2y,20,2);
                     break;
                case 4:
                     if(hgf==1)
                     circle(bm,t2x-1,t2y-1,20,1);
                     else
                     circle(bm,t2x,t2y,20,1);
                     break;
                case 5:
                     if(hgf==1)
                     {
                     circlefill(bm,t2x-1,t2y-1,5,6);
                     }
                     else
                     {
                     circlefill(bm,t2x,t2y,5,6);
                     for(int i=0;i<=6;i++)
                     {
                     if(b2[i].flag==1)
                     circlefill(bm,b2[i].x,b2[i].y,bs,6);
                     }
                     }
                     break;
                case 6:
                     break;
                case 7:
                     rect(bm,t2x-10,t2y-10,t2x+10,t2y+10,6);
                     break;
     }
     }
}
void LandMine::drawMine()
      {
                         
                 if(alive==1)
                 {
                 int a=10+20*x;
                 int b=10+20*y;
                 if(hgf==1)
                 {
                 LandMineS.drawSpr(a-1,b-1);
                 }
                 else
                 {
                 int fg=0;
                 for(int cntr=0;cntr<=10;cntr+=2)
                 {
                            if(fg%2==0)
                            circlefill(bm,a,b,10-cntr,1);
                            else
                            circlefill(bm,a,b,10-cntr,12);
                            
                            fg++;
                            fg=fg%2;
                 }
                 }
      }
}      
void LandMine::testCollision()
{
     if(alive==1)
     {
     for(int ctr=0;ctr<=6;ctr++)
     {
     if(b1[ctr].flag==1)
     {
     int a=10+20*x;
     int b=10+20*y;
     float xd=pow(a-b1[ctr].x,2.0);
     float yd=pow(b-b1[ctr].y,2.0);
     float r=sqrt(xd+yd);
     if(r<=13.0)
     {
              flag=1;
              b1[ctr].flag=0;
              
     }
     }
     }
     
     for(int ctr=0;ctr<=6;ctr++)
     {
     if(b2[ctr].flag==1)
     {
     int a=10+20*x;
     int b=10+20*y;
     float xd=pow(a-b2[ctr].x,2.0);
     float yd=pow(b-b2[ctr].y,2.0);
     float r=sqrt(xd+yd);
     if(r<=13.0)
     {
              flag=1;
              b2[ctr].flag=0;
              
     }
     }
     }
     }
     int t1r,t1c,t2r,t2c;
     for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }
                           
                          if(alive==1 && x==t1r && y==t1c)
                           {
                                     flag=1;
                           }
                           if(alive==1 && x==t2r && y==t2c)
                           {
                                     flag=1;
                           }
          
     if(flag==1)
     {
      explode();
      playSound(4);
            
     }
 }             
 
 void LandMine::explode()
{
      ps[pscnt].startParticleSystem(10+20*x,10+20*y,3,3,25,1.5,0.0,0.0,0);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
      ps[pscnt].startParticleSystem(10+20*x,10+20*y,2,3,100,15.0,1.01,0.5,11);
      pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
       alive=0;
       flag=0;
       removeTilesTanks();
}
void LandMine::removeTilesTanks()
{
     int xi,yj;
               xi=x;
               yj=y;
                
                int xr=(rand()% tbes) +1;
                int yr=(rand()% tbes) +1;
                 for(int i=0;i<=xr;i++)
                {
                        for(int j=0;j<=yr;j++)
                        {
                           int a,b,m,n,t1r,t1c,t2r,t2c;
                           for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }
                           
                           a=xi+i;
                           b=yj+j;
                           m=xi-i;
                           n=yj-j;
                           rectify(a,b);
                           rectify(m,n);
                           if(a==t1r && b==t1c)
                           {
                                     t1hc+=2;
                           }
                           if(a==t2r && b==t2c)
                           {
                                     t2hc+=2;
                           }
                           if(m==t1r && n==t1c)
                           {
                                     t1hc+=2;
                           }
                           if(m==t2r && n==t2c)
                           {
                                     t2hc+=2;
                           } 
                           if(map[a][b]==2 || map[m][n]==2)
                           {
                                           int count;
                                           for(count=0;count<lmc;count++)
                                           {
                                              if(lm[count].x==a && lm[count].y==b)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;
                                              }
                                              if(lm[count].x==m && lm[count].y==n)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;  
                                              }
                                           }
                                           for(count=0;count<hvbcnt;count++)
                                           {
                                              if(hvb[count].x==a && hvb[count].y==b)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;
                                              }
                                              
                                           }
                           }
                           if(map[a][b]!=3 && map[a][b]!=4 && map[a][b]!=5 && map[a][b]!=6)
                           { 
                           map[a][b]=0;
                           }
                           if(map[m][n]!=3 && map[m][n]!=4 && map[m][n]!=5 && map[m][n]!=6)
                           { 
                           map[m][n]=0;
                           }
                                    
                        }
                }

}

void TimeBomb::initBomb(int a,int b,int c)
{
     x=a;y=b;nt=c;
     starttime=sec;
     alive=1;
     ps[pscnt].startParticleSystem(x,y,4,10,100,20.0,1,1.01,10);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
 }
void TimeBomb::drawBomb()
      {
      if(curtime!=sec)
      {
                         
                 if(alive==1 && eflag!=1)
                 {
                 int a=x;
                 int b=y;
                 if(hgf==1)
                 {
                           
                 if(ani==0)
                 TB1S.drawSpr(a-1,b-1);
                 else if(ani==1)
                 TB2S.drawSpr(a-1,b-1);
                 
                 ani++;
                 ani=ani%2;
                 
                 playSound(11);
                 
                 }
                 else
                 { 
                            cntrt=(curtime-starttime)*2;   
                            circlefill(bm,a,b,10,2);
                            circlefill(bm,a,b,cntrt,12);
                            playSound(11);
                 }
                 }
      }
      else
      {
          if(alive==1 && eflag!=1)
                 {
                 int a=x;
                 int b=y;
                 if(hgf==1)
                 {
                           
                 if(ani==0)
                 TB1S.drawSpr(a-1,b-1);
                 else if(ani==1)
                 TB2S.drawSpr(a-1,b-1);
                 
                 ani++;
                 ani=ani%2;
                 
                 
                 
                 }
                 else
                 { 
                            cntrt=(curtime-starttime)*2;   
                            circlefill(bm,a,b,10,2);
                            circlefill(bm,a,b,cntrt,12);
                           
                 }
                 }
      }
}      
void TimeBomb::testActivation()
{
     if(alive==1 && eflag!=1)
     {
     curtime=sec;
     if((curtime-starttime)>=5)
     {
     
              flag=1;
                            
     }
     }
     
     
          
     if(flag==1)
     {
      explode();
      playSound(4);
            
     }
 }             
 
 void TimeBomb::explode()
{
      
      int a=x;
      int b=y;
      int n=3;
      
      ps[pscnt].startParticleSystem(x,y,3,3,20,1.3,0.0,0.0,0);
                       pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
      ps[pscnt].startParticleSystem(x,y,3,1,100,15.0,1.007,0.5,11);
      pscnt++;
                       if(pscnt>=MAXPS)
                       {
                       pscnt=0;
                       }
     
       alive=0;
       flag=0;
       eflag=1;
       removeTilesTanks();
}
void TimeBomb::removeTilesTanks()
{
     int xi,yj;
     for(int iq=0;iq<=31;iq++)
     {
     if(x>20*iq && x<=20*(iq+1))
     xi=iq;
     }
     for(int jq=0;jq<=23;jq++)
     {
     if(y>20*jq && y<=20*(jq+1))
     yj=jq;
     }
               
               
                
                int tbest=(rand()% 3) +1;
                
                if(tbest<2)
                tbest=2;
                
                int xr=tbest;
                int yr=tbest;
                
                for(int i=0;i<=xr;i++)
                {
                        for(int j=0;j<=yr;j++)
                        {
                           int a,b,m,n,q,w,o,p,t1r,t1c,t2r,t2c;
                           for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }
                           
                           a=xi+i;
                           b=yj+j;
                           m=xi-i;
                           n=yj-j;
                           q=xi+i;
                           w=yj-j;
                           o=xi-i;
                           p=yj+j;
                           rectify(a,b);
                           rectify(m,n);
                           rectify(o,p);
                           rectify(q,w);
                        
                           if(a==t1r && b==t1c && ((a+b)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(a==t2r && b==t2c && ((a+b)% 5)!=0)
                           {
                                     t2hc+=4;
                           }
                           if(m==t1r && n==t1c && ((m+n)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(m==t2r && n==t2c && ((m+n)%5)!=0)
                           {
                                     
                                     t2hc+=4;
                           }
                           if(o==t1r && p==t1c && ((o+p)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(o==t2r && p==t2c && ((o+p)%5)!=0)
                           {
                                     t2hc+=4;
                           }
                           if(q==t1r && w==t1c && ((q+w)%5)!=0)
                           {
                                     t1hc+=4;
                           }
                           if(q==t2r && w==t2c && ((q+w)%5)!=0)
                           {
                                     t2hc+=4;
                           }
                           
                           
                           
                            
                           if(map[a][b]==2 || map[m][n]==2 || map[o][p]==2 || map[q][w]==2 || map[a][b]==9 || map[m][n]==9 || map[o][p]==9 || map[q][w]==9 || map[a][b]==10 || map[m][n]==10 || map[o][p]==10 || map[q][w]==10)
                           {
                                           int count;
                                           for(count=0;count<lmc;count++)
                                           {
                                              if(lm[count].x==a && lm[count].y==b)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;
                                              }
                                              if(lm[count].x==m && lm[count].y==n)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;  
                                              }
                                           
                                           if(lm[count].x==o && lm[count].y==p)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;  
                                              }
                                           
                                           if(lm[count].x==q && lm[count].y==w)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;  
                                              }
                                           }
                                           for(count=0;count<hvbcnt;count++)
                                           {
                                              if(hvb[count].x==a && hvb[count].y==b)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;
                                              }
                                              if(hvb[count].x==m && hvb[count].y==n)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;  
                                              }
                                           
                                           if(hvb[count].x==o && hvb[count].y==p)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;  
                                              }
                                           
                                           if(hvb[count].x==q && hvb[count].y==w)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;  
                                              }
                                           }
                                           
                           }
                           if(map[a][b]!=3 && map[a][b]!=4 && map[a][b]!=5 && map[a][b]!=6)
                           { 
                           map[a][b]=0;
                           }
                           if(map[m][n]!=3 && map[m][n]!=4 && map[m][n]!=5 && map[m][n]!=6)
                           { 
                           map[m][n]=0;
                           }
                           if(map[o][p]!=3 && map[o][p]!=4 && map[o][p]!=5 && map[o][p]!=6)
                           { 
                           map[o][p]=0;
                           }
                           if(map[q][w]!=3 && map[q][w]!=4 && map[q][w]!=5 && map[q][w]!=6)
                           { 
                           map[q][w]=0;
                           }
                                    
                        }
                }
}

void HVBomb::drawMine()
      {
                         
                 if(alive==1)
                 {
                 int a=10+20*x;
                 int b=10+20*y;
                 if(hgf==1)
                 {
                           switch(type)
                           {
                                       case 1:
                                            HBombS.drawSpr(a-1,b-1);
                                            break;
                                       case 2:
                                            VBombS.drawSpr(a-1,b-1);
                                            break;
                           }
                           
                 }
                 
                 else
                 {
                                  int xt=a;
                                  int yt=b;
                      if(type==1)
                           {
                                                int points1[6]={xt-10,yt,xt-2,yt-10,xt-2,yt+10};
                                                polygon(bm,3,points1,1);
                                                int points2[6]={xt+10,yt,xt+2,yt-10,xt+2,yt+10};
                                                polygon(bm,3,points2,1);
                                                floodfill(bm,xt-3,yt,1); 
                                                floodfill(bm,xt+3,yt,1);                           
                           }
                           else if(type==2)
                           {                    
                                                                      
                                                int points3[6]={xt,yt-10,xt-10,yt-2,xt+10,yt-2};
                                                polygon(bm,3,points3,1);
                                                int points4[6]={xt,yt+10,xt-10,yt+2,xt+10,yt+2};
                                                polygon(bm,3,points4,1);
                                                floodfill(bm,xt,yt-3,1); 
                                                floodfill(bm,xt,yt+3,1);      
                           }
                 }
                 
                 }
      }
void HVBomb::testCollision()
{
     if(alive==1)
     {
     for(int ctr=0;ctr<=6;ctr++)
     {
     if(b1[ctr].flag==1)
     {
     int a=10+20*x;
     int b=10+20*y;
     float xd=pow(a-b1[ctr].x,2.0);
     float yd=pow(b-b1[ctr].y,2.0);
     float r=sqrt(xd+yd);
     if(r<=13.0)
     {
              flag=1;
              b1[ctr].flag=0;
              
     }
     }
     }
     
     for(int ctr=0;ctr<=6;ctr++)
     {
     if(b2[ctr].flag==1)
     {
     int a=10+20*x;
     int b=10+20*y;
     float xd=pow(a-b2[ctr].x,2.0);
     float yd=pow(b-b2[ctr].y,2.0);
     float r=sqrt(xd+yd);
     if(r<=13.0)
     {
              flag=1;
              b2[ctr].flag=0;
              
     }
     }
     }
     }
     int t1r,t1c,t2r,t2c;
     for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }
                           
                          if(alive==1 && x==t1r && y==t1c)
                           {
                                     flag=1;
                           }
                           if(alive==1 && x==t2r && y==t2c)
                           {
                                     flag=1;
                           }
          
     if(flag==1)
     {
      explode();
      playSound(4);
            
     }
 }             
 
 void HVBomb::explode()
{
      
      int a=10+20*x;
      int b=10+20*y;
      int n=3;

     for(int c=0;c<=n*3;c++)
     {
             if(type==2)
             {
                      int cr=rand()%15;
                      rectfill(screen,x*20,0,x*20+20,480,cr);
             }
             else if(type==1)
             {
                      int cr=rand()%15;
                      rectfill(screen,0,y*20,640,y*20+20,cr);
 
             }
                              
       
       }
       alive=0;
       flag=0;
       removeTilesTanks();
}
void HVBomb::removeTilesTanks()
{
     int xi,yj;
               xi=x;
               yj=y;
               if(type==1)
               {
               for(int i=0;i<=31;i++)
                {
                      
                           int a,b,m,n,t1r,t1c,t2r,t2c;
                           for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }
                           a=i;
                           b=y;
                           
                           rectify(a,b);
                           if(a==t1r && b==t1c)
                           {
                                     t1hc+=2;
                           }
                           if(a==t2r && b==t2c)
                           {
                                     t2hc+=2;
                           }
                           if(map[a][b]==2 || map[a][b]==9 || map[a][b]==10)
                           {
                                           int count;
                                           for(count=0;count<lmc;count++)
                                           {
                                              if(lm[count].x==a && lm[count].y==b)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;
                                              }
                                              
                                           }
                                           for(count=0;count<hvbcnt;count++)
                                           {
                                              if(hvb[count].x==a && hvb[count].y==b)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;
                                              }
                                              
                                           }
                                           
                           }
                           if(map[a][b]!=3 && map[a][b]!=4 && map[a][b]!=5 && map[a][b]!=6)
                           { 
                           map[a][b]=0;
                           }
                           
                                    
                        }
                }
                
                
                else if(type==2)
                {
                     
                      for(int i=0;i<=23;i++)
                {
                      
                           int a,b,m,n,t1r,t1c,t2r,t2c;
                           for(int iq=0;iq<=31;iq++)
                             {
                             if(t1x>20*iq && t1x<=20*(iq+1))
                             t1r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t1y>20*jq && t1y<=20*(jq+1))
                             t1c=jq;
                             }
                             for(int iq=0;iq<=31;iq++)
                             {
                             if(t2x>20*iq && t2x<=20*(iq+1))
                             t2r=iq;
                             }
                           for(int jq=0;jq<=23;jq++)
                             {
                             if(t2y>20*jq && t2y<=20*(jq+1))
                             t2c=jq;
                             }
                           a=x;
                           b=i;
                           
                           rectify(a,b);
                           if(a==t1r && b==t1c)
                           {
                                     t1hc+=2;
                           }
                           if(a==t2r && b==t2c)
                           {
                                     t2hc+=2;
                           }
                           if(map[a][b]==2 || map[a][b]==9 || map[a][b]==10)
                           {
                                           int count;
                                           for(count=0;count<lmc;count++)
                                           {
                                              if(lm[count].x==a && lm[count].y==b)
                                              {
                                              if(lm[count].alive==1)
                                               lm[count].flag=1;
                                              }
                                              
                                           }
                                           for(count=0;count<hvbcnt;count++)
                                           {
                                              if(hvb[count].x==a && hvb[count].y==b)
                                              {
                                              if(hvb[count].alive==1)
                                               hvb[count].flag=1;
                                              }
                                              
                                           }
                                           
                           }
                           if(map[a][b]!=3 && map[a][b]!=4 && map[a][b]!=5 && map[a][b]!=6)
                           { 
                           map[a][b]=0;
                           }
                           
                                    
                        }
                 }
}


