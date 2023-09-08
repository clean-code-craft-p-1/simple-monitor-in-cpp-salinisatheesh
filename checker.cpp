#include <iostream>
#include <cassert>
#include <unistd.h>
#include <map>
using namespace std;

// Vitals boundary structure
struct VitalBoundary {
    float lowerCelsius;    // Lower boundary in Celsius
    float upperCelsius;    // Upper boundary in Celsius
    float lowerFahrenheit; // Lower boundary in Fahrenheit
    float upperFahrenheit; // Upper boundary in Fahrenheit
    string condition;      // Condition message
};

// Function to convert Celsius to Fahrenheit
float celsiusToFahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Vitals class to encapsulate vitals-related logic
class Vitals {
public:
    Vitals() {
        // Map vitals to their boundaries and conditions
        vitalsMap = {
            {"Temperature", {35.0, 39.0, celsiusToFahrenheit(95.0), celsiusToFahrenheit(102.0), "Normal"}},
            {"PulseRate", {60.0, 100.0, 60.0, 100.0, "Normal"}},
            {"Spo2", {90.0, 100.0, 90.0, 100.0, "Normal"}},
        };
    }

    // Function to get the condition based on a vital value
    string getCondition(float value, const string& vitalName, bool isCelsius) {
        if (vitalsMap.find(vitalName) != vitalsMap.end()) {
            const VitalBoundary& boundary = vitalsMap[vitalName];
            float lower = isCelsius ? boundary.lowerCelsius : boundary.lowerFahrenheit;
            float upper = isCelsius ? boundary.upperCelsius : boundary.upperFahrenheit;

            if (value < lower) {
                return "Below " + boundary.condition;
            } else if (value >= lower && value <= upper) {
                float upperWarning = upper + (upper * 0.015); // 1.5% tolerance
                if (value <= upperWarning) {
                    return boundary.condition;
                } else {
                    return "Warning: " + boundary.condition;
                }
            } else {
                return "Above " + boundary.condition;
            }
        }
        return "Unknown Vital";
    }

    // Function to check overall vitals
    bool areVitalsOk(float temperature, float pulseRate, float spo2, bool isCelsius) {
        string tempCondition = getCondition(temperature, "Temperature", isCelsius);
        string pulseCondition = getCondition(pulseRate, "PulseRate", false); // Pulse rate is always in BPM.
        string spo2Condition = getCondition(spo2, "Spo2", false);

        cout << "Temperature: " << temperature << " " << (isCelsius ? "Celsius" : "Fahrenheit") << " - " << tempCondition << endl;
        cout << "Pulse Rate: " << pulseRate << " BPM - " << pulseCondition << endl;
        cout << "Oxygen Saturation: " << spo2 << " % - " << spo2Condition << endl;

        // Check overall vitals based on conditions
        if (tempCondition == "Normal" && pulseCondition == "Normal" && spo2Condition == "Normal") {
            return true;
        } else if (tempCondition == "Warning: Normal" && pulseCondition == "Warning: Normal" && spo2Condition == "Warning: Normal") {
            // Handle warning conditions (all in warning)
            cout << "Warning: All vitals in warning state." << endl;
            return true;
        } else if (tempCondition.find("Below") != string::npos || pulseCondition.find("Below") != string::npos || spo2Condition.find("Below") != string::npos) {
            // Handle error conditions (at least one below normal)
            cout << "Error: At least one vital is below normal." << endl;
            return false;
        } else {
            // Handle other error conditions (not covered above)
            cout << "Error: Multiple vitals in abnormal state." << endl;
            return false;
        }
    }

private:
    map<string, VitalBoundary> vitalsMap;
};

int main() {
    Vitals vitals; // Create an instance of the Vitals class

    // All vitals within normal range
    assert(vitals.areVitalsOk(98.6, 75, 98, false));  // Normal temperature, pulse rate, and spo2

    // At least one vital in warning state
    assert(vitals.areVitalsOk(101.5, 98, 95, false));  // Warning: High temperature
    assert(vitals.areVitalsOk(98.6, 55, 98, false));   // Warning: Low pulse rate
    assert(vitals.areVitalsOk(98.6, 75, 88, false));   // Warning: Low spo2

    cout << "All tests passed. Done" << endl;
}

