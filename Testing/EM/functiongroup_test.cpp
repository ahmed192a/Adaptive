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
#include <filesystem>
#include <gtest/gtest.h>
#include <iostream>
#include <variant>
using namespace std;
namespace ara
{
    namespace exec
    {
        /**
         * @brief FunctionGroupTest class
         * 
         */
        class FunctionGroupTest : public ::testing::Test
        {
        public:
            const std::string cShortnamePath_1 = "../App/Manifests/machine_manifest.json/MachineFG";        /*!< metaModelIdentifier for a valid function group machineFG */
            const std::string cShortnamePath_2 = "../App/Manifests/machine_manifest.json/FG_1";             /*!< metaModelIdentifier for a valid function group FG_1 */
            const std::string cShortnamePath_invalid = "../App/Manifests/machine_manifest.json/FG_in";      /*!< metaModelIdentifier for an invalid function group */
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup_1;                        /*!< variant for a valid function group */
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup_2;                        /*!< variant for a valid function group */
            variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup_invalid;                   /*!< variant for an invalid function group */
            // FunctionGroup functionGroup_invalid;
        protected:
            /**
             * @brief Set the Up object
             * 
             */
            void SetUp() override
            {
                // std::cout << "SetUp" << std::endl;
                _functionGroup_1 = FunctionGroup::Preconstruct(cShortnamePath_1);
                _functionGroup_2 = FunctionGroup::Preconstruct(cShortnamePath_2);
                _functionGroup_invalid = FunctionGroup::Preconstruct(cShortnamePath_invalid);
            }
            /**
             * @brief TearDown
             * 
             */
            void TearDown() override
            {
                // std::cout << "TearDown" << std::endl;
            }
        };
        /**
         * @brief Construct a new TEST object
         *
         */
        TEST_F(FunctionGroupTest, PreconstructSuccess)
        {
            bool t;
            switch (_functionGroup_1.index())
            {
            case 0:

                t = (get<0>(_functionGroup_1) == ara::exec::ExecErrc::kMetaModelError);
                EXPECT_FALSE(t == 1);
                break;

            case 1:
                FunctionGroup::CtorToken k{};
                t = (get<1>(_functionGroup_1) == k);
                EXPECT_FALSE(t == 1);
                break;
            }
        }
        /**
         * @brief Construct a new TEST object
         *
         */
        TEST_F(FunctionGroupTest, PreconstructFailed)
        {
            bool t;
            switch (_functionGroup_invalid.index())
            {
            case 0:

                t = (get<0>(_functionGroup_invalid) == ara::exec::ExecErrc::kMetaModelError);
                EXPECT_TRUE(t == 1);
                break;

            case 1:
                FunctionGroup::CtorToken k{};
                t = (get<1>(_functionGroup_invalid) == k);
                EXPECT_TRUE(t == 1);
                break;
            }
        }

        /**
         * @brief FunctionGroupTest::Equality
         * @details This function compares two FunctionGroup objects and verifies their equality.
         * @param functionGroup : A FunctionGroup object, constructed from std::get<1>(_functionGroup_1)
         * @param otherFunctionGroup : A FunctionGroup object, constructed from get<1>(_functionGroup_1)
         * @return true if functionGroup  and otherFunctionGroup are equal, otherwise false
         *
         */
        TEST_F(FunctionGroupTest, Equality)
        {
            FunctionGroup functionGroup(std::move(std::get<1>(_functionGroup_1)));
            FunctionGroup otherFunctionGroup(std::move(get<1>(_functionGroup_1)));

            EXPECT_TRUE(functionGroup == otherFunctionGroup);
        }
        /**
         * @brief This test verifies that two FunctionGroup objects are not equal.
         * @details This code creates two FunctionGroup objects from two different function group tuples and compares them for inequality. 
         *          The EXPECT_TRUE macro is used to verify that the two objects are indeed not equal.
         */
        TEST_F(FunctionGroupTest, Inequality)
        {

            auto functionGroup = FunctionGroup(std::move(get<1>(_functionGroup_1)));
            auto otherFunctionGroup = FunctionGroup(std::move(get<1>(_functionGroup_2)));

            EXPECT_TRUE(functionGroup != otherFunctionGroup);
        }

    }
}