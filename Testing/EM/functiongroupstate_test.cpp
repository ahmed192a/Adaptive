/**
 * @file functiongroupstate_test.cpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../../include/ara/exec/function_group.hpp"
#include "../../include/ara/exec/function_group_state.hpp"
#include "../../include/ara/exec/exec_error_domain.hpp"
#include <gtest/gtest.h>
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
        TEST(FunctionGroupStateTest, Preconstruct)
        {
            fg_num = 0;
            const std::string cShortnamePath{"../App/manifest_samples/machine_manifest.json"}; 
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(cShortnamePath);
            bool t;
            switch (_functionGroup.index())
            {
            case 0:
                t = (get<0>(_functionGroup) == ara::exec::ExecErrc::kMetaModelError || get<0>(_functionGroup) == ara::exec::ExecErrc::kGeneralError);
                EXPECT_TRUE(t == 1);
                break;

            case 1:
                FunctionGroup::CtorToken tok = get<1>(_functionGroup);
                FunctionGroup FG(std::move(tok));
                FunctionGroupState::CtorToken c;
                c.fg_name = FG.get_FGname();
                c.c_state = FG.get_states()[0];
                variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> _functionGroupState = FunctionGroupState::Preconstruct(FG, FG.get_FGname() + "/" + FG.get_states()[0]);
                switch (_functionGroupState.index())
                {
                case 0:
                    EXPECT_TRUE(get<0>(_functionGroupState) == ara::exec::ExecErrc::kMetaModelError);
                    break;
                case 1:
                    FunctionGroupState::CtorToken R = get<1>(_functionGroupState);
                    EXPECT_TRUE(c.fg_name == R.fg_name);
                    break;
                }

                break;
            }
            //EXPECT_TRUE(false);
        }

        /**
         * @brief Construct a new TEST object
         * 
         */
        TEST(FunctionGroupStateTest, Equality)
        {
            fg_num = 0;
            const std::string cShortnamePath{"../App/manifest_samples/machine_manifest.json"};
            
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(cShortnamePath);
            FunctionGroup FG(std::move(get<1>(_functionGroup)));

            variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> _functionGroupState = FunctionGroupState::Preconstruct(FG, FG.get_FGname() + "/" + FG.get_states()[0]);
            
            FunctionGroupState functionGroupState(std::move(get<1>(_functionGroupState)));
            FunctionGroupState otherfunctionGroupState(std::move(get<1>(_functionGroupState)));
            
            EXPECT_TRUE(functionGroupState == otherfunctionGroupState);
        }

        /**
         * @brief Construct a new TEST object
         * 
         */
        TEST(FunctionGroupStateTest, Inequality)
        {
            fg_num = 0;
            const std::string cShortnamePath{"../App/manifest_samples/machine_manifest.json"};
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(cShortnamePath);
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _otherfunctionGroup = FunctionGroup::Preconstruct(cShortnamePath);

            FunctionGroup FG(std::move(get<1>(_functionGroup)));
            FunctionGroup OFG(std::move(get<1>(_otherfunctionGroup)));
            variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> _functionGroupState = FunctionGroupState::Preconstruct(FG, FG.get_FGname() + "/" + FG.get_states()[0]);
            variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> _otherfunctionGroupState = FunctionGroupState::Preconstruct(OFG, OFG.get_FGname() + "/" + OFG.get_states()[0]);

            FunctionGroupState functionGroupState(std::move(get<1>(_functionGroupState)));
            FunctionGroupState otherfunctionGroupState(std::move(get<1>(_otherfunctionGroupState)));
            EXPECT_TRUE(functionGroupState != otherfunctionGroupState);
        }
    } // namespace exec

} // namespace ara