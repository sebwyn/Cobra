#include "Object.h"

std::string to_string(ObjectType t){
    switch(t){
        case(BOOLEAN): return "BOOL";
        case(FLOAT): return "FLOAT";
        case(NIL): return "NIL";
    }
}
