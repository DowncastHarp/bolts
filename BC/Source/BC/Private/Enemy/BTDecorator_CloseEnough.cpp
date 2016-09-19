// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FollowerEnemy.h"
#include "FollowerAI.h"
#include "BCCharacter.h"
#include "BTDecorator_CloseEnough.h"


bool UBTDecorator_CloseEnough::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFollowerAI *EnemyPC = Cast<AFollowerAI>(OwnerComp.GetAIOwner());

	ABCCharacter *Target = Cast<ABCCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->TargetKeyID));

	if (Target)
	{
		FVector EnemyLocation = EnemyPC->GetPawn()->GetActorLocation();

		FVector TargetLocation = Target->GetActorLocation();

		if ((EnemyLocation - TargetLocation).Size() >= AcceptanceDistance)
		{
			return true;
		}
	}

	return false;
}