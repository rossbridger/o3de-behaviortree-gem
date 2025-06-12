#pragma once

#include <AzCore/RTTI/TypeInfo.h>
#include <AzCore/RTTI/TemplateInfo.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Memory/Memory.h>
#include <AzCore/Asset/AssetCommon.h>


namespace BehaviorTree
{
	class Behavior;
	class BehaviorTreeAsset
		: public AZ::Data::AssetData
	{
	public:
		AZ_RTTI(BehaviorTreeAsset, "{C7262D20-2181-49CE-A2F9-8964F418F497}", AZ::Data::AssetData);

		static void Reflect(AZ::ReflectContext* context);
	private:
		AZStd::unique_ptr<Behavior> m_rootBehavior;
	};
}

