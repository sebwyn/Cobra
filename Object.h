#pragma once

#include "Cobra.h"

class Object {
private:
    class Internal {
    public:
        enum Type {
            FLOAT,
            BOOL,
            FUNCTION,
            NIL
        };

        virtual ~Internal() {}
        
        virtual Type getType(){ return NIL; }
        virtual std::string getTypeString(){ return "NIL"; }
    
        virtual std::string string(){ return getTypeString(); }
    };

    template<typename T>
    class InternalType : public Internal {
    public:
        
    	InternalType(T value)
         : value(value) {}	
        
        virtual ~InternalType() override {}

	    T get(){ return value; }
        
        virtual Internal::Type getType() override { return type; }
        virtual std::string getTypeString() override { return type_string; }
       	
	    virtual std::string string() override { return getTypeString(); }
 
        static Type type;
        static std::string type_string;
    private:
        T value; 
    };    
    

public:
    
    Object(){
        value = new Internal();
        //std::cout << "Constructing empty object at " << value << std::endl; 
    }
 
    template<typename T>
    Object(T _value){
        value = new InternalType<T>(_value);
        //std::cout << "Constructing object of type " << value->getTypeString() <<                     " at address " << value << std::endl;
    }

    ~Object(){
        delValue();
    }
    
    Object(const Object& other){
        copyValue(other);
    }

    Object& operator=(const Object& other){
        delValue();
	    copyValue(other);
    }
    
    template<typename T>
    bool checkType() const {
        return value->getType() == InternalType<T>::type;
    }

    bool compareType(const Object& other){
        return other.value->getType() == value->getType();
    }
 
    template<typename T>
    bool get(T& out) const {
        if(checkType<T>()){
            auto casted_value = dynamic_cast<InternalType<T>*>(value);
            out = casted_value->get();
            return true;
        }
        return false; 
    }
   	
    std::string string(){
        return value->string();
    }    
 
    Internal* value = NULL;

private:
    void delValue(){
        //std::cout << "Attempting to delete " << value << std::endl;
        //std::cout << "Deleting object of type " << value->getTypeString() <<
        //             " at address " << value << std::endl;
        delete value;
    }

    void copyValue(const Object& other){
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
            case Internal::NIL: {
                value = new Internal();
            }	
        }
        //std::cout << "Copying object at " << other.value << " with type: " << 
        //         other.value->getTypeString() << " into " << value << std::endl;
    }	
};
