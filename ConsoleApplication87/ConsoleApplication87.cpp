#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Wallet {
    double balance;
public:
    Wallet(double b) {
        balance = b;
    }
    double Balance() {
        return balance;
    }
    void deposit(double amount) {
        balance += amount;
    }
    bool vivod(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        else {
            return false;
        }
    }
};

class Card {
    double balance;
public:
    Card(double b) {
        balance = b;
    }
    double Balance() {
        return balance;
    }
    void deposit(double amount) {
        balance += amount;
    }
    bool vivod(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        else {
            return false;
        }
    }
};

class Schet {
    double amount;
    string category;
    string date;
public:
    Schet(double a, string c, string d) {
        amount = a;
        category = c;
        date = d;
    }
    double Amount() {
        return amount;
    }
    string Category() {
        return category;
    }
    string Date() {
        return date;
    }
};

class Report {
    vector<Schet> Schets;
public:
    void addSchet(Schet Schet) {
        Schets.push_back(Schet);
    }
    vector<Schet> getSchetsByDay(string date) {
        vector<Schet> daySchet;
        for (int i = 0; i < Schets.size(); i++) {
            if (Schets[i].Date() == date) {
                daySchet.push_back(Schets[i]);
            }
        }
        return daySchet;
    }
    vector<Schet> getSchetsByWeek(string date) {
        vector<Schet> weekSchet;
        return weekSchet;
    }
    vector<Schet> getSchetsByMonth(string date) {
        vector<Schet> monthSchet;
        return monthSchet;
    }
};

class Rating {
    map<string, double> categorySchets;
    map<string, double> weekSchet;
    map<string, double> monthSchet;
public:
    void addSchet(Schet Schet) {
        string category = Schet.Category();
        double amount = Schet.Amount();
        string date = Schet.Date();
        categorySchets[category] += amount;
    }
    vector<pair<string, double>> getTop3SchetsByWeek() {
        vector<pair<string, double>> top3Schets;
        return top3Schets;
    }
    vector<pair<string, double>> getTop3SchetsByMonth() {
        vector<pair<string, double>> top3Schets;
        return top3Schets;
    }
    vector<pair<string, double>> getTop3CategoriesByWeek() {
        vector<pair<string, double>> top3Categories;
        return top3Categories;
    }
    vector<pair<string, double>> getTop3CategoriesByMonth() {
        vector<pair<string, double>> top3Categories;
            for (auto const& entry : monthSchet) {
            top3Categories.push_back(make_pair(entry.first, entry.second));
            }
            sort(top3Categories.begin(), top3Categories.end(), [](pair<string, double>& a, pair<string, double>& b) {
                return a.second > b.second;
                });
            if (top3Categories.size() > 3) {
                top3Categories.resize(3);
            }
            return top3Categories;
        }
};
    int main() {
        Wallet wallet(1000.0);
        Card card(2000.0);
        Report report;
        Rating rating;

        wallet.deposit(500.0);
        card.deposit(1000.0);

        if (wallet.vivod(200.0)) {
            Schet Schet(200.0, "Food", "2023-04-15");
            report.addSchet(Schet);
            rating.addSchet(Schet);
        }

        if (card.vivod(100.0)) {
            Schet Schet(100.0, "Shopping", "2023-04-15");
            report.addSchet(Schet);
            rating.addSchet(Schet);
        }

        vector<Schet> daySchet = report.getSchetsByDay("2023-04-15");
        cout << "Schets for 2023-04-15:" << endl;
        for (int i = 0; i < daySchet.size(); i++) {
            cout << daySchet[i].Category() << " - " << daySchet[i].Amount() << endl;
        }

        vector<pair<string, double>> top3CategoriesByMonth = rating.getTop3CategoriesByMonth();
        cout << "Top 3 categories for the month:" << endl;
        for (int i = 0; i < top3CategoriesByMonth.size(); i++) {
            cout << top3CategoriesByMonth[i].first << " - " << top3CategoriesByMonth[i].second << endl;
        }

        return 0;
    }
