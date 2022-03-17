/**
 * @file function_group.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/exec/function_group.hpp"
#include "ara/exec/parser/manifest_parser.hpp"
#include <filesystem>
using namespace ara::exec;
using namespace nlohmann;
using namespace parser;
uint32_t fg_num = 0;

namespace ara
{
    namespace exec
    {

        boost::variant2::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> FunctionGroup::Preconstruct(std::string metaModelIdentifier) noexcept
        {
            boost::variant2::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> token;
            if (!std::filesystem::exists(metaModelIdentifier))
            {
                token.emplace<0>(ara::exec::ExecErrc::kMetaModelError);
                return token;
            }
            using namespace MMJsonKeys;
            auto manifest_json_full = read_manifest_file(metaModelIdentifier);
            MachineManifest man{};
            validate_content(manifest_json_full, kAsVector);

            json manifest_json_content{};
            read_value(manifest_json_full, kMachineManifest, manifest_json_content);

            // read_value(manifest_json_content, kMachineManifestId, man.manifest_id);

            json mode_declaration_groups{};
            if (read_value(manifest_json_content, kModeDeclarationGroup, mode_declaration_groups))
            {
                if (mode_declaration_groups.begin() + fg_num != mode_declaration_groups.end())
                {
                    json mode_declaration_group = *(mode_declaration_groups.begin() + fg_num);
                    fg_num++;
                    token.emplace<1>(mode_declaration_group);
                }
                else
                {
                    token.emplace<0>(ara::exec::ExecErrc::kGeneralError);
                }
            }
            return token;
        }

        FunctionGroup::FunctionGroup(FunctionGroup::CtorToken &&token) noexcept
        {
            using namespace MMJsonKeys;
            read_value(token, kFunctionGroupName, mFunction_group_name);

            json mode_declarations{};
            if (read_value(token, kModeDeclarations, mode_declarations))
            {
                for (auto &mode_declaration : mode_declarations)
                {
                    std::string mode;
                    read_value(mode_declaration, kMode, mode);
                    mstates.push_back(mode);
                }
            }
        }

        FunctionGroup::~FunctionGroup() noexcept
        {
        }

        void FunctionGroup::set_FGname(std::string fg_name)
        {
            mFunction_group_name = fg_name;
        }
        void FunctionGroup::set_states(std::vector<std::string> states)
        {
            mstates = states;
        }
        std::string FunctionGroup::get_FGname() const noexcept
        {
            return mFunction_group_name;
        }
        std::vector<std::string> FunctionGroup::get_states() const noexcept
        {
            return mstates;
        }

        bool FunctionGroup::operator==(FunctionGroup const &other) const noexcept
        {
            if (other.mFunction_group_name == this->mFunction_group_name)
            {
                return true;
            }
            return false;
        }

        bool FunctionGroup::operator!=(FunctionGroup const &other) const noexcept
        {
            if (this->mFunction_group_name == other.mFunction_group_name)
            {
                return false;
            }
            return true;
        }

        FunctionGroup &FunctionGroup::operator=(FunctionGroup &&other)
        {
            this->mFunction_group_name = std::move(other.mFunction_group_name);
            this->mstates = std::move(other.mstates);
            return *this;
        }
    } // namespace exec

} // namespace ara
