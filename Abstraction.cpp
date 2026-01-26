#include <iostream>     // cin, std::cout
#include <string>       // std::string
#include <vector>       // vector

// using namespace std;       // Pretend everything inside std is also in the current scope. expanded the search space.
// std:: contains: string, vector, count, distance, begin, end

// Avoid `using namespace std;`
// Reason:
// If std is imported blindly, names like `count`, `distance`, `begin`, `end`
// from the STL enter the global namespace.
//
// Example problem:
// int count = 0;                          // local variable
// std::unordered_map<int, std::string> m;
// m.count(1);                             // std::unordered_map::count
//
// With `using namespace std;`, `count` refers to:
// 1) local variable `count`
// 2) std::count (algorithm)
//
// This can lead to ambiguity errors or, worse, unintended function resolution.
// Using explicit `std::` keeps intent clear and prevents name collisions.


// No `using namespace std;`
// Prevents name collisions with common identifiers like `count`, `distance`, etc.
// Makes symbol resolution explicit and avoids ambiguous or unintended behavior.


// int count = 0;
// std::unordered_map<int, std::string> m;
// m.count(1);   // unambiguous: member function, not std::count


// OR

// using std::string;
// using std::vector;
// using std::cout;
// using std::endl;

enum class FuelType{
    PETROL,     //0
    DIESEL,     //1
    ELECTRIC,   //2
    CNG         //3
}; 

class Car{
    public:                       //I know what needs to happen, not how.
    // Every car must have this function
    // But Car itself does not know how to start
    // Someone else must define it

    virtual void startEngine()=0;
    virtual void accelerate(int speed)=0;
    virtual void brake()=0;
    virtual void stopEngine()=0;
    virtual void honk(){                         /// can be used as it is then do't redeclare inside child classes
        std::cout<<"Beep \n";
    }
    virtual void wheel() final{                  // not meant to be overridden at all, closes the extension point completely.
        std::cout<<"Circular wheel\n";
    }                                            // void wheel() override;   // ❌ compile-time error
    virtual ~Car()=default;                             // discructor is virtual to avoid memory leak
};

class ManualTransmission{
    public:

    virtual void shiftGear(int gear)=0;
    virtual ~ManualTransmission(){}

};

class OffRoadCar: public Car, public ManualTransmission{   // OffRoadCar is a real car and follows all Car rules.

private:
    std::string brand;
    std::string model;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;

    //Now the compiler checks:
                                // Compiler = strict teacher.
    // Did you implement every function Car demanded?
    // If yes → allowed
    // If no → compilation fails
public:

    // OffRoadCar(std::string b, std::string m){       // Like preparing a parked car.
    //     // First: empty std::string is created
    //     // Then: value is assigned
    //     this->brand = b;        // assignment       is default-constructed
    //     this->model = m;        // assignment       model is default-constructed
    //     isEngineOn = false;     // assignment       isEngineOn is uninitialized
    //     currentSpeed = 0;       // assignment       currentSpeed is uninitialized
    //     currentGear = 0;        // assignment       currentGear is uninitialized
    // }

    // VS

    OffRoadCar(std::string b, std::string m) : brand(b), model(m), isEngineOn(false), currentSpeed(0), currentGear(0){}
    // brand is constructed directly with b
    // model is constructed directly with m               No default construction.
    // isEngineOn is constructed as false                 No reassignment.
    // currentSpeed is constructed as 0                   No wasted work.
    // currentGear is constructed as 0


    // override:  //This function must override a virtual function from the base class. 
    // Any function that overrides a virtual base function must be marked override.
    // If it doesn’t, fail the build. compile-time contract, not syntax sugar.
    // Overriding without override is legal in C++, but unsafe. The override keyword turns a runtime polymorphism risk into a compile-time guarantee.

    // Am I changing base behavior?
    // Yes → mark override
    // No → don’t write the function at all
    // Did I write a function that I think overrides something?
    // Always add override
   
    void startEngine() override{   
        isEngineOn = true;
        std::cout<<brand <<" "<<model<<" : Engine starts with wrooom wrooom wrooom!!"<<std::endl;
    }

    void shiftGear(int gear) override{
        if(!isEngineOn){
            std::cout<<brand <<" "<<model<<" : Engine is not started. Please start the engine first."<<std::endl;
            return;
        }
        if(gear<0 || gear>5){
            std::cout<<brand <<" "<<model<<" : Invalid gear. Please select a gear between 0 and 5."<<std::endl;
            return;
        }
        currentGear = gear;
        std::cout<<brand <<" "<<model<<" : Shifted to gear "<<gear<<std::endl;
    }

    void accelerate(int speed) override{
        if(!isEngineOn){
            std::cout<<brand <<" "<<model<<" : Engine is not started. Please start the engine first."<<std::endl;
            return;
        }
        if(currentGear==0){
            std::cout<<brand <<" "<<model<<" : Car is in neutral gear. Please shift to a higher gear first."<<std::endl;
            return;
        }
        currentSpeed += speed;
        std::cout<<brand <<" "<<model<<" : Accelerated to "<<currentSpeed<<" km/h."<<std::endl;
    }

    void brake() override{
        if(!isEngineOn){
            std::cout<<brand <<" "<<model<<" : Engine is not started. Please start the engine first."<<std::endl;
            return;
        }
        if(currentSpeed==0){
            std::cout<<brand <<" "<<model<<" : Car is already stopped. Please start the engine first."<<std::endl;
            return;
        }
        if(currentSpeed < 10){
            currentSpeed = 0;
            std::cout<<brand <<" "<<model<<" : Car "<<model<<" is stopped."<<std::endl;
            return;
        }
        currentSpeed -= 10;
        std::cout<<brand <<" "<<model<<" : Braked to "<<currentSpeed<<" km/h."<<std::endl;
    }

    void stopEngine() override{
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
        std::cout<<"Engine Stopped\n";
    }
};

class ElectricCars : public Car{
    private: 
    std::string brand;
    std::string model;
    std::vector<FuelType> fuelTypes;
    bool isOn;
    int speed;

    public: 
    ElectricCars(std::string b, std::string m, std::vector<FuelType>fuels) : brand(b), model(m), fuelTypes(fuels), isOn(false), speed(0){}

    void startEngine() override{
        isOn = true;
        std::cout<<brand<<" "<<model<<" started using my electric car!";
        printFuelTypes();
    }

    void accelerate(int s) override{
        if(!isOn) return;
        speed += s;
        std::cout<<"Speed: "<< speed<< "km/h"<<std::endl;
    }

    void brake() override{
        speed -=10;
        if(speed<0) speed = 0;
        std::cout<<"Braking... Speed: "<< speed<<std::endl;
    }

    void stopEngine() override{
        isOn = false;
        speed = 0;
        std::cout<<"Power off"<<std::endl;
    }

private: 
    void printFuelTypes(){
        for(FuelType f: fuelTypes){
            std::cout<<fuelToString(f)<<" ";
        }
        std::cout<<std::endl;
    }

    std::string fuelToString(FuelType fuel){
        switch(fuel){
            case FuelType::PETROL : return "Petrol";
            case FuelType::DIESEL : return "Diesel";
            case FuelType::ELECTRIC : return "Electric";
            case FuelType::CNG : return "CNG";
        }
        return "";
    }
};

int main(){
    Car *Land_Cruiser = new OffRoadCar("Toyota", "Land Cruiser");   // Because Land_Cruiser is a Car* but points to an OffRoadCar.
    Land_Cruiser->startEngine();
    ManualTransmission* mt = dynamic_cast<ManualTransmission*>(Land_Cruiser);
    mt->shiftGear(1);
    Land_Cruiser->accelerate(50);
    Land_Cruiser->brake();
    Land_Cruiser->stopEngine();
    delete Land_Cruiser;                     //non-negotiable in interviews.

    Car *BE_6E = new ElectricCars("Mahindra", "BE 6E", {FuelType::PETROL, FuelType::ELECTRIC});
    BE_6E->startEngine();
    BE_6E->accelerate(80);
    BE_6E->brake();
    BE_6E->stopEngine();
    delete BE_6E;                    //non-negotiable in interviews.
    return 0;

}