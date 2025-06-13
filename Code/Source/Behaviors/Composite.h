#pragma once

#include <BehaviorTree/Node.h>

namespace BehaviorTree
{
    class Composite : public Node
    {
    public:
        AZ_RTTI(Composite, "{C1B9B0D6-4E9B-4E9B-9B1B-0D6B4E9B1B9B}", Node);

        static void Reflect(AZ::ReflectContext* context);
        class Task : public Node::Task
        {
        public:
            virtual ~Task() = default;
            virtual void OnInit();
            virtual Status OnUpdate(float deltaTime);
            virtual void OnTerminate(Status status);
        };
        Node::Task* CreateTask() override { return aznew Task(); }

        void DestroyTask(Task* Task) override;

        virtual ~Composite();
    protected:
        AZStd::vector<AZStd::unique_ptr<Node>> m_children;
    };
}