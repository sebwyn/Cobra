#pragma once

#include "Cobra.h"

enum ObjectType {
    BOOLEAN,
    FLOAT,
    NIL 
};

std::string to_string(ObjectType t);

class Object {
public:
    ObjectType type = NIL;
    
    Object(ObjectType type) : type(type) {}

    virtual std::string string(){ return "NIL"; }
};

class FloatObject : public Object {
public:
    FloatObject(float value) 
    : Object(FLOAT), value(value) {}    

    float get(){ return value; }

    virtual std::string string() override { 
        return "FLOAT " + std::to_string(value); 
    }
private:
    float value;
};

class BoolObject : public Object {
public:
    BoolObject(bool value) 
    : Object(BOOLEAN), value(value) {}

    bool get(){ return value; }

    virtual std::string string() override {
        if(value) return "true";
        return "false";
    }
private: 
    bool value;
};
