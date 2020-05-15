#include "Object.h"

template<> 
Object::Internal::Type Object::InternalType<float>::type = FLOAT;
template<> 
std::string Object::InternalType<float>::type_string = "FLOAT";
template<> 
Object::Internal::Type Object::InternalType<bool>::type = BOOL;
template<> 
std::string Object::InternalType<bool>::type_string = "BOOL";

template<>
std::string Object::InternalType<bool>::string(){
    if(value) return "true";
    else return "false";
}
 

template<>
std::string Object::InternalType<float>::string(){
    return std::to_string(value);
}
