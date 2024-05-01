// Fill out your copyright notice in the Description page of Project Settings.


#include "F1Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AF1Character::AF1Character()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 90.f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		meshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin_Female.SK_Mannequin_Female'"));
	GetMesh()->SetSkeletalMesh(meshAsset.Object);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance> animClass(
		TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'")
	);
	GetMesh()->SetAnimInstanceClass(animClass.Class);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 600.f;
	CameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraArm->SetUsingAbsoluteRotation(true);
	CameraArm->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>(TEXT("CursorToWorld"));
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> decalAsset(
		TEXT("Material'/Game/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	CursorToWorld->SetDecalMaterial(decalAsset.Object);
	CursorToWorld->DecalSize = FVector(16.f, 32.f, 32.f);
	CursorToWorld->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	
}

// Called when the game starts or when spawned
void AF1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AF1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* pc = Cast<APlayerController>(GetController());
	if (pc)
	{
		FHitResult traceHitResult;
		pc->GetHitResultUnderCursor(ECC_Visibility, true, traceHitResult);
		FVector CursorFV = traceHitResult.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();

		CursorToWorld->SetWorldLocation(traceHitResult.Location);
		CursorToWorld->SetWorldRotation(CursorR);
	}

}


