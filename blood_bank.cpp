#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class blood_bank
{
	char name[20], contact[10], addr[20], bgrp[5], gender;
	int id, age;

public :
        void accept()       //accepting the details of the donor
        {
            cout << "\n Enter the name of the donor : ";
            cin >> name;
            cout << "\n Enter the address : ";
            cin >> addr;
            cout << "\n Enter the contact number : ";
            cin >> contact;
            cout << "\n Enter the gender : ";
            cin >> gender;
            cout << "\n Enter the age : ";
            cin >> age;
            cout << "\n Enter the Id number : ";
            cin >> id;
            cout << "\n Enter blood group : ";
            cin >> bgrp;
        }

        void display()        //display the details
        {
            cout << "\n Name            : " << name;
            cout << "\n Blood Group     : " << bgrp;
            cout << "\n Gender          : " << gender;
            cout << "\n Age             : " << age;
            cout << "\n Id Number       : " << id;
            cout << "\n Address         : " << addr;
            cout << "\n Contact Number  : " << contact;
        }

        char* getbgrp()
        {
            char *bg = bgrp;
            return bg;
        }

        inline int getid()
        {
            return id;
        }
  };

void createFile()   //to create new file
{
    int n;
    blood_bank obj;

    cout << "\n Enter the number of donors : ";
    cin >> n;

    ofstream file;
    file.open("Data.DAT", ios::out);
    for(int i=0; i<n; i++)
    {
        obj.accept();
        file.write((char *)&obj, sizeof(obj));
    }
    file.close();
}

void displayFile()    //to display all the details from the file
{
    blood_bank obj;

    ifstream file;
    file.open("Data.DAT", ios::in);

    while(file)
    {
        file.read((char*)&obj, sizeof(obj));
      if(file.eof() != 0)
        break;
      obj.display();
      cout << endl;
    }
    file.close();
}

void add_record()   //add new entry in the file
{
    blood_bank obj;

    ofstream file;
    file.open("Data.DAT", ios::app);

    cout << "\n Enter the data to be added : ";
    obj.accept();
    file.write((char*)&obj, sizeof(obj));
    file.close();
}

void search_bgrp()    //search for blood group
{
    char bgrp_s[5];
    int flag=0;
    blood_bank obj;
    char *b;
    b = obj.getbgrp();

    ifstream file;
    file.open("Data.DAT", ios::in);

    cout << "\n Enter the blood group to be searched : ";
    cin >> bgrp_s;

    while(file)
    {
        file.read((char *)&obj, sizeof(obj));
        if(file.eof() != 0)
            break;
        if(strcmp(b, bgrp_s) == 0)                          //compare the two blood groups
        {
            cout << "\n Entry found ";
            obj.display();                                  //display the data to the user
            flag = 1;
            break;
        }
    }

    file.close();

    if(flag == 0)
        cout << "\n No blood group of that category available. ";
}

void deleter()    //to delete a particular record from the file
{
    ifstream file1;
    ofstream file2;

    file1.open("Data.DAT", ios::in);
    file2.open("temp.DAT", ios::out);

    int id_del;
    blood_bank obj;

    cout << "\n Enter Id number to delete : ";
    cin >> id_del;

    file1.read((char *)&obj, sizeof(obj));
    while(!file1.eof())
    {
        if(id_del != obj.getid())
        {
            cout << "\n Writing ";
            obj.display();
            file2.write((char *)&obj, sizeof(obj));
        }
        else
        {
            cout << "\n Reading ";
            obj.display();
            cout<<"Press Any Key....For Search"<<endl;
        }
        file1.read((char *)&obj, sizeof(obj));
    }

    file1.close();
    file2.close();
    remove("Data.DAT");
    rename("temp.DAT", "Data.DAT");
    cout << "\n Process complete. ";

}

int main()
{
	int ch;

	do
    { //displaying the menu
        cout << "\n PIMPRI CHINCHWAD BLOOD BANK "
                "\n Welcome "
                "\n 1. Create a new record "
                "\n 2. Add new record "
                "\n 3. Search by blood group "
                "\n 4. Delete a record "
                "\n 5. Display all the records "
                "\n Enter your choice here : ";
        cin >> ch;

        switch(ch)
        {
            case 1: createFile();
                break;

            case 2: add_record();
                break;

            case 3: search_bgrp();
                break;

            case 4: deleter();
                break;

            case 5: displayFile();
                break;

            default: cout << "\n !!!INVALID CHOICE!!! ";
                break;
        }
	}while(ch<6);

	return 0;
}
