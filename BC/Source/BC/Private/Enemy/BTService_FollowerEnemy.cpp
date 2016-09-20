// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FollowerEnemy.h"
#include "FollowerAI.h"
#include "BCCharacter.h"
#include "BTService_FollowerEnemy.h"


// Multi sphere ray trace
bool VTraceSphere(AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	const float Radius,
	TArray<FHitResult>& HitOuts,
	ECollisionChannel CollisionChannel = ECC_Pawn,
	bool ReturnPhysMat = false)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);

	TraceParams.bTraceComplex = true;

	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	TObjectIterator< APlayerController > ThePC;

	if (!ThePC) return false;

	return ThePC->GetWorld()->SweepMultiByChannel(
		HitOuts,
		Start,
		End,
		FQuat(),
		CollisionChannel,
		FCollisionShape::MakeSphere(Radius),
		TraceParams
	);
}

// Single line ray trace
bool VTraceLine(AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Pawn,
	bool ReturnPhysMat = false)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);

	TraceParams.bTraceComplex = true;

	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	TObjectIterator<APlayerController> ThePC;

	if (!ThePC) return false;

	return ThePC->GetWorld()->LineTraceSingleByChannel(
		HitOut,
		Start,
		End,
		CollisionChannel,
		TraceParams
	);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);
}

UBTService_FollowerEnemy::UBTService_FollowerEnemy()
{
	bCreateNodeInstance = true;
}

void UBTService_FollowerEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AFollowerAI *EnemyPC = Cast<AFollowerAI>(OwnerComp.GetAIOwner());

	if (EnemyPC)
	{
		bool findTarget = false;

		FVector EnemyLocation = EnemyPC->GetPawn()->GetActorLocation();

		TArray<FHitResult> HitResults;

		if (VTraceSphere(EnemyPC->GetPawn(), EnemyLocation, EnemyLocation + FVector(0, 0, 15), RayCastDistance, HitResults))
		{
			for (int i = 0; i < HitResults.Num(); i++)
			{
				ABCCharacter *Target = Cast<ABCCharacter>(HitResults[i].GetActor());

				if (Target)
				{
					FHitResult HitResult;

					if (VTraceLine(EnemyPC->GetPawn(), EnemyLocation, Target->GetActorLocation(), HitResult))
					{
						ABCCharacter *RealTarget = Cast<ABCCharacter>(HitResult.GetActor());

						if (RealTarget)
						{
							OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->TargetKeyID, HitResults[i].GetActor());

							findTarget = true;

							break;
						}
					}
				}
			}
		}

		if (!findTarget)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->TargetKeyID, NULL);
		}
	}
}