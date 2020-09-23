#include<fstream>
#include<iostream>
#include<conio.h>
#include<string.h>
using namespace std;

class menu
{
public:
    int itemcode;
    char name[50];
    int price;
    void accept()
    {
        cout<<endl<<"\t\t\tEnter Item Code";
        cin>>itemcode;
        cout<<endl<<"\t\t\tEnter Item Name";
        cin>>name;
        cout<<endl<<"\t\t\tEnter Item Price";
        cin>>price;
    }
    void display()
    {
        cout<<endl<<"\t\t\t"<<itemcode<<"\t\t"<<name<<"\t\t"<<price;
    }
};
menu obj; //global object
void additem()
{
    obj.accept();
    fstream wr;
    wr.open("F:\\billingproject\\menu.txt",ios::app);
    wr.write((char*)&obj,sizeof(obj));
    cout<<endl<<"\t\t\t\tITEM ADDED SUCESSFULLY";
}
void viewmenu()
{
    fstream rd;
    rd.open("F:\\billingproject\\menu.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        obj.display();
    }
}
void removeitem()
{
 fstream rd,wr;
 rd.open("F:\\billingproject\\menu.txt",ios::in);
 wr.open("F:\\billingproject\\temp.txt",ios::out);
 rd.seekg(0,ios::end);
 int n=rd.tellg()/sizeof(obj);
 rd.seekg(0,ios::beg);
 int sr;
 cout<<endl<<"\t\t\t Enter ITEM CODE to REMOVE ITEM";
 cin>>sr;
 for(int i=1;i<=n;i++)
 {
     rd.read((char*)&obj,sizeof(obj));
     if(obj.itemcode==sr)
     {
         cout<<endl<<"\t\t\t\tITEM REMOVED";
     }
     else
     {
         wr.write((char*)&obj,sizeof(obj));
     }
 }
 rd.close();
 wr.close();
 remove("F:\\billingproject\\menu.txt");
 rename("F:\\billingproject\\temp.txt","F:\\billingproject\\menu.txt");
}
class bill
{
public:
    int billnumber;
    int date,month,year;
    int itemcode,price,quantity,total;
    char itemname[50];
    void accept(int bn,int d,int m,int y,int ic,int q)
    {
        billnumber=bn;
        date=d;
        month=m;
        year=y;
        itemcode=ic;
        quantity=q;
        fstream rd;
        rd.open("F:\\billingprojectme\\menu.txt",ios::in);
        rd.seekg(0,ios::end);
        int n=rd.tellg()/sizeof(obj);
        rd.seekg(0,ios::beg);
        for(int i=1;i<=n;i++)
        {
            rd.read((char*)&obj,sizeof(obj));
            if(itemcode==obj.itemcode)
            {
                strcpy(itemname,obj.name);
                price=obj.price;
                total=price*quantity;
            }
        }
        cout<<endl<<"\t\t\tBILL NUMBER"<<billnumber;
        cout<<endl<<"\t\t\tDD-MM-YY"<<date<<"-"<<month<<"-"<<year;
        cout<<endl<<"\t\t\tITEM CODE"<<itemcode;
        cout<<endl<<"\t\t\tITEM NAME"<<itemname;
        cout<<endl<<"\t\t\tPRICE"<<price;
        cout<<endl<<"\t\t\tQUANTITY"<<quantity;
        cout<<endl<<"\t\t\tTOTAL"<<total;
    }
};
bill bobj;
void prepairbill()
{
  int bill_number;
  cout<<endl<<"ENTER BILL NUMBER";
  cin>>bill_number;
  cout<<endl<<"ENTER DATE IN DD MM YYYY FORMAT";
  int date,month,year;
  cin>>date>>month>>year;
  int choice=0;
  while(1)
  {
      int itemcode;
      cout<<endl<<"ENTER ITEM  CODE";
      cin>>itemcode;
      int quantity;
      cout<<endl<<"ENTER QUANTITY";
      cin>>quantity;
      bobj.accept(bill_number,date,month,year,itemcode,quantity);
      fstream wr;
      wr.open("F:\\billingproject\\bill.txt",ios::app);
      wr.write((char*)&bobj,sizeof(bobj));
      wr.close();
      cout<<endl<<"ENTER 1 TO ADD NEW ITEM";
      cout<<endl<<"ENTER 2 TO PREPAIR BILL";
      cin>>choice;
      if(choice==2)
      {
          break;
      }
  }
  cout<<endl<<"BILL NUMBER"<<bill_number<<"\t\t"<<"DATED:"<<date<<"-"<<month<<"-"<<year;
  cout<<endl<<"\t\t\t* * * * * * * * * * * * * * * * * * *";
  cout<<endl<<"\t\t\t*       AOROA CEMENT STORE          *";
  cout<<endl<<"\t\t\t* * * * * * * * * * * * * * * * * * *";
  fstream rd;
  rd.open("F:\\billingproject\\bill.txt",ios::in);
  rd.seekg(0,ios::end);
  int n=rd.tellg()/sizeof(bobj);
  rd.seekg(0,ios::beg);
  int ftotal=0;
  for(int i=1;i<=n;i++)
  {
      rd.read((char*)&bobj,sizeof(bobj));
      if(bobj.billnumber==bill_number)
      {
          cout<<endl<<bobj.itemcode<<"\t\t"<<bobj.itemname<<"\t\t"<<bobj.quantity<<"\t\t"<<bobj.price<<"\t\t"<<bobj.total;
          ftotal=ftotal+bobj.total;
      }
  }
  cout<<endl<<"\t\t\t* * * * * * * * * * * * * * * * * *";
  cout<<endl<<"\t\t\t     TOTAL AMOUNT IS="<<ftotal;
  cout<<endl<<"\t\t\t* * * * * * * * * * * * * * * * * * ";
}
void updateitem()
{
    fstream rd,wr;
    rd.open("F:\\billingproject\\menu.txt",ios::in);
    wr.open("F:\\billingproject\\temp.txt",ios::out);
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    int sr;
    cout<<endl<<"ENTER ITEM CODE TO UPDATED ITEM";
    cin>>sr;
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(obj.itemcode==sr)
        {
            obj.accept();
            wr.write((char*)&obj,sizeof(obj));
        }
        else
        {
            wr.write((char*)&obj,sizeof(obj));
        }
    }
    rd.close();
    wr.close();
    remove("F:\\billingproject\\menu.txt");
    rename("F:\\billingproject\\temp.txt","F:\\billingproject\\menu.txt");
}
main()
{
int e=0;
while(e!=1)
{
    cout<<endl<<"\t\t\t\t* * * * * * *ENTER YOUR CHOICE* * * * * * *";
    cout<<endl<<"\t\t\t\t*                                         *";
    cout<<endl<<"\t\t\t\t*          ENTER 1 TO ADD ITEM            *";
    cout<<endl<<"\t\t\t\t*          ENTER 2 TO VIEW MENU           *";
    cout<<endl<<"\t\t\t\t*          ENTER 3 TO REMOVE ITEM         *";
    cout<<endl<<"\t\t\t\t*          ENTER 4 TO UPDATE ITEM         *";
    cout<<endl<<"\t\t\t\t*          ENTER 5 TO PREPAIR BILL        *";
    cout<<endl<<"\t\t\t\t*             ENTER 6 TO EXIT             *";
    cout<<endl<<"\t\t\t\t*                                         *";
    cout<<endl<<"\t\t\t\t* * * * * * * * * * * * * * * * * * * * * *";
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:
        {
            additem();
            break;
        }
    case 2:
        {
            viewmenu();
            break;
        }
    case 3:
        {
            removeitem();
            break;
        }
    case 4:
        {
            updateitem();
            break;
        }
    case 5:
        {
            prepairbill();
            break;
        }
    case 6:
        {
            e=1;
            break;
        }
    }
}
}
