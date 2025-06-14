#pragma once

#include <AzCore/RTTI/TypeInfo.h>
#include <AzCore/RTTI/TemplateInfo.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Memory/Memory.h>
#include <AzCore/Asset/AssetCommon.h>
#include <BehaviorTree/Node.h>


namespace BehaviorTree
{
    class BehaviorTreeAsset
        : public AZ::Data::AssetData
    {
    public:
        AZ_RTTI(BehaviorTreeAsset, "{B1959000-F10F-4563-91AE-18C04BDCD982}", AZ::Data::AssetData);

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<BehaviorTreeAsset, AZ::Data::AssetData>()
                    ->Version(0);
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<BehaviorTreeAsset>("Behavior Tree Asset", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::Category, "Behavior Tree")
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(nullptr, &BehaviorTreeAsset::m_rootNode, "Root Node", "Root Node for the Behavior Tree");
                }
            }
        }

        Node* GetRootNode() { return m_rootNode.get(); }
    private:
        AZStd::unique_ptr<Node> m_rootNode;
    };
}


