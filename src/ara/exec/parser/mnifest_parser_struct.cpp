#include "manifest_parser_struct.h"

using namespace ara::exec::parser;



// Definitions of operators
bool ExecutionManifest::operator==(const ExecutionManifest &other) const noexcept
{
    return (manifest_id == other.manifest_id) && (processes == other.processes);
}

bool ExecutionManifest::operator!=(const ExecutionManifest &other) const noexcept
{
    return !(*this == other);
}

bool Process::operator==(const Process &other) const noexcept
{
    return (name == other.name) && (startup_configs == other.startup_configs);
}

bool Process::operator!=(const Process &other) const noexcept
{
    return !(*this == other);
}

bool Process::StartupConfig::operator==(const StartupConfig &other) const
    noexcept
{
    return (startup_options == other.startup_options) &&
            (machine_instance_refs == other.machine_instance_refs);
}

bool Process::StartupConfig::operator!=(const StartupConfig &other) const
    noexcept
{
    return !(*this == other);
}

bool Process::StartupConfig::StartupOption::operator==(
    const StartupOption &other) const noexcept
{
    return (kind == other.kind) && (name == other.name) && (arg == other.arg);
}

bool Process::StartupConfig::StartupOption::operator!=(
    const StartupOption &other) const noexcept
{
    return !(*this == other);
}

bool Process::StartupConfig::MachineInstanceRef::operator==(
    const MachineInstanceRef &other) const noexcept
{
    return (function_group == other.function_group) && (mode == other.mode);
}

bool Process::StartupConfig::MachineInstanceRef::operator!=(
    const MachineInstanceRef &other) const noexcept
{
    return !(*this == other);
}

bool MachineManifest::operator==(const MachineManifest &other) const noexcept
{
    return (manifest_id == other.manifest_id) &&
            (mode_declaration_groups == other.mode_declaration_groups);
}

bool MachineManifest::operator!=(const MachineManifest &other) const noexcept
{
    return !(*this == other);
}

bool MachineManifest::ModeDeclarationGroup::operator==(const ModeDeclarationGroup &other) const
    noexcept
{
    return (function_group_name == other.function_group_name) &&
            (mode_declarations == other.mode_declarations);
}

bool MachineManifest::ModeDeclarationGroup::operator!=(const ModeDeclarationGroup &other) const
    noexcept
{
    return !(*this == other);
}

bool MachineManifest::ModeDeclarationGroup::ModeDeclaration::operator==(
    const ModeDeclaration &other) const noexcept
{
    return (mode == other.mode);
}

bool MachineManifest::ModeDeclarationGroup::ModeDeclaration::operator!=(
    const ModeDeclaration &other) const noexcept
{
    return !(*this == other);
}