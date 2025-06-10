
#include <AzCore/Serialization/SerializeContext.h>
#include "BehaviorTreeEditorSystemComponent.h"

#include <BehaviorTree/BehaviorTreeTypeIds.h>

namespace BehaviorTree
{
    AZ_COMPONENT_IMPL(BehaviorTreeEditorSystemComponent, "BehaviorTreeEditorSystemComponent",
        BehaviorTreeEditorSystemComponentTypeId, BaseSystemComponent);

    void BehaviorTreeEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<BehaviorTreeEditorSystemComponent, BehaviorTreeSystemComponent>()
                ->Version(0);
        }
    }

    BehaviorTreeEditorSystemComponent::BehaviorTreeEditorSystemComponent() = default;

    BehaviorTreeEditorSystemComponent::~BehaviorTreeEditorSystemComponent() = default;

    void BehaviorTreeEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("BehaviorTreeEditorService"));
    }

    void BehaviorTreeEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("BehaviorTreeEditorService"));
    }

    void BehaviorTreeEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void BehaviorTreeEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void BehaviorTreeEditorSystemComponent::Activate()
    {
        BehaviorTreeSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void BehaviorTreeEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        BehaviorTreeSystemComponent::Deactivate();
    }

} // namespace BehaviorTree
