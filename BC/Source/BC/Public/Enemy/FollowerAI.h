// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "FollowerAI.generated.h"

/**
*
*/
UCLASS()
class BC_API AFollowerAI : public AAIController
{
	GENERATED_BODY()

		UPROPERTY(transient)
		class UBlackboardComponent *BlackboardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent *BehaviorComp;

public:

	AFollowerAI();

	virtual void Possess(APawn *inPawn) override;

	uint8 TargetKeyID;

};
