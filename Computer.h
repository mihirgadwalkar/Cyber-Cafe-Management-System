#include<iostream>
#include <string.h>
#include <fstream>
#include<conio.h>
#include<iomanip>

void ComputerEntryfun();
using namespace std;
class Computer_Entry
{
 protected:
 	char Computer_name[30];
	char ip_Adress[12];
	int memory;
	char processor_model[20];
	char motherbordcomp[20];
	char unique_code[20];

 public:
 	void getComputerData();
 	void showComputerData() const;
 	void storeComputer();
 	void readComputerRecord();
 	bool searchComputerRecord();
 	void searchComputerRecordEntry();
 	void delComputerRecord();
 	void updateComputerRecord();
 	void ComputerEntryfun();
};
 void Computer_Entry::getComputerData()
 {
 	int count = 0;
 	fflush(stdin);
	cout<<"Enter Computer Name : ";
 	cin.getline(Computer_name,30);
 	char copyname[30];
 	strcpy(copyname,Computer_name);
 	//ip adress 
 	getip:
 	cout<<"Enter IP Address of Computer : ";
 	cin.getline(ip_Adress,12);
 	for(int i = 0;i<strlen(ip_Adress);i++)
 	{
 		if(isdigit(ip_Adress[i]) || ip_Adress[i] == '.')
 		continue;
 		else
 		{
 			cout<<"\nIP address cannot have anything except digits and .\n";
 			goto getip;
		}
	}
	if(strlen(ip_Adress) < 4 || strlen(ip_Adress) > 12)
    {
    	cout<<"\nInvalid IP !!!!! Re-Enter\n";
    	goto getip;
	}
	for(int i = 0; i < strlen(ip_Adress) ; i++)
	{
		if(ip_Adress[i] == '.')
		count++;
	}
	if(count < 2)
	{
		cout<<"\nIP address must have atleast two \".\" \n";
		goto getip;
	}
	//ip adress checks finished
	char copyip[50];
	strcpy(copyip,ip_Adress);
 	while(1)
 	{
 	cout<<"Enter Computer Memory : ";
 	cin>>memory;
 	if(cin.good())
 	break;
 	cin.clear();
 	cout<<"Invalid Memory ! Re-Enter"<<endl;
 	cin.ignore(10,'\n');
    }
    int copymem;
    copymem = memory;
    fflush(stdin);
 	cout<<"Enter Processor Model : ";
 	cin.getline(processor_model,20);
 	char copympd[20];
 	strcpy(copympd,processor_model);
    cout<<"Enter Motherboard Company : ";
    cin.getline(motherbordcomp,20);
    char copycomp[20];
    strcpy(copycomp,motherbordcomp);
    setcode:
    cout<<"Enter Unique Code for Computer : ";
    cin.getline(unique_code,20);
    char copycod[20];
    strcpy(copycod,unique_code);
    ifstream chkcomp;
    chkcomp.open("Computer_Entry.dat",ios::in|ios::binary);
    if(chkcomp.fail())
    goto out;
	chkcomp.read(reinterpret_cast<char*>(this),sizeof(*this));
	while(!chkcomp.eof())
	{
		if(!strcmp(copycod,unique_code))
		{
			cout<<"Unique Code already exists\n ";
			goto setcode;
		}
		chkcomp.read(reinterpret_cast<char*>(this),sizeof(*this));
	}
	out:
		strcpy(Computer_name,copyname);
		strcpy(ip_Adress,copyip);
		memory = copymem ;
		strcpy(processor_model,copympd);
		strcpy(motherbordcomp,copycomp);
		strcpy(unique_code,copycod);
 }
 void Computer_Entry::showComputerData() const
 {
 	cout<<"Computer Name                : "<<Computer_name<<endl;
 	cout<<"Computer IP_Address          : "<<ip_Adress<<endl;
 	cout<<"Computer Memory              : "<<memory<<" GB"<<endl;
 	cout<<"computer Processor Model     : "<<processor_model<<endl;
 	cout<<"Computer Motherboard Company : "<<motherbordcomp<<endl;
 	cout<<"Computer Unique Code         : "<<unique_code<<endl;
 	cout<<"_________________________________________"<<endl;
 }
 void Computer_Entry::storeComputer()
 {
 	ofstream strcomp;
 	strcomp.open("Computer_Entry.dat",ios::app|ios::binary);
 	strcomp.write(reinterpret_cast<char*>(this),sizeof(*this));
 	strcomp.close();
 	cout<<"Data saved to external file successfully";
 }
 void Computer_Entry::readComputerRecord()
 {
 	ifstream readcomp;
 	readcomp.open("Computer_Entry.dat",ios::in|ios::binary);
 	if(readcomp.fail())
 	{
 		cout<<"Error in opening file !, file not found ";
 		return ;
	}
	cout<<"...........Computer Data from the file........."<<endl;
	readcomp.read(reinterpret_cast<char*>(this), sizeof(*this));
	while(!readcomp.eof())
	{
		showComputerData();
		readcomp.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	readcomp.close();
 }
void Computer_Entry::searchComputerRecordEntry()
 {
 	fflush(stdin);
 	char ip[20];
 	cout<<"Enter the unique code of Computer to search : ";
 	cin.getline(ip,20);
 	int count = 0;
 	ifstream searcomp;
 	searcomp.open("Computer_Entry.dat",ios::in|ios::binary);
 	if(searcomp.fail())
 	{
 		cout<<"Error in opening file !,file not found"; 
 		return;
	}
	searcomp.read(reinterpret_cast<char*>(this),sizeof(*this));
	while(!searcomp.eof())
 	{
 		if(!strcmp(ip,unique_code))
 		{
 			showComputerData();
 			count++;
 			return;
		}
		searcomp.read(reinterpret_cast<char*>(this),sizeof(*this));
	}
	if(!count)
	{
		cout<<"There is no computer with this unique code ";
        return;
	}
	searcomp.close();
 }
 bool Computer_Entry::searchComputerRecord()
 {
 	fflush(stdin);
 	char ip[20];
 	cout<<"Enter the unique code of Computer to search : ";
 	cin.getline(ip,20);
 	int count = 0;
 	ifstream seeusecomp;
 	seeusecomp.open("Using_comp.dat",ios::binary);
 	if(seeusecomp.fail())
 	{
 		goto seeout;
	}
 	seeusecomp.read(reinterpret_cast<char*>(this), sizeof(*this));
 	while(!seeusecomp.eof())
 	{
 		if(!strcmp(ip,unique_code))
 		{
 		cout<<"\t\t\tComputer already in use\n";	
 		return false;
 	    }
 		seeusecomp.read(reinterpret_cast<char*>(this), sizeof(*this));	
	}
	seeout:
	seeusecomp.close();
 	ifstream searcomp;
 	searcomp.open("Computer_Entry.dat",ios::in|ios::binary);
 	if(searcomp.fail())
 	{
 		cout<<"Error in openning file!,file not found"; 
 		return false;
	}
	searcomp.read(reinterpret_cast<char*>(this),sizeof(*this));
	while(!searcomp.eof())
 	{
 		if(!strcmp(ip,unique_code))
 		{
 			showComputerData();
 			count++;
 			return true;
		}
		searcomp.read(reinterpret_cast<char*>(this),sizeof(*this));
	}
	if(!count)
	{
		cout<<"There is no computer with this unique code ";
    return false;
	}
	searcomp.close();
 }
 void Computer_Entry::delComputerRecord()
 {
 	fflush(stdin);
 	char s[20];
 	cout<<"Enter the unique code of Computer to delete : ";
 	cin.getline(s,20);
 	int count = 0;
 	ofstream outfile;
 	ifstream infile;
 	infile.open("Computer_Entry.dat",ios::in|ios::binary);
 	if(infile.fail())
 	{
 		cout<<"Error in opening file!,file not found ";
 		return;
	}
	outfile.open("tempcomp.dat",ios::out|ios::binary);
	infile.read(reinterpret_cast<char *>(this),sizeof(*this));
	while(!infile.eof())
	{
		if(!strcmp(s,unique_code))
		{ 
		    cout<<"\t\t\tComputer you want to delete found !\n";
		    cout<<"Are you sure you want to Delete (y/n)?\n";
 			if(getche() == 'n' || getche() == 'N')
            {
            	outfile.close();
				remove("tempcomp.dat");	
				return;	
			}
		    count++;
	    }
	    deleted:
	    if(strcmp(s,unique_code))
		outfile.write(reinterpret_cast<char *>(this),sizeof(*this));
		infile.read(reinterpret_cast<char *>(this),sizeof(*this));
	}
	infile.close();
	outfile.close();
	if(!count)
	cout<<"the computer you want to delete does not exist";
	if(count)
	cout<<"Record deleted successfully";
	remove("Computer_Entry.dat");
	rename("tempcomp.dat","Computer_Entry.dat");
 }
 void Computer_Entry::updateComputerRecord()
 {
 	fflush(stdin);
 	char a[20];
 	cout<<"Enter the unique code of computer to Update that particular computer : ";
 	cin.getline(a,20);
 	int count = 0;
 	fstream inoutfile;
 	inoutfile.open("Computer_Entry.dat",ios::in|ios::out|ios::ate|ios::binary);
 	if(inoutfile.fail())
 	{
 		cout<<"Error in opening file!,file not found ";
 		return;
	}
 	inoutfile.seekg(0);
	inoutfile.read(reinterpret_cast<char *>(this),sizeof(*this));
 	while(!inoutfile.eof())
 	{
 		if(!strcmp(a,unique_code))
 		{
 			cout<<"\t\t\tComputer you want to Update found \n";
            cout<<"Are you sure you want to update (y/n)?\n";
 			if(getche() == 'n' || getche() == 'N')
 			return;
 			system("cls");
 			cout<<"\t\t\t\t Enter new data\n";
 			getComputerData();
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
void Computer_Entry::ComputerEntryfun()
{
 	Computer_Entry c;
 	int choice;
 	while(true)
 	{
 		system("cls");
	cout << "\n\n\n\n\t\t\t        ";
    cout << "\n\n";
    cout<<"\t\t\t      MENU/MASTER ENTRY/COMPUTER ENTRY         ";
    cout<<    "\n\t\t\t\t __________________________";
    cout<<    "\n\t\t\t\t|                          |";
	cout << "\n\t\t \t \t|     1. Add Computer      |";
    cout << "\n \t\t\t \t|     2. Show Computers    |";
    cout << "\n \t\t\t \t|     3. Search Computer   |";
	cout << "\n \t\t\t \t|     4. Delete Computer   |";
	cout << "\n \t\t\t \t|     5. Update Computer   |";
	cout << "\n \t\t\t \t|     6. Return            |\n";
    cout<<  "\t\t    \t\t|__________________________|\n";
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
 	    		system("cls");
 	    		char ch;
 	    		do
 	    		{
 	    		getComputerData();
 	    		storeComputer();
 	    		cout<<"\nDo you want to add another computer (y/n)"<<endl;
 	    		cin>>ch;
			    }
			    while(ch == 'y'|| ch == 'Y');
			    break;
			case 2:
				system("cls");
			    readComputerRecord();
			    while(getche() != '\r'); 
			    break; 
			case 3:
				system("cls");
				searchComputerRecordEntry();
				while(getche() != '\r'); 
				break;
			case 4:
				system("cls");
				delComputerRecord();
				while(getche() != '\r'); 
				break;   
			case 5:
				system("cls");
				updateComputerRecord();
				while(getche() != '\r'); 
				break;
			case 6:
			    return ;
			    break; 
			default:
		cout<<"Invalid choice ! Re-Enter ";
		return ComputerEntryfun();
		break;		
		}
	}
 }
