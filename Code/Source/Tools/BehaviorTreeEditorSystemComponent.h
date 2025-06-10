
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/BehaviorTreeSystemComponent.h>

namespace BehaviorTree
{
    /// System component for BehaviorTree editor
    class BehaviorTreeEditorSystemComponent
        : public BehaviorTreeSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = BehaviorTreeSystemComponent;
    public:
        AZ_COMPONENT_DECL(BehaviorTreeEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        BehaviorTreeEditorSystemComponent();
        ~BehaviorTreeEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace BehaviorTree
