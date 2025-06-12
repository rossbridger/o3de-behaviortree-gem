#pragma once

#include <AzCore/Component/Component.h>
#include <BehaviorTree/BehaviorTreeSystemBus.h>

namespace AzFramework
{
    template<typename AssetType>
	class GenericAssetHandler;
}

namespace BehaviorTree
{
    class BehaviorTreeAsset;

    class BehaviorTreeSystemComponent
        : public AZ::Component
        , protected BehaviorTreeSystemRequestBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(BehaviorTreeSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        BehaviorTreeSystemComponent();
        ~BehaviorTreeSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // BehaviorTreeSystemRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    private:
        AzFramework::GenericAssetHandler<BehaviorTreeAsset>* m_behaviorTreeAssetHandler;
    };

} // namespace BehaviorTree
