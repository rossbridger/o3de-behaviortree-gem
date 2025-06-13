#include "BehaviorTreeAsset.h"
#include "BehaviorTreeComponent.h"

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

    void BehaviorTreeComponent::OnTick(float deltaTime, AZ::ScriptTimePoint time)
    {
        if (m_currentTask == nullptr)
        {
            return;
        }
        if (m_currentStatus == Status::Invalid)
        {
            m_currentTask->OnInit();
        }
        m_currentStatus = m_currentTask->OnUpdate();
        if (m_currentStatus != Status::Running)
        {
            m_currentTask->OnTerminate(m_currentStatus);
        }
    }

    void BehaviorTreeComponent::EditorSetPrimaryAsset(const AZ::Data::AssetId& assetId)
    {
    }

    void BehaviorTreeComponent::OnAssetReady(AZ::Data::Asset<AZ::Data::AssetData> asset)
    {
        if (BehaviorTreeAsset* behaviorTreeAsset = azrtti_cast<BehaviorTreeAsset*>(asset.Get()))
        {
            m_currentTask = behaviorTreeAsset->GetRootNode()->CreateTask();
        }
    }
    void BehaviorTreeComponent::OnAssetReloaded(AZ::Data::Asset<AZ::Data::AssetData> asset)
    {
        m_behaviorTreeAsset->GetRootNode()->DestroyTask(m_currentTask);
        m_currentTask = nullptr;
        m_behaviorTreeAsset = asset;
        if (asset.IsReady())
        {
            OnAssetReady(asset);
        }
    }

    void BehaviorTreeComponent::OnAssetUnloaded(const AZ::Data::AssetId assetId, const AZ::Data::AssetType assetType)
    {
        m_behaviorTreeAsset->GetRootNode()->DestroyTask(m_currentTask);
        m_currentTask = nullptr;
    }
}

