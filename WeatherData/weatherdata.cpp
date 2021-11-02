#include <iostream>

using std::cout;

class CurrentConditionsDisplay {
public:
    void update(float temp, float humidity, float pressure) {
        cout << "Current conditions" << '\n';
        cout << "Temperature: " << temp << '\n';
        cout << "Humidity: " << humidity << '\n';
        cout << "Pressure: " << pressure << '\n';
        cout << '\n';
    }
};

class StatisticsDisplay {
public:
    void update(float temp, float humidity, float pressure) {
        cout << "Statistics" << '\n';
        cout << temp << '\n';
        cout << humidity << '\n';
        cout << pressure << '\n';
        cout << '\n';
    }
};

class ForecastDisplay {
public:
    void update(float temp, float humidity, float pressure) {
        cout << "Forecast" << '\n';
        cout << "Tomorrow will be:" << '\n';
        cout << "Temperature: " << temp << '\n';
        cout << "Humidity: " << humidity << '\n';
        cout << "Pressure: " << pressure << '\n';
        cout << '\n';
    }
};

class WeatherData {
public:
    float getTemperature() {
        return 25.0;
    }
    float getHumidity() {
        return 80.0;
    }
    float getPressure() {
        return 770.0;
    }

    void measurementsChanged() {
        CurrentConditionsDisplay currentConditionsDisplay;
        StatisticsDisplay statisticsDisplay;
        ForecastDisplay forecastDisplay;

        float temp = getTemperature();
        float humidity = getHumidity();
        float pressure = getPressure();

        currentConditionsDisplay.update(temp, humidity, pressure);
        statisticsDisplay.update(temp, humidity, pressure);
        forecastDisplay.update(temp, humidity, pressure);
    }
};
int main() {
    WeatherData weatherData;
    weatherData.measurementsChanged();

    return 0;
}