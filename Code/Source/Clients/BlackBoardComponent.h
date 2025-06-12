#pragma once

namespace BehaviorTree
{
	class BlackBoardComponent
		: public AZ::Component
	{
	public:
		AZ_COMPONENT(BehaviorTreeSystemComponent, "{A7E0D864-EB98-48E6-AE71-FB2C3FDE9029}", AZ::Component);

		static void Reflect(AZ::ReflectContext* context);
	}
}