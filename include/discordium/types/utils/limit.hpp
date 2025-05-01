#pragma once
#include <stdexcept>
#include <algorithm>

template <typename T>
class Limit {
private:
    T min;
    T max;

public:
    T value;

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

    operator T() const {
        return value;
    }

    T getValue() const {
        return value;
    }

    void clamp() {
        value = std::clamp(value, min, max);
    }

    T getMin() const {
        return min;
    }

    T getMax() const {
        return max;
    }

    Limit& operator=(T newValue) {
        setValue(newValue);
        return *this;
    }
};