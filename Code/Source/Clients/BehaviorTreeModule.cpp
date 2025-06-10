
#include <BehaviorTree/BehaviorTreeTypeIds.h>
#include <BehaviorTreeModuleInterface.h>
#include "BehaviorTreeSystemComponent.h"

namespace BehaviorTree
{
    class BehaviorTreeModule
        : public BehaviorTreeModuleInterface
    {
    public:
        AZ_RTTI(BehaviorTreeModule, BehaviorTreeModuleTypeId, BehaviorTreeModuleInterface);
        AZ_CLASS_ALLOCATOR(BehaviorTreeModule, AZ::SystemAllocator);
    };
}// namespace BehaviorTree

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), BehaviorTree::BehaviorTreeModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_BehaviorTree, BehaviorTree::BehaviorTreeModule)
#endif
