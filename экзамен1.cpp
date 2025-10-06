#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <algorithm>

using namespace std;

// Структура для хранения информации о транзакции
struct Transaction {
    string category;  // Категория расхода (еда, транспорт, развлечения и т.д.)
    double amount;    // Сумма транзакции
    time_t date;      // Дата и время транзакции (в формате time_t)
};

// Класс для управления финансами (кошелек)
class Wallet {
private:
    double balance;                              // Текущий баланс кошелька
    map<string, double> categories;             // Словарь категорий и суммарных расходов по ним
    vector<Transaction> transactions;           // Вектор всех транзакций

public:
    // Конструктор кошелька с начальным балансом
    Wallet(double initialBalance) : balance(initialBalance) {}

    // Метод для пополнения кошелька
    void deposit(double amount) {
        balance += amount;  // Увеличиваем баланс на указанную сумму
        cout << "Deposited: " << amount << ". New balance: " << balance << endl;
    }

    // Метод для расходования средств
    bool spend(double amount, const string& category) {
        // Проверяем, достаточно ли средств на балансе
        if (balance >= amount) {
            balance -= amount;                   // Уменьшаем баланс
            categories[category] += amount;      // Добавляем сумму к соответствующей категории
            // Создаем новую транзакцию и добавляем в историю
            Transaction transaction = {category, amount, time(nullptr)};
            transactions.push_back(transaction);
            cout << "Spent: " << amount << " on " << category << ". Remaining balance: " << balance << endl;
            return true;  // Транзакция успешна
        }
        cout << "Failed to spend " << amount << ". Insufficient balance: " << balance << endl;
        return false;  // Недостаточно средств
    }

    // Метод для генерации отчетов по периодам
    void generateReports(const string& reportType) {
        time_t now = time(nullptr);      // Получаем текущее время
        tm* currentTime = localtime(&now); // Преобразуем в локальное время
        
        // Генерируем отчет в зависимости от указанного типа
        if (reportType == "day") {
            cout << "=== DAILY REPORT ===" << endl;
            cout << "Balance: " << balance << endl;
            // В реальной реализации здесь была бы фильтрация транзакций за день
        } else if (reportType == "week") {
            cout << "=== WEEKLY REPORT ===" << endl;
            cout << "Balance: " << balance << endl;
            // В реальной реализации здесь была бы фильтрация транзакций за неделю
        } else if (reportType == "month") {
            cout << "=== MONTHLY REPORT ===" << endl;
            cout << "Balance: " << balance << endl;
            // В реальной реализации здесь была бы фильтрация транзакций за месяц
        } else {
            cout << "Unknown report type" << endl;
        }
        
        // Выводим расходы по категориям
        cout << "Expenses by category:" << endl;
        for (const auto& category : categories) {
            cout << "  " << category.first << ": " << category.second << endl;
        }
    }

    // Метод для генерации ТОП-3 расходов по периодам
    void generateTopExpenses(const string& reportType) {
        if (reportType == "week") {
            cout << "=== TOP 3 WEEKLY EXPENSES ===" << endl;
            // В реальной реализации:
            // 1. Фильтруем транзакции за неделю
            // 2. Сортируем по убыванию суммы
            // 3. Выводим первые 3
        } else if (reportType == "month") {
            cout << "=== TOP 3 MONTHLY EXPENSES ===" << endl;
            // Аналогично для месяца
        } else {
            cout << "Unknown report type for top expenses" << endl;
            return;
        }
        
        // Временная заглушка - выводим все транзакции
        cout << "All transactions (sorted by amount):" << endl;
        vector<Transaction> sortedTransactions = transactions;
        sort(sortedTransactions.begin(), sortedTransactions.end(), 
             [](const Transaction& a, const Transaction& b) { return a.amount > b.amount; });
        
        for (size_t i = 0; i < min(sortedTransactions.size(), size_t(3)); i++) {
            cout << "  " << i+1 << ". " << sortedTransactions[i].category << ": " 
                 << sortedTransactions[i].amount << endl;
        }
    }

    // Метод для генерации ТОП-3 категорий по расходам
    void generateTopCategories(const string& reportType) {
        if (reportType == "week") {
            cout << "=== TOP 3 WEEKLY CATEGORIES ===" << endl;
            // В реальной реализации - анализируем расходы за неделю по категориям
        } else if (reportType == "month") {
            cout << "=== TOP 3 MONTHLY CATEGORIES ===" << endl;
            // В реальной реализации - анализируем расходы за месяц по категориям
        } else {
            cout << "Unknown report type for top categories" << endl;
            return;
        }
        
        // Выводим категории, отсортированные по сумме расходов
        cout << "Categories sorted by total spending:" << endl;
        vector<pair<string, double>> sortedCategories(categories.begin(), categories.end());
        sort(sortedCategories.begin(), sortedCategories.end(), 
             [](const pair<string, double>& a, const pair<string, double>& b) { return a.second > b.second; });
        
        for (size_t i = 0; i < min(sortedCategories.size(), size_t(3)); i++) {
            cout << "  " << i+1 << ". " << sortedCategories[i].first << ": " 
                 << sortedCategories[i].second << endl;
        }
    }

    // Метод для сохранения отчетов в файл
    void saveReportsToFile(const string& reportType, const string& filename) {
        ofstream file(filename);  // Открываем файл для записи
        if (file.is_open()) {
            file << "=== FINANCIAL REPORT ===" << endl;
            file << "Report type: " << reportType << endl;
            file << "Balance: " << balance << endl;
            file << "Generated at: " << ctime(&(time_t&)time(nullptr)); // Время генерации
            
            // Сохраняем расходы по категориям
            file << "\nExpenses by category:" << endl;
            for (const auto& category : categories) {
                file << "  " << category.first << ": " << category.second << endl;
            }
            
            // Сохраняем ТОП-3 расходов если это недельный или месячный отчет
            if (reportType == "week" || reportType == "month") {
                file << "\nTop 3 expenses:" << endl;
                vector<Transaction> sortedTransactions = transactions;
                sort(sortedTransactions.begin(), sortedTransactions.end(), 
                     [](const Transaction& a, const Transaction& b) { return a.amount > b.amount; });
                
                for (size_t i = 0; i < min(sortedTransactions.size(), size_t(3)); i++) {
                    file << "  " << i+1 << ". " << sortedTransactions[i].category << ": " 
                         << sortedTransactions[i].amount << endl;
                }
                
                file << "\nTop 3 categories:" << endl;
                vector<pair<string, double>> sortedCategories(categories.begin(), categories.end());
                sort(sortedCategories.begin(), sortedCategories.end(), 
                     [](const pair<string, double>& a, const pair<string, double>& b) { return a.second > b.second; });
                
                for (size_t i = 0; i < min(sortedCategories.size(), size_t(3)); i++) {
                    file << "  " << i+1 << ". " << sortedCategories[i].first << ": " 
                         << sortedCategories[i].second << endl;
                }
            }
            
            file.close();  // Закрываем файл
            cout << "Report saved to " << filename << endl;
        } else {
            cout << "Unable to open the file for saving report." << endl;
        }
    }

    // Метод для сохранения всех данных кошелька в файл
    void saveToFile(const string& filename) {
        ofstream file(filename);  // Открываем файл для записи
        if (file.is_open()) {
            // Сохраняем основной баланс
            file << "Balance: " << balance << endl;
            
            // Сохраняем категории и суммы по ним
            file << "Categories:" << endl;
            for (const auto& category : categories) {
                file << category.first << ": " << category.second << endl;
            }
            
            // Сохраняем полную историю транзакций
            file << "Transactions:" << endl;
            for (const auto& transaction : transactions) {
                file << transaction.category << " " << transaction.amount << " " 
                     << transaction.date << endl;
            }
            
            file.close();  // Закрываем файл
            cout << "All data saved to " << filename << endl;
        } else {
            cout << "Unable to open the file for saving." << endl;
        }
    }
};

// Главная функция программы
int main() {
    double initialBalance;
    
    // Запрашиваем начальный баланс у пользователя
    cout << "Enter your initial balance: ";
    cin >> initialBalance;
    
    // Создаем объект кошелька с указанным начальным балансом
    Wallet wallet(initialBalance);

    // Основной цикл программы
    while (true) {
        // Выводим меню доступных операций
        cout << "\n=== PERSONAL FINANCE MANAGER ===" << endl;
        cout << "1. Deposit money" << endl;
        cout << "2. Spend money" << endl;
        cout << "3. Generate Reports" << endl;
        cout << "4. Generate Top Expenses" << endl;
        cout << "5. Generate Top Categories" << endl;
        cout << "6. Save all data to File" << endl;
        cout << "7. Save Report to File" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;  // Считываем выбор пользователя

        // Обрабатываем выбор пользователя
        switch (choice) {
            case 1: {  // Пополнение кошелька
                double depositAmount;
                cout << "Enter the deposit amount: ";
                cin >> depositAmount;
                wallet.deposit(depositAmount);
                break;
            }
            case 2: {  // Расходование средств
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
            case 3: {  // Генерация отчетов
                string reportType;
                cout << "Enter report type (day/week/month): ";
                cin >> reportType;
                wallet.generateReports(reportType);
                break;
            }
            case 4: {  // ТОП-3 расходов
                string topExpensesType;
                cout << "Enter report type for top expenses (week/month): ";
                cin >> topExpensesType;
                wallet.generateTopExpenses(topExpensesType);
                break;
            }
            case 5: {  // ТОП-3 категорий
                string topCategoriesType;
                cout << "Enter report type for top categories (week/month): ";
                cin >> topCategoriesType;
                wallet.generateTopCategories(topCategoriesType);
                break;
            }
            case 6: {  // Сохранение всех данных
                string filename;
                cout << "Enter the filename to save all data: ";
                cin >> filename;
                wallet.saveToFile(filename);
                break;
            }
            case 7: {  // Сохранение отчета
                string reportType, filename;
                cout << "Enter report type (day/week/month): ";
                cin >> reportType;
                cout << "Enter the filename to save report: ";
                cin >> filename;
                wallet.saveReportsToFile(reportType, filename);
                break;
            }
            case 8:  // Выход из программы
                cout << "Goodbye! Thank you for using Personal Finance Manager." << endl;
                return 0;
            default:  // Неверный выбор
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}