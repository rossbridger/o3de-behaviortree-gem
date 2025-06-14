#include <AzCore/Component/ComponentBus.h>

namespace BehaviorTree
{
    enum class Status;

    class BehaviorTreeNotifications
        : public AZ::ComponentBus
    {
    public:
        virtual void OnBehaviorTreeTaskComplete(Status status) = 0;
    };
    using BehaviorTreeNotificationBus = AZ::EBus<BehaviorTreeNotifications>;
}