#pragma once

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <algorithm>

template <typename T>
class Limit {
private:
    T value;
    T min;
    T max;

public:
    Limit(T minValue, T maxValue, T defaultValue)
        : min(minValue), max(maxValue), value(defaultValue) {
        if (value < min || value > max) {
            throw std::out_of_range("Initial value is out of bounds");
        }
    }

    void setValue(T newValue) {
        if (newValue < min || newValue > max) {
            throw std::out_of_range("Value out of bounds");
        }
        value = newValue;
    }

    T getValue() const { return value; }

    operator T() const { return value; }
};

class Duration {
public:
    int days;
    int hours;
    int minutes;
    int seconds;

    Duration(int d = 0, int h = 0, int m = 0, int s = 0)
        : days(d), hours(h), minutes(m), seconds(s) {}

    void applyToTimestamp(Timestamp& ts, bool add = true) const;

    Timestamp operator+(const Timestamp& ts) const;
    Timestamp operator-(const Timestamp& ts) const;
};

struct Timestamp {
    Limit<int> year;
    Limit<int> month;
    Limit<int> day;
    Limit<int> hour;
    Limit<int> minute;
    Limit<int> second;

    Timestamp(const std::string& iso8601)
        : year(1900, 9999, 1970),
          month(1, 12, 1),
          day(1, 31, 1),
          hour(0, 23, 0),
          minute(0, 59, 0),
          second(0, 59, 0) {
        parseISO8601(iso8601);
    }

    void parseISO8601(const std::string& iso8601) {
        std::istringstream ss(iso8601);
        char separator;

        if (!(ss >> year >> separator >> month >> separator >> day >> separator >> hour >> separator >> minute >> separator >> second)) {
            throw std::invalid_argument("Invalid ISO 8601 timestamp format.");
        }

        validateDate();
    }

    void validateDate() {
        int d = day.getValue();
        int m = month.getValue();
        int y = year.getValue();
        int daysInMonth = 31;

        if (m == 2) {
            daysInMonth = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 29 : 28;
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            daysInMonth = 30;
        }

        day.setValue(std::min(d, daysInMonth));
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << std::setw(4) << std::setfill('0') << year
            << "-" << std::setw(2) << std::setfill('0') << month
            << "-" << std::setw(2) << std::setfill('0') << day
            << "T" << std::setw(2) << std::setfill('0') << hour
            << ":" << std::setw(2) << std::setfill('0') << minute
            << ":" << std::setw(2) << std::setfill('0') << second;
        return oss.str();
    }

    operator std::string() const { return toString(); }

    Timestamp operator+(const Duration& duration) const;
    Timestamp operator-(const Duration& duration) const;
};

namespace TimeUtils {

    Timestamp addSeconds(const Timestamp& ts, int seconds);
    
    int toSeconds(const Duration& duration);

    Duration parseDuration(const std::string& durationString);
    
    Timestamp getCurrentTime();
}