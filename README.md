
# Hospital Management System

This project is a comprehensive Hospital Management System built using C++ and MySQL. It simulates the management of hospital operations including bed occupancy, patient admissions, and inventory management. The system connects to a MySQL database to store and retrieve information efficiently.


## Features
## Bed Management:
* Display total and available beds.
Automatically update bed availability when a patient is admitted or discharged.

## Patient Management:
* Admit new patients with relevant details such as name, age, medical condition, and severity.
Automatically assign beds to patients and store their information in the database.
View details of all admitted patients.

## Inventory Management:
* Add items to the hospital inventory.
View the current stock of inventory items.

## Installation

## Prerequisites
* MySQL Server
* C++ Compiler (e.g., MinGW for Windows)
* MySQL Connector/C++ (for connecting C++ with MySQL)
* A terminal or command prompt

## Demonstration:
  * Code:

  https://github.com/user-attachments/assets/acc45807-c90a-483d-875b-7a2a02c46000

  * Output:

https://github.com/user-attachments/assets/74188ef0-4c21-498e-96d4-00595aa5b2da

  * Database Interaction:

https://github.com/user-attachments/assets/82b443f8-6257-4316-90e0-ed358c9ea672

## Steps
* **Clone the Repository:**
```bash
git clone https://github.com/krishna25092005/hospital-management-system.git
cd Hospital-Management-System
```
* **Set Up MySQL Database:**
  * Create a new database named 'mydb'.
  * Run the following SQL script to create the required table:
```sql
CREATE TABLE patients (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    age INT,
    medical_condition VARCHAR(255),
    severity INT,
    bed_id INT
);
```
* **Compile the Program:**
  Use a C++ compiler to compile the program. For example, using  MinGW:
```bash
g++ main.cpp -o HospitalManagementSystem -lmysql
```
* **Run the Program:**
```bash
./HospitalManagementSystem
```

    
## Usage
* Start the program and you will be greeted with a menu offering options to view available beds, admit a patient, manage inventory, or view admitted patients.
* Follow the on-screen prompts to manage hospital operations.
## Sample Outputs
* View Available Beds:
```bash
Hospital: General Hospital
Total Beds: 250
Available Beds: 249
```
* Admit Patient:
```bash
Enter Patient Name: XYZ
Enter Patient Age: 45
Enter Patient Condition: High Fever
Enter Severity Level (1-5): 4
Patient admitted successfully to bed ID: 5
```
* Manage Inventory:
```bash
(1) Add Item to Inventory
(2) View Current Stock
(3) Go Back
Enter Your Choice: 2
Current Inventory Stock:
Item: Gloves, Quantity: 100
```

## Contributing

Contributions are always welcome! Please feel free to submit a Pull Request.



Please adhere to this project's `code of conduct`.


## License
This project is licensed under the MIT License.

[MIT](https://choosealicense.com/licenses/mit/)


## Authors

- [@krishna25092005](https://github.com/krishna25092005)

