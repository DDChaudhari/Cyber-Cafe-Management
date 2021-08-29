#include<iostream>
#include<vector>
#include<stdio.h>
#include<cstring>
#include<fstream>
#include<algorithm>
using namespace std;
class user
{
	public:
		long int reg;
		char name[80];
		void input()
		{
			cout<<"\n Enter  User name: ";
			gets(name);
			cout<<"\n Enter Id: ";
			cin>>reg;
		}
		void display()
		{
			system("CLS");
			cout<<"\t\tDisplay Records";
			cout<<"\n";
			cout<<"\n  User Name - "<<name;
			cout<<"\n Id - "<<reg;
			cout<<"\n";
			system("PAUSE");
			system("CLS");
		}
		bool operator == (user a)
		{
			if(reg==a.reg)
				return true;
			else
				return false;
		}
};
vector <user>v;
int search_reg(long int reg,int &i);
void get_file()
{
	user x;
	int i=0;
	fstream f;
	f.open("Cafe.txt",ios::in);
	if(f)
	{
		f.read((char *) &x,sizeof(class user));
		while(!f.eof())
		{
			v.push_back(x);
			f.read((char *) &x,sizeof(class user));
		}
	}
	else
		;
	f.close();
}
void bubblesort()
{
	int i,j;
	user x;
	for(i=0;i<v.size();i++)
		for(j=0;j<v.size()-i-1;j++)
			if(v[j].reg>v[j+1].reg)
			{
				x=v[j];
				v[j]=v[j+1];
				v[j+1]=x;
			}	
}
void insert_new()
{
	char ch='y';
	int ta;
	while(ch=='y')
	{
		fflush(stdin);
		user x;
		x.input();
		if(search_reg(x.reg, ta)==0)
			v.push_back(x);
		else
			cout<<"\nTHE Id ALREADY EXIST!!!\nCANNOT ADD";
		cout<<"\n Press [Y] to enter more: ";
		cin>>ch;
		fflush(stdin);
	}
}
void write_file()
{
	bubblesort();
	fstream f;
	f.open("Cafe.txt",ios::out);
	for(int i=0;i<v.size();i++)
	{
		user x=v[i];
		f.write((char *) &x,sizeof(class user));
	}
	f.close();
}
int search_reg(long int reg,int &i)
{
	int ta=0;
	for(i=0;i<v.size();i++)
		if(v[i].reg==reg)
		{
			ta=1;
			break;
		}
	return ta;
}
int search_name(char name[],vector<int> &vi)
{
	int i,ta=0;
	for(i=0;i<v.size();i++)
		if(strcmp(v[i].name,name)==0)
		{
			ta=1;
			vi.push_back(i);
		}
	return ta;
}
void search_and_show()
{
	int ch,i,ta=0;
	char name[80];
	vector <int>vi; 
	vector <int>vj;
	long int reg;
	poi:
	cout<<"\n1.Press to search id"
	<<"\n2.Press to search name";
	cin>>ch;
	switch(ch)
	{
		case 1:
			cout<<"\nEnter id: ";
			cin>>reg;
			if(search_reg(reg,i)==1)
				v[i].display();
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		case 2:
			cout<<"\nEnter name: ";
			fflush(stdin);
			gets(name);
			if(search_name(name,vi)==1)
			{
				for(int j=0;j<vi.size();j++)
					v[vi[j]].display();
			}
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		default:
			cout<<"\nWrong CHOICE!!!";
			goto poi;
	}
}
void show()
{
	int i;
	for(i=0;i<v.size();i++)
		v[i].display();
}

void delete_data()
{
	int i,j;
	long int reg;
	vector <user>::iterator p=v.begin();
	cout<<"\nEnter Id: ";
	cin>>reg;
	if(search_reg(reg,i)==1)
	{
		user x=v[i];
		cout<<"\n The following data is being deleted";
		x.display();
		p+=i;
		v.erase(p,p+1);
		
	}
}
void edit_data()
{
	int i,j;
	long int reg;
	vector <user>vi;
	cout<<"\nEnter Id: ";
	cin>>reg;
	if(search_reg(reg,i)==1)
	{
		cout<<"\nEnter new data:";
		fflush(stdin);
		v[i].input();
	}
}
int main()
{
	int i=1;
	get_file();
	while(i)
	{
		system("CLS");
		cout<<"\t\t\t****************************************\n";
		cout<<"\t\t\t         WELCOM TO D's CYBER CAFE         \n";
		cout<<"\t\t\t****************************************\n";
		cout<<"\t\t\t     Cyber Cafe Management System\n";
		cout<<"\t\t\t****************************************\n";
		cout<<"\n\t\t\tEnter <1> to Add new user"
			<<"\n\t\t\tEnter <2> to Display all user"
			<<"\n\t\t\tEnter <3> to Remove user"
			<<"\n\t\t\tEnter <4> to Edit user"
			<<"\n\t\t\tEnter <5> to Search user"
			<<"\n\t\t\tEnter <0> to Exit\n";
		cout<<"\n\n\t\t\tEnter Your Choice:";	
		cin>>i;
		switch(i)
		{
			case 1 :
				insert_new();
				break;
			case 2 :
				show();
				break;
			case 3 :
				delete_data();
				break;
			case 4 :
				edit_data();
				break;
			case 5 :
				search_and_show();
				break;
			case 0 :
				write_file();
				break;
			default :
				cout<<"\nWRONG CHOICE!!!\nTRY AGAIN";
		}
	}
	return 0;
}

