#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class EMPLOYEE{
    char name[30];
    int age;
    char designation[30];
public:
    void set_edata(){
        cout << "Enter employee details\n";
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter designation: ";
        cin >> designation;
    }
    void show_edata(){
        cout << setw(10) << name
             << setw(10) << age
             << setw(15) << designation
             << endl;
    }
};


int main(){
    int choice;
    fstream file;
    
    char emp_id[10];    // filename must be string
    do
    {
        cout << "\n====== EMS ======" <<endl;
        cout << "Press 1: Add Record" <<endl;
        cout << "Press 2: View Record" <<endl;
        cout<<  "Press 3: Exit Program"<<endl;
        cout << "choice :";
        cin >> choice;
        switch (choice)
        {
        case 1:

            //Read in emp-id from user 
            cout << "Enter emp-id: ";   
            cin >> emp_id;

            // validate if file with entered emp-id exists
            file.open(emp_id, ios::in);
           
            //ios::in opens file for reading, fails if file does not exist. Does not create new file.
            
            cout << "\n--OUTPUT--"<<endl;
            if(file){ 
                cout << "Record with emp-id: " << emp_id <<" already exist" << endl;
            }
            else{
                file.open(emp_id, ios::out); //open file for writing, create new file if not exist.

                EMPLOYEE emp;   //create object of EMPLOYEE (in memory)
               
                //take in employee data from user 
                emp.set_edata();   // read in employee data into object in the memory
               
                file.write((char *)&emp, sizeof(emp)); // copy/write byte by byte from memory to file
                cout << "Successfully uploaded new employee data" << endl;
            }
            
            file.close();
            break;
        case 2: 
                char text[20];

            cout << "Enter emp-id: ";
            cin >> emp_id;
            // file.open(emp_id, ios::in);  // if file does not exist inform user
            file.open(emp_id, ios:: in | ios::out | ios::binary);
            cout << "\n--OUTPUT--"<<endl;
            if(!file){
                // FILE NOT FOUND CONDITION:
                cout << "SORRY ! No record found with emp-id: " <<emp_id <<endl;
            }
            else{
                //create a EMPLOYEE object in the memory 
                EMPLOYEE emp;

                // read emp data into object
                file.read((char *)&emp, sizeof(emp));

                // display employee data using objects show_edata function
                emp.show_edata();

                //  if additional data present
                char additional_data[100];
                while (file.getline(additional_data, 100)) {
                    cout << additional_data << endl;
                }

                int choice2;
                choice2 = 0;
                do
                {
                    cout << "\nPress 1: Edit " << endl;
                    cout << "Press 2: Append address(or any data)" << endl;
                    cout << "Press 3: Exit " << endl;
                    cin >> choice2;
                    switch (choice2)
                    {
                    case 1: 
                        file.clear();   // turn of EOF flag
                        EMPLOYEE emp;   //create employee object
                        emp.set_edata();    // re set values into employee object

                        file.seekp(0, ios::beg);     // take the file pointer to start
                        file.write((char *)&emp, sizeof(emp)); // overwrite existing data with new employee object data
                        cout << "Successfully Updated Employee data" << endl;
                        break;

                    case 2:
                        file.clear();   // turn of EOF flag

                        // append address at the eof
                        // file.open(emp_id, ios::app);
                        cout << "\nEnter data in key: value format" <<endl; 
                        // cin.getline(text,20);    not working
                        cin >> text;
                        file.seekp(sizeof(emp), ios::beg);     // take the file pointer towards end of data
                        file.write((char *)&text, sizeof(text));
                        if(file){
                            cout << "Update successful" << endl;
                        }
                        file.close();
                        
                        break;
                    
                    default:
                        break;
                    }
                } while (choice2 != 3);
                file.close(); 
                
            }

            // file.close();

            break;
        default:
            break;
        }
    } while (choice != 3);
 
}




