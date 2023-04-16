#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;
using std::cout;

class Wallet {
private:
    string name;
    double balance;
public:
    Wallet() {}
    Wallet(string name, double balance) : name(name), balance(balance) {}
    string NameG() const {
        return name;
    }
    double Balance() const {
        return balance;
    }

    void Deposit(double amount) {
        balance += amount;
    }
    void vivod(double amount) {
        if (amount > balance) {
            cout << "Nedostatochno deneg na " << name << "\n";
            cerr << "Nedostatochno deneg na " << name << "\n";
        }
        else {
            balance -= amount;
        }
    }
};

class Card {
private:
    string name;
    double balance;
public:
    Card() {}
    Card(string name, double balance) : name(name), balance(balance) {}
    string NameG() const {
        return name;
    }
    double Balance() const {
        return balance;
    }
    void Deposit(double amount) {
        balance += amount;
    }
    void vivod(double amount) {
        if (amount > balance) {
            cout << "Nedostatochno deneg na " << name << "\n";
            cerr << "Nedostatochno deneg na " << name << "\n";
        }
        else {
            balance -= amount;
        }
    }
};

class Schet {
private:
    double amount;
    string category;
    string date;
public:
    Schet() {}
    Schet(double amount, string category, string date) : amount(amount), category(category), date(date) {}
    string CategoryG() const {
        return category;
    }

    double AmountG() const {
        return amount;
    }

    string DateG() const {
        return date;
    }
};

class FinanceManager {
private:
    vector<Wallet> wallets;
    vector<Card> cards;
    vector<Schet> Schets;
public:
    void WalletG(const Wallet& wallet) {
        wallets.push_back(wallet);
    }
    void CardG(const Card& card) {
        cards.push_back(card);
    }
    void deposit(const string& name, double amount) {
        bool found = false;
        for (auto& wallet : wallets) {
            if (wallet.NameG() == name) {
                wallet.Deposit(amount);
                found = true;
                break;
            }
        }
        if (!found) {
            for (auto& card : cards) {
                if (card.NameG() == name) {
                    card.Deposit(amount);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            cerr << "Error! " << name << "\n";
        }
    }
    void addSchet(double amount, const string& category, const string& date) {
        Schets.push_back(Schet(amount, category, date));
    }
    void SchetDate(const string& start, const string& end = "") {
        map<string, double> SchetCategory;
        double SchetSum = 0.0;
        for (const auto& Schet : Schets) {
            if (Schet.DateG() >= start && (end.empty() || Schet.DateG() <= end)) {
                SchetCategory[Schet.CategoryG()] += Schet.AmountG();
                SchetSum += Schet.AmountG();
            }
        }
        for (const auto& pair : SchetCategory) {
            cout << pair.first << ": " << pair.second << "\n";
        }
        cout << "Vsego: " << SchetSum << "\n";
    }
    vector<pair<string, double>> SchetTop(const string& start, const string& end = "") {
        map<string, double> SchetCategory;
        for (const auto& Schet : Schets) {
            if (Schet.DateG() >= start && (end.empty() || Schet.DateG() <= end)) {
                SchetCategory[Schet.CategoryG()] += Schet.AmountG();
            }
        }
        vector<pair<string, double>> SchetS(SchetCategory.begin(), SchetCategory.end());
        sort(SchetS.begin(), SchetS.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
        return vector<pair<string, double>>(SchetS.begin(), SchetS.begin() + min(static_cast<size_t>(3), SchetS.size()));
    }
    vector<pair<string, double>> SchetTopC(const string& start, const string& end = "") {
        map<string, double> SchetCategory;
        for (const auto& Schet : Schets) {
            if (Schet.DateG() >= start && (end.empty() || Schet.DateG() <= end)) {
                SchetCategory[Schet.CategoryG()] += Schet.AmountG();
            }
        }
        vector<pair<string, double>> SchetS(SchetCategory.begin(), SchetCategory.end());
        sort(SchetS.begin(), SchetS.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
        return vector<pair<string, double>>(SchetS.begin(), SchetS.begin() + min(static_cast<size_t>(3), SchetS.size()));
    }
};

int main() {
    FinanceManager manager;
    while (true) {
        cout << "Vvedite 'w' chtobi dobavit koshelek, 'c' chtobi dobavit kartu, 'd' chovi vnesti popolneniye balanca , \n 'e' chtobi dobavit rashod, 'p' chtobi poluchit rashodi za period, 't' chtobi poluchit top rashodov i kategoriy, \n ili 'q' chtobi viiti\n";
        char choice;
        cin >> choice;
        if (choice == 'w') {
            string name;
            double balance;
            cout << "Vvedite snachalo imya koshelka, zatem cherez enter balance\n";
            cin >> name >> balance;
            manager.WalletG(Wallet(name, balance));
        }
        else if (choice == 'c') {
            string name;
            double balance;
            cout << "Vvedite snachalo imya carti, zatem cherez enter balance\n";
            cin >> name >> balance;
            manager.CardG(Card(name, balance));
        }
        else if (choice == 'd') {
            string name;
            double amount;
            cout << "Vvedite snachalo imya carti ili koshelka, zatem sumu dlya popolneniya cherez enter\n";
            cin >> name >> amount;
            manager.deposit(name, amount);
        }
        else if (choice == 'e') {
            string category, date;
            double amount;
            cout << "Vvedite kategoriyu, zatem summu i posle datu cherez enter\n";
            cin >> category >> amount >> date;
            manager.addSchet(amount, category, date);
        }
        else if (choice == 'p') {
            string start, end;
            cout << "VVetie nachalnyuy i konechnyuy daty( god-den-mecyac, naprimer 2023-01-01) cherez enter\n";
            cin >> start >> end;
            manager.SchetDate(start, end);
        }
        else if (choice == 't') {
            string start, end;
            cout << "VVetie nachalnyuy i konechnyuy daty( god-den-mecyac, naprimer 2023-01-01) cherez enter" << "\n";
            cin >> start >> end;
            vector<pair<string, double>> topSchets = manager.SchetTop(start, end);
            vector<pair<string, double>> topCategories = manager.SchetTopC(start, end);
            ofstream outFile("report.txt");
            cout << "Top 3 rashodov po kategoriyam:\n";
            outFile << "Top 3 rashodov po kategoriyam:\n";
            for (const auto& pair : topSchets) {
                cout << pair.first << ": " << pair.second << "\n";
                outFile << pair.first << ": " << pair.second << "\n";
            }
            cout << "Top 3 rashodov po obshim rashodam:\n";
            outFile << "Top 3 rashodov po obshim rashodam:\n";
            for (const auto& pair : topCategories) {
                outFile << pair.first << ": " << pair.second << "\n";
            }
            outFile.close();
        }
        else if (choice == 'q') {
            break;
        }
    }
    return 0;
}