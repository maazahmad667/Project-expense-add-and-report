#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int id = 0;

// Node for ID
class idNode {
public:
    int id;
    idNode* Next;
};

// Node for Name
class NameNode {
public:
    string name;
    NameNode* Next;
};

// Node for Price
class PriceNode {
public:
    int price;
    PriceNode* Next;
};

// Node for Date
class DateNode {
public:
    int day;
    int month;
    int year;
    DateNode* Next;
};

class expensetracking {
protected:
    NameNode* nameHead;
    PriceNode* priceHead;
    DateNode* dateHead;
    idNode* idHead;

public:
    // Initializing the head of the linked list
    expensetracking() : nameHead(NULL), priceHead(NULL), dateHead(NULL), idHead(NULL) {}

    // Function to add expense
    void addExpense() {
        // Getting Input from the user
        cout << "Enter the name of the expense: ";
        string name;
        cin >> name;
        cout << "Enter the price of the expense: ";
        int price;
        cin >> price;

        // Label for Date Section
    datesection:
        cout << "Enter the date of the expense (DD-MM-YYYY) or Press Enter For Today Date: ";
        string day, month, year;
        day = month = year = "";
        string dateinp;
        cin.ignore();
        getline(cin, dateinp);

        // If user does not enter the date, then the current date will be taken
        if (dateinp == "") {
            time_t currentTime = time(0);
            tm* now = localtime(&currentTime);
            year = to_string(now->tm_year + 1900);
            month = to_string(now->tm_mon + 1);
            day = to_string(now->tm_mday);
            cout << day << "-" << month << "-" << year << endl;
        } else {
            int count = 0;
            for (char c : dateinp) {
                if (c == '-') {
                    count++;
                    continue;
                }
                if (count == 0) {
                    day += c;
                } else if (count == 1) {
                    month += c;
                } else if (count == 2) {
                    year += c;
                }
            }
        }

        // Date Validation
        int d = stoi(day);
        int m = stoi(month);
        int y = stoi(year);

        if (d < 1 || d > 31) {
            cout << "Invalid Day\n";
            goto datesection;
        }
        if (m < 1 || m > 12) {
            cout << "Invalid Month\n";
            goto datesection;
        }
        // Months with 30 days
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            if (d > 30) {
                cout << "Invalid Day for this month\n";
                goto datesection;
            }
        }
        // February validation (simple, non-leap year check)
        if (m == 2 && d > 28) {
            cout << "Invalid Day for February\n";
            goto datesection;
        }

        // Storing Data in Nodes
        NameNode* newNameNode = new NameNode();
        newNameNode->name = name;
        newNameNode->Next = NULL;

        PriceNode* newPriceNode = new PriceNode();
        newPriceNode->price = price;
        newPriceNode->Next = NULL;

        DateNode* newDateNode = new DateNode();
        newDateNode->day = d;
        newDateNode->month = m;
        newDateNode->year = y;
        newDateNode->Next = NULL;

        idNode* newIdNode = new idNode();
        newIdNode->id = ++id;
        newIdNode->Next = NULL;

        // Adding Nodes to the linked list
        if (nameHead == NULL) {
            nameHead = newNameNode;
            priceHead = newPriceNode;
            dateHead = newDateNode;
            idHead = newIdNode;
        } else {
            NameNode* tempNameNode = nameHead;
            while (tempNameNode->Next != NULL) {
                tempNameNode = tempNameNode->Next;
            }
            tempNameNode->Next = newNameNode;

            PriceNode* tempPriceNode = priceHead;
            while (tempPriceNode->Next != NULL) {
                tempPriceNode = tempPriceNode->Next;
            }
            tempPriceNode->Next = newPriceNode;

            DateNode* tempDateNode = dateHead;
            while (tempDateNode->Next != NULL) {
                tempDateNode = tempDateNode->Next;
            }
            tempDateNode->Next = newDateNode;

            idNode* tempIDNode = idHead;
            while (tempIDNode->Next != NULL) {
                tempIDNode = tempIDNode->Next;
            }
            tempIDNode->Next = newIdNode;
        }
        cout << "Successfully Added Expense\n";
    }

    // Display all expenses
    bool displayExpense() {
        NameNode* tempNameNode = nameHead;
        PriceNode* tempPriceNode = priceHead;
        DateNode* tempDateNode = dateHead;
        idNode* tempIDNode = idHead;
        if (tempNameNode == NULL) {
            cout << "No Expense Found\n";
            return false;
        }
        cout << "\n\n===== Expense List =====\n\n";
        cout << "ID\tName\tPrice\tDate\n";
        cout << "--\t----\t-----\t----\n";
        while (tempNameNode != NULL) {
            cout << tempIDNode->id << "\t" << tempNameNode->name << "\t" << tempPriceNode->price << "\t"
                 << tempDateNode->day << "-" << tempDateNode->month << "-" << tempDateNode->year << endl;
            tempNameNode = tempNameNode->Next;
            tempPriceNode = tempPriceNode->Next;
            tempDateNode = tempDateNode->Next;
            tempIDNode = tempIDNode->Next;
        }
        return true;
    }

    // Delete expense by ID
    void deleteExpense() {
        bool have_record = displayExpense();
        if (!have_record) {
            return;
        }
        cout << "Enter ID To Delete: ";
        int loc_id;
        cin >> loc_id;

        NameNode* tempNameNode = nameHead;
        PriceNode* tempPriceNode = priceHead;
        DateNode* tempDateNode = dateHead;
        idNode* tempIDNode = idHead;
        NameNode* prevNameNode = NULL;
        PriceNode* prevPriceNode = NULL;
        DateNode* prevDateNode = NULL;
        idNode* prevIDNode = NULL;

        if (loc_id == 1) {
            nameHead = nameHead->Next;
            priceHead = priceHead->Next;
            dateHead = dateHead->Next;
            idHead = idHead->Next;
            delete tempNameNode;
            delete tempPriceNode;
            delete tempDateNode;
            delete tempIDNode;
            cout << "Expense Deleted\n";
            return;
        }

        while (tempIDNode != NULL && tempIDNode->id != loc_id) {
            prevNameNode = tempNameNode;
            prevPriceNode = tempPriceNode;
            prevDateNode = tempDateNode;
            prevIDNode = tempIDNode;
            tempNameNode = tempNameNode->Next;
            tempPriceNode = tempPriceNode->Next;
            tempDateNode = tempDateNode->Next;
            tempIDNode = tempIDNode->Next;
        }

        if (tempIDNode == NULL) {
            cout << "ID Not Found\n";
            return;
        }

        prevNameNode->Next = tempNameNode->Next;
        prevPriceNode->Next = tempPriceNode->Next;
        prevDateNode->Next = tempDateNode->Next;
        prevIDNode->Next = tempIDNode->Next;
        delete tempNameNode;
        delete tempPriceNode;
        delete tempDateNode;
        delete tempIDNode;
        cout << "Expense Deleted\n";
    }

    // Update expense by ID
    void updateExpense() {
        bool have_record = displayExpense();
        if (!have_record) {
            return;
        }
        cout << "Enter ID To Update: ";
        int loc_id;
        cin >> loc_id;

        NameNode* tempNameNode = nameHead;
        PriceNode* tempPriceNode = priceHead;
        DateNode* tempDateNode = dateHead;
        idNode* tempIDNode = idHead;

        while (tempIDNode != NULL && tempIDNode->id != loc_id) {
            tempNameNode = tempNameNode->Next;
            tempPriceNode = tempPriceNode->Next;
            tempDateNode = tempDateNode->Next;
            tempIDNode = tempIDNode->Next;
        }

        if (tempIDNode == NULL) {
            cout << "ID Not Found\n";
            return;
        }

        cout << "Enter New Name: ";
        string name;
        cin.ignore();
        getline(cin, name);
        tempNameNode->name = name;
        cout << "Enter New Price: ";
        int price;
        cin >> price;
        tempPriceNode->price = price;

    datesection:
        cout << "Enter the date of the expense (DD-MM-YYYY) or Press Enter For Today Date: ";
        string day, month, year;
        day = month = year = "";
        string dateinp;
        cin.ignore();
        getline(cin, dateinp);

        if (dateinp == "") {
            time_t currentTime = time(0);
            tm* now = localtime(&currentTime);
            year = to_string(now->tm_year + 1900);
            month = to_string(now->tm_mon + 1);
            day = to_string(now->tm_mday);
            cout << day << "-" << month << "-" << year << endl;
        } else {
            int count = 0;
            for (char c : dateinp) {
                if (c == '-') {
                    count++;
                    continue;
                }
                if (count == 0) {
                    day += c;
                } else if (count == 1) {
                    month += c;
                } else if (count == 2) {
                    year += c;
                }
            }
        }

        // Date Validation
        int d = stoi(day);
        int m = stoi(month);
        int y = stoi(year);

        if (d < 1 || d > 31) {
            cout << "Invalid Day\n";
            goto datesection;
        }
        if (m < 1 || m > 12) {
            cout << "Invalid Month\n";
            goto datesection;
        }
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            if (d > 30) {
                cout << "Invalid Day for this month\n";
                goto datesection;
            }
        }
        if (m == 2 && d > 28) {
            cout << "Invalid Day for February\n";
            goto datesection;
        }

        tempDateNode->day = d;
        tempDateNode->month = m;
        tempDateNode->year = y;
        cout << "Expense Updated\n";
    }

    // Last week report (last 7 days)
    void lastweekreport() {
        cout << "\n===== Last 7 Days Report =====\n";
        cout << "ID\tName\tPrice\tDate\n";
        cout << "--\t----\t-----\t----\n";

        DateNode* dtemp = dateHead;
        PriceNode* ptemp = priceHead;
        NameNode* ntemp = nameHead;
        idNode* itemp = idHead;

        time_t now = time(0);
        tm* t = localtime(&now);
        int today_day = t->tm_mday;
        int today_mon = t->tm_mon + 1;
        int today_year = t->tm_year + 1900;

        int total = 0;
        bool found = false;

        while (dtemp != NULL) {
            int d1 = today_year * 365 + today_mon * 30 + today_day;
            int d2 = dtemp->year * 365 + dtemp->month * 30 + dtemp->day;
            int diff_days = d1 - d2;

            if (diff_days >= 0 && diff_days <= 7) {
                cout << itemp->id << "\t" << ntemp->name << "\t" << ptemp->price << "\t"
                     << dtemp->day << "-" << dtemp->month << "-" << dtemp->year << endl;
                total += ptemp->price;
                found = true;
            }
            dtemp = dtemp->Next;
            ptemp = ptemp->Next;
            ntemp = ntemp->Next;
            itemp = itemp->Next;
        }

        if (!found) {
            cout << "No expenses in the last 7 days\n";
        } else {
            cout << "------------------------\n";
            cout << "Total\t\t" << total << endl;
        }
    }

    // Last month report (user-specified month, YYYY-MM)
    void lastmonthreport() {
        cout << "Enter month (YYYY-MM): ";
        string monthinp;
        getline(cin, monthinp);
        int target_year, target_month;
        string year = "", month = "";
        int count = 0;
        for (char c : monthinp) {
            if (c == '-') {
                count++;
                continue;
            }
            if (count == 0) {
                year += c;
            } else {
                month += c;
            }
        }
        target_year = stoi(year);
        target_month = stoi(month);

        if (target_month < 1 || target_month > 12) {
            cout << "Invalid Month\n";
            return;
        }

        cout << "\n===== Report for " << monthinp << " =====\n";
        cout << "ID\tName\tPrice\tDate\n";
        cout << "--\t----\t-----\t----\n";

        DateNode* dtemp = dateHead;
        PriceNode* ptemp = priceHead;
        NameNode* ntemp = nameHead;
        idNode* itemp = idHead;

        int total = 0;
        bool found = false;

        while (dtemp != NULL) {
            if (dtemp->year == target_year && dtemp->month == target_month) {
                cout << itemp->id << "\t" << ntemp->name << "\t" << ptemp->price << "\t"
                     << dtemp->day << "-" << dtemp->month << "-" << dtemp->year << endl;
                total += ptemp->price;
                found = true;
            }
            dtemp = dtemp->Next;
            ptemp = ptemp->Next;
            ntemp = ntemp->Next;
            itemp = itemp->Next;
        }

        if (!found) {
            cout << "No expenses in " << monthinp << "\n";
        } else {
            cout << "------------------------\n";
            cout << "Total\t\t" << total << endl;
        }
    }

    // Expenses by specific date
    void expensesByDate() {
        cout << "Enter date (DD-MM-YYYY): ";
        string dateinp, day = "", month = "", year = "";
        getline(cin, dateinp);
        int count = 0;
        for (char c : dateinp) {
            if (c == '-') {
                count++;
                continue;
            }
            if (count == 0) {
                day += c;
            } else if (count == 1) {
                month += c;
            } else {
                year += c;
            }
        }

        int d = stoi(day);
        int m = stoi(month);
        int y = stoi(year);

        if (d < 1 || d > 31 || m < 1 || m > 12) {
            cout << "Invalid Date\n";
            return;
        }
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            if (d > 30) {
                cout << "Invalid Day for this month\n";
                return;
            }
        }
        if (m == 2 && d > 28) {
            cout << "Invalid Day for February\n";
            return;
        }

        cout << "\n===== Expenses for " << dateinp << " =====\n";
        cout << "ID\tName\tPrice\tDate\n";
        cout << "--\t----\t-----\t----\n";

        DateNode* dtemp = dateHead;
        PriceNode* ptemp = priceHead;
        NameNode* ntemp = nameHead;
        idNode* itemp = idHead;

        int total = 0;
        bool found = false;

        while (dtemp != NULL) {
            if (dtemp->day == d && dtemp->month == m && dtemp->year == y) {
                cout << itemp->id << "\t" << ntemp->name << "\t" << ptemp->price << "\t"
                     << dtemp->day << "-" << dtemp->month << "-" << dtemp->year << endl;
                total += ptemp->price;
                found = true;
            }
            dtemp = dtemp->Next;
            ptemp = ptemp->Next;
            ntemp = ntemp->Next;
            itemp = itemp->Next;
        }

        if (!found) {
            cout << "No expenses on " << dateinp << "\n";
        } else {
            cout << "------------------------\n";
            cout << "Total\t\t" << total << endl;
        }
    }

    // Expenses by specific month
    void expensesByMonth() {
        cout << "Enter month (YYYY-MM): ";
        string monthinp;
        getline(cin, monthinp);
        int target_year, target_month;
        string year = "", month = "";
        int count = 0;
        for (char c : monthinp) {
            if (c == '-') {
                count++;
                continue;
            }
            if (count == 0) {
                year += c;
            } else {
                month += c;
            }
        }
        target_year = stoi(year);
        target_month = stoi(month);

        if (target_month < 1 || target_month > 12) {
            cout << "Invalid Month\n";
            return;
        }

        cout << "\n===== Expenses for " << monthinp << " =====\n";
        cout << "ID\tName\tPrice\tDate\n";
        cout << "--\t----\t-----\t----\n";

        DateNode* dtemp = dateHead;
        PriceNode* ptemp = priceHead;
        NameNode* ntemp = nameHead;
        idNode* itemp = idHead;

        int total = 0;
        bool found = false;

        while (dtemp != NULL) {
            if (dtemp->year == target_year && dtemp->month == target_month) {
                cout << itemp->id << "\t" << ntemp->name << "\t" << ptemp->price << "\t"
                     << dtemp->day << "-" << dtemp->month << "-" << dtemp->year << endl;
                total += ptemp->price;
                found = true;
            }
            dtemp = dtemp->Next;
            ptemp = ptemp->Next;
            ntemp = ntemp->Next;
            itemp = itemp->Next;
        }

        if (!found) {
            cout << "No expenses in " << monthinp << "\n";
        } else {
            cout << "------------------------\n";
            cout << "Total\t\t" << total << endl;
        }
    }

    // Find most/least expensive item for day, week, or month
    void extremeExpense() {
        cout << "Enter period (day/week/month): ";
        string period;
        getline(cin, period);

        int target_day = 0, target_month = 0, target_year = 0;
        if (period == "day" || period == "week") {
            cout << "Enter date (DD-MM-YYYY): ";
            string dateinp, day = "", month = "", year = "";
            getline(cin, dateinp);
            int count = 0;
            for (char c : dateinp) {
                if (c == '-') {
                    count++;
                    continue;
                }
                if (count == 0) {
                    day += c;
                } else if (count == 1) {
                    month += c;
                } else {
                    year += c;
                }
            }
            target_day = stoi(day);
            target_month = stoi(month);
            target_year = stoi(year);

            if (target_day < 1 || target_day > 31 || target_month < 1 || target_month > 12) {
                cout << "Invalid Date\n";
                return;
            }
            if (target_month == 4 || target_month == 6 || target_month == 9 || target_month == 11) {
                if (target_day > 30) {
                    cout << "Invalid Day for this month\n";
                    return;
                }
            }
            if (target_month == 2 && target_day > 28) {
                cout << "Invalid Day for February\n";
                return;
            }
        } else if (period == "month") {
            cout << "Enter month (YYYY-MM): ";
            string monthinp, year = "", month = "";
            getline(cin, monthinp);
            int count = 0;
            for (char c : monthinp) {
                if (c == '-') {
                    count++;
                    continue;
                }
                if (count == 0) {
                    year += c;
                } else {
                    month += c;
                }
            }
            target_year = stoi(year);
            target_month = stoi(month);
            if (target_month < 1 || target_month > 12) {
                cout << "Invalid Month\n";
                return;
            }
        } else {
            cout << "Invalid period. Use day, week, or month\n";
            return;
        }

        cout << "1. Most Expensive\n2. Least Expensive\nEnter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice != 1 && choice != 2) {
            cout << "Invalid choice\n";
            return;
        }

        DateNode* dtemp = dateHead;
        PriceNode* ptemp = priceHead;
        NameNode* ntemp = nameHead;
        idNode* itemp = idHead;

        int extreme_price = (choice == 1) ? -1 : 999999;
        int extreme_id = -1;
        string extreme_name = "";
        int extreme_day = 0, extreme_month = 0, extreme_year = 0;
        bool found = false;

        while (dtemp != NULL) {
            bool include = false;
            if (period == "day") {
                include = (dtemp->day == target_day && dtemp->month == target_month && dtemp->year == target_year);
            } else if (period == "week") {
                int d1 = target_year * 365 + target_month * 30 + target_day;
                int d2 = dtemp->year * 365 + dtemp->month * 30 + dtemp->day;
                int diff_days = d1 - d2;
                include = (diff_days >= 0 && diff_days <= 7);
            } else if (period == "month") {
                include = (dtemp->year == target_year && dtemp->month == target_month);
            }

            if (include) {
                if ((choice == 1 && ptemp->price > extreme_price) || 
                    (choice == 2 && ptemp->price < extreme_price)) {
                    extreme_price = ptemp->price;
                    extreme_id = itemp->id;
                    extreme_name = ntemp->name;
                    extreme_day = dtemp->day;
                    extreme_month = dtemp->month;
                    extreme_year = dtemp->year;
                    found = true;
                }
            }
            dtemp = dtemp->Next;
            ptemp = ptemp->Next;
            ntemp = ntemp->Next;
            itemp = itemp->Next;
        }

        if (!found) {
            cout << "No expenses found for the specified " << period << "\n";
        } else {
            cout << "\n===== " << (choice == 1 ? "Most" : "Least") << " Expensive for " << period << " =====\n";
            cout << "ID\tName\tPrice\tDate\n";
            cout << "--\t----\t-----\t----\n";
            cout << extreme_id << "\t" << extreme_name << "\t" << extreme_price << "\t"
                 << extreme_day << "-" << extreme_month << "-" << extreme_year << endl;
        }
    }
};

int main() {
    expensetracking* expense = new expensetracking();
    cout << "===== Welcome To Expense Tracking App =====\n\n";
    int selection;
    do {
        cout << "\n\n1. Add Expense\n2. View Expense\n3. Delete Expense\n4. Update Expense\n"
             << "5. Last Week Report\n6. Last Month Report\n7. Expenses by Date\n"
             << "8. Expenses by Month\n9. Most/Least Expensive\n10. Exit\n";
        cin >> selection;
        cin.ignore();
        switch (selection) {
            case 1:
                expense->addExpense();
                break;
            case 2:
                expense->displayExpense();
                break;
            case 3:
                expense->deleteExpense();
                break;
            case 4:
                expense->updateExpense();
                break;
            case 5:
                expense->lastweekreport();
                break;
            case 6:
                expense->lastmonthreport();
                break;
            case 7:
                expense->expensesByDate();
                break;
            case 8:
                expense->expensesByMonth();
                break;
            case 9:
                expense->extremeExpense();
                break;
            case 10:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Selection\n";
        }
    } while (selection != 10);
    delete expense;
    return 0;
}
