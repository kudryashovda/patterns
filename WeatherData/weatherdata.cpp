#include <iostream>

class WeatherData {
public:
    float getTemperature() {
        measurementsChanged();
        return 25.0;
    }
    float getHumidity() {
        measurementsChanged();
        return 80.0;
    }
    float getPressure() {
        measurementsChanged();
        return 770.0;
    }

    void measurementsChanged() {
        // here will be our code
    }
};
int main() {
    WeatherData weatherData;

    return 0;
}