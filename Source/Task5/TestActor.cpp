// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"
#include "Engine/Engine.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	float TotalDistance = 0;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Actor has spawned!"));
	}

	SetActorLocation(FVector(0, 50, 0));

	FVector ActorLocation = GetActorLocation();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("시작 위치 Actor : %s"), *ActorLocation.ToString()));
	}

	for (int i = 0; i < 10; ++i)
	{
		FVector CurrentLocation = GetActorLocation();
		TriggerEvent(50);
		FVector NewLocation = GetActorLocation();
		TotalDistance += GetDistance(CurrentLocation, NewLocation);



		FVector RndActorLocation = GetActorLocation();
		FRotator RndActorRotation = GetActorRotation();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Actor : %s"), *RndActorLocation.ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Actor : %s"), *RndActorRotation.ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("%d번째 이동"), MoveCount+RotateCount));
		}

	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Total Move Distance : %f"), TotalDistance));
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("%d번 이동"), MoveCount));
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("%d번 회전"), RotateCount));
	}
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::Move()
{
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + FVector(10.f, 50.f, 0.f);
	SetActorLocation(NewLocation);
	GetDistance(CurrentLocation, NewLocation);
	++MoveCount;
}

void ATestActor::Turn()
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = CurrentRotation + FRotator(0.f, 0.f, 50.f);
	SetActorRotation(NewRotation);
	++RotateCount;
}

void ATestActor::TriggerEvent(float Probability)
{
	int32 RandomValue = FMath::RandRange(1, 100); // 1 ~ 100의 난수 생성
	if (RandomValue < Probability)
	{
		UE_LOG(LogTemp, Log, TEXT("Event Triggered!"));
		Move();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Event Not Triggered"));
		Turn();
	}
}

float ATestActor::GetDistance(FVector first, FVector second)
{
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	return FMath::Sqrt(dx*dx + dy*dy);
}

