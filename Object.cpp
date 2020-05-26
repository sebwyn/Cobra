#include "Object.h"

#include "Function.h"

template<> 
Object::Internal::Type Object::InternalType<float>::type = FLOAT;
template<> 
std::string Object::InternalType<float>::type_string = "FLOAT";

template<> 
Object::Internal::Type Object::InternalType<bool>::type = BOOL;
template<> 
std::string Object::InternalType<bool>::type_string = "BOOL";

template<>
Object::Internal::Type Object::InternalType<Function>::type = FUNCTION;
template<>
std::string Object::InternalType<Function>::type_string = "FUNCTION";

template<>
std::string Object::InternalType<bool>::string(){
    if(value) return "true";
    else return "false";
}
 

template<>
std::string Object::InternalType<float>::string(){
    return std::to_string(value);
}


void Object::copyValue(const Object& other){
    switch(other.value->getType()){
        case Internal::BOOL: {
            bool v;
            other.get(v);
            value = new InternalType<bool>(v);
            break;
        }
        case Internal::FLOAT: {
            float v;
            other.get(v);
            value = new InternalType<float>(v);
            break; 
        }
        case Internal::FUNCTION: {    
        	Function v;
            other.get(v);
            value = new InternalType<Function>(v);
            break;
        }	
        case Internal::NIL: {
            value = new Internal();
            break;
        }	
    }
    //std::cout << "Copying object at " << other.value << " with type: " << 
    //        other.value->getTypeString() << " into " << value << std::endl;
}	
