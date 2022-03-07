/**
 * @file function_group_state.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "function_group_state.h"
#include <string>

using namespace ara::exec;
using namespace std;

FunctionGroupState::CtorToken FunctionGroupState::Preconstruct(FunctionGroup const &functionGroup, std::string metaModelIdentifier) noexcept
{
    return "";
}

FunctionGroupState::FunctionGroupState(FunctionGroupState::CtorToken &&token) noexcept
{
    int f = token.find('/');
    this->Function_group_name =  token.substr(0, f); 
    this->state = token.substr(f+1, token.length()-f-1); 
}

FunctionGroupState::~FunctionGroupState() noexcept{

}

bool FunctionGroupState::operator==(FunctionGroupState const &other) const noexcept{
    if(this->Function_group_name == other.Function_group_name){
        return true;
    }
    return false;
}

bool FunctionGroupState::operator!=(FunctionGroupState const &other) const noexcept{
        if(this->Function_group_name == other.Function_group_name){
        return false;
    }
    return true;
}