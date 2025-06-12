
#pragma once

#include <BehaviorTree/BehaviorTreeTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace BehaviorTree
{
    class BehaviorTreeSystemRequests
    {
    public:
        AZ_RTTI(BehaviorTreeSystemRequests, BehaviorTreeRequestsTypeId);
        virtual ~BehaviorTreeSystemRequests() = default;
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

    using BehaviorTreeSystemRequestBus = AZ::EBus<BehaviorTreeSystemRequests, BehaviorTreeBusTraits>;
    using BehaviorTreeInterface = AZ::Interface<BehaviorTreeSystemRequests>;

} // namespace BehaviorTree
