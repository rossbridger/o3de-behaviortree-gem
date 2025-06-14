#pragma once
#include <AzCore/std/containers/vector.h>
#include <BehaviorTree/Node.h>

namespace BehaviorTree
{
    class Composite
        : public Node
    {
    public:
        AZ_RTTI(Composite, "{C1B9B0D6-4E9B-4E9B-9B1B-0D6B4E9B1B9B}", Node);

        enum class Type
        {
            Sequence,
            Selector,
        };

        class SequenceTask : public Node::Task
        {
        public:
            SequenceTask(Composite& node, AZ::EntityId entityId) : Node::Task(node, entityId) {}

            void OnInit(AZ::EntityId entityId) override;
            Status OnUpdate(AZ::EntityId entityId, float deltaTime) override;
            void OnTerminate(AZ::EntityId entityId, Status status) override;

            Composite* GetNode() { return static_cast<Composite*>(m_node); }
        private:
            size_t m_currentChildIndex = 0;
            Node::Task* m_currentChildTask = nullptr;
        };

        class SelectorTask : public Node::Task
        {
        public:
            SelectorTask(Composite& node, AZ::EntityId entityId) : Node::Task(node, entityId) {}

            void OnInit(AZ::EntityId entityId) override;
            Status OnUpdate(AZ::EntityId entityId, float deltaTime) override;
            void OnTerminate(AZ::EntityId entityId, Status status) override;

            Composite* GetNode() { return static_cast<Composite*>(m_node); }
        private:
            size_t m_currentChildIndex = 0;
            Node::Task* m_currentChildTask = nullptr;
        };
        static void Reflect(AZ::ReflectContext* context);

        AZStd::vector<AZStd::unique_ptr<Node>>& GetChildren() { return m_children; }
        virtual ~Composite() {}

        Node::Task* CreateTask(AZ::EntityId entityId) override;

        void DestroyTask([[maybe_unused]] AZ::EntityId entityId, Node::Task* task) override { delete task; }
    protected:
        Type m_type;
        AZStd::vector<AZStd::unique_ptr<Node>> m_children;
    };
}