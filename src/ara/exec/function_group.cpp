#include "function_group.h"


using namespace ara::exec;

FunctionGroup::CtorToken  FunctionGroup::Preconstruct(std::string metaModelIdentifier) noexcept
{
    // parse this FG 
    return "";

}


FunctionGroup::FunctionGroup(FunctionGroup::CtorToken &&token) noexcept{
    // parse this FG 
    this->Function_group_name = token;
}


FunctionGroup::~FunctionGroup() noexcept{

}

bool FunctionGroup::operator==(FunctionGroup const &other) const noexcept{
    if(this->Function_group_name == other.Function_group_name){
        return true;
    }
    return false;
}

bool FunctionGroup::operator!=(FunctionGroup const &other) const noexcept{
    if(this->Function_group_name == other.Function_group_name){
        return false;
    }
    return true;
}