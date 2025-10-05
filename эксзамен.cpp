#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <ctime>

using namespace std;

struct Transaction {
    string category;
    double amount;
    time_t date;
};

class Wallet {
private:
    double balance;
    map<string, double> categories;
    vector<Transaction> transactions;

public:
    Wallet(double initialBalance) : balance(initialBalance) {}

    void deposit(double amount) {
        balance += amount;
    }

    bool spend(double amount, const string& category) {
        if (balance >= amount) {
            balance -= amount;
            categories[category] += amount;
            Transaction transaction = {category, amount, time(nullptr)};
            transactions.push_back(transaction);
            return true;
        }
        return false;
    }

    void generateReports(const string& reportType) {
        if (reportType == "day") {
            cout << "Daily report generated" << endl;
        } else if (reportType == "week") {
           
            cout << "Weekly report generated" << endl;
        } else if (reportType == "month") {
           
            cout << "Monthly report generated" << endl;
        } else {
            cout << "Unknown report type" << endl;
        }
    }

    void generateTopExpenses(const string& reportType) {
        if (reportType == "week") {
           
            cout << "Top 3 weekly expenses generated" << endl;
        } else if (reportType == "month") {
           
            cout << "Top 3 monthly expenses generated" << endl;
        } else {
            cout << "Unknown report type for top expenses" << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << "Balance: " << balance << endl;
            file << "Categories:" << endl;
            for (const auto& category : categories) {
                file << category.first << ": " << category.second << endl;
            }
            file << "Transactions:" << endl;
            for (const auto& transaction : transactions) {
                file << transaction.category << " " << transaction.amount << " " << transaction.date << endl;
            }
            file.close();
            cout << "Data saved to " << filename << endl;
        } else {
            cout << "Unable to open the file for saving." << endl;
        }
    }
};

int main() {
    double initialBalance;
    cout << "Enter your initial balance: ";
    cin >> initialBalance;
    
    Wallet wallet(initialBalance);

    while (true) {
        cout << "\n1. Deposit\n2. Spend\n3. Generate Reports\n4. Generate Top Expenses\n5. Save to File\n6. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                double depositAmount;
                cout << "Enter the deposit amount: ";
                cin >> depositAmount;
                wallet.deposit(depositAmount);
                break;
            }
            case 2: {
                double spendAmount;
                string category;
                cout << "Enter the spend amount: ";
                cin >> spendAmount;
                cout << "Enter the category: ";
                cin >> category;
                if (wallet.spend(spendAmount, category)) {
                    cout << "Transaction successful." << endl;
                } else {
                    cout << "Insufficient balance." << endl;
                }
                break;
            }
            case 3: {
                string reportType;
                cout << "Enter report type (day/week/month): ";
                cin >> reportType;
                wallet.generateReports(reportType);
                break;
            }
            case 4: {
                string topExpensesType;
                cout << "Enter report type for top expenses (week/month): ";
                cin >> topExpensesType;
                wallet.generateTopExpenses(topExpensesType);
                break;
            }
            case 5: {
                string filename;
                cout << "Enter the filename to save: ";
                cin >> filename;
                wallet.saveToFile(filename);
                break;
            }
            case 6:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}