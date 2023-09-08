#include <iostream>
#include <cassert>
#include <unistd.h>
using namespace std;

// Function to display an animated message
void animateMessage(const string& message) {
    for (int i = 0; i < 6; i++) {
        cout << "\r" << message << " " << flush;
        sleep(1);
        cout << "\r" << string(message.length(), ' ') << flush;
        sleep(1);
    }
}

// Pure function to check temperature
bool isTemperatureOk(float temperature) {
    return temperature >= 95 && temperature <= 102;
}

// Pure function to check pulse rate
bool isPulseRateOk(float pulseRate) {
    return pulseRate >= 60 && pulseRate <= 100;
}

// Pure function to check oxygen saturation
bool isSpo2Ok(float spo2) {
    return spo2 >= 90;
}

// Function to check and display vital status
bool checkAndDisplayVital(float value, const string& vitalName) {
    if (!value) {
        animateMessage(vitalName + " critical!");
        return false;
    }
    return true;
}

// Function to check overall vitals
bool vitalsOk(float temperature, float pulseRate, float spo2) {
    bool temperatureOk = isTemperatureOk(temperature);
    bool pulseRateOk = isPulseRateOk(pulseRate);
    bool spo2Ok = isSpo2Ok(spo2);

    return temperatureOk && pulseRateOk && spo2Ok;
}

int main() {
    assert(!vitalsOk(99, 102, 70));
    assert(vitalsOk(98.1, 70, 98));

    // Additional test cases
    assert(!checkAndDisplayVital(99, "Temperature"));
    assert(!checkAndDisplayVital(55, "Pulse Rate"));
    assert(!checkAndDisplayVital(85, "Oxygen Saturation"));
    assert(checkAndDisplayVital(98, "Temperature"));
    assert(checkAndDisplayVital(75, "Pulse Rate"));
    assert(checkAndDisplayVital(95, "Oxygen Saturation"));

    cout << "All tests passed. Done\n";
}
