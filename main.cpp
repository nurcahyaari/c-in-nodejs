#include <nan.h>
#include <iostream>
#include<vector>

// NAN_METHOD is a Nan macro enabling convenient way of creating native node functions.
// It takes a method's name as a param. By C++ convention, I used the Capital cased name.
NAN_METHOD(Hello) {
    // Create an instance of V8's String type
    auto message = Nan::New("Hello from C++!").ToLocalChecked();
    // 'info' is a macro's "implicit" parameter - it's a bridge object between C++ and JavaScript runtimes
    // You would use info to both extract the parameters passed to a function as well as set the return value.
    info.GetReturnValue().Set(message);
}

int P(int n, int p){
    static int i = 1;
    if(i == p) return n;
    else return n * P(n, p - 1);
}

bool isPrime(int number){
    for (int a = 2; a < number; a++) {
        if (number % a == 0) {
            return false;
        }
    }
    return true;
}


NAN_METHOD(Prime){
    if(!info[0]->IsNumber()){
        Nan::ThrowTypeError("argument must be a number!");
        return;
    }
    std::vector<int> v;
    int maxPrimeToGenerate = (int)info[0]->NumberValue();
    std::cout<<maxPrimeToGenerate<<std::endl;
    for(int startPrime = 0; startPrime < maxPrimeToGenerate; startPrime++){
        if(isPrime(startPrime)){
            std::cout<<startPrime<<std::endl;
        }
    }
    auto message = Nan::New("Success to generate Prime number").ToLocalChecked();
    info.GetReturnValue().Set(message);
}

NAN_METHOD(Pangkat) {
    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("argument must be a number!");
        return;
    }
    std::cout << info[0]->NumberValue() << std::endl;
    int number = (int) info[0]->NumberValue();
    
    int h = P(number, 2);
    
    auto message = Nan::New(h);
    info.GetReturnValue().Set(message);
}

// Module initialization logic
NAN_MODULE_INIT(Initialize) {
    // Export the `Hello` function (equivalent to `export function Hello (...)` in JS)
    NAN_EXPORT(target, Hello);
    NAN_EXPORT(target, Pangkat);
    NAN_EXPORT(target, Prime);
}

// Create the module called "addon" and initialize it with `Initialize` function (created with NAN_MODULE_INIT macro)
NODE_MODULE(addon, Initialize);