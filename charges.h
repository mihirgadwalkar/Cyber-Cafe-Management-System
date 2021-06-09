#include<iostream>
#include<string.h>
#include<fstream>
#include<time.h>
#include<conio.h>
using namespace std;
int charge;
class Charges: public Time 
{
	public:
		void calcharges();
		void showallcharges();
		void chargesfun();
};
void Charges::calcharges()
{
	int a,chargerate,logintime_inmin,logoutime_inmin,time_used,count = 0,count_1 = 0;
	string name;
	while(1)
	{
	cout<<"Enter member id for which you want to calculate charges : ";
	cin>>a;
	if(cin.good())
 	break;
 	cin.clear();
 	cout<<"\t\t\tInvalid  enter a valid"<<endl;
 	cin.ignore(10,'\n');
    }
	ifstream calcha;
	fflush(stdin);
	calcha.open("login_time.dat",ios::out|ios::binary);
	if(calcha.fail())
	{
	cout<<"Error in findding logged in member";
	return;
    }
	calcha.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!calcha.eof())
	{	
		if(a == loggedin_mem_id)
		{
	       cout<<"\nLogin time = "<<hours<<":"<<minutes<<":"<<seconds;
		   	logintime_inmin =(date*24*60)+ (hours*60)+minutes;
		   	name = loggedin_mem_name;
		   	count_1++;
		   	break;
		}
		calcha.read(reinterpret_cast<char *>(this),sizeof(*this));
	}
	calcha.close();
	//openning logout time file
	ifstream  outime;
	outime.open("logout_time.dat",ios::out|ios::binary);
	if(outime.fail())
	goto out;
    outime.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!outime.eof())
	{	
		if(a == loggedin_mem_id)
		{
	       cout<<"\nLogout time = "<<hours<<":"<<minutes<<":"<<seconds;
	       logoutime_inmin = (date*24*60)+ (hours*60)+minutes;
	       count++;
	       break;
		}
	outime.read(reinterpret_cast<char *>(this),sizeof(Time));	
	}
	outime.close();
	out:
	if(count_1 == 1 && count == 0)
	{
		cout<<"\nMember is still loged in ! but charges till now \n";
		time_t z= time(NULL);
        tm tm=*localtime(&z);
		time_used = ((tm.tm_mday*24*60)+(tm.tm_hour*60)+tm.tm_min)-logintime_inmin;
		cout<<endl<<name <<" have used system for "<<time_used<<" minutes till now\n";
		while(1)
	{
	cout<<"Enter charge rate per minute : ";
	cin>>chargerate;
	if(cin.good())
 	    break;
 	    cin.clear();
 	    cout<<"\t\t\tInvalid charges ! Renter"<<endl;
 	    cin.ignore(10,'\n');
    }
	cout<<"charges = "<<chargerate*time_used;
	}
	if(count_1 == 1 && count == 1)
	{
	ofstream temp;
	temp.open("templogin.dat",ios::app|ios::binary);
	calcha.open("login_time.dat",ios::out|ios::binary);
	calcha.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!calcha.eof())
	{	
		if(a != loggedin_mem_id)
		{
			temp.write(reinterpret_cast<char *>(this),sizeof(*this));
	    }
		calcha.read(reinterpret_cast<char *>(this),sizeof(*this));
	}
	calcha.close();
	temp.close();
	remove("login_time.dat");
	rename("templogin.dat","login_time.dat");
	
	temp.open("templogout.dat",ios::app|ios::binary);
	calcha.open("logout_time.dat",ios::out|ios::binary);
	calcha.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!calcha.eof())
	{	
		if(a != loggedin_mem_id)
		{
			temp.write(reinterpret_cast<char *>(this),sizeof(*this));
	    }
		calcha.read(reinterpret_cast<char *>(this),sizeof(*this));
	}
	calcha.close();
	temp.close();
	remove("logout_time.dat");
	rename("templogout.dat","logout_time.dat");	
	time_used = logoutime_inmin-logintime_inmin;
    cout<<endl<<name <<" used system for "<<time_used<<" minutes\n";
    while(1)
	{
	cout<<"Enter charge rate per minute : ";
	cin>>chargerate;
	if(cin.good())
 	    break;
 	    cin.clear();
 	    cout<<"\t\t\tInvalid charges ! Renter"<<endl;
 	    cin.ignore(10,'\n');
    }
    charge = chargerate*time_used;
	cout<<"charges = "<<charge;
	ofstream charges;
	charges.open("All_charges.dat",ios::out|ios::app|ios::binary);
	charges << loggedin_mem_id <<" "<<charge<<" ";
	charges.close();
	}
	if(count_1 == 0 && count == 0)
	{
		cout<<"this member is not logged in";
	}
}
void Charges::showallcharges()
{
	ifstream incharge;
	incharge.open("All_charges.dat",ios::in|ios::binary);
	if(incharge.fail())
	{
		cout<<"Error in openning file! file not found";
		return;
	}
	incharge >> loggedin_mem_id >> charge;
	while(!incharge.eof())
	{
	cout<<"Member id : " << loggedin_mem_id <<endl;
	cout<<"Charges   : " <<charge<<endl;	
	cout<<"__________________"<<endl;
	incharge >> loggedin_mem_id >> charge;
    }
}
void Charges::chargesfun()
{
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout<<"\t\t\t\t  MENU/CAFE MANAGMENT/CHARGES          \n";
    cout<<     "\t\t    ____________________________________________________\n";
    cout<<     "\t\t   |                                                    |";
	cout << "\n \t\t   |     1. Calculate Charges for a particular member   |";
    cout << "\n \t\t   |     2. Show all charges                            |";
	cout << "\n \t\t   |     3. Back                                        |";
    cout << "\n \t\t   |____________________________________________________|";
	cout << "\n\n\n";
    int ch;
	while(1)
    {
    cout << "\t\t\t\t Select Your Choice ->> ";
    cin>>ch;
    if(cin.good())
 	break;
 	cin.clear();
 	cout<<"\t\t\tInvalid choice enter a valid choice"<<endl;
 	cin.ignore(10,'\n');
	}
	switch(ch)
	{
		case 1:
			system("cls");
		    calcharges();
		    while(getche() != '\r');
		    return chargesfun();
		    break;
		case 2:
			system("cls");
		    showallcharges();
		    while(getche() != '\r');
		    return chargesfun();
		    break;
		case 3:
			return; 
		default:
		cout<<"Invalid choice ! Renter ";
		return chargesfun();
		break;	   
	}
}
