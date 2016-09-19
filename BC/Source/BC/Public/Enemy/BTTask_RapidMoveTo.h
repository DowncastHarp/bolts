// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RapidMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class BC_API UBTTask_RapidMoveTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Default)
	float AcceptanceRadius = 2.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;		
};
