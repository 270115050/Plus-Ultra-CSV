#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Employee {
    string name;
    int id;

    Employee(string defStr = "", int defNum = 0) {
        name = defStr;
        id = defNum;
    }
};

vector<Employee> storeVectEmp(vector<Employee>, vector<string>);
void printEmployeeList(vector<Employee>);

int main()
{
    const int MAX = 2;
    struct Employee emp[MAX], transaction;
    vector<Employee> vectEmp;

    vector<string> empData;
    string line, tempStr, tempName;
    int empID;
    char choice;
    bool isFound = true;

//Im using vector because we dont know how many data we have in the file and since vector is dynamic we dont have to specify the size of our array
//------------------------------------------------------------------------------------------------------------
// This block of code is for writing in CSV FILE and if you dont know where the CSV file is, it is inside your project folder

    ofstream writingFromCSV("emp.txt", ios::out);

    for (int i = 0; i < MAX; i++) {
        cout << "Enter the name of employee: ";
        getline(cin, emp[i].name);

        cout << "Enter the Id of employee: ";
        cin >> emp[i].id;
        cin.ignore();
        writingFromCSV << emp[i].name << "," << emp[i].id << endl;
    }
    writingFromCSV.close();

//------------------------------------------------------------------------------------------------------------
//This block of code is for reading from the CSV FILE
//What I am trying to do here is I am reading the data from CSV FILE and storing it in vector struct
//I will explain why Im storing it in a vector<struct> in the update employee section

    ifstream myfile;
    myfile.open("emp.txt", ios::in);

    while (getline(myfile, line)) { //loop while there is data in CSV FILE
        stringstream ss(line); //get the row of data in CSV file and put it inside ss, inside ss will look like this ss = "NAME","ID"

        while (!ss.eof()) {// loop while its not the end of the ss, like loop while there is more data to read

            // this line pretty much says lets take the first data
            // the data will look like this "NAME","ID" the data is separated with ,
            // so everytime we loop it goes to the next data
            // first loop will get the name and in the next loop it will get the ID
            getline(ss, tempStr, ','); 

            //Then I store that data inside a vector string
            //This will contain the name and id of employee
            //Note when taking data from csv file all of the data are type string
            empData.push_back(tempStr);
        }

        //Then I pass all of the data in the function storeVectEmp then it will return the data to our vectEmp
        vectEmp = storeVectEmp(vectEmp, empData);
        //The reason why im clearing the empData is so when we go for the next employee it wont contain the previous data of the employee
        empData.clear();
    }
    myfile.close();
//------------------------------------------------------------------------------------------------------------
    //print the employee inside the vector
    printEmployeeList(vectEmp);

//------------------------------------------------------------------------------------------------------------
//Now we have a Identical copy of our CSV File in our vector employee
//This will make it easier for us to manipulate the data of employees

    
    cout << "--------------UPDATE EMPLOYEE NAME----------------------\n\n"
        << "\tPlease enter employee id: ";
    cin >> empID;

    //loop through vector employee 
    for (int i = 0; i < vectEmp.size(); i++) {
        //check if user input is equal to existing employee id
        if (vectEmp[i].id == empID) {
            isFound = true;
            cout << "Employee found would you like to change Employee name? Press Y to change press N to exit: ";
            cin >> choice;
            if (tolower(choice) == 'y') {
                cout << "Enter new Employee name: ";
                cin >> tempName;
                //change employee name
                vectEmp[i].name = tempName;
                cout << "Employee name has been successfully update..\n\n";
            }
            else
                cout << "\n\n\t\tGOOD BYE\n\n";
            break;
        }
        else
            isFound = false;
    }
    if (!isFound)
        cout << "\n\tEmployee not found BYE BYE\n\n";


    //print employee again to show the changes
    printEmployeeList(vectEmp);

//-----------------------------------------------------------------------------------------------------------
//Now our CSV FILE and VECTOR EMPLOYEE is not identical because we just updated the name of our employee inside the VECTOR EMPLOYEE
//What we need to do now is to update the CSV File with the updated data in Vector Employee

    // re-writing/updating EMPLOYEE DATA
    ofstream updateCSVWithNewData("emp.txt", ios::out);
    for (int i = 0; i < vectEmp.size(); i++) {
        updateCSVWithNewData << vectEmp[i].name << "," << vectEmp[i].id << endl;
    }
    updateCSVWithNewData.close();

    return 0;
}
//And thats it!! That is how you Write, Read and Update data in CSV
//I really hope what I wrote made sense, try to modify the code and experiment with it have fun :D
//I dont know if this is the best way to manipulate the data inside the CSV but its the only solution that I was able to come up with and
//If you found a better way to manipulate data please share it thank you :D
//                               PLUS ULTRA!!!!!

//-----------------------------------------------------------------------------------------------------------

//This function is used to store that data that is gotten from the CSV FILE
vector<Employee> storeVectEmp(vector<Employee> vectEmp, vector<string> empData) {
    Employee emp;

    emp.name = empData[0];
    emp.id = stoi(empData[1]);// converting string to int

    vectEmp.push_back(emp);

    return vectEmp;
}

//This function prints out all of the employees
//Note this is not reading from the CSV FILE, it is reading the data inside the vector Employee
void printEmployeeList(vector<Employee> vectEmp) {
    cout << "--------------EMPLOYEE LIST---------------------\n\n";
    for (int i = 0; i < vectEmp.size(); i++) {
        cout << "Employee ID: " << vectEmp[i].id << "\tEmployee name: " << vectEmp[i].name << endl << endl;
    }
}
