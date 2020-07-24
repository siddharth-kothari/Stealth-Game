// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "FPSAIGuard.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicious,

	Alerted
};
UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	UFUNCTION()
	void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;

	UFUNCTION()
	void OnRep_GuardState();

	UFUNCTION()
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category="AI")
	void OnStateChanged(EAIState NewState);

	UPROPERTY(EditDefaultsOnly, Category="AI")
	bool bPatrol;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta = (EditCondition = "bPatrol"))
	AActor* FirstPatrolPoint;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;
	
	AActor* CurrentpatrolPoint;

	void MoveToNextPatrolPoint();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
