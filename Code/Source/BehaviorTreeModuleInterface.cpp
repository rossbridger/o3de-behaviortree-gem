
#include "BehaviorTreeModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <BehaviorTree/BehaviorTreeTypeIds.h>

#include <Clients/BehaviorTreeSystemComponent.h>
#include <Clients/BehaviorTreeComponent.h>

namespace BehaviorTree
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(BehaviorTreeModuleInterface,
        "BehaviorTreeModuleInterface", BehaviorTreeModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(BehaviorTreeModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(BehaviorTreeModuleInterface, AZ::SystemAllocator);

    BehaviorTreeModuleInterface::BehaviorTreeModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            BehaviorTreeSystemComponent::CreateDescriptor(),
            BehaviorTreeComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList BehaviorTreeModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<BehaviorTreeSystemComponent>(),
        };
    }
} // namespace BehaviorTree
