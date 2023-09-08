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

// Function to check temperature
bool isTemperatureOk(float temperature) {
    if (temperature > 102 || temperature < 95) {
        animateMessage("Temperature critical!");
        return false;
    }
    return true;
}

// Function to check pulse rate
bool isPulseRateOk(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        animateMessage("Pulse Rate is out of range!");
        return false;
    }
    return true;
}

// Function to check oxygen saturation
bool isSpo2Ok(float spo2) {
    if (spo2 < 90) {
        animateMessage("Oxygen Saturation out of range!");
        return false;
    }
    return true;
}

// Function to check overall vitals
bool vitalsOk(float temperature, float pulseRate, float spo2) {
    return isTemperatureOk(temperature) && isPulseRateOk(pulseRate) && isSpo2Ok(spo2);
}

int main() {
    assert(!vitalsOk(99, 102, 70));
    assert(vitalsOk(98.1, 70, 98));
    cout << "Done\n";
}
