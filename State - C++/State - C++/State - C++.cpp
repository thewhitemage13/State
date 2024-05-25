#include <iostream>
#include <string>
using namespace std;

class TrafficLight;

class State {
protected:
    TrafficLight* trafficLight;
public:
    virtual ~State() {};
    void SetTrafficLight(TrafficLight* tr) {
        trafficLight = tr;
    }
    virtual void NextState() = 0;
    virtual void PreviousState() = 0;
};

class TrafficLight {
private:
    State* state;
public:
    TrafficLight(State* st) : state(nullptr) {
        SetState(st);
    }
    void SetState(State* st) {
        if (state != nullptr) delete state;
        state = st;
        state->SetTrafficLight(this);
    }
    void NextState() {
        state->NextState();
    }
    void PreviousState() {
        state->PreviousState();
    }
};

class GreenState : public State {
public:
    void NextState() override;
    void PreviousState() override {
        cout << "Green color...\n";
    }
}; 

class YellowState : public State {
public:
    void NextState();
    void PreviousState() override {
        cout << "yellow to green...\n";
        trafficLight->SetState(new GreenState());
    }
};

void GreenState::NextState() {
    cout << "green to yellow...\n";
    trafficLight->SetState(new YellowState());
}

class RedState : public State {
public:
    void NextState() override {
        cout << "Red color\n";
    }
    void PreviousState() override {
        cout << "Red to Yellow\n";
        trafficLight->SetState(new YellowState());
    }
};

void YellowState::NextState() {
    cout << "Yellow to red\n";
    trafficLight->SetState(new RedState());
}

int main() {
    TrafficLight* traffic = new TrafficLight(new YellowState());
    traffic->NextState();
    traffic->NextState();
    traffic->PreviousState();
    traffic->PreviousState();
    traffic->PreviousState();
    delete traffic;
}