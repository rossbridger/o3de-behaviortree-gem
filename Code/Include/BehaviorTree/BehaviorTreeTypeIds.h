
#pragma once

namespace BehaviorTree
{
    // System Component TypeIds
    inline constexpr const char* BehaviorTreeSystemComponentTypeId = "{4A930DF1-0E35-4AA8-9316-1790055BCF8A}";
    inline constexpr const char* BehaviorTreeEditorSystemComponentTypeId = "{B4C428DF-995B-431B-A0E1-61CFC87780EA}";

    // Module derived classes TypeIds
    inline constexpr const char* BehaviorTreeModuleInterfaceTypeId = "{56000204-AB31-494D-8AE3-09DC6FE52BFF}";
    inline constexpr const char* BehaviorTreeModuleTypeId = "{26767F6F-E72B-45A7-9524-957494977CD2}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* BehaviorTreeEditorModuleTypeId = BehaviorTreeModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* BehaviorTreeRequestsTypeId = "{D46C0E6C-676A-4E05-A7D9-8EFA3F710675}";
} // namespace BehaviorTree
