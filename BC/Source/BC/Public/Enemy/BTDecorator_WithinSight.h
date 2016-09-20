// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_WithinSight.generated.h"

UCLASS()
class BC_API UBTDecorator_WithinSight : public UBTDecorator
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Default)
	float SightRange = 500.f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
