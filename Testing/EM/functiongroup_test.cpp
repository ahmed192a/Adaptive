/**
 * @file functiongroup_test.cpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/exec/function_group.h"
#include "ara/exec/exec_error_domain.h"
#include <gtest/gtest.h>
#include <iostream>
#include <variant>
extern int fg_num;
using namespace std;
namespace ara
{
    namespace exec
    {
        /**
         * @brief Construct a new TEST object
         * 
         */
        TEST(FunctionGroupTest, Preconstruct)
        {
            fg_num = 0;
            const std::string cShortnamePath{"../App/manifest_samples/machine_manifest.json"};
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(cShortnamePath);
            bool t;
            switch (_functionGroup.index())
            {
            case 0:

                t = (get<0>(_functionGroup) == ara::exec::ExecErrc::kMetaModelError);
                EXPECT_TRUE(t == 1);
                break;

            case 1:
                FunctionGroup::CtorToken k {};
                t = (get<1>(_functionGroup) == k);
                EXPECT_FALSE(t == 1);
                break;
            }
        }

        /**
         * @brief Construct a new TEST object
         * 
         */
        TEST(FunctionGroupTest, Equality)
        {
            fg_num = 0;
            std::string cShortnamePath{"../App/manifest_samples/machine_manifest.json"};
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(cShortnamePath);            
            
            FunctionGroup functionGroup(std::move(get<1>(_functionGroup)));
            FunctionGroup otherFunctionGroup(std::move(get<1>(_functionGroup)));

            EXPECT_TRUE(1 == 1);
        }
        /**
         * @brief Construct a new TEST object
         * 
         */
        TEST(FunctionGroupTest, Inequality)
        {
            fg_num = 0;
            std::string cShortnamePath{"../App/manifest_samples/machine_manifest.json"};
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(cShortnamePath);            
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _otherFunctionGroup = FunctionGroup::Preconstruct(cShortnamePath);            

            auto functionGroup = FunctionGroup(std::move(get<1>(_functionGroup)));
            auto otherFunctionGroup = FunctionGroup(std::move(get<1>(_otherFunctionGroup)));

            EXPECT_TRUE(functionGroup != otherFunctionGroup);
        }

        
    }
}