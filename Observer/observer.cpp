#include <iostream>
#include <set>

using std::cout;
using std::set;

class IListener {
public:
    virtual void update() = 0;
    virtual ~IListener() = default;
};

class IPublisher {
public:
    virtual void subscribe(IListener* listener) = 0;
    virtual void unsubscribe(IListener* listener) = 0;
    virtual void notifyAll() = 0;
    virtual ~IPublisher() = default;
};

class FirstListener : public IListener {
public:
    FirstListener(IPublisher* publisher)
        : publisher_(publisher) {
        publisher_->subscribe(this);
    }

    void update() override {
        cout << "FirstListener: Opa! I have been notified\n";
        // do some work
    }

    void unsubscribe() {
        publisher_->unsubscribe(this);
    }

private:
    IPublisher* publisher_ = nullptr;
};

class SecondListener : public IListener {
public:
    SecondListener(IPublisher* publisher)
        : publisher_(publisher) {
        publisher_->subscribe(this);
    }

    void update() override {
        cout << "SecondListener: Opa! I have been notified too\n";
        // do some work
    }

    void unsubscribe() {
        publisher_->unsubscribe(this);
    }

private:
    IPublisher* publisher_ = nullptr;
};

class Publisher : public IPublisher{
public:
    void subscribe(IListener* listener) override {
        listeners_.insert(listener);
    }

    void unsubscribe(IListener* listener) override {
        listeners_.erase(listener);
    }

    void notifyAll() override {
        for (auto* it : listeners_) {
            it->update();
        }
    }

private:
    set<IListener*> listeners_;
};

int main() {

    Publisher publisher;

    FirstListener firstListener(&publisher);
    SecondListener secondListener(&publisher);

    publisher.notifyAll();

    secondListener.unsubscribe();
    cout << "\nsecond listener was unsubscribed\n\n";

    publisher.notifyAll();

    return 0;
}