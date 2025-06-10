
#include <BehaviorTree/BehaviorTreeTypeIds.h>
#include <BehaviorTreeModuleInterface.h>
#include "BehaviorTreeEditorSystemComponent.h"

namespace BehaviorTree
{
    class BehaviorTreeEditorModule
        : public BehaviorTreeModuleInterface
    {
    public:
        AZ_RTTI(BehaviorTreeEditorModule, BehaviorTreeEditorModuleTypeId, BehaviorTreeModuleInterface);
        AZ_CLASS_ALLOCATOR(BehaviorTreeEditorModule, AZ::SystemAllocator);

        BehaviorTreeEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                BehaviorTreeEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<BehaviorTreeEditorSystemComponent>(),
            };
        }
    };
}// namespace BehaviorTree

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), BehaviorTree::BehaviorTreeEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_BehaviorTree_Editor, BehaviorTree::BehaviorTreeEditorModule)
#endif
