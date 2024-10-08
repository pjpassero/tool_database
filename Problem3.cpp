/*
 Problem3.cpp
 Hardware Store
 Philip Passero
 May 07, 2024
 
Allows the user to manage their hardware store inventory. Can add a tool, update a tool, delete a tool, and load tools
 from an outside fileNam.txt file. The user can also create and reset their database as well as view all the filled records.
 
 
 */


#include <iostream>
#include <string>
#include <fstream>
#include "Hardware.h"

const string DATABASE_FILE = "hardware.dat";
using namespace std;

void displayStartMenu();
void listAllFullRecords();
void updateToolRecord();
void inputNewTool();
void deleteToolRecord();
void populateFromTextFile(const string& textFileName);
void initalizeDatabase();
void handleInput(int num);


int main() {
    int optionSelected;
    cout << "Welcome to the database. Please Refer to the Table Below for Actions." << endl;
    do {
        displayStartMenu();
        cout << "\nEnter Option:";
        cin >> optionSelected;
        handleInput(optionSelected);
    }while (optionSelected != 7);
    
    cout << "Thank you for using the database. Program Ended" << endl;
    
    return 0;
}

void displayStartMenu() {
  
    cout << "1:Initalize Database" << endl;
    cout << "2: Populate From Text File" << endl;
    cout << "3: Input New Data" << endl;
    cout << "4: List All Full Records" << endl;
    cout << "5: Update a Tool Record" << endl;
    cout << "6: Delete a record" << endl;
    cout << "7: Terminate Program" << endl;
    
    
}
/*
 Initalizes the database to 100 empty files.
 Checks to make sure the user wants to initalize the database
 
 */
void initializeDatabase() {
    ofstream file(DATABASE_FILE, ios::binary | ios::out);
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    string input;
    cout << "Are you sure you want to initalize the database? All previously stored records will be lost (y/n):";
    cin >> input;
    if(input == "y") {
        Tool emptyRecord;
        for (int i = 0; i < 100; ++i) {
            file.write((char*)&emptyRecord, sizeof(Tool));
        }
        cout << "\nDatabase Initalized Successfully. \n\n";
    } else {
        cout << "User selected no\n" << endl;
    }
  
    file.close();
}
/*
 Populates the .dat file using data found in the txt file. Writes each tool to its proper location in the .dat file.
 Takes in a reference to the file name from the user and opens the file based on that name. 
 */
void populateFromTextFile(const string& fileName) {
    ofstream outFile(DATABASE_FILE, ios::binary | ios::in);
    ifstream inFile(fileName);

    if(!inFile) {
        cerr << "File error" << endl;
    }
    bool populated = false;
    Tool tool;
    while(inFile >> tool) {
        streampos position = (tool.getID() - 1) * sizeof(Tool);

        outFile.seekp(position);
        outFile.write((char*)&tool, sizeof(Tool));
        populated = true;
    }
    if(populated) {
        cout << "\nDatabase successfully populated from: " << fileName << "\n\n";

    } else {
        cout << "\nError, Database unsuccessfully populated from: " << fileName << "\n\n";

    }
    
    outFile.close();
    inFile.close();
}
/*
 Input new tool at given index.
 
 */
void inputNewTool() {
    Tool newTool;
    cout << "Enter new Tool Data: (Tool ID, Tool Cost, Tool Quantity, Tool Name): \n";
    cin >> newTool;

    ofstream file(DATABASE_FILE, ios::binary |  ios::in | ios::out);

    if (!file) {
        cerr << "File not found!" << endl;
        
        return;
    }

    // Calculate the position where the new tool's data should be written
    streampos position = (newTool.getID() - 1) * sizeof(Tool);

    file.seekp(position);
    file.write((char*)&newTool, sizeof(Tool));

    
    cout << "\nTool" << newTool.getName() << " successfully written to Database \n\n";
    file.close();
}
/*
 Lists all full records in the .dat file. Does not include empty records.
 Displays tools in a formatted table
 */
void listAllFullRecords() {
    ifstream file(DATABASE_FILE, ios::binary | ios::out);
    if (!file) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }
    cout << left <<setw(10) << "Tool ID" << "\t" << setw(20) << "Tool Name"<< "\t" << setw(8)<< "Tool Quantity" << "\t$" << setw(5) << "Tool Cost"<< endl;
    cout << "---------------------------------------------------------------------" << endl;
    Tool tool;
    while (file.read((char*)&tool, sizeof(Tool))) {
        if (tool.getID() != -1) { // Check if the record is not empty
            cout << tool << endl;
        }
    }
    cout << "\n";
}
/*
 Deletes a tool at a user specified location. Replaces the tool with an empty tool record.
 */
void deleteToolRecord() {
    fstream file(DATABASE_FILE, ios::binary | ios::out | ios::in);
    int itemNum;
    bool found = false;
    cout << "Please Enter the Tool ID you'd like to delete:";
    cin >> itemNum;
    Tool tool;
    while (file.read((char*)&tool, sizeof(Tool))) {
        if (tool.getID() == itemNum) {
            found = true;
            cout << tool << endl;
            Tool emptyTool;
            streampos position = (tool.getID() - 1) * sizeof(Tool);

            file.seekp(position);
            file.write((char*)&emptyTool, sizeof(Tool));
            cout << "Tool Removed!";
            break;
        }
    }
    if (found) {
        cout << "\nRecord " << itemNum << " deleted successfully" << "\n\n";

    } else {
        cout << "\nRecord " << itemNum << " deleted unsuccessfully. Record was unable to be found!" << "\n\n";

    }

    file.close();
    
}
/*
 Allows the user to update a tool based on the input recordID.
 Will write the new data to the recordID specified by the user
 */
void updateToolRecord(int recordID) {
    fstream file(DATABASE_FILE, ios::binary | ios::out | ios::in);
    
    if(!file) {
        cerr << "Error opening " << DATABASE_FILE << endl;
    }
    
    Tool tool;
    Tool newTool;
    bool found = false;
    while(file.read((char*)&tool, sizeof(Tool))) {
        if(tool.getID() == recordID) {
            found = true;
            cout << tool << endl;
            cout << "Please enter new Tool Data (ID, Cost, Quantity, Name):";
            cin >> newTool;
            streampos position = (recordID - 1) *sizeof(Tool);
            file.seekp(position);
            file.write((char*)&newTool, sizeof(Tool));
            break;
        }
    }
    if(found) {
        cout << "Record found and Updated" << endl;
    } else {
        cout << "Record not Found" << endl;
    }
    file.close();
    
}
/*
 Handles the user input. Calls each function based on the action the user wants to perform.
 Input integer number represents the user's choice from the menu.
 
 */
    void handleInput(int num) {
            switch (num) {
                case 1: {
                    initializeDatabase();
                    break;
                }
                case 2: {
                    string textFileName;
                    cout << "Enter the name of the Text File:";
                    cin >> textFileName;
                    populateFromTextFile(textFileName);
                    break;
                }
                case 3: {
                    inputNewTool();
                    break;
                }
                case 4: {
                    listAllFullRecords();
                    break;
                    
                }
                case 5: {
                    int recordID;
                    cout << "Please enter the record id to update:";
                    cin >> recordID;
                    updateToolRecord(recordID);
                    break;
                    
                }
                case 6: {
                    deleteToolRecord();
                    break;
                    
                }
                case 7: {
                    cout <<"Program Will End" << endl;
                    break;
                    
                }
                default: {
                    cout << "Instruction not found!";
                }
                    
            }
        
    }


