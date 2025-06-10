
#pragma once

#include <BehaviorTree/BehaviorTreeTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace BehaviorTree
{
    class BehaviorTreeRequests
    {
    public:
        AZ_RTTI(BehaviorTreeRequests, BehaviorTreeRequestsTypeId);
        virtual ~BehaviorTreeRequests() = default;
        // Put your public methods here
    };

    class BehaviorTreeBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using BehaviorTreeRequestBus = AZ::EBus<BehaviorTreeRequests, BehaviorTreeBusTraits>;
    using BehaviorTreeInterface = AZ::Interface<BehaviorTreeRequests>;

} // namespace BehaviorTree
