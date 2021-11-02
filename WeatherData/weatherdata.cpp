#include <iostream>
#include <set>

using std::cout;
using std::set;

class Observer {
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class DisplayElement {
public:
    virtual void display() = 0;
};

class CurrentConditionsDisplay : public Observer, DisplayElement {
public:
    CurrentConditionsDisplay(Subject* weatherData) {
        weatherData_ = weatherData;
        weatherData->registerObserver(this);
    }

    void display() override {
        cout << "Current conditions: " << temperature_ << " C degrees and " << humidity_ << "% humidity" << '\n';
    }

    void update(float temp, float humidity, float pressure) override {
        temperature_ = temp;
        humidity_ = humidity;
        (void)pressure;
        display();
    }

private:
    Subject* weatherData_;

    float temperature_ = 0.0;
    float humidity_ = 0.0;
};

class StatisticsDisplay : public Observer, DisplayElement {
public:
    StatisticsDisplay(Subject* weatherData) {
        weatherData_ = weatherData;
        weatherData->registerObserver(this);
    }

    void display() override {
        cout << "Statistics: " << temperature_ << " " << humidity_ << " " << pressure_ << '\n';
    }

    void update(float temp, float humidity, float pressure) override {
        temperature_ = temp;
        humidity_ = humidity;
        pressure_ = pressure;
        display();
    }

private:
    Subject* weatherData_;

    float temperature_ = 0.0;
    float humidity_ = 0.0;
    float pressure_ = 0.0;
};

class ForecastDisplay : public Observer, DisplayElement {
public:
    ForecastDisplay(Subject* weatherData) {
        weatherData_ = weatherData;
        weatherData->registerObserver(this);
    }

    void display() override {
        cout << "Tomorrow will be a good day (50%)" << '\n';
    }

    void update(float temp, float humidity, float pressure) override {
        (void)temp;
        (void)humidity;
        pressure_ = pressure;
        display();
    }

private:
    Subject* weatherData_;

    float pressure_ = 0.0;
};

class WeatherData : public Subject {
public:
    void registerObserver(Observer* observer) override {
        observers_.insert(observer);
    };
    void removeObserver(Observer* observer) override {
        observers_.erase(observer);
    }
    void notifyObservers() override {
        for (auto* observer : observers_) {
            observer->update(temperature_, humidity_, pressure_);
        }
    }

    void measurementsChanged() {
        notifyObservers();
    }

    void setMeasurements(float temp, float humidity, float pressure) {
        temperature_ = temp;
        humidity_ = humidity;
        pressure_ = pressure;

        measurementsChanged();
    }

private:
    set<Observer*> observers_;
    float temperature_ = 0.0;
    float humidity_ = 0.0;
    float pressure_ = 0.0;
};
int main() {
    WeatherData weatherData;

    CurrentConditionsDisplay currentConditionsDisplay(&weatherData);
    StatisticsDisplay statisticsDisplay(&weatherData);
    ForecastDisplay forecastDisplay(&weatherData);

    weatherData.setMeasurements(80, 65, 30.4);

    return 0;
}