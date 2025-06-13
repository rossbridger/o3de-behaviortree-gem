#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Asset/AssetCommon.h>
#include <AzCore/Component/Entity.h>
#include <BehaviorTree/Node.h>
#include <AzFramework/Components/EditorEntityEvents.h>

namespace BehaviorTree
{
    class BehaviorTreeComponent
        : public AZ::Component
        , public AZ::TickBus::Handler
        , private AzFramework::EditorEntityEvents
        , private AZ::Data::AssetBus::Handler
    {
    public:
        AZ_COMPONENT(BehaviorTreeComponent, "{A7E0D864-EB98-48E6-AE71-FB2C3FDE9029}", AZ::Component);

        static void Reflect(AZ::ReflectContext* context);

        void Activate() override;
        void Deactivate() override;

        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override; // Fix override issue by matching the base class signature

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
        {
            provided.push_back(AZ_CRC_CE("BehaviorTreeService"));
        }
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
        {
            incompatible.push_back(AZ_CRC_CE("BehaviorTreeService"));
        }

    private:
        void OnAssetReady(AZ::Data::Asset<AZ::Data::AssetData> asset) override;

        void EditorSetPrimaryAsset(const AZ::Data::AssetId& assetId) override;
        void OnAssetReady(AZ::Data::Asset<AZ::Data::AssetData> asset) override;
        void OnAssetReloaded(AZ::Data::Asset<AZ::Data::AssetData> asset) override;
        void OnAssetUnloaded(const AZ::Data::AssetId assetId, const AZ::Data::AssetType assetType) override;

        AZ::Data::Asset<BehaviorTreeAsset> m_behaviorTreeAsset;
        AZ::Entity m_blackBoardEntity;
        Node::Task* m_currentTask = nullptr;
        Status m_currentStatus = Status::Invalid;
    };
}