#pragma once

#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Entity/EntityId.h>

namespace BehaviorTree
{
    enum class Status
    {
        Invalid,
        Running,
        Success,
        Failure
    };

    class Node
    {
    public:

        class Task
        {
        public:
            Task(Node& node, AZ::EntityId entityId) {}
            virtual void OnInit() = 0;
            virtual Status OnUpdate(float deltaTime) = 0;
            virtual void OnTerminate(Status status) = 0;
        private:
            Node* m_node;
        };

        AZ_TYPE_INFO(Node, "{0CD4A186-5B8D-45E4-9795-01B1373F8A8F}");
        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Node>()
                    ->Version(0)
                    ->Attribute(AZ::Edit::Attributes::EnableForAssetEditor, true)
                    ->Field("Name", &Node::m_name);
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Node>("Node", "Base class for Behavior Tree Nodes")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Node::m_name, "Name", "Name");
                }
            }
        }

        virtual Task* CreateTask(AZ::EntityId entityId) = 0;
        virtual void DestroyTask(Task* task) = 0;
        virtual ~Node() {};

    private:
        AZStd::string m_name;
    };
}