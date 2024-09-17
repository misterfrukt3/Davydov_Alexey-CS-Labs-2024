#include <iostream>

namespace {
const int kMorningStart = 5;
const int kHalfADay = 12;
const int kEveningStart = 18;
const int kEveningEnd = 23;

const int kMinHour = 0;
const int kMaxHour = 23;

const int kMinMinute = 0;
const int kMaxMinute = 59;

const int kHourNominativeSingular = 1;
const int kHourGenitiveSingularLeftBoundary = 1;
const int kHourGenitiveSingularRightBoundary = 5;

const int kMinuteNominativeSingular = 1;
const int kMinuteGenetivePluralStart = 11;
const int kMinuteGenetivePluralEnd = 20;
const int kMinuteNominativePluralLeftBoundary = 1;
const int kMinuteNominativePluralRightBoundary = 5;


const int kBaseDecimal = 10;
const int kBaseHoursEnglishFormat = 12;
}  // namespace

int main() {
    int hoursEuropeanFormat = 0;
    int minutes = 0;
    std::cout << "Введите часы (0<=x<=23) и минуты (0<=y<=59) через пробел: \n";
    std::cin >> hoursEuropeanFormat >> minutes;

    if (hoursEuropeanFormat < kMinHour || hoursEuropeanFormat > kMaxHour || minutes < kMinMinute || minutes > kMaxMinute) {
        std::cout << "Введены недопустимые данные\n";
        return -1;
    }

    if (hoursEuropeanFormat == kHalfADay && minutes == kMinMinute) {
        std::cout << "Полдень\n";
        return 0;
    }
    if (hoursEuropeanFormat == kMinHour && minutes == kMinMinute) {
        std::cout << "Полночь\n";
        return 0;
    }

    int hoursEnglishFormat = hoursEuropeanFormat % kBaseHoursEnglishFormat;
    if (hoursEuropeanFormat == kHalfADay) {
        std::cout << kHalfADay << " ";
    } else {
        std::cout << hoursEnglishFormat << " ";
    }

    if (hoursEnglishFormat == kHourNominativeSingular) {
        std::cout << "час ";
    } else if (hoursEnglishFormat > kHourGenitiveSingularLeftBoundary && hoursEnglishFormat < kHourGenitiveSingularRightBoundary) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }

    if (minutes != kMinMinute) {
        std::cout << minutes;
        if (minutes % kBaseDecimal == kMinuteNominativeSingular && minutes != kMinuteGenetivePluralStart) {
            std::cout << " минута ";
        } else if (minutes % kBaseDecimal > kMinuteNominativePluralLeftBoundary && minutes % kBaseDecimal < kMinuteNominativePluralRightBoundary &&
                   !(minutes > kMinuteGenetivePluralStart && minutes < kMinuteGenetivePluralEnd)) {
            std::cout << " минуты ";
        } else {
            std::cout << " минут ";
        }
    }

    if (hoursEuropeanFormat >= kMorningStart && hoursEuropeanFormat < kHalfADay) {
        std::cout << "утра ";
    } else if (hoursEuropeanFormat >= kHalfADay && hoursEuropeanFormat < kEveningStart) {
        std::cout << "дня ";
    } else if (hoursEuropeanFormat >= kEveningStart && hoursEuropeanFormat <= kMaxHour) {
        std::cout << "вечера ";
    } else {
        std::cout << "ночи ";
    }

    if (minutes == kMinMinute) {
        std::cout << "ровно";
    }

    std::cout << '\n';
    return 0;
}
