/*
  - Steven Albert   (00000011011)
  - Evan Harsojo    (00000012185)
  - Reinard Johan   (00000013273)
*/

#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

void reset(int);
void deal(int,int);
void typerank(int);
void instruction(int);
bool check(int, int, int);
void cmp(int, int, string, string);
int rsl(int, string, int);
void printk(int);

void reset(int all[4][13])
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<13; j++)
		{
                all[i][j]=1;
        }
	}
}

bool check(int t, int c, int cards[])
{
	bool ok=false;
	for(int i=1; i<c; i++)
	{
		if(t==(cards[i-1]%13))
		{
			ok=true;
			break;
		}
	}
	return ok;
}

void deal(int all[4][13], int card[])
{
	int x;
	for(int i=1, j=1; i<=5; i++)
	{
		do
		{
                 long int rn=time(NULL)/(j+i)/(j*i);
            	 srand(rn);
	             x=(rand()%52);
                 j++;
		}
		while(all[x/13][x%13]==0 || check(x%13, i, card));
		card[i-1]=x;
		all[x/13][x%13]--;
	}
}

void typerank(int x)
{
	int length=16;
	if(x==55)cout<<"<fold>         ";
	else
	{
    	switch(x%13)
	    {
		            case 12: cout<<"King "; length-=5; break;
                    case 0: cout<<"Ace "; length-=4; break;
		            case 10: cout<<"Jack "; length-=5; break;
		            case 11: cout<<"Queen "; length-=6; break;
		            case 9: cout<<"10 "; length-=3; break;
		            default : cout<<x%13 + 1<<" "; length-=2;
        }
	    if(x/13==0){cout<<"diamond"; length-=7;} else
     	if(x/13==1){cout<<"club"; length-=4;} else
      	if(x/13==2){cout<<"heart"; length-=5;} else
       	if(x/13==3){cout<<"spade"; length-=5;}
	    for(int i=0; i<length-1; i++)cout<<" ";
    }
}

void instruction(int i)
{
	string instr, ins, todo;
	if(i==1){instr="d";todo="deal card";}else
	if(i==2){instr="c";todo="compare card";}else
	if(i==3){instr="r";todo="show result";}
	do
	{
		cout<<"Press "<<instr<<" to "<<todo<<" : ";
		cin>>ins;
	}
	while(ins!=instr);
}

void cmp(int ca1[], int ca2[], string p1, string p2)
{
     int ok=0, c1=0, c2=0;
     for(int f=0; f<5; f++)
     {
             for(int s=0; s<5; s++)
             {
                     if((ca1[f]%13)==(ca2[s]%13))
                     {
                                       if(ca1[f]<ca2[s])ca1[f]=55;
                                       else ca2[s]=55;
                                       break;
                     }
             }
     }
}

int rsl(int c1[5], string p, int pl)
{
     int sum=0, op=0;
     cout<<"Player "<<pl<<" ("<<p<<")";
     if(p=="You")cout<<"         : ";
     else cout<<"    : ";
     for(int o=0; o<5; o++)
     {
             int a;
             if(c1[o]==55) a=0;
             else
             {
                 switch(c1[o]%13)
                 {
                                 case 0: a=15; break;
                                 case 10:
                                 case 11:
                                 case 12: a=12; break;
                                 default: a=(c1[o]%13 + 1);
                 }
             }
             sum+=a;
             if(op==1 && a!=0)cout<<" + ";
             if(a!=0){cout<<a;op=1;}
     }
     cout<<" = "<<sum<<" points";
     return sum;
}

void printk(int a[5], string p, int pl)
{
     cout<<"Player "<<pl<<" ("<<p<<")";
     if(p=="You")cout<<"         :\n";
     else cout<<"    :\n";
     for(int i=0; i<5; i++)
     typerank(a[i]);
     cout<<"\n\n";
}

int main()
{
	int allcards[4][13], card1[5], card2[5], phase=1, c=0, total=52, p1, p2;
	string ply1, ply2, player, tryagain;
	reset(allcards);           
	cout<<"ATTENTION!! \"all inputs are case-sensitives\"\n\n";
    cout<<"Welcome to Card Game!"<<endl<<endl;
	
	do
	{
  		if(c>0)
		{
               total-=10;
               string res="";
			   if(total<10)
               {
                           cout<<"\"WARNING only 2 cards left in deck\" --> ";
                           cout<<"|| AUTO RESHUFFLE ALL CARDS ||"<<endl; 
                           res="Y";
               }
               else
               {
                   cout<<"\nDo you want to reset your deck? (Y/N) : ";
                   do{cin>>res;}
                   while(res!="Y" && res!="N");
               }
			   cout<<endl;
               if(res=="Y")
               {
                           cout<<"Your deck is reshuffled\n";
                           reset(allcards);
                           total=52;
               }
		}
		do
		{
			cout<<"Choose player (1: Player 1; 2: Player 2) : ";
			cin>>player;
		}
		while(player!="1" && player!="2");
		if(player=="1")
		{
                       p1=1;
                       p2=2;
			ply1="You";
			ply2="Computer";
		}
		else
		{
            p1=2;
            p2=1;
			ply1="Computer";
			ply2="You";
		}
		cout<<endl;
		instruction(phase);
		//bagian bagi kartu
		deal(allcards, card1);
		printk(card1, ply1, p1);
		deal(allcards, card2);
		printk(card2, ply2, p2);
        //bagian banding
		phase++;
		instruction(phase);
		cmp(card1, card2, ply1, ply2);
		printk(card1, ply1, p1);
		printk(card2, ply2, p2);
		//bagian result
		phase++;
		instruction(phase);
		int r1=rsl(card1, ply1, p1);
		cout<<"\n";
		int r2=rsl(card2, ply2, p2);
		//membandingkan nilai pemain
        if(r1>r2)
        {if(ply2=="You")cout<<"\nYou LOSE!\n"; else cout<<"\nYou WIN!\n";}
        else if(r2>r1)
        {if(ply1=="You")cout<<"\nYou LOSE!\n"; else cout<<"\nYou WIN!\n";}
        else cout<<"\nThe Game Result is DRAW\n";
        cout<<"\n";
	    //bagian lanjut/tidak permainan
		phase=1;
		do
		{
		        cout<<"Do you want to continue (Y/N) : ";
		        cin>>tryagain;
        }
        while(tryagain!="Y" && tryagain!="N");
		c++;
	}
	while(tryagain=="Y" || tryagain=="y");
	cout<<"\n\nThank You for Playing This Card Game!\n";        
	cout<<"\nThis game will closed in. . .\n";                      //tambahan
	long long int s, t;
	for(int exit=3; exit>=0; exit--)
	{
            s=time(NULL);
            do
	        { 
                 t=time(NULL);
            }
            while(t-s<1);
            cout<<"\a";
            if(exit==3)cout<<"*****\n    *\n   * \n    *\n*   *\n *** \n\n";
            if(exit==2)cout<<" *** \n*   *\n   * \n  *  \n *   \n*****\n\n";
            if(exit==1)cout<<" **  \n* *  \n  *  \n  *  \n  *  \n*****\n\n";
            if(exit==0)cout<<" *** \n*   *\n*   *\n*   *\n*   *\n *** \n";
    }
	return 0;
}
