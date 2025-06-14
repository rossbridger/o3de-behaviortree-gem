#pragma once

#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Component/EntityId.h>

namespace BehaviorTree
{
    enum class Status
    {
        Invalid,
        Running,
        Success,
        Failure,
        Aborted,
    };

    class Node
    {
    public:

        // stores runtime state
        class Task
        {
        public:
            Task(Node& node, [[maybe_unused]] AZ::EntityId entityId)
                : m_node(&node)
                , m_status(Status::Invalid) {}
            virtual void OnInit(AZ::EntityId entityId) = 0;
            virtual Status OnUpdate(AZ::EntityId entityId, float deltaTime) = 0;
            virtual void OnTerminate(AZ::EntityId entityId, Status status) = 0;

            Status OnTick(AZ::EntityId entityId, float deltaTime)
            {
                if (m_status == Status::Invalid)
                {
                    OnInit(entityId);
                }
                m_status = OnUpdate(entityId, deltaTime);
                if (m_status != Status::Running)
                {
                    OnTerminate(entityId, m_status);
                }
                return m_status;
            }

            const Status GetStatus() const { return m_status; }
        protected:
            Node* m_node;
            Status m_status = Status::Invalid;
        };

        AZ_TYPE_INFO(Node, "{D3BC61F3-489E-4783-B3B0-1A9E773A9EA3}");
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

        /* Node should handle managing tasks memory. Theoretically the task can be shared between entities for some "hivemind" effects, so the component should not free the task itself */
        virtual Task* CreateTask(AZ::EntityId entityId) = 0;
        virtual void DestroyTask(AZ::EntityId entityId, Task* task) = 0;
        virtual ~Node() {};

    private:
        AZStd::string m_name;
    };
}