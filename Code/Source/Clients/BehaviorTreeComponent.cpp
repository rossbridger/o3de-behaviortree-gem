#include <BehaviorTree/BehaviorTreeComponentBus.h>
#include "BehaviorTreeAsset.h"
#include "Clients/BehaviorTreeComponent.h"

namespace BehaviorTree
{
    void BehaviorTreeComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<BehaviorTreeComponent, AZ::Component>()
                ->Version(0);
            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<BehaviorTreeComponent>("Behavior Tree Component", "")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "Behavior Tree");
            }
        }
    }

    void BehaviorTreeComponent::Activate()
    {
        AZ::Data::AssetBus::Handler::BusConnect(m_behaviorTreeAsset.GetId());
        AZ::TickBus::Handler::BusConnect();
    }

    void BehaviorTreeComponent::Deactivate()
    {
        AZ::Data::AssetBus::Handler::BusDisconnect(m_behaviorTreeAsset.GetId());
        AZ::TickBus::Handler::BusDisconnect();
    }

    void BehaviorTreeComponent::OnTick(float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
        if (m_currentTask == nullptr)
        {
            return;
        }
        m_currentStatus = m_currentTask->OnTick(GetEntityId(), deltaTime);
        if (m_currentStatus == Status::Success || m_currentStatus == Status::Failure)
        {
            BehaviorTreeNotificationBus::Event(GetEntityId(), &BehaviorTreeNotificationBus::Events::OnBehaviorTreeTaskComplete, m_currentStatus);
            // oneshot task behavior, maybe change this later
            m_behaviorTreeAsset->GetRootNode()->DestroyTask(GetEntityId(), m_currentTask);
            m_currentTask = nullptr;
        }
    }

    void BehaviorTreeComponent::EditorSetPrimaryAsset(const AZ::Data::AssetId& assetId)
    {
        m_behaviorTreeAsset.Create(assetId);
    }

    void BehaviorTreeComponent::OnAssetReady(AZ::Data::Asset<AZ::Data::AssetData> asset)
    {
        if (BehaviorTreeAsset* behaviorTreeAsset = azrtti_cast<BehaviorTreeAsset*>(asset.Get()))
        {
            m_currentTask = behaviorTreeAsset->GetRootNode()->CreateTask(GetEntityId());
        }
    }
    void BehaviorTreeComponent::OnAssetReloaded(AZ::Data::Asset<AZ::Data::AssetData> asset)
    {
        m_currentTask->OnTerminate(GetEntityId(), Status::Aborted);
        m_behaviorTreeAsset->GetRootNode()->DestroyTask(GetEntityId(), m_currentTask);
        m_currentTask = nullptr;
        m_behaviorTreeAsset = asset;
        if (asset.IsReady())
        {
            OnAssetReady(asset);
        }
    }

    void BehaviorTreeComponent::OnAssetUnloaded(const AZ::Data::AssetId assetId, const AZ::Data::AssetType assetType)
    {
        m_currentTask->OnTerminate(GetEntityId(), Status::Aborted);
        m_behaviorTreeAsset->GetRootNode()->DestroyTask(GetEntityId(), m_currentTask);
        m_currentTask = nullptr;
    }
}

