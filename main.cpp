#include <iostream>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }

    int operator-(const Date& other) const {
        int total_days = calculateTotalDays(*this) - calculateTotalDays(other);
        return total_days;
    }

    Date operator+(int days) const {
        Date result = *this;

        for (int i = 0; i < days; ++i) {
            result.day++;
            if (result.day > getDaysInMonth(result.month, result.year)) {
                result.day = 1;
                result.month++;
                if (result.month > 12) {
                    result.month = 1;
                    result.year++;
                }
            }
        }

        return result;
    }

private:
    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int getDaysInMonth(int m, int y) const {
        int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (isLeapYear(y) && m == 2) {
            return 29; // If it's a leap year and February, return 29 days
        }
        return days_in_month[m];
    }

    int calculateTotalDays(const Date& date) const {
        const int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int total_days = date.year * 365 + date.day;

        for (int i = 1; i < date.month; ++i) {
            total_days += days_in_month[i];
        }

        total_days += countLeapYears(date);

        return total_days;
    }

    int countLeapYears(const Date& date) const {
        int years = date.year;

        if (date.month <= 2) {
            years--;
        }

        return years / 4 - years / 100 + years / 400;
    }
};

int main() {
    int day1, month1, year1;
    int day2, month2, year2;

    std::cout << "Enter the first date (day month year): ";
    std::cin >> day1 >> month1 >> year1;

    std::cout << "Enter the second date (day month year): ";
    std::cin >> day2 >> month2 >> year2;

    Date date1(day1, month1, year1);
    Date date2(day2, month2, year2);

    int difference = date2 - date1;
    std::cout << "Difference between dates: " << difference << " days\n";

    int days_to_add;
    std::cout << "Enter the number of days to add to the first date: ";
    std::cin >> days_to_add;

    Date new_date = date1 + days_to_add;
    std::cout << "New date after adding " << days_to_add << " days: "
              << new_date.getDay() << "/" << new_date.getMonth() << "/" << new_date.getYear() << std::endl;

    return 0;
}
