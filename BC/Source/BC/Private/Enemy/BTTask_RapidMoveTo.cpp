// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FollowerEnemy.h"
#include "FollowerAI.h"
#include "BCCharacter.h"
#include "BTTask_RapidMoveTo.h"


EBTNodeResult::Type UBTTask_RapidMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFollowerAI *EnemyPC = Cast<AFollowerAI>(OwnerComp.GetAIOwner());

	ABCCharacter *Target = Cast<ABCCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->TargetKeyID));

	if (Target)
	{
		EnemyPC->MoveToLocation(Target->GetActorLocation(), AcceptanceRadius, true, true, true, true, 0, true);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

