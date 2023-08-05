//PROGRAM TO SEARCH FOR WORD IN DICTIONARY

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<dos.h>
#include<graphics.h>
#include<time.h>

/*
THE FILES THAT ARE USED IN THIS PROGRAM ARE

 -> 12DICT.txt          - Original Dictionary File
 -> 12LISBIN.txt        - File Containing List of Words with Memory Location in File
 -> 12SUGG.txt          - File Containing Words for Suggestion
 -> 12NEW.txt           - File Containing User Defined Words
 -> 12NLIS.txt          - File Containing List of user Defined Words With Location
 -> 12NSUGG.txt         - File Containing List of User Defined Words for Suggestion

*/


int FOUND=0;  //TO FLAG WHETHER WORD IS FOUND OR NOT


void worddir(char srcfil[],char destfil[]) //TO CREATE A WORD LIST WITH LOCATION

	{
	 ifstream fin;
	 ofstream fout;

	 fin.open(srcfil,ios::binary);
	 fout.open(destfil);

	 char buf[20],ch;

	 while(!fin.eof())
		{fin.get(ch);
		 if(ch=='\n')
			{
			 fin.getline(buf,20,' ');
			 fout<<buf<<endl;
			 fout<<fin.tellg();

			}
		}

	 fin.close();
	 fout.close();

	}



//FUNTION TO CONVERT NUM IN STRING TO int TYPE
unsigned long int conv(char pos[100])
	{
	 unsigned long int i=0;
	 while(pos[i])
		i++;
		--i;

	 unsigned long int p=i,num=0,w,temp;

	 for(unsigned long int count=0;count<=i;count++,p--)
		{
		 w=pow(10,p);
		 temp=(unsigned long int)pos[count]-48;
		 num=num+(w*temp);

		}

	 return num;
	}


void suggest(char srcfil[],char destfil[]) //TO CREATE FILE FOR WORD SUGGESTION

	{
	 ifstream fin;
	 ofstream fout;

	 fin.open(srcfil,ios::binary);   //12DICT.txt
	 fout.open(destfil); //12SUGG

	 char buf[20],ch;

	 while(!fin.eof())
		{
		 fin.get(ch);
		 if(ch=='\n')
			 {
			  fin.getline(buf,20,' ');
			  fout<<buf;
			 }
		}
	 outtextxy(300,310,"UPDATED FILES READY FOR USE");
	 delay(1000);


	 fout.close();

	 fin.close();
	 fout.clear();

	}


//TO SEARCH FOR WORD IN LIST WITH POSITION
unsigned long int search(char word[],char srcfile[])
	{
	 ifstream f;

	 f.open(srcfile);

	 char buf[100],pos[100];

	 char flag='n';

	 while(!f.eof())
		{
		 f.getline(buf,100);
		 if(strcmpi(word,buf)==0)
			{
			 if(flag=='n')
			 FOUND=1;
			 flag='y';
			 f.getline(pos,100);
			}

		}


	 unsigned long int ret;
	 if(flag=='y')
		ret=conv(pos);
	 else
		ret=0;

	 return ret;
       }



//TO ADD NEW WORD TO DICTIONARY

void newword()
	{int gd=DETECT,gmode;
	 initgraph(&gd,&gmode,"C:\\TURBOC3\\BGI");

	 clearviewport();

	 ofstream f;

	 f.open("12NEW.txt",ios::app);

	 char word[20],meaning[1000];

	 cout<<"NEW WORD:"<<endl;

	 gets(word);

	 cout<<endl<<"MEANING:"<<endl;

	 gets(meaning);

	 f<<endl<<endl<<word<<' '<<meaning<<endl<<endl;

	 outtextxy(200,200,"NEW WORD ADDED TO DICTIONARY");

	 delay(1000);
	}


//TO MATCH ENTERED WORD WITH THOSE STORED IN ORIGINAL DICTIONARY
void match1(char word[],int size) //TO SUGGEST WORDS
	{
	 ifstream f1;

	 f1.open("12SUGG.txt");

	 char buf[50];

	 int flag=0;

	 while(flag==0)
		{
		  f1.getline(buf,50,'\n');

		  if(strncmpi(buf,word,size)==0)
			flag=1;

		  if(f1.eof()==1)
			flag=1;

		}


	 if(flag!=0) //DISPLAY NEXT FEW WORDS

	       {
		outtextxy(120,250,buf);

		for(int i=0,y=260;i<10;i++,y+=10)
			{
			 f1.getline(buf,50);
			 outtextxy(120,y,buf);
			}
	       }

	 if(f1.eof()==1)
		cout<<endl<<"Word not found in Original Dictionary"<<endl;
	}



//TO MATCH ENTERED WORD WITH THOSE STORED IN USER DICTIONARY
void match2(char word[],int size) //TO SUGGEST WORDS
	{
	 ifstream f1;

	 f1.open("12NSUGG.txt");

	 char buf[50];

	 int flag=0;

	 while(flag==0)
		{
		 f1.getline(buf,50,'\n');

		 if(strncmpi(buf,word,size)==0)
			flag=1;

		 if(f1.eof()==1)
			flag=1;

		}


	 if(flag!=0) //DISPLAY NEXT FEW WORDS

	       {
		outtextxy(400,250,buf);
	       }

	 if(f1.eof()==1)
		cout<<endl<<"Word not found in User Dictionary"<<endl;
	}


char buf[100]; //BUFFER TO STORE THE ENTERED WORD
	       //SAME VARIABLE USED BY enter() and main() FUNCTIONS

char ch;       //TO ACCEPT EACH LETTER AND TEST IT

int i;         //TO KEEP TRACK OF NUMBER OF LETTERS


void enter()   //TO ENTER THE WORD LETTER BY LETTER AND SHOW SUGGESTIONS

	{
	 int gd=DETECT,gm;
	 initgraph(&gd,&gm,"C:\\TC\\BGI");
	 setbkcolor(BLACK);

	 ch=' '; //INITIALISING VALUES
	 i=0;

	 clearviewport();

	 while(ch!=13)

		{clrscr();
		 clearviewport();

		 outtextxy(100,230,"DID YOU MEAN:");


		 for(int k=0;k<i;k++)  //DISPLAYING LETTER BY LETTER
			cout<<buf[k];


		 //MATCHING WORD ENTERED SO FAR WITH STORED WORDS

		 match1(buf,i);
		 match2(buf,i);

		 ch=getch();

		 if(ch==8)       //ASCII VALUE OF BACKSPACE
			i--;

		 else if(ch==13) //ASCII VALUE OF ENTER
			break;

		 else
			{
			 buf[i]=ch;
			 i++;
			}
		}
	 buf[i]='\0'; //TERMINATING STRING TO AVOID ERROR AFTER REPEATED USE

	}


void homescreen()
	{
	 cout<<"SELECT ONE OF THE OPTIONS GIVEN BELOW"<<endl;
	 cout<<"_____________________________________"<<endl<<endl;
	 cout<<"1.Search    2.Add New Words    3.Exit"<<endl;
	}


void main()
       {
	clock_t start,end;


	int gd=DETECT,gmode;

	initgraph(&gd,&gmode,"C:\\TURBOC3\\BGI");

	start=clock();

	outtextxy(300,290,"LOADING...PLEASE WAIT");

	outtextxy(300,300,"UPDATING FILES");

	worddir("12DICT.txt","12LISBIN.txt");

	suggest("12DICT.txt","12SUGG.txt");

	suggest("12NEW.txt","12NSUGG.txt");

	worddir("12NEW.txt","12NLIS.txt");

	end=clock();

	cout<<"Time Taken:"<<(end-start)/18<<" seconds";
	delay(1000);

	char choice;

	clrscr();

	clearviewport();

	homescreen();

	choice=getch();

	ifstream f1;

	ifstream f2;

	while(choice=='1')
		{
		 clearviewport();

		 enter();

		 clearviewport();
		 unsigned long int pos1=search(buf,"12LISBIN.txt");

		 unsigned long int pos2=search(buf,"12NLIS.txt");

		 f1.open("12DICT.txt",ios::binary);

		 f2.open("12NEW.txt",ios::binary);

		 if(FOUND==1)
			cout<<endl<<"WORD FOUND"<<endl;
		 else
			cout<<"WORD NOT FOUND"<<endl;

		 FOUND=0;

		 f1.seekg(pos1);

		 char meaning[2000];

		 f1.getline(meaning,1000);

		 cout<<"\n";

		 cout<<endl<<"MEANING:"<<endl;

		 puts(meaning);

		 f2.seekg(pos2);

		 f2.getline(meaning,1000);

		 cout<<"\n";

		 puts(meaning);

		 f1.close();

		 f2.close();

		 cout<<"*********************************"<<endl;

		 homescreen();

		 choice=getch();
		}

	if (choice=='2')
	       newword();

       getch();
       }