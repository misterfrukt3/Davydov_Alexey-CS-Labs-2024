#include <iostream>
namespace {
const int kTestCaseOne = 1;
const int kTestCaseFive = 5;
const int kTestCaseTen = 10;
const int kTestCaseEleven = 11;
const int kTestCaseTwelve = 12;
const int kTestCaseTwenty = 20;

const int kMorningStart = 5;
const int kHalfADay = 12;
const int kEveningStart = 18;
const int kEveningEnd = 23;

const int kTenForRest = 10;
const int kTwelveForRest = 12;

const int kMaxHour = 23;
const int kMaxMinute = 59;
}

int main() {
    int hoursEuropeanFormate = 0;
    int hoursEnglishFormate = 0;
    int enterMinute = 0;
    std::cout << "Введите время: \n";
    std::cin >> hoursEuropeanFormate >> enterMinute;

    if (hoursEuropeanFormate < 0 || hoursEuropeanFormate > kMaxHour || enterMinute < 0 || enterMinute > kMaxMinute) {
        std::cout << "Введены недопустимые данные\n";
        return -1;
    }
    if (hoursEuropeanFormate == kHalfADay && enterMinute == 0) {
        std::cout << "Полдень\n";
        return 0;
    }
    if (hoursEuropeanFormate == 0 && enterMinute == 0) {
        std::cout << "Полночь\n";
        return 0;
    }

    hoursEnglishFormate = hoursEuropeanFormate % kTwelveForRest;
    if (hoursEuropeanFormate < kTestCaseFive && hoursEuropeanFormate > 0) {
        std::cout << hoursEnglishFormate << " ";
    } else {
        if (hoursEuropeanFormate == kHalfADay) {
            hoursEnglishFormate = kHalfADay;
            std::cout << hoursEnglishFormate << " ";
        } else {
            std::cout << hoursEnglishFormate << " ";
        }
    }

    if (hoursEnglishFormate == kTestCaseOne) {
        std::cout << "час ";
    } else if (kTestCaseOne < hoursEnglishFormate && hoursEnglishFormate < kTestCaseFive) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }

    if (enterMinute != 0) {
        std::cout << enterMinute;
        if (enterMinute % kTestCaseTen == kTestCaseOne && enterMinute != kTestCaseEleven) {
            std::cout << " минута ";
        } else if (kTestCaseOne < enterMinute % kTenForRest && enterMinute % kTenForRest < kTestCaseFive &&
                   (kTestCaseTen > enterMinute || enterMinute > kTestCaseTwenty)) {
            std::cout << " минуты ";
        } else {
            std::cout << " минут ";
        }

        if (kMorningStart <= hoursEuropeanFormate && hoursEuropeanFormate < kHalfADay) {
            std::cout << "утра \n";
            return 0;
        } else if (kHalfADay <= hoursEuropeanFormate && hoursEuropeanFormate < kEveningStart) {
            std::cout << "дня \n";
            return 0;
        } else if (kEveningStart <= hoursEuropeanFormate && hoursEuropeanFormate <= kMaxHour) {
            std::cout << "вечера \n";
            return 0;
        }
        std::cout << "ночи \n";
        return 0;

    } else {
        if (kMorningStart <= hoursEuropeanFormate && hoursEuropeanFormate < kHalfADay) {
            std::cout << "утра ровно \n";
            return 0;
        } else if (kHalfADay <= hoursEuropeanFormate && hoursEuropeanFormate < kEveningStart) {
            std::cout << "дня ровно \n";
            return 0;
        } else if (kEveningStart <= hoursEuropeanFormate && hoursEuropeanFormate <= kMaxHour) {
            std::cout << "вечера ровно \n";
            return 0;
        }
        std::cout << "ночи ровно \n";
        return 0;
    }
}
