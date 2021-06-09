#include <iostream>
#include <string>
#include <process.h>
#include <fstream>
#include "display.h"
#include "computer.h"
#include "Member.h"
#include "memberlogin.h"
#include "charges.h"
void valid(); int choice,x,we;
void Menu();
void Master_Entryfun();
void ComputerEntryfun();
void Member_Entryfun();
void cafe_managmentfun();
void booking();
using namespace std;
int main()
{
	while(getche() != '\r');
	system("COLOR 09");
	display();
	for(int i = 0 ; i < 2000000000 ; i++){}
	system("cls");
	system("COLOR 0C");
	displaypro();
	for(int i = 0 ; i < 2000000000 ; i++){}
	system("cls");
	system("COLOR 0E");
	displayroll();
	for(int i = 0 ; i < 2000000000 ; i++){}
	system("cls");
	system("COLOR 0B");
	displaywelcom();
	while(getche() != '\r');
	system("cls");
	system("COLOR 70");
	string username = "admin";
	string pass = "admin123";
	fflush(stdin);
	string iuser;
	char ipass[20];
	for(int i = 0 ; i<3 ; i++)
	{
	system("cls");
	cout << "\n\n\n\n\t\t\t      ====== LOG IN ======";
    cout << "\n\n\n\n\n";
    cout << "\n \t\t \t  Enter the User name : " ;
    getline(cin,iuser);
    cout << "\n\t\t\t     Enter password : ";
	{
 		char a;
 		for(int i = 0;;)
 		{
 			a = getch();
 			if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
 			{
 				ipass[i] = a;
 				i++;
 				cout<<"*";
			}
			if(a == '\b' && i >= 1)
			{
				cout<<"\b \b";
				i--;
			}
			if(a == '\r')
			{
				ipass[i] = '\0';
				break;
			}
	    }
    }
    if(iuser == username && ipass == pass)
	{
		cout<<"\n\n\t\t Successfully loged in ! Press Enter to continue \n";
		while(getche() != '\r');
		Menu();
	}
	cout<<"\n\n\t\t  User name or password incorrect ! Retry";
    while(getche() != '\r');
	}
 return 0;
}
void Menu()
{
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout << "\t\t\t\t           MENU         \n";
    cout << "\t\t\t\t ________________________\n";
    cout << "\t\t\t\t|                        |";
	cout << "\n\t \t\t \t|     1. Master Entry    |";
    cout << "\n \t\t\t \t|     2. Cafe Managment  |";
    cout << "\n \t\t\t \t|     3. Exit            |\n";
    cout << "\t\t\t    \t|________________________|\n";
	cout << "\n\n";
 	valid();
	switch(choice)
 	{
 		case 1:
 			Master_Entryfun();
		    break;
 		case 2:
		    cafe_managmentfun();
		 	break;
		 case 3:
		 	exit(0);
		 	break;
		default:
		cout<<"Invalid choice ! Re-Enter ";
		return Menu();
		break;  			 	
	}
}
void Master_Entryfun()
{
	Computer_Entry c;
	Member_Entry m;
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout << "\t\t\t\t    MENU/MASTER ENTRY         \n";
    cout << "\t\t\t\t ________________________\n";
    cout << "\t\t\t\t|                        |";
	cout << "\n\t \t\t \t|     1. Member Entry    |";
    cout << "\n \t\t\t \t|     2. Computer Entry  |";
    cout << "\n \t\t\t \t|     3. Exit            |\n";
    cout << "\t\t\t    \t|________________________|\n";
	cout << "\n\n";
	valid();
    switch(choice)
    {
        case 1:
        	m.Member_Entryfun();
        	Master_Entryfun();
        	break;
        case 2:
			c.ComputerEntryfun();
			Master_Entryfun();
			break;
		case 3:
			return Menu();
			break;	
		default:
		cout<<"Invalid choice ! Re-Enter! ";
		return Master_Entryfun();
		break;	
	}
}
void cafe_managmentfun()
{
	Member_Entry k;
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout<<"\t\t\t\t    MENU/CAFE MANAGMENT         \n";
    cout<<"\t\t\t\t ________________________\n";
    cout<<"\t\t\t\t|                        |";
	cout << "\n\t \t\t \t|     1. Booking         |";
    cout << "\n \t\t\t \t|     2. Charges         |";
    cout << "\n \t\t\t \t|     3. Renewal         |";
	cout << "\n \t\t\t \t|     4. Return          |\n";
    cout<<"\t\t\t    \t|________________________|\n";
	cout << "\n\n";
	valid();
    Charges c;
    switch(choice)
    {
    	case 1:
    		booking();
	        break;
	    case 2:
	    	system("cls");
		    c.chargesfun();
		    return cafe_managmentfun();
		    break;    
		case 3:
			system("cls");
		    k.renewalfun();
		    return cafe_managmentfun();
		    break;
	    case 4:
		    return Menu();
		    break;
		default:
		    cout<<"Invalid choice ! Re-Enter! ";
		    return cafe_managmentfun();
		    break;	    
	}
}
void booking()
{
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout<<"\t\t\t       MENU/CAFE MANAGMENT/BOOKING         \n";
    cout<<"\t\t\t _______________________________________\n";
    cout<<"\t\t\t|                                       |";
	cout << "\n\t \t \t|     1. Member log in                  |";
    cout << "\n \t\t \t|     2. Member log out                 |";
    cout << "\n \t\t \t|     3. Non Member User Log in         |";
	cout << "\n \t\t \t|     4. Logged in members              |";
	cout << "\n \t\t \t|     5. Which members used the systems ??  |";
	cout << "\n \t\t \t|     6. Return                         |\n";
    cout<<"\t\t    \t|_______________________________________|\n";
	cout << "\n\n";
    Member_login m;
    Computer_Entry c;
    valid();
    switch(choice)
    {
    	case 1:
    		case1:
    		system("cls");
	        if(c.searchComputerRecord())
	        {   
	        	cout<<"\t\t\tComputer you want to use found!\n\t\t\t Enter user name and password \n";
	            x = m.logintomemberid();
	            int i = x;
				if(x)
	        	{
	        	ifstream chk;
	        	chk.open("Using_comp.dat",ios::binary);
	        	if(chk.fail())
	        	goto newcomp;
	        	chk.read(reinterpret_cast<char *>(&c),sizeof(c));
	        	chk >> x ;
				while(!chk.eof())
	        	{
	        		if(i == x)
	        		{
					cout<<"computer already in use ";
	        		return;
	        	    }
	        	    chk.read(reinterpret_cast<char *>(&c),sizeof(c));
	        	    chk >> x ;
				}
				chk.close();
				newcomp:
	        	ofstream outcomp;
	        	outcomp.open("Using_comp.dat",ios::app|ios::binary);
	        	outcomp.write(reinterpret_cast<char *>(&c),sizeof(c));
	        	outcomp << x ; 
	        	outcomp.close();
	            }
			}
			else
			{
				cout<<"\nWant to Retry (y/n)? ";
				char ch;
				cin >>ch;
				if(ch == 'y' || ch == 'y')
				goto case1;
				else
				return booking();
			}
	        while(getche() != '\r');
	        return booking();
	        break;
	    case 2:
		    system("cls");
	        m.logout();
	        return booking();
			break;
		case 3:
			system("cls");
			cout<<"You are Logging in as a non member so \n"; 
			cout<<"1- Give us your required informations(so that we can add you to our member list ) \n";
			cout<<"2- Set your user name and password \n";
			cout<<"3- Then enter your user name and password to login\n\n";
	        m.nonuserlogin();
	        while(getche() != '\r');
	        return booking();
			break;
	    case 4:
		    system("cls");
	        m.showloggedin_mem();
	        while(getche() != '\r');
	        return booking();
	        break;
	    case 5:
		    system("cls");
	        m.showloggedout_mem();
	        while(getche() != '\r');
	        return booking();
	        break;    
	    case 6:
		    return cafe_managmentfun();
		    break;
		default:
		    cout<<"Invalid choice ! Re-Enter! ";
		    return booking();
		    break;    
	}
}
void valid()
{
	while(1)
 	    {
 	    cout << "\t\t\t\t Select Your Choice ->> ";
 	    cin>>choice;
 	    if(cin.good())
 	    break;
 	    cin.clear();
 	    cout<<"\t\t\tInvalid choice enter a valid choice"<<endl;
 	    cin.ignore(10,'\n');
		}
}
