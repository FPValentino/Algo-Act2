#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Node.h"
#include "Sort.h"
using namespace std;

//prototypes
int checkValid(const string& input);
void GUI();
void dSpace();
void cls();
bool isDateValid(const string& date);
void prompt();

class InvalidInputException : public exception {
    public:
        const char* what() const noexcept override {
            return "Invalid input.";
    }
 };

class bankRecords {
private:
    Node* head;

    Node* binarySearch(int loanID) { //change tom for customizable parameter
    if (!head) return NULL;

    Node* leftN = head;
    Node* rightN = NULL;

    do {
        // Find the middle node between leftN and rightN
        Node* mid = leftN;
        Node* fast = leftN;

        while (fast != rightN && fast->next != rightN) {
            mid = mid->next;
            fast = fast->next->next;
        }
        cout << "Checking node with loanID: " << mid->loanID << endl;

        if (mid->loanID == loanID) {
            cout << "Found loanID: " << loanID << " at middle " << endl;
            return mid;
        } else if (mid->loanID < loanID) {
            cout << "Searching right half..." << endl;
            leftN = mid->next;
        } else {
            cout << "Searching left half..." << endl;
            rightN = mid;
        }

    } while (rightN != leftN);

    return NULL;
}

public:
    bankRecords() {
        head = NULL;
    }

    void addRecord(string name, int age, int loanID, string loanDate, string dueDate, int loanAmount, int origAmount) {
        Node* newNode = new Node(name, age, 0, loanDate, dueDate, loanAmount, origAmount); 
    
        if (head == NULL) {
            newNode->loanAmount = (loanAmount * 0.06) + loanAmount;
            newNode->loanID = 100; 
            head = newNode;
            return;
        }
    
        bool found[1000] = {false}; 
        int counter = 0;
        
        Node* temp = head;
        while (temp != NULL) {
            found[temp->loanID] = true;
            if(temp->name == name)
                counter++;
            temp = temp->next;
        }

        if(counter > 2) {
            cout << "User cannot exceed the limit of 2 maximum loans...\n";
            cout << "Loan cannot be initialized...\n";
            prompt();
            return;
        }
    
        int missingID = 100; 
        while (found[missingID]) {
            missingID++;
        }
    
        newNode->loanID = missingID;
    
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        newNode->loanAmount = (loanAmount * 0.06) + loanAmount;
        temp->next = newNode;
        cout << "Loan Record ID # " << missingID <<" Added Successfully...\n";
        prompt();
    }
    

    void displayRecords(){
        bool recordExists = false;
        int i = 1;
        Node *p = head;
            
            //check if there are records
            if(p!=NULL){
                recordExists = true;
            } else {
                cout << "No loans currently exists...\n";
                cout << "Returning to main...\n";
                prompt();
                return;
            }
    
        cout << "=======================================================================================================================================================\n";
        cout << setw(18) << "LOAN ID" << setw(10) << " || " 
        << setw(12) << "NAME" << setw(10) << " || " 
        << setw(15) << "LOAN DATE" << setw(10) << " || " 
        << setw(15) << "DUE DATE" << setw(10) << " || " 
        << setw(15) << "LOAN AMOUNT" << setw(10) << " || " 
        << setw(15) << "DUE AMOUNT" << endl;
        cout << "=======================================================================================================================================================\n";
        p = head;
            
        while (p != NULL) {
            cout << left << "#" << setw(10) << i  
            << "|" << setw(17) << p->loanID  
            << setw(25) << p->name  
            << setw(25) << p->loanDate  
            << setw(25) << p->dueDate  
            << setw(25) << p->origAmount  
            << setw(25) << p->loanAmount << endl;  
            p = p->next;
            i++;
        }
        prompt();
    }

    void sortByMerge(int sortKey) {
        head = Sort::mergeSort(head, sortKey);
    }

    void sortByLoanDate() {
        if (!head || !head->next) return;
        Node* tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        Sort::quickSort(head, tail);
    }

    Node* findBinary(int loanID) {
        return binarySearch(loanID);
    }

    void saveFile() {
        ofstream rec("record.txt");
        Node* tmp = head;
        while (tmp != NULL) {
            rec << tmp->name << " "
                << tmp->age << " "
                << tmp->loanID << " "
                << tmp->loanDate << " "
                << tmp->dueDate << " "
                << tmp->loanAmount << " "
                << tmp->origAmount << endl;
            tmp = tmp->next;
        }
        rec.close();
    }
    void loadFile() {
        bool check = false;
    
        ifstream rec("record.txt");
        if (!rec) {
            cout << "Error opening file.\n";
            return;
        }
    
        string name, loanDate, dueDate;
        int age, loanID, loanAmount, origAmount;
    
        while (rec >> name >> age >> loanID >> loanDate >> dueDate >> loanAmount >> origAmount) {
            Node* newNode = new Node(name, age, loanID, loanDate, dueDate, loanAmount, origAmount);
            if (head == NULL) {
                head = newNode;
            } else {
                Node* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            check = true;
        }
        rec.close();
    
        if (check) {
            cout << "Data loaded successfully\n";
        } else {
            cout << "No data found in file.\n";
        }
    }

    Node* getHead() { 
        return head; 
    }
    void setHead(Node* newHead) { 
        head = newHead; 
    }
};

int main() {
    GUI();
    return 0;
}

void GUI(){
    bankRecords bank;
	bank.loadFile(); //initialize saved data

	while (1){
		char choice;
		string validInput;

        cls();
		dSpace();
		cout << setw(40) << "HADJI LOAN SYSTEM\n";
		dSpace();
		cout <<"A. ADD LOAN\n";
		cout <<"B. UPDATE LOAN\n";
		cout <<"C. VIEW ALL LOANS\n";
		cout <<"D. SAVE LOANS\n";
        cout <<"E. EXIT\n";
		dSpace();
		cout <<"Your Choice: ";

        while (true) {
			try {
				cin >> choice;

				if (cin.fail() || cin.peek() != '\n' || !isalpha(choice)) {
					throw InvalidInputException();
				}
				break;
			} catch (const InvalidInputException &e) {
				cout << e.what() << endl;
				cin.ignore(10000, '\n');
			}
    	}

        choice = toupper(choice);
        switch(choice) {
            case 'A': {
                string name, dDate, lDate, temp;
                int age, lID = 0, lAmount = 0, oAmount;

                cls();
                dSpace();
                cout << setw(35) << "ADD LOAN\n";
                dSpace();
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Age: ";
                cin >> temp;
                age = checkValid(temp);
                if(age == -1){
                    prompt();
                    break;
                }

                cout << "Enter Loan Amount: ";
                cin >> temp;
                oAmount = checkValid(temp);
                if(oAmount == -1) {
                    prompt();
                    break;
                }

                if(oAmount > 500000) {
                    cout << "Only loan amounts of 1 - 500,000 available...";
                    prompt();
                    break;
                }

                cout << "Enter Date (YYYY/MM/DD): ";
                cin >> lDate;
                if (!isDateValid(lDate)) {
                    cout << "Invalid date format...\n";
                    prompt();
                    break;
                }

                cout << "Enter Due Date (YYYY/MM/DD): ";
                cin >> dDate;
                if (!isDateValid(dDate)) {
                    cout << "Invalid date format...\n";
                    prompt();
                    break;
                }
                
                lAmount = oAmount;
                bank.addRecord(name, age, lID, lDate, dDate, lAmount, oAmount); 
                bank.saveFile();
                break;
            }
            case 'B': {
                string temp;
                cout << "ENTER LOAN ID: ";
                cin >> temp;
                int loanID = checkValid(temp);
                bank.sortByMerge(2);
                dSpace();
                Node* binary = bank.findBinary(loanID);
                dSpace();
                prompt();
                cls();
                if(binary) {
                cout << "Found record ID " << binary->loanID << endl 
                << "NAME: " << binary->name << endl 
                << "Due Amount: " << binary->loanAmount << endl 
                << "Due Date: " << binary->dueDate << endl;
                
                string choices;
                dSpace();
                cout << "1. Add Loan Amount\n";
                cout << "2. Deduct Loan Amount\n";
                dSpace();
                cout << "Your Choice: ";
                cin >> choices;

                int decider = checkValid(choices);
                    if(decider == 1) {
                        string amount;
                        cout << "Enter Amount to add: ";
                        cin >> amount;
                        int addAm = checkValid(amount);
                        int tempAm = binary->loanAmount;
                        if(tempAm+addAm > 500000) {
                            cout << "Loan cannot exceed the maximum of 500000...\n";
                            cout << "Cannot add loan...\n";
                            break;
                        }
                        binary->loanAmount += addAm;
                        cout << "Successfully updated!...\n";
                    } else if(decider == 2) {
                        string amount;
                        cout << "Enter Amount to deduct: ";
                        cin >> amount;
                        int minusAm = checkValid(amount);
                        int tempAm = binary->loanAmount;
                        if(tempAm - minusAm < 0) {
                            cout << "Invalid Amount\n"; 
                            break;
                        } else if (tempAm - minusAm == 0) {
                            cout << "Loan fully paid! Deleting record...\n";
                            
                            if (binary == bank.getHead()) {  
                                bank.setHead(binary->next);
                            } else {
                                Node* prev = bank.getHead();
                                while (prev->next != binary) {
                                    prev = prev->next;
                                }
                                prev->next = binary->next;
                            }
                        
                            delete binary;
                            cout << "Record deleted successfully!\n";
                        } else {
                            binary->loanAmount -= minusAm;
                            cout << "Successfully updated!...\n";
                        }
                    } else {
                        cout << "Invalid choice...";
                    }
                prompt();
                } else {
                    cout << "Record with Loan ID " << loanID << " not found...";
                    prompt();
                }  
                bank.saveFile();   
                break;
            }
            case 'C':  {
                int decision = 0;
                cls();
                dSpace();
                cout << setw(35) << "VIEW LOANS\n";
                dSpace();
                cout << "1. SORT BY DUE DATE\n";
                cout << "2. SORT BY AMOUNT OWED\n";
                cout << "3. SORT BY LOAN ID\n";
                cout << "4. SEARCH BY LOAN ID\n";
                cout << "5. BACK\n";
                dSpace();
                cout << "Your Choice: ";
                    string temp;
                    cin >> temp;
                    decision = checkValid(temp);
                    if(decision == -1) {
                        cin.clear();
                        break;
                    }
                
                switch(decision){
                    case 1: {
                        cls();
                        bank.sortByLoanDate();
                        prompt();
                        cls();
                        bank.displayRecords();
                        break;
                    }
                    case 2: {
                        cls();
                        bank.sortByMerge(1);
                        prompt();
                        cls();
                        bank.displayRecords();
                        break;
                    }
                    case 3: {
                        cls();
                        bank.sortByMerge(2);
                        prompt();
                        cls();
                        bank.displayRecords();
                        break;
                    }
                    case 4: {
                        string temp;
                        cout << "ENTER LOAN ID: ";
                        cin >> temp;
                        int loanID = checkValid(temp);
                        bank.sortByMerge(2);
                        dSpace();
                        Node* binary = bank.findBinary(loanID);
                        dSpace();
                        prompt();
                        cls();
                        if(binary) {
                        cout << "Found record ID " << binary->loanID << endl 
                        << "NAME: " << binary->name << endl 
                        << "Due Amount: " << binary->loanAmount << endl 
                        << "Due Date: " << binary->dueDate << endl;
                        prompt();
                        } else {
                            cout << "Record with Loan ID " << loanID << " not found...";
                            prompt();
                        }
                        break;
                    }
                    case 5: {
                        goto x;
                        break;
                    }
                    default: {
                        cout << "Please Enter numbers 1-4\n";
                    }
                }
                x:
                break;
            }
            case 'D': {
                bank.saveFile();
                cout << "Saved Sucessfully...\n";
                prompt();
                break;
            }
            case 'E': {
                cout <<"Thank you! Exiting...\n";
				return;
                break;
            }
            default: {
                cout << "Please Enter letters A-D\n";
            }
        }
	}
}

void dSpace(){
	for (int i = 0; i < 57; i++){
		cout << "=";
	}
	cout << endl;
}

int checkValid(const string& input) { //input validity checking
    bool checkValid = false;
    try { 
    for(char c : input) {
        if(!isdigit(c)) {
            throw InvalidInputException();
        }
    }
        return stoi(input);
    } catch (const exception& e) {
        cout << e.what() << endl;
        return -1;
    }
}

bool isDateValid(const string& date) { //date format checking
    if(date.length() != 10)
        return false;

    if(date[4] != '/' || date[7] != '/')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) 
            continue; 
        if (!isdigit(date[i])) 
            return false; 
    }
    return true;
}

void cls() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void prompt() {
    cout <<"\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    cout << resetiosflags(ios::adjustfield | ios::basefield | ios::floatfield); //reset setw
}

