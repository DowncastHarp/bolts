// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_FollowerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BC_API UBTService_FollowerEnemy : public UBTService
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Default)
	float RayCastDistance = 1500.f;

	UBTService_FollowerEnemy();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
