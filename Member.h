#include<iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>
void Member_Entryfun();
using namespace std;
int yr,mon,dy,id,redays,i;
class Member_Entry
{
 protected:
 	char name[30];
	int member_id;
	char adress[50];
	char phone_No[20];
	char Email[40];
	char Username[30];
	char password[20];
 public:
 	void getMemberData();
 	void showMemberData() const;
 	void showMemberData1() const;
	void storeMember();
 	void readMemberRecord();
 	void searchMemberRrcord();
 	void searchMemberRrcordbyname();
	void delMemberRecord();
 	void updateMemberRecord(int);
 	void renewal();
 	void showrenewedMembers();
 	void renewalfun();
 	void Member_Entryfun();
 	void chkrenewal_finished();
 };
 void Member_Entry::getMemberData()
 {
 	char copyname[30];
 	fflush(stdin);
 	getname:                                    //if name is input wrong return here
	cout<<"Enter name of member   : ";
 	cin.getline(name,30);
 	strcpy(copyname,name);
 	for(int i = 0 ; i < strlen(name) ; i++)
 	{
 		if(isalpha(name[i]) || name[i] == ' ')
 		continue;
 		if(!isalpha(name[i]))
 		{
			cout<<"\nName cannot contain anything except alphabets! Re-Enter\n";
 			goto getname;
		}
	}
	getid:                                               // if id is already present in file returns here
 	while(1)
 	{
	cout<<"Enter the member id    : ";
 	cin>>member_id;
 	if(cin.good())
 	break;
	cin.clear();
	cout<<"\nIncorrect input! Enter a valid id\n"<<endl;
	cin.ignore(20,'\n');
    }
    int i = member_id;
    ifstream chkmem;
    chkmem.open("Member_Entry.dat",ios::in|ios::binary);
    if(chkmem.fail())
    {
    	goto getadress;                //if 1st member entry then goto without comparing with file
	}
    chkmem.read(reinterpret_cast<char*>(this),sizeof(*this));
    while(!chkmem.eof())
    {
    	if(i == member_id)
    	{
    		cout<<"\nThis id already exist for "<<name <<" ! Re-Enter\n";
    		chkmem.close();
     	    goto getid;
        }
    	chkmem.read(reinterpret_cast<char*>(this),sizeof(*this));
	}
	chkmem.close();
	getadress:                                           //control comes here if id does not match or 1st member
	member_id = i;
	strcpy(name,copyname);
 	fflush(stdin);
 	cout<<"Enter the adress of member   : ";
 	cin.getline(adress,50);
 	char copyadd[50];
 	strcpy(copyadd,adress);
 	getphone:
 	cout<<"Enter phone number of member  : ";
 	cin.getline(phone_No,20);
 	for(int i = 0 ; i < strlen(phone_No) ; i++)
 	{
 		if(isdigit(phone_No[i]))
 		continue;
 		if(!isdigit(phone_No[i]))
 		{
 			cout<<"\nYou cannot put anything except digits in phone number\n";
		    goto getphone;
		}
	}
	if(strlen(phone_No) != 10)
	{
	     MessageBox(NULL,"Phone number must have 10 digits","Renter!", MB_OK | MB_ICONEXCLAMATION);
		 goto getphone;
	}
	char copyph[20];
	strcpy(copyph,phone_No);
 	cout<<"Enter the Email of member  : ";
 	cin.getline(Email,40);
 	char copyemail[40];
 	strcpy(copyemail,Email);
 	getuserpass:
 	cout<<"Enter the user name      : ";
 	cin.getline(Username,30);
 	setpass:
 	cout<<"Set password      : ";
 	{
 		for(int i = 0;;)
 		{
 		    char a = getch();
 			if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
 			{
 				password[i] = a;
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
				password[i] = '\0';
				break;
			}
	    }
		if(strlen(password) < 5)
		{
			cout<<"\nPassword should be atleast 6 digit long ! \n\t\tEnter again\n";
			goto setpass;
		}
	}
	char userchk[20];
	char passchk[20];
	strcpy(userchk,Username);
	strcpy(passchk,password);
	ifstream chk;
	chk.open("Member_Entry.dat",ios::in|ios::binary);
	if(chk.fail())
	{
		goto out;
	}
	chk.read(reinterpret_cast<char*>(this),sizeof(*this));
	while(!chk.eof())
	{
		if(!strcmp(userchk,Username) && !strcmp(passchk,password))
		{
			cout<<"\nTwo members cannot have same user name and passsword\n";
			goto getuserpass;
		}
		chk.read(reinterpret_cast<char*>(this),sizeof(*this));
	}
	out:
	member_id = i;
	strcpy(name,copyname);
	strcpy(adress,copyadd);
	strcpy(phone_No,copyph);
	strcpy(Email,copyemail);
	strcpy(Username,userchk);
	strcpy(password,passchk);
	}
   void Member_Entry::showMemberData() const
   {
 	cout<<"Member Name      : "<<name<<endl;
 	cout<<"Member ID        : "<<member_id<<endl;
 	cout<<"Member Address    : "<<adress<<endl;
 	cout<<"Member Phone_No  : "<<phone_No<<endl;
 	cout<<"Member Email     : "<<Email<<endl;
 	cout<<"Member User name : "<<Username<<endl;
 	cout<<"Member Password  : "<<password<<endl;
 	//cout<<"__________________________________"<<endl;
 }
 void Member_Entry::showMemberData1() const
 {
 	cout<<setw(22)<<name<<setw(7)<<member_id<<setw(20)<<adress<<setw(15)<<phone_No <<setw(30)<<Email<<setw(15)<<Username<<endl;
 }
 void Member_Entry::storeMember()
 {
 	ofstream strmem;
 	strmem.open("Member_Entry.dat",ios::app|ios::binary);
 	strmem.write(reinterpret_cast<char*>(this),sizeof(*this));
 	strmem.close();
 	cout<<"\nData saved to external file successfully\n";
 }
 void  Member_Entry::readMemberRecord()
 {
 	i=0;
 	ifstream readmem;
 	readmem.open("Member_Entry.dat",ios::in|ios::binary);
 	if(readmem.fail())
 	{
 		cout<<"Error in opening file ! File not found ";
 		return ;
	}
	cout<<"\n\nsr.no       Member name      id           adress      Phone number               Email                 username\n";
	cout<<"______________________________________________________________________________________________________________\n"<<endl;
	readmem.read(reinterpret_cast <char *>(this),sizeof(*this));
	while(!readmem.eof())
	{
		i++;
		cout<<setw(2)<<i;
		showMemberData1();
		readmem.read(reinterpret_cast <char *>(this),sizeof(*this));
	}
	readmem.close();
 }
 void Member_Entry::searchMemberRrcord()
 {
 	int  a,count = 0;
 	cout<<"Enter the Member id to search : ";
 	cin>>a;
 	ifstream searmem;
 	searmem.open("Member_Entry.dat",ios::in|ios::binary);
 	if(searmem.fail())
 	{
	cout<<"Error in opening file ! File not found ";
	return;
	}
	searmem.read(reinterpret_cast <char*>(this),sizeof(*this));
	while(!searmem.eof())
	{
		if(a == member_id)
		{
			cout<<"_________________________________\n";
			cout<<" \tSEARCHED MEMBER\n";
			cout<<"_________________________________\n";
			showMemberData();
			count++;
			break;
		}
		searmem.read(reinterpret_cast <char*>(this),sizeof(*this));
	}
	if(!count)
	{
		cout<<"There is no member with id "<<a<<endl;
	}
	searmem.close();
 }
 void Member_Entry::searchMemberRrcordbyname()
 {
 	ifstream searmem;
 	ofstream writemem;
 	writemem.open("Tempmem.dat",ios::app|ios::binary);
 	searmem.open("Member_Entry.dat",ios::in|ios::binary);
	searmem.read(reinterpret_cast <char*>(this),sizeof(*this));
	while(!searmem.eof())
	{
	    writemem.write(reinterpret_cast <char*>(this),sizeof(*this));
		searmem.read(reinterpret_cast <char*>(this),sizeof(*this));
    }
    searmem.close();
    writemem.close();
 	char cname[20];
 	ifstream sear;
 	ofstream here;
	cout<<"Enter the Member name to search : ";
	for(i = 0 ; i<20 ; i++)
	{
	int count = 0;
	sear.open("Tempmem.dat",ios::in|ios::binary);
	cname[i] = getche();
	system("cls");
	cout<<"Enter the Member name to search : ";
	for (int j = 0; j<=i ; j++)
	{
		cout<<cname[j];
	}
	cout<<"\n\n      Member name      id           adress      Phone number               Email                 username\n";
	cout<<"_____________________________________________________________________________________________________\n"<<endl;
	sear.read(reinterpret_cast <char*>(this),sizeof(*this));
	while(!sear.eof())
	{
		if(toupper(cname[i] )== name[i] || (tolower (cname[i]) == name[i]))
		{
			count++;
			cout<<setw(18)<<name<<setw(7)<<member_id<<setw(20)<<adress<<setw(15)<<phone_No <<setw(30)<<Email<<setw(15)<<Username<<endl;
			here.open("ABC.txt",ios::app|ios::binary);
			here.write(reinterpret_cast <char*>(this),sizeof(*this));
			here.close();
		}
    sear.read(reinterpret_cast <char*>(this),sizeof(*this));
   }
    sear.close();
    remove("Tempmem.dat");
    rename("ABC.txt","Tempmem.dat");
    if(!count)
    {
    	remove("Tempmem.dat");
        cout<<"\nyour searched record does not exist\n";
		return;
	}
}
remove("Tempmem.dat");
}
 void Member_Entry::delMemberRecord()
 {
 	int  a;
 	while(1)
 	    {
 	    cout<<"Enter the member id to delete : ";
 	    cin>>a;
 	    if(cin.good())
 	    break;
 	    cin.clear();
 	    cout<<"\t\t\tInvalid choice enter a valid choice"<<endl;
 	    cin.ignore(10,'\n');
		}
 	int count = 0;
 	ifstream seelogin;
    seelogin.open("Logedin_Members.dat",ios::in|ios::binary);
    if(seelogin.fail() )
	{
		goto deleted;
	}
	seelogin.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!seelogin.eof())
	{
    	if(a == member_id)
    	{
		    cout<<"\nThis member is logged into your system you cannot delete this member until he/she is logged out\n";
	        return;
	    }
	    seelogin.read(reinterpret_cast<char *>(this),sizeof(*this));
    }
    deleted:
	seelogin.close();
	ofstream outfile;
 	ifstream infile;
 	infile.open("Member_Entry.dat",ios::in|ios::binary);
 	if(infile.fail())
 	{
 		cout<<"Error in openning file ! File not found ";
 		return;
	}
	outfile.open("tempmem.dat",ios::out|ios::binary);
	infile.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!infile.eof())
	{
		if(a == member_id)
		{
			cout<<"_________________________________\n";
			cout<<" \tDELETING MEMBER\n";
			cout<<"_________________________________\n";
			showMemberData();
            cout<<"\n\nAre you sure you want to Delete (y/n)?\n";
 			if( getche() == 'n' ||  getche() == 'N')
 			{
 			outfile.close();
 			remove("tempmem.dat");
 		    return;
 		    }
		    count++;
	    }
		if(a != member_id)
		outfile.write(reinterpret_cast<char *>(this),sizeof(*this));
		infile.read(reinterpret_cast<char *>(this),sizeof(*this));
	}
	infile.close();
	outfile.close();
	remove("Member_Entry.dat");
	rename("tempmem.dat","Member_Entry.dat");
	if(!count)
	cout<<"There is no member with id "<<a<<endl;
	if(count)
	cout<<"Record deleted successfully";

 }
 void Member_Entry::updateMemberRecord(int a)
 {
 	fflush(stdin);
 	int count = 0;
 	ifstream seelogin;
	seelogin.open("Logedin_Members.dat",ios::in|ios::binary);
	if(seelogin.fail() )
	goto update;
	seelogin.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!seelogin.eof())
	{
		if(a == member_id)
			{
			cout<<"\nThis member is logged into your system you cannot Update this member until he/she is logged out\n";
	        return;
		    }
		    seelogin.read(reinterpret_cast<char *>(this),sizeof(*this));
	}
	seelogin.close();
	update:
 	fstream inoutfile;
 	inoutfile.open("Member_Entry.dat",ios::in|ios::out|ios::ate|ios::binary);
 	inoutfile.seekg(0);
	 inoutfile.read(reinterpret_cast<char *>(this),sizeof(*this));
 	while(!inoutfile.eof())
 	{
 		if(a == member_id)
 		{
 			cout<<"_________________________________\n";
			cout<<" \tUPDATING MEMBER\n";
			cout<<"_________________________________\n";
			showMemberData();
            cout<<"\n\nAre you sure you want to update (y/n)?\n";
 			if(getche() == 'n' || getche() == 'N')
 			return;
 			system("cls");
			cout<<"\t\t\t\t Enter new data\n";
			getMemberData();
 			inoutfile.seekp(inoutfile.tellp()-sizeof(*this));
 			inoutfile.write(reinterpret_cast<char *>(this),sizeof(*this));
 			count++;
		}
		inoutfile.read(reinterpret_cast<char *>(this),sizeof(*this));
	}
	inoutfile.close();
	if(!count)
	{
		cout<<"The record you want to update does not exist";
	}
	if(count)
	{
		cout<<"Record updated successfully";
	}
 }
 void Member_Entry::renewal()
 {
 	int count = 0,inid;
	fflush(stdin);
	cout<<"\nEnter id of member which you want to renew : ";
	cin>>inid;
	ifstream infile,chk;
	ofstream outfile;
	chk.open("Renewed_Members.dat",ios::in|ios::binary);
	if(chk.fail())
	goto out;
	chk.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	while(!chk.eof())
	{
		if(inid == member_id)
		{
			cout<<"Member is already renewed";
			while(getche()!='\r');
			return;
		}
		chk.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	}
	out:
	infile.open("Member_Entry.dat",ios::in|ios::binary);
	if(infile.fail())
	{
		cout<<"\nError in finding loged in members \n";
		return;
	}
	infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	while(!infile.eof())
	{
		if(inid == member_id)
		{
			cout<<"\nMember you want to renew found \n";
			char credit_num[20];
			cout<<"Enter credit card number for payment :";
			fflush(stdin);
			cin.getline(credit_num,20);
			char vcode[10];
			cout<<"Enter variefied code : ";
			cin.getline(vcode,10);
			getdays:
			cout<<"Enter number days for which you want renew member : ";
			cin>>redays;
			if(redays<7)
			{
				cout<<"\nMember cannot have renewal for less than 7 days \n";
				goto getdays;
			}
			ofstream renewedmem;
			renewedmem.open("Renewed_Members.dat",ios::app|ios::binary);
			renewedmem.write(reinterpret_cast<char *>(this),sizeof(*this));
			time_t z = time(NULL);
            tm tm = *localtime(&z);
            id = member_id;
            yr = tm.tm_year + 1900;
            mon = tm.tm_mon + 1;
            dy = tm.tm_mday;
            ofstream renewtime;
			renewtime.open("renew_time.dat",ios::app|ios::binary);
			renewtime << id <<" "<< yr <<" "<< mon<<" " << dy <<" "<< redays <<endl;
			renewtime.close();
			count++;
			return;
		}
		infile.read(reinterpret_cast<char *>(this),sizeof(Member_Entry));
	}
	outfile.close();
	infile.close();
	if(!count)
	{
		cout<<"\nThere is no member with this data\n";
	}
	if(count)
	{
		cout<<"\nMember renewed Successfully";
	}
	while(getche()!='\r');
 }
 void Member_Entry::showrenewedMembers()
 {
 	ifstream readrenewmem;
 	readrenewmem.open("Renewed_Members.dat",ios::binary);
 	if(readrenewmem.fail())
 	{
 		cout<<"Error in opening file ! File not found ";
 		return ;
	}
	cout<<"===========RENEWED MEMBERS=========="<<endl;
	cout<<"______________________________________"<<endl;
	readrenewmem.read(reinterpret_cast <char *>(this),sizeof(*this));
	while(!readrenewmem.eof())
	{
		showMemberData();
		ifstream retime;
		retime.open("renew_time.dat",ios::binary);
		while(!retime.eof())
		{
			retime >> id >> yr >> mon >> dy >> redays;
			if(id == member_id)
			{
			cout<<"Renewed date     : "<< yr << "-" << mon  << "-"<< dy<<endl;
		    cout<<"Renew days       : "<<redays<<" days"<<endl;
			cout<<"\n_______________________________\n";
		    break;
	        }
		}
		readrenewmem.read(reinterpret_cast <char *>(this),sizeof(*this));
	}
	readrenewmem.close();
	while(getche()!='\r');
 }
 void Member_Entry:: chkrenewal_finished()
 {
 	    ifstream retime;
		retime.open("renew_time.dat",ios::binary);
		if(!retime)
		{
			cout<<"file not found \n";
			return;
		}
		retime >> id >> yr >> mon >> dy >> redays;
		while(!retime.eof())
		{
			cout<<"Member id        : "<<id<<endl;
			cout<<"Renewed date     : "<< yr << "-" << mon  << "-"<< dy<<endl;
		    cout<<"Renew days       : "<<redays<<" days"<<endl;
		    int k = dy + redays , y = yr  , m = mon;
			for(k = k ; k > 31;)
 	        {
 	        if(m == 1|| m == 3|| m == 5|| m == 7|| m == 8|| m == 10|| m == 12)
 	   	    k-= 31;
	        else if(m == 4|| m == 6|| m == 9|| m == 11)
 	   	    k-= 30;
	        else
		    {
		    if(y%4 == 0 || y%100 == 0)
 	   	    k-= 29;
 		    else if(y%4 != 0 || y%100 != 0)
 	   	    k-= 28;
 	        }
 	        m++;
		        if(m >12)
		        {
			    int tempyear = m/12;
			    y+= tempyear;
			    m = m%12;
		        }
		   }
		   cout<<"Finishing date   : "<< y << "-" << m << "-"<< k <<endl;
		    time_t z = time(NULL);
            tm tm = *localtime(&z);
            id = member_id;
            yr = tm.tm_year + 1900;
            mon = tm.tm_mon + 1;
            dy = tm.tm_mday;
            cout<<"Current Date     : "<<yr << "-" << mon << "-"<<  dy<<endl;
            if(((y*365*24)+(m*30*24)+(k*24)) < ((yr*365*24)+(mon*30*24)+(dy*24)))
            cout<<"\t\t\tRenewal finished \n";
           cout<<"\n_______________________________\n";
           retime >> id >> yr >> mon >> dy >> redays;
		}
		while(getche()!='\r');
 }
 void Member_Entry::Member_Entryfun()
 {
 	int  choice;
 	while(true)
 	{
 	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout<<"\t\t\t\t MENU/MASTER ENTRY/MEMBER ENTRY         ";
    cout<<    "\n\t\t\t\t _______________________________";
    cout<<    "\n\t\t\t\t|                               |";
	cout << "\n\t\t \t \t|     1. Add Member             |";
    cout << "\n \t\t\t \t|     2. Show Members           |";
    cout << "\n \t\t\t \t|     3. Search Member by id    |";
	cout << "\n \t\t\t \t|     4. Search Member by name  |";
	cout << "\n \t\t\t \t|     5. Delete Member          |";
	cout << "\n \t\t\t \t|     6. Update Member          |";
	cout << "\n \t\t\t \t|     7. Return                 |\n";
    cout<<  "\t\t    \t\t|_______________________________|\n";
	cout << "\n\n";
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
 	switch(choice)
 	{
 		case 1:
 			char ch;
 			do
 			{
 			system("cls");
 			cout<<"\t\t\t=========ENTER NEW MEMBER DATA==========\n";
 			getMemberData();
			 storeMember();
 	        cout<<"\n\nDo you want to add another member (y/n)"<<endl;
 	        cin>>ch;
 	        }
 	        while(ch == 'y'|| ch == 'Y');
 	        break;
 	    case 2:
 	    	system("cls");
		    readMemberRecord();
			while(getche() != '\r');
			break;
		case 3:
			system("cls");
			searchMemberRrcord();
			while(getche() != '\r');
			break;
		case 4:
			system("cls");
			searchMemberRrcordbyname();
			while(getche() != '\r');
			break;
		case 5:
			system("cls");
			delMemberRecord();
			while(getche() != '\r');
			break;
		case 6:
			system("cls");
			int a;
			cout<<"Enter the member id to Update: ";
 	        cin>>a;
			updateMemberRecord(a);
			while(getche() != '\r');
			break;
		case 7:
			return ;
			break;
		default:
		    cout<<"Invalid choice ! Renter ";
		    return Member_Entryfun();
		    break;
	}
    }
 }
 void Member_Entry:: renewalfun()
 {
 	int ch;
 	system("cls");
    cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout<<"\t\t\t       MENU/CAFE MANAGMENT/RENEWAL         \n";
    cout<<     "\t\t\t    ________________________________\n";
    cout<<     "\t\t\t   |                                |";
	cout << "\n\t\t \t   |     1. Renew a member          |";
    cout << "\n \t\t\t   |     2. Show Renewed Members    |";
    cout << "\n \t\t\t   |     3. Check renewal           |";
	cout << "\n \t\t\t   |     4. Back                    |";
    cout << "\n \t\t\t   |________________________________|";
	cout << "\n\n\n";
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
		    renewal();
		    return renewalfun();
			break;
		case 2:
			system("cls");
			showrenewedMembers();
			return renewalfun();
			break;
		case 3:
			system("cls");
			chkrenewal_finished();
			return renewalfun();
			break;
		case 4:
			system("cls");
			return;
			break;
	}
 }
