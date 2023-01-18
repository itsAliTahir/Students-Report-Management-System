#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

struct node{
	string name, grade, status;
	int sub1, sub2, sub3, total, reg, val;
	float percentage;	
	node *next;
};

class list{
		node *head;
		node *tail;
		node *sorted;
		string changes = "Saved";
	public:		
		list()
		{
			head = NULL;
			tail = NULL;
		}
		string getChange()
		{
			return changes;
		}
		void addStudent();
		void displayAll();
		string grading(int);
		void writeFile();
		void searchStudent();
		int inputCheckNum(string str);
		string inputCheckString(string str);
		void readFile(int);
		int studentCount();
		int studentCount2();
		void deleteStudent();
		void modify();
		void sortAuto();
		void sortedInsert(node*);
		void insertionSort();
};

int main ()
{	
	system("color 70");
	list obj;
	string input;
	int loop=1;
	char option, method, sure;
	obj.readFile(obj.studentCount2());
	string search;
	do
	{
		cout << "\n\t     Menu" <<endl;
		cout << "------------------------------ " <<endl;
		cout << " 1. Add Student" <<endl;
		cout << " 2. Display Result" <<endl;
		cout << " 3. Search Student" <<endl;
		cout << " 4. Modify Data" <<endl;
		cout << " 5. Delete Student" <<endl;
		cout << " 6. Sort Data" <<endl;
		cout << " 7. Save Changes" <<endl;
		cout << " 8. Exit Program" <<endl<<endl;
		cout << "\t    Total Students: " <<obj.studentCount() <<endl;
		cout << "\t    Changes: " << obj.getChange() <<endl;
		cout << "------------------------------ " <<endl;
		cout << " Please Select your option" <<endl;
		option = getch();
		system("CLS");
		switch(option)
		{
		 start:
			case '1':
				obj.addStudent();
				break;
			case '2':
				obj.displayAll();
				break;
			case '3':
				obj.searchStudent();
				break;
			case '4':
				obj.modify();
				break;
			case '5':
				obj.deleteStudent();
				break;
			case '6':
				obj.sortAuto();
				break;
			case '7':
				obj.writeFile();
				break;
			case '8':
				if (obj.getChange()!="Saved")
				{
					cout << "Some Changes Arent Saved" <<endl;
					jump:
					cout << "Press 1 to Exit Without Saving" <<endl;		
					cout << "Press 2 to Save Changes and Exit" <<endl;
					cout << "Press 3 to Go Back" <<endl;
					sure = getch();
					if (sure=='1') 	loop = 0;
					else if (sure=='2')
					{
						obj.writeFile();
						loop=0;
					}
					else if(sure == '3') loop=1;
					else 
					{
						system("CLS");	
						cout << "Invalid Option\nPlease Reselect an Option" <<endl;
						goto jump;
					}
				}
				else loop=0;
				break;
			default:
				cout << "Invalid Option";	
				break;
		}
		cout << endl;
		if (loop == 1) system("pause");
		system("CLS");
	}while(loop==1);
	cout << "Closing System";
	return 0;
}

int list::inputCheckNum(string str)
{
	int num;
	bool flag = false;
	char arr[str.length() + 1];
	strcpy(arr, str.c_str()); 
	for (int i = 0; i < str.length(); i++)
	{
		if (arr[i]>=48 && arr[i]<=57)
		{
			flag = true;
		}
		else
		{
			flag = false;
			return 0;
		}
	}
	if (flag == true && str.length() < 4)
	{
		num = stoi(str);
		return num;
	}
	return 0;
}

string list::inputCheckString(string str)
{
	bool flag = false;
	char arr[str.length() + 1];
	strcpy(arr, str.c_str()); 
	for (int i = 0; i < str.length(); i++)
	{
		if ((arr[i]>=65 && arr[i]<=90) || (arr[i]>=97 && arr[i]<=122) || arr[i] == 32)
		{
			flag = true;
		}
		else
		{
			flag = false;
			return "N/A";
		}
	}
	if (flag == true)
	{
		return str;
	}
	return "N/A";
}

void list::addStudent()
{
	cout << "\n\t  Add Student" <<endl;
	cout << "------------------------------ " <<endl;	
	string n, input;
	int r,s1,s2,s3;
	cout << "Enter Student Name: ";
	getline(cin >> ws, input);
	n = inputCheckString(input);
	if (n == "N/A") {cout << "Invalid Input"; return;}	
	cout << "Enter Registration Number: 21-CS-";
	getline(cin >> ws, input);
	r = inputCheckNum(input);
	if (r == 0) {cout << "Invalid Input"; return;}
	cout << "Enter Subject 1 marks: ";
	getline(cin >> ws, input);
	s1 = inputCheckNum(input);
	if (s1 == 0) {cout << "Invalid Input"; return;}
	cout << "Enter Subject 2 marks: ";
	getline(cin >> ws, input);
	s2 = inputCheckNum(input);
	if (s2 == 0) {cout << "Invalid Input"; return;}
	cout << "Enter Subject 3 marks: ";
	getline(cin >> ws, input);
	s3 = inputCheckNum(input);
	if (s3 == 0) {cout << "Invalid Input"; return;}
	node *temp = new node;
	temp->name=n;
	temp->reg=r;
	temp->sub1=s1;
	temp->sub2=s2;
	temp->sub3=s3;
	temp->total=s1+s2+s3;
	temp->percentage=(s1+s2+s3)/3;
	temp->grade=grading(s1+s2+s3);
	temp->val=temp->total;
	if(s1>=40 && s2>=40 && s3>=40) temp->status= "Passed";
	else temp->status= "Failed";
	temp->next=NULL;
	if (head==NULL)
	{
		head = temp;
		tail = temp;
	}
	else
	{
		tail->next =temp;
		tail = temp;
	}
	changes = "Unsaved";
}

void list::searchStudent()
{
	cout << "\n\tSearch Student" <<endl;
	cout << "------------------------------ " <<endl;	
	string search, input;
	int num = 0;
	bool flag = false;
	node *temp;
	temp = head;
	if (head == NULL)
	{
		cout << "Empty List";
	}
	else
	{
		cout << "Enter Student Name or Registration Number (21-CS-): ";
		getline(cin >> ws, input);
		search = inputCheckString(input);		
		num = inputCheckNum(input);
		if (search == "N/A" && num==0) {cout << "Invalid Input"; return;}	
		while (temp!=NULL)
		{
			if(temp->name == search || temp->reg==num)
			{
				cout << "Name: " << temp->name << endl;
				cout << "Registration Number: 21-CS-" << temp->reg << endl;
				cout << "Subject 1 Marks: " << temp->sub1 << endl;
				cout << "Subject 2 Marks: " << temp->sub2 << endl;
				cout << "Subject 3 Marks: " << temp->sub3 << endl;
				cout << "Total Marks: " << temp->total << endl;
				cout << "Percentage: " << temp->percentage << "%" << endl;
				cout << "Grade: " << temp->grade << endl;
				cout << "Result Status: " << temp->status;
				flag = true;
			}
			temp = temp -> next;
		}
		if (flag == false) cout << "Student Not Found";
	}
}

void list::displayAll()
{
	cout << "\n\t\t\t\t   Display Student" <<endl;
	cout << "---------------------------------------------------------------------------------------- " <<endl;	
	cout << "  Name\t\tReg No.\t\tSub1\tSub2\tSub3\tTotal\t%age\tGrade\tStatus"<<endl;
	node *temp;
	temp = head;
	if (head == NULL)
	{
		cout << "Empty List";
	}
	else
	{
		while (temp!=NULL)
		{
			cout << temp -> name << "\t21-CS-" << temp -> reg << "\t" << temp -> sub1 << "\t" << temp -> sub2 << "\t" << temp -> sub3 << "\t" << temp -> total << "\t" << temp -> percentage << "%\t" << temp -> grade << "\t" << temp -> status <<"\n";
			temp = temp -> next;
		}
	}
}

string list::grading(int total)
{
	int percentage = (total/3);
	if (percentage >= 80) return "A";
	else if (percentage >= 75 && percentage < 80) return "A-";
	else if (percentage >= 70 && percentage < 75) return "B+";
	else if (percentage >= 65 && percentage < 70) return "B";
	else if (percentage >= 60 && percentage < 65) return "B-";
	else if (percentage >= 55 && percentage < 60) return "C+";
	else if (percentage >= 50 && percentage < 55) return "C";
	else if (percentage >= 45 && percentage < 50) return "C-";
	else if (percentage >= 40 && percentage < 45) return "D";
	else return "F";
}

void list::writeFile()
{
	node *temp;
	temp = head;
	ofstream myFile;
	int count=0;
	if (head == NULL)
	{
		cout << "Empty List\nProcess Failed";
	}
	else
	{
		myFile.open("data.csv");
		while (temp!=NULL)
		{
			myFile << "#" << ++count << "," << temp->reg << "," << temp->name << "," << temp->sub1 << "," << temp->sub2 << "," << temp->sub3 << "," << temp->total << "," << temp->percentage << "%," << temp->grade << "," << temp->status << ", " <<", " << "\n";
			temp = temp -> next;
		}
		myFile.close();
		cout << "Saved Successfully";
		changes = "Saved";
	}
}

void list::readFile(int totalStudent)
{
	int counter=0;
	ifstream myFile;
	myFile.open("data.csv");
	while (counter<totalStudent)
	{
		string line;
		node *temp = new node;
		getline(myFile, line, ',');
		getline(myFile, line, ','); temp->reg = stoi(line);
		getline(myFile, line, ','); temp->name = line;
		getline(myFile, line, ','); temp->sub1 = stoi(line);
		getline(myFile, line, ','); temp->sub2 = stoi(line);
		getline(myFile, line, ','); temp->sub3 = stoi(line);
		getline(myFile, line, ','); temp->total = stoi(line);
		getline(myFile, line, ','); temp->percentage = stoi(line);
		getline(myFile, line, ','); temp->grade = line;
		getline(myFile, line, ','); temp->status = line;		
		getline(myFile, line, ',');	
		counter++;
		temp->val=temp->total;
		temp->next=NULL;
		if (head==NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	myFile.close();
}

int list::studentCount()
{
	node *temp;
	node *pre;
	temp = head;
	int counter=0;
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		while (temp!=NULL)
		{
			pre = temp;
			temp = temp -> next;
			counter++;
		}
		tail = pre;
		return counter;
	}
}

int list::studentCount2()
{
	int stud=0;
	ifstream myFile;
	myFile.open("data.csv");
	while (myFile.good())
	{
		string line;
		getline(myFile, line, ',');
		if (line == "Passed" || line == "Failed") stud++;
	}	
	myFile.close();
	return stud;
}

void list::deleteStudent()
{
	cout << "\n\tDelete Student" <<endl;
	cout << "------------------------------ " <<endl;	
	string input,search;
	node *temp, *pre;
	int num;
	temp = head;
	cout << "Enter Student Name or Registration Number (21-CS-): ";
	getline(cin >> ws, input);
	search = inputCheckString(input);		
	num = inputCheckNum(input);
	if (search == "N/A" && num==0) {cout << "Invalid Input"; return;}	
	if (head == NULL)
	{
		cout << "Empty List";
		return;
	}
	else if (head->name == search || head->reg == num)
	{
		temp = head;
		head = head->next;
		cout << temp->name << "\t21-CS-" <<temp->reg;
		delete temp;
		cout << "\nDeleted Successfully";
		changes = "Unsaved";
		return;
	}
	else
	{
		while (temp!=NULL)
		{
			if ((temp->name == search && temp->next != NULL) || (temp->reg == num && temp->next != NULL))
			{
				pre->next=temp->next;
				cout << temp->name << "\t21-CS-" <<temp->reg<<endl;	
				delete temp;				
				cout << "\nDeleted Successfully";
				changes = "Unsaved";				
				return;
			}
			if ((temp->name == search && temp->next == NULL) || (temp->reg == num && temp->next == NULL))
			{
				pre->next = NULL;
				tail = pre;
				tail->next = NULL;
				cout << temp->name << "\t21-CS-" <<temp->reg<<endl;	
				delete temp;	
				cout << "\nDeleted Successfully";
				changes = "Unsaved";			
				return;
			}
			pre = temp;
			temp = temp -> next;
		}
		cout << "Couldn't Find Student";
	}
}

void list::modify()
{
	cout << "\n\tModify Student" <<endl;
	cout << "------------------------------ " <<endl;	
	node *temp;
	temp = head;
	string search, value, input;
	char method;
	int num,snum;
	if (head == NULL)
	{
		cout << "";
	}
	else
	{
		cout << "Enter Student Name or Registration Number (21-CS-): ";
		getline(cin >> ws, input);
		search = inputCheckString(input);		
		snum = inputCheckNum(input);
		if (search == "N/A" && snum==0) {cout << "Invalid Input"; return;}
		while (temp!=NULL)
		{
			if(temp->name == search || temp->reg==snum)
			{
				cout << "Student Found:\t" << temp->name << "\t21-CS-" << temp->reg << "\n\n";
				cout << "What do you want to change" <<endl;
				cout << "1. Name" << endl <<"2. Registration Number" << endl <<"3. Subject 1 Marks" << endl <<"4. Subject 2 Marks" << endl <<"5. Subject 3 Marks" << endl ;
				method = getch();
				if (method != '1' && method != '2' && method !='3' && method !='4' && method !='5')
				{
					cout << "Invalid Input";
					return;	
				}
				cout << "Enter New Value: ";
				getline(cin >> ws, value);
				if (method == '2' || method == '3' || method == '4' || method == '5') num = stoi(value);				
				if (method == '1') temp->name = value;
				if (method == '2') temp->reg = num;
				if (method == '3') temp->sub1 = num;
				if (method == '4') temp->sub2 = num;
				if (method == '5') temp->sub3 = num;
				temp->total=temp->sub1+temp->sub2+temp->sub3;
				temp->percentage=(temp->total)/3;
				temp->grade=grading(temp->total);
				if(temp->sub1>=40 && temp->sub2>=40 && temp->sub3>=40) temp->status= "Passed";
				else temp->status= "Failed";
				temp->val=temp->total;
				changes = "Unsaved";	
				return;																						
			}
			temp = temp -> next;
		}
	}
	cout << "Couldn't Find Student";
}

void list::sortAuto()
{
	cout << "\n\t   Sort Student" <<endl;
	cout << "----------------------------------- " <<endl;
	char method;
	int meth;
	cout << "How do you want to sort?" <<endl;
	cout << "1. By Registration Number" << endl <<"2. By Total Marks Ascending Order" << endl <<"3. By Total Marks Descending Order" << endl;
	method = getch();
	meth = method - '0';	
	if (meth != 1 && meth != 2 && meth !=3)
	{
		cout << "Invalid Input";
		return;	
	}			
	node *temp;
	temp = head;
	if (head == NULL)
	{
		cout << "Empty List";
		return;
	}
	else
	{
		while (temp!=NULL)
		{
			if (meth==1) temp->val=temp->reg;
			if (meth==2) temp->val=temp->total;
			if (meth==3) temp->val=temp->total*(-1);					
			temp=temp->next;					
		}
	}
	insertionSort();
	cout << "\nSorted Successfully";
	changes = "Unsaved";	
}

void list::insertionSort()
{
	sorted = NULL;
	node* temp = head;
    while (temp != NULL)
    {
        node* next = temp->next;
        sortedInsert(temp);
        temp = next;
    }
    head = sorted;
}

void list::sortedInsert(node* tempNode)
{
    if (sorted == NULL || sorted->val >= tempNode->val)
    {
        tempNode->next = sorted;
        sorted = tempNode;
    }
    else
    {
        node* current = sorted;
        while (current->next != NULL && current->next->val < tempNode->val)
        {
            current = current->next;
        }
        tempNode->next = current->next;
        current->next = tempNode;
    }
}
