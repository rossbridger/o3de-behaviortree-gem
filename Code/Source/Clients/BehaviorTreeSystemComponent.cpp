
#include "BehaviorTreeSystemComponent.h"

#include <BehaviorTree/BehaviorTreeTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <BehaviorTree/BehaviorNode.h>
#include "BehaviorTreeComponent.h"


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
        provided.push_back(AZ_CRC_CE("BehaviorTreeSystemService"));
    }

    void BehaviorTreeSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("BehaviorTreeSystemService"));
    }

    void BehaviorTreeSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("AssetDatabaseService"));
        required.push_back(AZ_CRC_CE("AssetCatalogService"));
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
        BehaviorTreeSystemRequestBus::Handler::BusConnect();
    }

    void BehaviorTreeSystemComponent::Deactivate()
    {
        BehaviorTreeSystemRequestBus::Handler::BusDisconnect();
    }

} // namespace BehaviorTree
