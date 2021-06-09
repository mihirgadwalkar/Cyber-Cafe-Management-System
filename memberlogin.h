#include<iostream>
#include<string.h>
#include<fstream>
#include<time.h>
#include<conio.h>
using namespace std;
class Time
{
	public:
		char loggedin_mem_name[30];
		int loggedin_mem_id;
		int date;
		int hours;
		int minutes;
		int seconds;
};
class Member_login:public Member_Entry
{
public:
	int logintomemberid();
	void logout();
	void showloggedin_mem();
	void nonuserlogin();
	void showloggedout_mem();
};
int Member_login::logintomemberid()
{
	fflush(stdin);
	int count = 0,c = 0;
	char user_name[30];
	char pass_word[20];
	cout<<"Enter user name : ";
	cin.getline(user_name,30);
	cout<<"Enter password : ";
	{
 		for(int i = 0;;)
 		{
 			char a = getch();
 			if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
 			{
 				pass_word[i] = a;
 				i++;
 				cout<<"*";
			}
			if(a == '\b' && i >= 1)
			{
				cout<<"\b \b ";
				i--;
			}
			if(a == '\r')
			{
				pass_word[i] = '\0';
				break;
			}
		}
	}
	     ifstream chklogedinmem;
	     chklogedinmem.open("Logedin_Members.dat",ios::app|ios::binary);
	     chklogedinmem.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	     while(!chklogedinmem.eof())
	     {
	     	if(!strcmp(user_name,Username) && !strcmp(pass_word,password))
	     	{
			 cout<<"\nMember is already logged in\n";
			 return 0;
		    }
	     	chklogedinmem.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
		 }
		 ifstream infile;
	infile.open("Member_Entry.dat",ios::in|ios::binary);
	if(infile.fail())
 	{
	cout<<"\nError in openning file ! File not found\n ";
	return 0;
	}
	infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	while(!infile.eof())
	{
		if(!strcmp(user_name,Username) && !strcmp(pass_word,password))
		{
				cout<<"\nSuccessfully loged in";
				ofstream intime,outfile;
				ofstream logedinmem;
				logedinmem.open("Logedin_Members.dat",ios::app|ios::binary);
				logedinmem.write(reinterpret_cast<char *>(this),sizeof(Member_Entry));
				intime.open("login_time.dat",ios::app|ios::binary);
	            time_t z= time(NULL);
                tm tm = *localtime(&z);
		        Time t;
	            strcpy(t.loggedin_mem_name,name);
				t.loggedin_mem_id = member_id;
				       t.date = tm.tm_mday;
					   t.hours = tm.tm_hour;
					   t.minutes = tm.tm_min;
					   t.seconds = tm.tm_sec;
					   intime.write(reinterpret_cast<char *>(&t),sizeof(t));
					   intime.close();
				count++;
				return member_id;
				break;
		}
		infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
    }
    infile.close();
    if(!count)
    {
    char c;
    cout<<"\nUser name or password incorrect ! Try again (y/n)\n";
    cin>>c;
	if(c == 'y' || c == 'Y')
	logintomemberid();
    }
    return 0;
	infile.close();
}
void Member_login::logout()
{
	int count = 0,k;
	fflush(stdin);
	char ipass[20];
	char iuser[20];
	cout<<"Enter user name of member you want to logout : ";
	cin.getline(iuser,20);
	cout<<"Enter password of member you want to logout : ";
 		for(int i = 0;;)
 		{
 			char a = getch();
 			if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
 			{
 				ipass[i] = a;
 				i++;
 				cout<<"*";
			}
			if(a == '\b' && i >= 1)
			{
				cout<<"\b \b ";
				i--;
			}
			if(a == '\r')
			{
				ipass[i] = '\0';
				break;
			}
		}
	ofstream outfile,loginmem;
	ifstream infile;
	infile.open("Logedin_Members.dat",ios::in|ios::binary);
	if(infile.fail())
	{
		cout<<"\nError in finding loged in members \n";
		return ;
	}
	loginmem.open("temploginmem.dat",ios::out|ios::binary);
	outfile.open("logged_outmem.dat",ios::out|ios::app|ios::binary);
	infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	while(!infile.eof())
	{
		if(!strcmp(iuser,Username) && !strcmp(ipass,password))
		{
			outfile.write(reinterpret_cast<char *>(this),sizeof(Member_Entry));
			ofstream outime;
			outime.open("logout_time.dat",ios::app|ios::in|ios::binary);
			time_t z = time(NULL);
            tm tm = *localtime(&z);
	        Time w;
	            strcpy(w.loggedin_mem_name,name);
				w.loggedin_mem_id = member_id;
				       w.date = tm.tm_mday;
					   w.hours = tm.tm_hour;
					   w.minutes = tm.tm_min;
					   w.seconds = tm.tm_sec;
					   outime.write(reinterpret_cast<char *>(&w),sizeof(Time));
					   outime.close();
		    count++;
		}
		if(strcmp(iuser,Username) || strcmp(ipass,password))
	    loginmem.write(reinterpret_cast<char *>(this),sizeof(Member_Entry));
		infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));

	}
	if(count)
	{
		cout<<"\t\t\tMember logged out successfully\n";
	}
	if(!count)
	{
		cout<<"\nThe member you want to logout is not logged in\n";
	}
	infile.close();
	outfile.close();
	loginmem.close();
	remove("Logedin_Members.dat");
	rename("temploginmem.dat","Logedin_Members.dat");
	while(getche()!='\r');
}
void Member_login::showloggedin_mem()
{
	cout<<"...........................Loggedin Members.........................\n";
	ifstream infile;
	infile.open("Logedin_Members.dat",ios::in|ios::binary);
	if(!infile)
	{
		cout<<"Error in finding logged in members";
		return;
	}
	infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	while(!infile.eof())
	{
		showMemberData();
		cout<<"_______________________________\n";
		infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	}
	infile.close();
}
void Member_login::showloggedout_mem()
{
	cout<<"_______________________MEMBERS WHO LOGGED OUT OF SYSYTEMS_________________________\n";
	ifstream infile;
	infile.open("logged_outmem.dat",ios::in|ios::binary);
	if(!infile)
	{
		cout<<"Error in finding logged in members";
		return;
	}
	infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	while(!infile.eof())
	{
		showMemberData();
		cout<<"_______________________________\n";
		infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	}
	infile.close();
}
void Member_login::nonuserlogin()
{
	getMemberData();
	storeMember();
	system("cls");
	cout<<"\n\n Now Enter your user name and passward to login into system\n";
	logintomemberid();
}
