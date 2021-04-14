#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
class staff
{
protected:
  int code;
  char name[20];
public:
  void enter()					//Input record
  {
    cout<<"Enter code:";
    cin>>code;
    cout<<"Enter name:";
    gets(name);
  }
  void display()					//Display record
  {
    cout<<"Code="<<code;
    cout<<"\nName:"<<name;
  }
  int getcode()
  {  return code;  }
  char* getname()
  {  return name;  }
}s;

class teacher:public staff
{
protected:
  char sec[5];
  char sub[20];
public:
  void input()
  {
    enter();
    cout<<"Enter section (P for primary, S for secondary, Sc for senior secondary):";
    gets(sec);
    cout<<"Enter subject:";
    gets(sub);
  }
  void show()
  {
    display();
    cout<<"\nSection:"<<sec;
    cout<<"\nSubject:"<<sub;
  }
}t;

class student:public staff
{
protected:
  int CLASS;
  int roll;
public:
  void input()
  {
    enter();
    cout<<"Enter current class:";
    cin>>CLASS;
    cout<<"Enter roll number:";
    cin>>roll;
  }
  void show()
  {
    display();
    cout<<"\nClass="<<CLASS;
    cout<<"\nRoll number="<<roll;
  }
}st;

void twrite()				//function to write in file ‘Teacher.dat”
{
  ofstream fout("teacher.dat",ios::binary|ios::app);
  t.input();
  fout.write((char*)&t,sizeof(t));
  fout.close();
}

void tread()				//function to read in file ‘Teacher.dat”
{
  ifstream fin("teacher.dat",ios::binary|ios::in);
  while(fin.read((char*)&t,sizeof(t)))
  {
    t.show();
    cout<<"\n-------------------------------------------------\n";
    if(fin.eof())
      break;
  }
  fin.close();
}

void swrite()				//function to write in file ‘Student.dat”
{
  ofstream fout("student.dat",ios::binary|ios::app);
  st.input();
  fout.write((char*)&st,sizeof(st));
  fout.close();
}

void sread()				//function to read in file ‘Student.dat”
{ ifstream fin("student.dat",ios::binary|ios::in);
  while(fin.read((char*)&s,sizeof(s)))
  {
    st.show();
    cout<<"\n-------------------------------------------------\n";
    if(fin.eof())
      break;
  }
  fin.close();
}

void searchbycodet()			//Search by teacher code
{
  int x,flag=0;
  cout<<"Enter code to search:";
  cin>>x;
  ifstream fin1("teacher.dat",ios::binary|ios::in);
  while(fin1.read((char*)&t,sizeof(t)))
  {
    if(x==t.getcode())
    {
      flag++;
      cout<<"!Record found in teacher database"<<endl;
      t.show();
      getch();
    }
    if(fin1.eof())
      break;
  }
  fin1.close();
  if(flag==0)
    cout<<"No record found";
  getch();
}

void searchbycodes()			//Search by student code

{
  int x,flag=0;
  cout<<"Enter code to search:";
  cin>>x;
  ifstream fin2("student.dat",ios::binary|ios::in);
  while(fin2.read((char*)&s,sizeof(s)))
  {
    if(x==s.getcode())
    {
      flag++;
      cout<<"!Record found in student database"<<endl;
      st.show();
      getch();
    }
    if(fin2.eof())
      break;
  }
  fin2.close();
  if(flag==0)
    cout<<"No record found";
  getch();
}

void tdelete()				//function to delete record
{
  int x,flag=0;
  cout<<"Input teacher code of record to be deleted=";
  cin>>x;
  ifstream fin("teacher.dat",ios::binary|ios::in);
  ofstream fout("temp.dat",ios::binary|ios::out);
  while(fin.read((char*)&t,sizeof(t)))
  {
    if(t.getcode()!=x)
      fout.write((char*)&t,sizeof(t));
    else
      flag=1;
    if(fin.eof())
      break;
  }
  fin.seekg(0,ios::beg);
  fin.close();
  fout.close();
  remove("teacher.dat");
  rename("temp.dat","teacher.dat");
  if(flag!=0)
    cout<<"Record successfully deleted!";
  if(flag==0)
    cout<<"!Record not found";
  getch();
}

void sdelete()				//function to delete record

{
  int x,flag=0;
  cout<<"Input student code of record to be deleted=";
  cin>>x;
  ifstream fin("student.dat",ios::binary|ios::in);
  ofstream fout("temp2.dat",ios::binary|ios::out);
  while(fin.read((char*)&st,sizeof(st)))
  {
    if(st.getcode()!=x)
      fout.write((char*)&st,sizeof(st));
    else
      flag=1;
    if(fin.eof())
      break;
  }
  fin.seekg(0,ios::beg);
  fin.close();
  fout.close();
  remove("student.dat");
  rename("temp2.dat","student.dat");
  if(flag!=0)
    cout<<"Record successfully deleted!";
  if(flag==0)
    cout<<"!Record not found";
  getch();
}
void main()
{
  clrscr();
  int menu;
  do
  {
X:  clrscr();
    cout<<"===WELCOME TO SCHOOL DATABASE MANAGEMENT===";
    cout<<"\n1.Teacher database";
    cout<<"\n2.Student database";
    cout<<"\n3.Exit";
    cin>>menu;
    switch(menu)
    {
      case 1:
      do
      {
	clrscr();
	int menu;
	cout<<"==TEACHER DATABASE==";
	cout<<"\n1.Write";
	cout<<"\n2.Read";
	cout<<"\n3.Search record";
	cout<<"\n4.Delete record";
	cout<<"\n5.Jump to main menu";
	cin>>menu;
	switch(menu)
	{
	  case 1:twrite();break;
	  case 2:tread();getch();break;
	  case 3:searchbycodet();break;
	  case 4:tdelete();break;
	  default:goto X;
	}
      }while(menu<4);
      break;
      case 2:
      do
      {
	clrscr();
	int menu;
	cout<<"==STUDENT DATABASE==";
	cout<<"\n1.Write";
	cout<<"\n2.Read";
	cout<<"\n3.Search record";
	cout<<"\n4.Delete record";
	cout<<"\n5.Jump to main menu";
	cin>>menu;
	switch(menu)
	{
	  case 1:swrite();break;
	  case 2:sread();getch();break;
	  case 3:searchbycodes();break;
	  case 4:sdelete();break;
	  default:goto X;
	}
      }while(menu<4);
      break;
    }
  }while(menu<3);
  getch();
}
