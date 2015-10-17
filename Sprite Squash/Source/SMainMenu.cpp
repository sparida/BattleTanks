#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    char innf[30];
    char outf[30];
    int ch; 
    ifstream i;
    i.open("Settings\\Settings.txt",ios::in);
    i>>innf;
    i>>outf;
    i.close();
do
{
    cout<<"1.Change Input File\n2.Change Output File\n3.Exit\n";
    cout<<"Enter choice:";
    cin>>ch;
    if(ch==1)
    {
    cout<<"\nEnter Input File Name:\n";
    cin>>innf;
    ofstream o;
    o.open("Settings\\Settings.txt",ios::out);
    o<<innf<<"\n";
    o<<outf<<"\n";
    o.close();
    cout<<"\n";         
    }
    else if(ch==2)
    {
    cout<<"\nEnter Output File Name:\n";
    cin>>outf;
    ofstream o;
    o.open("Settings\\Settings.txt",ios::out);
    o<<innf<<"\n";
    o<<outf<<"\n";
    o.close();
    cout<<"\n";         
    }
    else if(ch==3)
    {
         ch=3;
    }
} while(ch!=3);
    
    return EXIT_SUCCESS;
}
