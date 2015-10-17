#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{   
    int ch,ex=0,winner,t1hc,t2hc,t1blcnt,t2blcnt,mc=0,hch,mch=1,sch=1,sv=128,gs=50,fnb=5,puc=1,hgf=1;
    char dummy,p1n[10],p2n[10],w[10],l[10],bc,mapn[50];
    char innf[30];
    char outf[30];
    
    ofstream fout;
    fout.open("Data Files\\Match Stats.txt",ios::app);
    fout<<"Beginninng of Session\n\n";
    fout.close();
    
    ifstream i;
    i.open("Data Files\\MSettings.txt",ios::in);
    i>>innf;
    i>>outf;
    i.close();
    
    ifstream in;
    in.open("Data Files\\Settings.txt",ios::in);
    in>>mch;
    in>>sch;
    in>>sv;
    in>>gs;
    in>>fnb;
    in>>mapn;
    in>>puc;
    in>>hgf;
    in.close();

    do
    {
               system("Cls");
        
    cout<<"                             Welcome to BATTLE TANKS v5.17\n";
    cout<<"                                    Main Menu\n";
    cout<<"1.New Game\n2.Map Editor\n3.Help\n4.Settings\n5.Exit\n";
    cout<<"Enter your choice:\n";
    cin>>ch;
    if(ch==1)
    {
         mc++;
         cout<<"Enter Player1 Name:";
         cin>>p1n; 
         cout<<"Enter Player2 Name:";
         cin>>p2n;  
         system("NewGame.exe");
         ifstream inf;
         inf.open("Data Files\\Final Score.txt",ios::in);
         inf>>winner;
         inf>>t1hc;
         inf>>t2hc;
         inf>>t1blcnt;
         inf>>t2blcnt;
         inf.close();
         ofstream fout;
         fout.open("Data Files\\Match Stats.txt",ios::app);
         if(winner==1)
         {
                      strcpy(w,p1n);
                      strcpy(l,p2n);
                      }
         else if(winner==2)
         {
                      strcpy(w,p2n);
                      strcpy(l,p1n);
                      }
                    
         cout<<w<<" (Player "<<winner<<") is the Winner!!!\n";
         cout<<"Hits:\n";
         cout<<"Player1:"<<t2hc<<endl;
         cout<<"Player2:"<<t1hc<<endl;
         cout<<"Bullets Used:\n";
         cout<<"Player1:"<<t1blcnt<<endl;
         cout<<"Player2:"<<t2blcnt<<endl;
         fout<<"Match "<<mc<<" Stats"<<endl;
         fout<<w<<" (Player "<<winner<<") was the Winner!!!\n";
         fout<<"Hits:\n";
         fout<<"Player1:"<<t2hc<<endl;
         fout<<"Player2:"<<t1hc<<endl;
         fout<<"Bullets Used:\n";
         fout<<"Player1:"<<t1blcnt<<endl;
         fout<<"Player2:"<<t2blcnt<<endl;
         fout<<endl;
         fout.close();
         cout<<"Press any key to character to go back to main menu.\n";
         cin>>dummy;
         ch=0;
         }
    else if(ch==2)
    {
         mslabel:
         system("Cls");
         int chr;
         cout<<"Current Input  Map : "<<innf<<endl;
         cout<<"Current Output Map : "<<outf<<endl;
         cout<<endl;
         cout<<"1.Change Input Map\n2.Change Output Map\n3.Start Map Editor\n4.Go Back To Main Menu\n";
    cout<<"Enter choice:";
    cin>>chr;
    if(chr==1)
    {
    cout<<"\nEnter Input Map Name:\n";
    cin>>innf;
    ofstream o;
    o.open("Data Files\\MSettings.txt",ios::out);
    o<<innf<<"\n";
    o<<outf<<"\n";
    o.close();
    cout<<"\n";  
    goto mslabel;       
    }
    else if(chr==2)
    {
    cout<<"\nEnter Output Map Name:\n";
    cin>>outf;
    ofstream o;
    o.open("Data Files\\MSettings.txt",ios::out);
    o<<innf<<"\n";
    o<<outf<<"\n";
    o.close();
    cout<<"\n"; 
    goto mslabel;        
    }
    else if(chr==3)
    {
         system("MapEditor.exe");
    }
    else if(chr==4)
    {
         
    }
    else
    {
        goto mslabel;
    }
    }
    //*******************************************************************************************
    else if(ch==3)
    {
         hlabel:
                system("Cls");
         cout<<"\n                                    Help Menu\n";
    cout<<"1.General\n2.Game Controls\n3.Map Editor\n4.Go Back To Main Menu\n";
    cout<<"Enter your choice:\n";
    cin>>hch;
    if(hch==1)    
    {
                  cout<<"Battle Tanks is a two player arcade shooting game. The objective of the player is to ";
                  cout<<"shoot the enemy tank atleast four times or by detonating an inherent bomb in each tank by a key, to cause it to explode and thus win. Match Stats are stored in a file named \"Match Stats\" in the root folder.\n";
                  cout<<"Game Specifics:\n\n";
                  cout<<"1.Play Area:\n";
                  cout<<"The play area consists of two tanks, tiles and possibly bombs, keys and detonating locations. The Player1 Tank is situated at the bottom left corner while the Player2 Tank is situated at the top left corner.\n";
                  cout<<"2.Tanks:\n";
                  cout<<"The tanks are controlled via keyboard. They explode after being hit 4 times or when detonated by its key. When a tank reaches critical condition i.e. one more hit for K.O., it turns red to indicate  critical condition. ";
                  cout<<"Tanks cannot pass through barriers.\n"; 
                  cout<<"\n3.Bullets\n";
                  cout<<"The bullets are the soul of the game. Designed to perfection, at their best they can render any Ground Moving Vehicle immobile. At a time, a tank is allowed to use five bullets max. Bullets do not harm Barriers.\n";
                  cout<<"\n4.Barriers\n";
                  cout<<"The barriers add strategy to the play. They are resolute towards tanks and bullets, never allowing them to pass through. However they are turned to splinters in case a barrier bomb explodes. They are of the followinf two types:\n";
                  cout<<"\tA.Simple Barrier  :  It acts as a barrier to all objects.\n";
                  cout<<"\tB.Quantum Barrier :  It acts as a barrier to all objects except bullets\n";
                  cout<<"\t\t\t\tand missiles.\n";
                  cout<<"\n5.Barrier Bombs\n";
                  cout<<"Barrier Bombs are useful in removing barriers and getting out of CSUs. They do not harm tanks. A tank can carry only two bombs to each battle.\n";
                  cout<<"\n6.Ground Bombs\n";
                  cout<<"These are marked as red in the play area. Each ground bomb explodes either when a tank walks into it or when it is detonated remotely via a bullet. Ground Bombs destroy barriers abd tanks, by increasing their hit count by two. Further they can also detonate other Ground Bombs creating a chain reaction.\n";
                  cout<<"\n7.Time Bombs\n";
                  cout<<":These (Max 2 Per Tank) appear as green circles initially and after each second start filling up in red until after 5 seconds they explode.\n";
                  cout<<"\n8.CSUs\n";
                  cout<<"Corner Stuff Ups occur when a tank is caught in three adjacent barriers and is unable to move. Pretty Irrtitaing.\n";
                  cout<<"\n9.The Shadow Mode\n";
                  cout<<"The Shadow Mode shrouds a tank in invisibility, rendering significant setback to opponent intelligence. The tank can be manouvered with the help of collision indicators, which draw a blue circle around a barrier each time the collides with one. However the shadow mode has two catches:\n";  
                  cout<<"i. You cannot fire bullets under the Shadow Mode. The Shadow Mode has to be activated before firing.\n";
                  cout<<"ii. Each time a tank steps into Shadow Mode, a significant chunk of its energy is used to set up the shadow vortex. Thus its defensive capabilities decrease. Its hit count increases by two.\n";
                  cout<<"\n10.The Key Mechanism\n.";
                  cout<<"Each game might have a key and detonating location for each tank. Remember though that the detonating location is of same colour as the tank but the key has to be of the other tank. when a key is pickedup and detonated, the other tank explodes.\n";
                  cout<<"\n11.Vortex\n";
                  cout<<"The vortexes support teleportation through hyperspace and carry you to other vortexes. Hoever they can be rendered useless by bombs.\n";
                  cout<<"\n12.Missiles\n";
                  cout<<"Each tank is equipped with a one time use missile. Missiles wipe away almost a quarter of the game screen and deal lethal damage.\n";
                  cout<<"\n13 Horizontal and Vertical Bombs\n";
                  cout<<"These bombs act pretty mush like Ground Bombs in their explosive qualities but wipe away linear areas (A particular row or column).\n";
                  cout<<"\n14.Power Ups\n";
                  cout<<"They are made available in regular interval and each of their effects lasts for the current interval. They are of the following types:\n\n";
                  cout<<"\tENERGY[E]     - Increases energy bar by 2\n";
                  cout<<"\t(Blue)\n";
                  cout<<"\tSHIELD[S]     - Makes tank immune to enemy bullets\n";
                  cout<<"\t(Green)\n";
                  cout<<"\tANTISHIELD[S] - Reduces enemy energy by 1 each time it attacks\n";
                  cout<<"\t(Red)\n";
                  cout<<"\tMISSILE[M]    - Provides one missile(Max 1)\n";
                  cout<<"\t(Purple)\n";
                  cout<<"\tBOMB[B]       - Provides two barrier bombs(Max 2)\n";
                  cout<<"\t(Yellow)\n";
                  cout<<"\tTIMEBOMB[TB]  - Provides two barrier bombs(Max 2)\n";
                  cout<<"\t(Green & Red)\n";
                  cout<<"\tCANNON[C]     - Increases bullet hitpower by two times\n";
                  cout<<"\t(Cyan)\n";
                  cout<<"\tATOMIZER[A]   - Tank can pass through barriers\n";
                  cout<<"\t(Cyan)\n";
                  cout<<"\nPress H/h to go back to help menu or M/m to go back to main menu.\n";
                  cin>>bc;
                   
                  if(bc== 'h' || bc== 'H')
                  goto hlabel;
    }
    else if(hch==2)    
    {
                  cout<<"New Game starts a new battle.\n";
                  
                  cout<<"Player 1 Controls:\n";
                  cout<<"UP     - Move Up\n";
                  cout<<"DOWN   - Move Down\n";
                  cout<<"LEFT   - Move Left\n";
                  cout<<"RIGHT  - Move Right\n";
                  cout<<"ENTER  - Fire Bullet\n";
                  cout<<"RSHIFT - Fire Missile\n";
                  cout<<"+ENTER\n";
                  cout<<"P      - Explode Barrier Bomb\n";
                  cout<<"RSHIFT - Plant Time Bomb\n";
                  cout<<"   + P\n";
                  cout<<"RSHIFT - Activate/Deactivate Shadow Mode\n";
                  cout<<"   + O\n";
                  cout<<"U      - Pick Up Opponent Key\n";
                  cout<<"I      - Drop Opponent Key\n";
                  cout<<"L      - Enter Vortex\n";
                                    
                  cout<<"\nPlayer 2 Controls:\n";
                  cout<<"W      - Move Up\n";
                  cout<<"S      - Move Down\n";
                  cout<<"A      - Move Left\n";
                  cout<<"D      - Move Right\n";
                  cout<<"SPACE  - Fire Bullet\n";
                  cout<<"LSHIFT - Fire Missile\n";
                  cout<<"+SPACE\n";
                  cout<<"X      - Explode Barrier Bomb\n";
                  cout<<"LSHIFT - Plant Time Bomb\n";
                  cout<<"   + X\n";
                  cout<<"LSHIFT - Activate/Deactivate Shadow Mode\n";
                  cout<<"   + C\n";
                  cout<<"V      - Pick Up Opponent Key\n";
                  cout<<"B      - Drop Opponent Key\n\n";
                  cout<<"F      - Enter Vortex\n";
                  cout<<endl;
                  cout<<"ESCAPE - Exit To Main Menu\n";
                  cout<<"\nPress H/h to go back to help menu or M/m to go back to main menu.\n";
                  cin>>bc;
                   
                  if(bc== 'h' || bc== 'H')
                  goto hlabel;
    }
    else if(hch==3)    
    {
                  cout<<"Map Editor lets you create your own Maps(PLay Area)\n";
                  cout<<"The Map is a tile based play area.\n";
                  cout<<"\nControls:\n";
                  cout<<"LMOUSE - Place Tile\n";
                  cout<<"RMOUSE - Erase Tile\n";
                  cout<<"S      - Save Map\n";
                  cout<<"O      - Open Saved Map\n";
                  cout<<"C      - Clear Map\n";
                  cout<<"R      - Generate Random Map\n";
                  cout<<"UP     - Increase Tile Density In Random Map\n";
                  cout<<"DOWN   - Decrease Tile Density In Random Map\n";
                  cout<<"B      - Ground Bomb Tile\n";
                  cout<<"U      - Horizontal Bomb Tile\n";
                  cout<<"I      - Vertical Bomb Tile\n";
                  cout<<"T      - Barrier Tile\n";
                  cout<<"Y      - Quantum Barrier Tile\n";
                  cout<<"V      - Vortex Tile\n";
                  cout<<"H      - Tank1 Key Tile\n";
                  cout<<"J      - Tank2 Key Tile\n";
                  cout<<"K      - Tank1 Detonating Site Tile\n";
                  cout<<"L      - Tank2 Detonating Site Tile\n";
                  cout<<"1      - Tank1 Initial Position Tile\n";
                  cout<<"2      - Tank2 Initial Position Tile\n";
                  cout<<"\nBasic Tile Colour Codes:\n";
                  cout<<"White  - Barrier Tile\n";
                  cout<<"Red    - Ground Bomb Tile\n";
                  cout<<"\nPress H/h to go back to help menu or M/m to go back to main menu.\n";
                  cin>>bc;
                   
                  if(bc== 'h' || bc== 'H')
                  goto hlabel;
    }
    else if(hch==4)    
    {
    }
    else
    {
    }
    }
    
    else if(ch==4)
    {
         int chc;
         slabel:
                system("Cls");
         cout<<"\n                    Settings Menu\n";
         cout<<"1.Music Settings\n2.SFX Settings\n3.SFX Volume\n4.Game Speed\n5.Number Of Hits\n6.Map File Name\n7.Power Ups\n8.High(Sprite) Graphics\n9.Go Back To Main Menu\n";
         cout<<"Enter your choice:\n";
         cin>>chc;
         if(chc==1)
         {
                  char chch;
                  cout<<"\nMusic:";
                  if(mch==1)
                  cout<<"On\n";
                  else if(mch==0)
                  cout<<"Off\n";
                  cout<<"Press C for changing,S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else if(chch=='C' || chch=='c')
                  {
                       mch++;
                       mch=mch%2;
                  }
                  else
                  {
                  }
         }
         
         else if(chc==2)
         {
                  char chch;
                  cout<<"\nSound Effects:";
                  if(sch==1)
                  cout<<"On\n";
                  else if(sch==0)
                  cout<<"Off\n";
                  cout<<"Press C for changing,S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else if(chch=='C' || chch=='c')
                  {
                       sch++;
                       sch=sch%2;
                  }
                  else
                  {
                  }
         }
         else if(chc==3)
         {
              
              cout<<"\nCurrent SFX Volume:"<<sv<<endl;
              cout<<"Enter new volume(0-255):";
              cin>>sv;
              if(sv>=255)
              sv=255;
              if(sv<=0)
              sv=0;
              char chch;
              cout<<"Press S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else
                  {
                  }

         }
         else if(chc==4)
         {
              
              cout<<"\nCurrent Game Speed:"<<gs<<endl;
              cout<<"Lower the Number, Higher is the Game Speed.\n";
              cout<<"Enter New Game Speed:";
              cin>>gs;
              if(sv>=255)
              sv=255;
              if(sv<=0)
              sv=0;
              char chch;
              cout<<"Press S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else
                  {
                  }

         }
         else if(chc==5)
         {
              
              cout<<"\nCurrent Number Of Hits Required:"<<fnb<<endl;
              cout<<"Enter Number Of Hits Required:";
              cin>>fnb;
              if(sv>=255)
              sv=255;
              if(sv<=1)
              sv=1;
              char chch;
              cout<<"Press S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else
                  {
                  }

         }
         else if(chc==6)
         {
              
              cout<<"\nCurrent Map File Name:"<<mapn<<endl;
              cout<<"Enter New Map File Name:"<<endl;
              cin>>mapn;
                            char chch;
              cout<<"Press S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else
                  {
                  }

         }
         
         else if(chc==7)
         {
                  char chch;
                  cout<<"\nPower Ups are:";
                  if(puc==1)
                  cout<<"On\n";
                  else if(puc==0)
                  cout<<"Off\n";
                  cout<<"Press C for changing,S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else if(chch=='C' || chch=='c')
                  {
                       puc++;
                       puc=puc%2;
                  }
                  else
                  {
                  }
         }
         else if(chc==8)
         {
                  char chch;
                  cout<<"\nHigh(Sprite) Graphics:";
                  if(hgf==1)
                  cout<<"On\n";
                  else if(hgf==0)
                  cout<<"Off\n";
                  cout<<"Press C for changing,S for settings menu or M to go back to Main Menu.\n";
                  cin>>chch;
                  if(chch=='S' || chch=='s')
                  goto slabel;
                  else if(chch=='M' || chch=='m')
                  {
                  }
                  else if(chch=='C' || chch=='c')
                  {
                       hgf++;
                       hgf=hgf%2;
                  }
                  else
                  {
                  }
         }
         else if(chc==9)
         {
         }
         else
         {
             goto slabel;
         }     
         
    ofstream fout;
    fout.open("Data Files\\Settings.txt",ios::out);
    fout<<mch<<"\n"<<sch<<"\n"<<sv<<"\n"<<gs<<"\n"<<fnb<<"\n"<<mapn<<"\n"<<puc<<"\n"<<hgf<<"\n";
    fout.close();   
    }
    
    else if(ch==5)
    {
         ofstream fout;
         fout.open("Data Files\\Match Stats.txt",ios::app);
         fout<<"End of Session.\n\n";
         fout.close();
       ex=1;
    }
    else
    {
    }
    } while (ex!=1);
    system("PAUSE");
    return EXIT_SUCCESS;
}
