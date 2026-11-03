#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



struct Measurement {
    std::string locationID;
    int sensorNumber;
    int value;

    Measurement(std::string id, int sensor, int val) : locationID(id), sensorNumber(sensor), value(val) {}
};

bool compareMeasurements(const Measurement& m1, const Measurement& m2) {
    if (m1.locationID == m2.locationID) {
        if (m1.sensorNumber == m2.sensorNumber) {
            return m1.value > m2.value;
        }
        return m1.sensorNumber < m2.sensorNumber;
    }
    return m1.locationID < m2.locationID;
}

void quickSort(std::vector<Measurement>& measurements, int low, int high) {
    if (low < high) {
        Measurement pivot = measurements[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (compareMeasurements(measurements[j], pivot)) {
                i++;
                std::swap(measurements[i], measurements[j]);
            }
        }
        std::swap(measurements[i + 1], measurements[high]);

        int pi = i + 1;
        quickSort(measurements, low, pi - 1);
        quickSort(measurements, pi + 1, high);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    std::vector<Measurement> measurements;
    measurements.reserve(n);

    for (int i = 0; i < n; ++i) {
        std::string id;
        int sensor, value;
        std::cin >> id >> sensor >> value;
        measurements.emplace_back(id, sensor, value);
    }

    quickSort(measurements, 0, static_cast<int>(measurements.size()) - 1);

    long long result = 0;
    for (int i = 0; i < measurements.size(); ++i) {
        result += static_cast<long long>(measurements[i].value) * i;
    }

    std::cout << result << "\n";

    return 0;
}
