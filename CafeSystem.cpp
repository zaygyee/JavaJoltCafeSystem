#include <iostream>
#include <string>
#include <vector>
#include <iomanip>  // For formatting the output (setw)

using namespace std;

// Base class for Employee information
class Employee {
protected:
    string employeeId;
    string employeeName;
    string position;
    string employeeType; // Full-time or Part-time
    int leaveDays;
    double overtimeHours;
    double workingHours; // Used for part-time employees
    string startDate;

public:
    Employee() : employeeId(""), employeeName(""), position(""), employeeType(""),
                leaveDays(0), overtimeHours(0), workingHours(0) {}

    void inputEmployeeDetails() {
        cout << "Enter employee ID: ";
        getline(cin, employeeId);
        cout << "Enter employee Name: ";
        getline(cin, employeeName);

        // Position choices
        cout << "Enter Position (1: Barista, 2: Cashier, 3: Kitchen Staff, 4: Cleaner, 5: Waiter, 6: Supervisor): ";
        int posChoice;
        cin >> posChoice;
        cin.ignore();  // Clear buffer

        // Validate position choice
        while (posChoice < 1 || posChoice > 6) {
            cout << "Invalid position! Please enter a valid position (1-6): ";
            cin >> posChoice;
            cin.ignore();  // Clear buffer
        }

        // Assign position based on number
        switch (posChoice) {
            case 1: position = "barista"; break;
            case 2: position = "cashier"; break;
            case 3: position = "kitchen staff"; break;
            case 4: position = "cleaner"; break;
            case 5: position = "waiter"; break;
            case 6: position = "supervisor"; break;
            default: position = "unknown"; break;
        }

        // Employee type: f for full-time, p for part-time
        cout << "Enter Employee Type (F/f for Full-time, P/p for Part-time): ";
        char typeChoice;
        cin >> typeChoice;
        cin.ignore(); // Clear buffer

        // Validate employee type
        while (typeChoice != 'f' && typeChoice != 'F' && typeChoice != 'p' && typeChoice != 'P') {
            cout << "Invalid input! Please enter 'F/f' for Full-time or 'P/p' for Part-time: ";
            cin >> typeChoice;
            cin.ignore(); // Clear buffer
        }

        // Assign employee type
        if (typeChoice == 'f' || typeChoice == 'F') {
            employeeType = "full-time";
        } else if (typeChoice == 'p' || typeChoice == 'P') {
            employeeType = "part-time";
        } else {
            employeeType = "Wrong Input!";
        }

         // Ask for start date
        cout << "Enter Start Date (yyyy-mm-dd): ";
        getline(cin, startDate); // Assuming the format is yyyy-mm-dd

        // Only ask for leave days and overtime if the employee is full-time
        if (employeeType == "full-time") {
            cout << "Enter Leave Days: ";
            cin >> leaveDays;

            cout << "Enter Overtime Hours: ";
            cin >> overtimeHours;
        }

        // Only ask for working hours if the employee is part-time
        if (employeeType == "part-time") {
            cout << "Enter Working Hours (Only for part-time): ";
            cin >> workingHours;
        }

        cin.ignore(); // Clear the buffer
    }

    void displayEmployeeDetails() const {
        cout << "| " << setw(12) << left << employeeId
             << "| " << setw(20) << left << employeeName
             << "| " << setw(15) << left << position
             << "| " << setw(12) << left;

        // Display full form of employee type
        if (employeeType == "full-time") {
            cout << "Full-time";
        } else if (employeeType == "part-time") {
            cout << "Part-time";
        } else {
            cout << "Unknown";
        }

        // Only show Leave Days and Overtime for Full-time employees
        if (employeeType == "full-time") {
            cout << "| " << setw(10) << left << leaveDays
                 << "| " << setw(14) << left << overtimeHours;
        } else {
            cout << "| " << setw(10) << left << "N/A"
                 << "| " << setw(14) << left << "N/A";
        }
        cout << "| " << setw(12) << left << startDate;  // Display start date
        cout << " |" << endl;
    }

    string getEmployeeId() const { return employeeId; } // Getter for Employee ID
    string getEmployeeName() const { return employeeName; } // Getter for Employee Name
    string getPosition() const { return position; }
    string getEmployeeType() const { return employeeType; }
    int getLeaveDays() const { return leaveDays; }
    double getOvertimeHours() const { return overtimeHours; }
    double getWorkingHours() const { return workingHours; }
    string getStartDate() const { return startDate; }
};

// Salary Calculation Class
class SalaryCalculator {
public:
    double calculateBasicSalary(const Employee& emp) const {
        if (emp.getPosition() == "barista") return 1920;
        else if (emp.getPosition() == "cashier") return 1790;
        else if (emp.getPosition() == "kitchen staff" && emp.getEmployeeType() == "full-time") return 1850;
        else if (emp.getPosition() == "kitchen staff" && emp.getEmployeeType() == "part-time") return 1850;
        else if (emp.getPosition() == "cleaner" && emp.getEmployeeType() == "full-time") return 1400;
        else if (emp.getPosition() == "cleaner" && emp.getEmployeeType() == "part-time") return 1400;
        else if (emp.getPosition() == "waiter" && emp.getEmployeeType() == "full-time") return 1700;
        else if (emp.getPosition() == "waiter" && emp.getEmployeeType() == "part-time") return 1700;
        else if (emp.getPosition() == "supervisor") return 2400;
        return 0;
    }

    // Calculate part-time salary based on working hours per day
    double calculatePartTimeSalary(const Employee& emp) const {
        double basicSalary = calculateBasicSalary(emp) / 30;  // Monthly salary divided by 30 days
        double hourlyWage = basicSalary / 8;    // Daily wage divided by 8 to get hourly wage
        return hourlyWage * emp.getWorkingHours(); // Multiply to get  salary
    }

    // Calculate leave bonus (only for full-time employees)
    double calculateLeaveBonus(const Employee& emp) const {
        if (emp.getEmployeeType() == "part-time") return 0;

        if (emp.getLeaveDays() >= 4) {
            // If leave days are 4 or more, no bonus for full-time employees
            return 0;
        } else if (emp.getLeaveDays() == 0) {
            return 300;
        } else if (emp.getLeaveDays() == 1) {
            return 200;
        } else if (emp.getLeaveDays() == 2) {
            return 100;
        }
        return 0;
    }

    // Calculate overtime pay (only for full-time employees)
    double calculateOvertimePay(const Employee& emp) const {
        if (emp.getEmployeeType() == "part-time") return 0;

        // If the full-time employee has 4 or more leave days, no overtime pay
        if (emp.getLeaveDays() >= 4) {
            return 0;
        }

        double basicSalary = calculateBasicSalary(emp);
        double dailyWage = basicSalary / 30; // Assuming 30 working days in a month
        double hourlyWage = dailyWage / 8; // Assuming 8 working hours in a day
        return emp.getOvertimeHours() * (hourlyWage * 2); // Overtime is paid at double the hourly wage
    }

    // Calculate penalties (only for full-time employees)
    double calculatePenalties(const Employee& emp) const {
        if (emp.getEmployeeType() == "part-time") return 0;

        double penalty = 0;

        // If leave days are 4 or more and there is overtime, apply 1% penalty to the salary
        if (emp.getLeaveDays() >= 4 && emp.getOvertimeHours() > 0) {
            penalty = calculateBasicSalary(emp) * 0.01; // 1% salary reduction
        }
        return penalty;
    }

    // Calculate total salary including deductions and bonuses
    double calculateSalary(const Employee& emp) const {
        double basicSalary = calculateBasicSalary(emp);
        double leaveBonus = calculateLeaveBonus(emp);
        double overtimePay = calculateOvertimePay(emp);
        double penalties = calculatePenalties(emp);

        double totalSalary = 0;

        if (emp.getEmployeeType() == "part-time") {
            totalSalary = calculatePartTimeSalary(emp); // Only part-time salary calculation
        } else {
            // If leave days >= 4 and there is overtime, remove bonuses and apply 1% penalty
            if (emp.getLeaveDays() >= 4 && emp.getOvertimeHours() > 0) {
                leaveBonus = 0;
                overtimePay = 0;
                totalSalary = basicSalary - (basicSalary * 0.01); // 1% penalty on the total salary
            } else {
                totalSalary = basicSalary + leaveBonus + overtimePay - penalties;
            }
        }

        // For full-time employees, deduct tax and social security
        if (emp.getEmployeeType() == "full-time") {
            double tax = totalSalary * 0.02; // 2% tax
            double socialSecurity = 10; // Fixed $10 social security tax
            return totalSalary - tax - socialSecurity;
        }

        // For part-time employees, no tax deductions
        return totalSalary;
    }
};

// Manager Class to handle adding, viewing, updating, and deleting employees
class EmployeeManager {
private:
    vector<Employee> employees;
    SalaryCalculator salaryCalculator;
    
    void merge(vector<Employee>& arr, int left, int mid, int right, bool sortByName) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Employee> leftArray(n1);
        vector<Employee> rightArray(n2);

        for (int i = 0; i < n1; i++)
            leftArray[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArray[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (sortByName) {
                if (leftArray[i].getEmployeeName() <= rightArray[j].getEmployeeName()) {
                    arr[k] = leftArray[i];
                    i++;
                } else {
                    arr[k] = rightArray[j];
                    j++;
                }
            } else {
                if (leftArray[i].getEmployeeId() <= rightArray[j].getEmployeeId()) {
                    arr[k] = leftArray[i];
                    i++;
                } else {
                    arr[k] = rightArray[j];
                    j++;
                }
            }
            k++;
        }

        while (i < n1) {
            arr[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }

    void mergeSort(vector<Employee>& arr, int left, int right, bool sortByName) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid, sortByName);
            mergeSort(arr, mid + 1, right, sortByName);

            merge(arr, left, mid, right, sortByName);
        }
    }

public:
    void sortEmployees(bool sortByName = true) {
        if (employees.empty()) {
            cout << "No employees to sort.\n";
            return;
        }
        mergeSort(employees, 0, employees.size() - 1, sortByName);
        cout << (sortByName ? "Employees sorted by name.\n" : "Employees sorted by ID.\n");
        
        // Display sorted employees
        displayEmployees();
    }
    
    void addEmployee() {
        Employee emp;
        emp.inputEmployeeDetails();
        employees.push_back(emp);
        cout << "Employee added successfully!\n";
    }

   void displayEmployees() const {
    if (employees.empty()) {
        cout << "No employees to display.\n";
    } else {
        // Display header for full-time employee table
        cout << "\n--- Full-time Employees ---\n";
        cout << "| " << setw(12) << left << "Employee ID"
             << "| " << setw(20) << left << "Employee Name"
             << "| " << setw(15) << left << "Position"
             << "| " << setw(12) << left << "Type"
             << "| " << setw(10) << left << "Leave Days"
             << "| " << setw(14) << left << "Overtime Hours"
             << "| " << setw(12) << left << "Start Date"
             << "| " << setw(13) << left << "Basic Salary"
             << "| " << setw(12) << left << "Leave Bonus"
             << "| " << setw(14) << left << "Overtime Bonus"
             << "| " << setw(12) << left << "Tax"
             << "| " << setw(14) << left << "Salary"
             << " |\n";
        cout << string(185, '-') << endl;

        // Display full-time employee details
        for (const auto& emp : employees) {
            if (emp.getEmployeeType() == "full-time") {
                cout << "| " << setw(12) << left << emp.getEmployeeId()
                     << "| " << setw(20) << left << emp.getEmployeeName()
                     << "| " << setw(15) << left << emp.getPosition()
                     << "| " << setw(12) << left << "Full-time"
                     << "| " << setw(10) << left << emp.getLeaveDays()
                     << "| " << setw(14) << left << emp.getOvertimeHours()
                     << "| " << setw(12) << left << emp.getStartDate();

                // Calculate and display bonuses, tax, and salary
                double basicSalary = salaryCalculator.calculateBasicSalary(emp);
                double leaveBonus = salaryCalculator.calculateLeaveBonus(emp);
                double overtimeBonus = salaryCalculator.calculateOvertimePay(emp);
                double totalSalary = salaryCalculator.calculateSalary(emp);
                double tax = totalSalary * 0.02; // 2% tax

                cout << "| " << "$" << setw(12) << right << fixed << setprecision(2) << basicSalary
                     << "| " << "$" << setw(11) << right << fixed << setprecision(2) << leaveBonus
                     << "| " << "$" << setw(13) << right << fixed << setprecision(2) << overtimeBonus
                     << "| " << "$" << setw(11) << right << fixed << setprecision(1) << tax
                     << "| " << "$" << setw(13) << right << fixed << setprecision(2) << totalSalary
                     << " |\n";
                cout << string(185, '-') << endl;
            }
        }

        // Display header for part-time employee table
        cout << "\n--- Part-time Employees ---\n";
        cout << "| " << setw(12) << left << "Employee ID"
             << "| " << setw(20) << left << "Employee Name"
             << "| " << setw(15) << left << "Position"
             << "| " << setw(12) << left << "Type"
             << "| " << setw(14) << left << "Working Hours"
             << "| " << setw(12) << left << "Start Date"
             << "| " << setw(14) << left << "Salary"
             << " |\n";
        cout << string(115, '-') << endl;

        // Display part-time employee details
        for (const auto& emp : employees) {
            if (emp.getEmployeeType() == "part-time") {
                double totalSalary = salaryCalculator.calculatePartTimeSalary(emp);

                cout << "| " << setw(12) << left << emp.getEmployeeId()
                     << "| " << setw(20) << left << emp.getEmployeeName()
                     << "| " << setw(15) << left << emp.getPosition()
                     << "| " << setw(12) << left << "Part-time"
                     << "| " << setw(14) << left << emp.getWorkingHours()
                     << "| " << setw(12) << left << emp.getStartDate()
                     << "| " << "$" << setw(13) << right << fixed << setprecision(2) << totalSalary
                     << " |\n";
                cout << string(115, '-') << endl;
            }
        }
    }
}

    //Monthly Report
    void generateMonthlyReport() const {
    int fullTimeCount = 0, partTimeCount = 0;
    double totalFullTimeSalary = 0, totalPartTimeSalary = 0;

    // Calculate the total full-time and part-time salary and counts
    for (const auto& emp : employees) {
        if (emp.getEmployeeType() == "full-time") {
            fullTimeCount++;
            totalFullTimeSalary += salaryCalculator.calculateSalary(emp); // Full-time salary including bonuses and deductions
        } else if (emp.getEmployeeType() == "part-time") {
            partTimeCount++;
            totalPartTimeSalary += salaryCalculator.calculatePartTimeSalary(emp); // Part-time salary
        }
    }

    double totalSalary = totalFullTimeSalary + totalPartTimeSalary;

    // Display the monthly report in a table format
    cout << "\n--- Monthly Report ---\n";
    cout << string(63, '-') << endl;

    cout << "| " << setw(36) << left << "Total Full-time Employees"
         << "| " << setw(21) << right << fullTimeCount << " |" << endl;
    cout << string(63, '-') << endl;

    cout << "| " << setw(36) << left << "Total Part-time Employees"
         << "| " << setw(21) << right << partTimeCount << " |" << endl;
    cout << string(63, '-') << endl;

    cout << "| " << setw(36) << left << "Total Full-time Salary"
         << "| " << "$" << setw(20) << right << fixed << setprecision(2) << totalFullTimeSalary << " |" << endl;
    cout << string(63, '-') << endl;

    cout << "| " << setw(36) << left << "Total Part-time Salary"
         << "| " << "$" << setw(20) << right << fixed << setprecision(2) << totalPartTimeSalary << " |" << endl;
    cout << string(63, '-') << endl;

    cout << "| " << setw(30) << left << "Total Salary (Full-time + Part-time)"
         << "| " << "$" << setw(20) << right << fixed << setprecision(2) << totalSalary << " |" << endl;
    cout << string(63, '-') << endl;
}

    void updateEmployee() {
        string employeeId;
        cout << "Enter Employee ID to update: ";
        cin >> employeeId;
        cin.ignore();

        bool found = false;
        for (auto& emp : employees) {
            if (emp.getEmployeeId() == employeeId) {
                found = true;
                cout << "Employee found! Please enter the new details.\n";
                emp.inputEmployeeDetails();
                cout << "Employee details updated successfully!\n";
                break;
            }
        }
        if (!found) {
            cout << "Employee with ID " << employeeId << " not found.\n";
        }
    }
};

// Main function
int main() {
    EmployeeManager manager;
    int choice;

    while (true) {
        cout << "\n---Employee Payroll System---\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Sort Employees\n"; //  for monthly report
        cout << "5. Generate Monthly Reports\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            manager.addEmployee(); // Add employee
        } else if (choice == 2) {
            manager.displayEmployees(); // View all employees
        } else if (choice == 3) {
            manager.updateEmployee(); // Update employee details
        } else if (choice == 4) {
            cout << "Sort employees by:\n1. Name\n2. ID\nEnter choice: ";
            int sortChoice;
            cin >> sortChoice;

            if (sortChoice == 1) {
                manager.sortEmployees(true);  // Sort by name
            } else if (sortChoice == 2) {
                manager.sortEmployees(false);  // Sort by ID
            } else {
                cout << "Invalid sorting choice. Please try again.\n";
            }
        } else if (choice == 5) {
            cout << "Generating monthly report...\n";
             manager.generateMonthlyReport(); // Generate and view the monthly report
        } else if (choice == 6) {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
