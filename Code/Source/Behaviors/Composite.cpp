#include "Behaviors/Composite.h"

namespace BehaviorTree
{
    void Composite::SequenceTask::OnInit(AZ::EntityId entityId)
    {
        m_currentChildIndex = 0;
        m_currentChildTask = nullptr;
        m_status = Status::Running;
    }
    Status Composite::SequenceTask::OnUpdate(AZ::EntityId entityId, float deltaTime)
    {
        while (m_currentChildIndex < GetNode()->m_children.size())
        {
            if (m_currentChildTask != nullptr)
            {
                m_currentChildTask = GetNode()->m_children[m_currentChildIndex]->CreateTask(entityId);
            }
            Status m_childStatus = m_currentChildTask->OnTick(entityId, deltaTime);
            if (m_status == Status::Running)
            {
                return m_status;
            }
            GetNode()->m_children[m_currentChildIndex]->DestroyTask(entityId, m_currentChildTask);
            m_currentChildTask = nullptr;
            if (m_status == Status::Failure)
            {
                return m_status;
            }
            m_currentChildIndex++;
        }
        return Status::Success;
    }
    void Composite::SequenceTask::OnTerminate(AZ::EntityId entityId, Status status)
    {
        if (m_currentChildTask != nullptr)
        {
            m_currentChildTask->OnTerminate(entityId, status);
            GetNode()->m_children[m_currentChildIndex]->DestroyTask(entityId, m_currentChildTask);
            m_currentChildTask = nullptr;
            m_currentChildIndex = 0;
        }
    }

    void Composite::SelectorTask::OnInit(AZ::EntityId entityId)
    {
        m_currentChildIndex = 0;
        m_currentChildTask = nullptr;
        m_status = Status::Running;
    }
    Status Composite::SelectorTask::OnUpdate(AZ::EntityId entityId, float deltaTime)
    {
        while (m_currentChildIndex < GetNode()->m_children.size())
        {
            if (m_currentChildTask != nullptr)
            {
                m_currentChildTask = GetNode()->m_children[m_currentChildIndex]->CreateTask(entityId);
            }
            Status m_childStatus = m_currentChildTask->OnTick(entityId, deltaTime);
            if (m_status == Status::Running)
            {
                return m_status;
            }
            GetNode()->m_children[m_currentChildIndex]->DestroyTask(entityId, m_currentChildTask);
            m_currentChildTask = nullptr;
            if (m_status == Status::Success)
            {
                return m_status;
            }
            m_currentChildIndex++;
        }
        return Status::Failure;
    }
    void Composite::SelectorTask::OnTerminate(AZ::EntityId entityId, Status status)
    {
        if (m_currentChildTask != nullptr)
        {
            m_currentChildTask->OnTerminate(entityId, status);
            GetNode()->m_children[m_currentChildIndex]->DestroyTask(entityId, m_currentChildTask);
            m_currentChildTask = nullptr;
            m_currentChildIndex = 0;
        }
    }

    static void Composite::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<Composite, Node>()
                ->Version(0)
                ->Field("Type", &Composite::m_type)
                ->Field("Children", &Composite::m_children);
            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<Composite>("Composite", "")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &Composite::m_type, "Type", "Type of the composite node")
                    ->EnumAttribute(Type::Sequence, "Sequence")
                    ->EnumAttribute(Type::Selector, "Selector")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &Composite::m_children, "Children", "Children of the composite node");
            }
        }
    }

    Node::Task* Composite::CreateTask(AZ::EntityId entityId)
    {
        switch (m_type)
        {
        case Type::Sequence:
            return aznew SequenceTask(entityId, this);
            break;
        case Type::Selector:
            return aznew SelectorTask(entityId, this);
            break;
        default:
            return nullptr;
        }
    }
}