
#include "BehaviorTreeSystemComponent.h"

#include <BehaviorTree/BehaviorTreeTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace BehaviorTree
{
    AZ_COMPONENT_IMPL(BehaviorTreeSystemComponent, "BehaviorTreeSystemComponent",
        BehaviorTreeSystemComponentTypeId);

    void BehaviorTreeSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<BehaviorTreeSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void BehaviorTreeSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("BehaviorTreeService"));
    }

    void BehaviorTreeSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("BehaviorTreeService"));
    }

    void BehaviorTreeSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void BehaviorTreeSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    BehaviorTreeSystemComponent::BehaviorTreeSystemComponent()
    {
        if (BehaviorTreeInterface::Get() == nullptr)
        {
            BehaviorTreeInterface::Register(this);
        }
    }

    BehaviorTreeSystemComponent::~BehaviorTreeSystemComponent()
    {
        if (BehaviorTreeInterface::Get() == this)
        {
            BehaviorTreeInterface::Unregister(this);
        }
    }

    void BehaviorTreeSystemComponent::Init()
    {
    }

    void BehaviorTreeSystemComponent::Activate()
    {
        BehaviorTreeRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void BehaviorTreeSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        BehaviorTreeRequestBus::Handler::BusDisconnect();
    }

    void BehaviorTreeSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace BehaviorTree
