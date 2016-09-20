// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FollowerEnemy.h"
#include "FollowerAI.h"


AFollowerAI::AFollowerAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AFollowerAI::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);

	AFollowerEnemy *Char = Cast<AFollowerEnemy>(InPawn);

	if (Char && Char->BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Char->BehaviorTree->BlackboardAsset);

		TargetKeyID = BlackboardComp->GetKeyID("TargetToFollow");

		BehaviorComp->StartTree(*Char->BehaviorTree);
	}
}
