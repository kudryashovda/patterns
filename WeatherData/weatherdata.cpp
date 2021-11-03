#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::set;
using std::vector;

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;

    [[nodiscard]] virtual float getTemperature() const = 0;
    [[nodiscard]] virtual float getHumidity() const = 0;
    [[nodiscard]] virtual float getPressure() const = 0;
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

    void update() override {
        temperature_ = weatherData_->getTemperature();
        humidity_ = weatherData_->getHumidity();
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
        cout << "Avg/Max/Min: " << average_temp_ << '/' << max_temp_ << '/' << min_temp_ << '\n';
    }

    void update() override {
        float temperature_ = weatherData_->getTemperature();

        temps_.push_back(temperature_);
        if (temperature_ > max_temp_) {
            max_temp_ = temperature_;
        }

        if (temperature_ < min_temp_) {
            min_temp_ = temperature_;
        }
        float sum_temp = 0.0;
        for (float temp : temps_) {
            sum_temp += temp;
        }
        if (!temps_.empty()) {
            average_temp_ = sum_temp / temps_.size();
        }

        display();
    }

private:
    Subject* weatherData_;

    float min_temp_ = 273;
    float max_temp_ = -273;
    float average_temp_ = 0.0;
    vector<float> temps_;
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

    void update() override {
        pressures_.push_back(weatherData_->getPressure());
        display();
    }

private:
    Subject* weatherData_;
    vector<float> pressures_;
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
            observer->update();
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

    [[nodiscard]] float getTemperature() const override {
        return temperature_;
    }

    [[nodiscard]] float getHumidity() const override {
        return humidity_;
    }

    [[nodiscard]] float getPressure() const override {
        return pressure_;
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
    weatherData.setMeasurements(82, 70, 30.4);
    weatherData.setMeasurements(81, 78, 30.4);

    return 0;
}