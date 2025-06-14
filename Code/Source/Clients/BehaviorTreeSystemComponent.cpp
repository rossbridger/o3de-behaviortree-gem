
#include "BehaviorTreeSystemComponent.h"

#include <BehaviorTree/BehaviorTreeTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzFramework/Asset/GenericAssetHandler.h>
#include <BehaviorTree/Node.h>
#include "Behaviors/Composite.h"
#include "Clients/BehaviorTreeComponent.h"


namespace BehaviorTree
{
    AZ_COMPONENT_IMPL(BehaviorTreeSystemComponent, "BehaviorTreeSystemComponent",
        BehaviorTreeSystemComponentTypeId);

    void BehaviorTreeSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        Node::Reflect(context);
        Composite::Reflect(context);
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
        m_behaviorTreeAssetHandler = new AzFramework::GenericAssetHandler<BehaviorTreeAsset>("Buildable Catalog", "Other", "buildables", AZ::AzTypeInfo<BehaviorTreeComponent>::Uuid(), nullptr, AZ::DataStream::ST_JSON);
        m_behaviorTreeAssetHandler->Register();
    }

    void BehaviorTreeSystemComponent::Deactivate()
    {
        m_behaviorTreeAssetHandler->Unregister();
        delete m_behaviorTreeAssetHandler;
        BehaviorTreeSystemRequestBus::Handler::BusDisconnect();
    }

} // namespace BehaviorTree
