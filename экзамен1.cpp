#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <algorithm> // для сортировки

using namespace std;

// Структура для хранения информации о транзакции
struct Transaction {
    string category;  // Категория расхода
    double amount;    // Сумма транзакции
    time_t date;      // Дата транзакции
};

// Класс для управления финансами
class Wallet {
private:
    double balance;                              // Текущий баланс
    map<string, double> categories;             // Категории и суммы расходов
    vector<Transaction> transactions;           // История всех транзакций

public:
    // Конструктор - создает кошелек с начальным балансом
    Wallet(double initialBalance) : balance(initialBalance) {}

    // Пополнение баланса
    void deposit(double amount) {
        balance += amount;
    }

    // Расходование средств с указанием категории
    bool spend(double amount, const string& category) {
        if (balance >= amount) {
            balance -= amount;
            categories[category] += amount; // Увеличиваем сумму в категории
            // Создаем новую транзакцию и добавляем в историю
            Transaction transaction = {category, amount, time(nullptr)};
            transactions.push_back(transaction);
            return true;
        }
        return false;
    }

    // Генерация отчетов за разные периоды
    void generateReports(const string& reportType) {
        if (reportType == "day") {
            cout << "Daily report generated" << endl;
            // Здесь будет детальный отчет за день
        } else if (reportType == "week") {
            cout << "Weekly report generated" << endl;
            // Здесь будет детальный отчет за неделю
        } else if (reportType == "month") {
            cout << "Monthly report generated" << endl;
            // Здесь будет детальный отчет за месяц
        } else {
            cout << "Unknown report type" << endl;
        }
        
        // Показываем общие расходы по категориям
        cout << "Expenses by category:" << endl;
        for (const auto& category : categories) {
            cout << "  " << category.first << ": " << category.second << endl;
        }
    }

    // Генерация ТОП-3 самых больших расходов
    void generateTopExpenses(const string& reportType) {
        if (reportType == "week") {
            cout << "Top 3 weekly expenses:" << endl;
        } else if (reportType == "month") {
            cout << "Top 3 monthly expenses:" << endl;
        } else {
            cout << "Unknown report type for top expenses" << endl;
            return;
        }
        
        // Сортируем транзакции по убыванию суммы
        vector<Transaction> sortedTransactions = transactions;
        sort(sortedTransactions.begin(), sortedTransactions.end(), 
            [](const Transaction& a, const Transaction& b) {
                return a.amount > b.amount;
            });
        
        // Выводим ТОП-3
        for (int i = 0; i < min(3, (int)sortedTransactions.size()); i++) {
            cout << i+1 << ". " << sortedTransactions[i].category << ": " 
                 << sortedTransactions[i].amount << endl;
        }
    }

    // Генерация ТОП-3 категорий по расходам 
    void generateTopCategories(const string& reportType) {
        if (reportType == "week") {
            cout << "Top 3 weekly categories:" << endl;
        } else if (reportType == "month") {
            cout << "Top 3 monthly categories:" << endl;
        } else {
            cout << "Unknown report type for top categories" << endl;
            return;
        }
        
        // Сортируем категории по убыванию суммы расходов
        vector<pair<string, double>> sortedCategories;
        for (const auto& category : categories) {
            sortedCategories.push_back(category);
        }
        
        sort(sortedCategories.begin(), sortedCategories.end(), 
            [](const pair<string, double>& a, const pair<string, double>& b) {
                return a.second > b.second;
            });
        
        // Выводим ТОП-3 категории
        for (int i = 0; i < min(3, (int)sortedCategories.size()); i++) {
            cout << i+1 << ". " << sortedCategories[i].first << ": " 
                 << sortedCategories[i].second << endl;
        }
    }

    // Сохранение отчетов в файл 
    void saveReportsToFile(const string& reportType, const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << "Financial Report - " << reportType << endl;
            file << "Balance: " << balance << endl;
            file << "Categories report:" << endl;
            
            // Сохраняем категории
            for (const auto& category : categories) {
                file << category.first << ": " << category.second << endl;
            }
            
            // Сохраняем ТОП-3 расходов
            file << "Top 3 expenses:" << endl;
            vector<Transaction> sortedTransactions = transactions;
            sort(sortedTransactions.begin(), sortedTransactions.end(), 
                [](const Transaction& a, const Transaction& b) {
                    return a.amount > b.amount;
                });
            
            for (int i = 0; i < min(3, (int)sortedTransactions.size()); i++) {
                file << i+1 << ". " << sortedTransactions[i].category << ": " 
                     << sortedTransactions[i].amount << endl;
            }
            
            // Сохраняем ТОП-3 категорий
            file << "Top 3 categories:" << endl;
            vector<pair<string, double>> sortedCategories;
            for (const auto& category : categories) {
                sortedCategories.push_back(category);
            }
            
            sort(sortedCategories.begin(), sortedCategories.end(), 
                [](const pair<string, double>& a, const pair<string, double>& b) {
                    return a.second > b.second;
                });
            
            for (int i = 0; i < min(3, (int)sortedCategories.size()); i++) {
                file << i+1 << ". " << sortedCategories[i].first << ": " 
                     << sortedCategories[i].second << endl;
            }
            
            file.close();
            cout << "Report saved to " << filename << endl;
        } else {
            cout << "Unable to open the file for saving report." << endl;
        }
    }

    // Сохранение всех данных кошелька в файл
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
    
    // Создаем кошелек с начальным балансом
    Wallet wallet(initialBalance);

    // Главный цикл программы
    while (true) {
        // Меню выбора действий
        cout << "\n1. Deposit\n2. Spend\n3. Generate Reports\n4. Generate Top Expenses\n5. Generate Top Categories\n6. Save to File\n7. Save Report to File\n8. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        // Обработка выбора пользователя
        switch (choice) {
            case 1: { // Пополнение баланса
                double depositAmount;
                cout << "Enter the deposit amount: ";
                cin >> depositAmount;
                wallet.deposit(depositAmount);
                break;
            }
            case 2: { // Расходование средств
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
            case 3: { // Генерация отчетов
                string reportType;
                cout << "Enter report type (day/week/month): ";
                cin >> reportType;
                wallet.generateReports(reportType);
                break;
            }
            case 4: { // ТОП-3 расходов
                string topExpensesType;
                cout << "Enter report type for top expenses (week/month): ";
                cin >> topExpensesType;
                wallet.generateTopExpenses(topExpensesType);
                break;
            }
            case 5: { // ТОП-3 категорий 
                string topCategoriesType;
                cout << "Enter report type for top categories (week/month): ";
                cin >> topCategoriesType;
                wallet.generateTopCategories(topCategoriesType);
                break;
            }
            case 6: { // Сохранение всех данных
                string filename;
                cout << "Enter the filename to save: ";
                cin >> filename;
                wallet.saveToFile(filename);
                break;
            }
            case 7: { // Сохранение отчета 
                string reportType, filename;
                cout << "Enter report type (day/week/month): ";
                cin >> reportType;
                cout << "Enter the filename to save report: ";
                cin >> filename;
                wallet.saveReportsToFile(reportType, filename);
                break;
            }
            case 8: // Выход из программы
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
