#include "display.h"

class error {
public:
    virtual void show(display &str) = 0;
};

class no_library : public error {
public:
    virtual void show(display &str) {
        str << "Unable to load libraries";
    }
};

class no_proc : public error {
public:
    virtual void show(display &str) {
        str << "Unable to get procedure addresses";
    }

};
