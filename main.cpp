#include <iostream>
#include <mysql.h>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <windows.h>

using namespace std;

// Forward declaration if needed
class Inventory;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "Amitian@123";
const char* DB = "mydb";

class Hospital {
private:
    string Name;
    int TotalBeds;
    int Fees;

public:
    Hospital(string name, int totalBeds, int fees)
        : Name(name), TotalBeds(totalBeds), Fees(fees) {}

    string getName() {
        return Name;
    }

    int getTotalBeds() {
        return TotalBeds;
    }

    int getFees() {
        return Fees;
    }

    int getOccupiedBeds(MYSQL* conn) {
        string query = "SELECT COUNT(*) FROM patients";
        if (mysql_query(conn, query.c_str())) {
            cout << "Error: " << mysql_error(conn) << endl;
            return 0;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == NULL) {
            cout << "Error: " << mysql_error(conn) << endl;
            return 0;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        int occupiedBeds = atoi(row[0]);
        mysql_free_result(res);

        return occupiedBeds;
    }

    void displayBeds(MYSQL* conn) {
        int occupiedBeds = getOccupiedBeds(conn);
        int availableBeds = TotalBeds - occupiedBeds;

        cout << "Hospital: " << Name << endl;
        cout << "Total Beds: " << TotalBeds << endl;
        cout << "Available Beds: " << availableBeds << endl;
    }
};

class Inventory {
private:
    map<string, int> items;

public:
    void addItem(string itemName, int quantity) {
        items[itemName] += quantity;
    }

    void checkInventory() {
        cout << "Current Inventory Stock:\n";
        for (map<string, int>::iterator it = items.begin(); it != items.end(); ++it) {
            cout << "Item: " << it->first << ", Quantity: " << it->second << endl;
        }
    }
};

// Function declarations
void displayBeds(Hospital &hospital, MYSQL* conn);
void admitPatient(Hospital &hospital, MYSQL* conn);
void manageInventory(Inventory &inventory);
void displayAdmittedPatients(MYSQL* conn);

// Function definitions
void displayBeds(Hospital &hospital, MYSQL* conn) {
    hospital.displayBeds(conn);
}

void admitPatient(Hospital &hospital, MYSQL* conn) {
    string name;
    int age, severity;
    string condition;

    // Input the patient details
    cout << "Enter Patient Name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);
    cout << "Enter Patient Age: ";
    cin >> age;
    cout << "Enter Patient Condition: ";
    cin.ignore(); // Clear input buffer
    getline(cin, condition);
    cout << "Enter Severity Level (1-5): ";
    cin >> severity;

    // Validate the input
    if (name.empty() || condition.empty() || severity < 1 || severity > 5) {
        cout << "Error: Please provide valid inputs for all patient details." << endl;
        return;
    }

    int occupiedBeds = hospital.getOccupiedBeds(conn);
    int availableBeds = hospital.getTotalBeds() - occupiedBeds;

    if (availableBeds > 0) {
        int bedId = occupiedBeds + 1;  // Assign the next available bed ID

        stringstream ss;
        ss << "INSERT INTO patients (name, age, medical_condition, severity, bed_id) VALUES ('"
           << name << "', " << age << ", '" << condition << "', " << severity << ", " << bedId << ")";

        if (mysql_query(conn, ss.str().c_str())) {
            cout << "Error: " << mysql_error(conn) << endl;
        } else {
            cout << "Patient admitted successfully to bed ID: " << bedId << endl;
        }
    } else {
        cout << "No beds available." << endl;
    }
}

void manageInventory(Inventory &inventory) {
    int choice;
    string itemName;
    int quantity;

    bool exitInventory = false;
    while (!exitInventory) {
        cout << "(1) Add Item to Inventory\n(2) View Current Stock\n(3) Go Back\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Item Name: ";
                cin.ignore(); // Clear input buffer
                getline(cin, itemName);
                cout << "Enter Quantity: ";
                cin >> quantity;
                inventory.addItem(itemName, quantity);
                break;

            case 2:
                inventory.checkInventory();
                break;

            case 3:
                exitInventory = true; // Exit the inventory management loop
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
}

void displayAdmittedPatients(MYSQL* conn) {
    string query = "SELECT * FROM patients";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == NULL) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_ROW row;

    cout << "Admitted Patients Details:\n";
    cout << "----------------------------\n";

    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            cout << mysql_fetch_field_direct(res, i)->name << ": " << (row[i] ? row[i] : "NULL") << endl;
        }
        cout << "----------------------------\n";
    }

    mysql_free_result(res);
}

int main() {
    MYSQL* conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return 1;
    } else {
        cout << "Logged into Database" << endl;
    }
    Sleep(1000);

    Hospital hospital("General Hospital", 250, 5000);
    Inventory inventory;

    bool exit = false;
    while (!exit) {
        cout << "\nWelcome to Hospital Management System" << endl;
        cout << "------------------*************-------------------" << endl;
        cout << "(1) View Available Beds" << endl;
        cout << "(2) Admit Patient" << endl;
        cout << "(3) Manage Inventory" << endl;
        cout << "(4) View Admitted Patients" << endl;
        cout << "(5) Exit" << endl;
        cout << "Enter Your Choice: ";
        int val;
        cin >> val;

        switch (val) {
            case 1:
                displayBeds(hospital, conn);
                break;
            case 2:
                admitPatient(hospital, conn);
                break;
            case 3:
                manageInventory(inventory);
                break;
            case 4:
                displayAdmittedPatients(conn);
                break;
            case 5:
                exit = true;
                cout << "Exiting the system..." << endl;
                Sleep(1000);
                break;
            default:
                cout << "Invalid Input" << endl;
                Sleep(1000);
        }
    }

    mysql_close(conn);
    return 0;
}

