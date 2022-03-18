// Shoot Them Up Game. All Rights Reserved


#include "Player/STU_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/WeaponComponent.h"

ASTU_PlayerCharacter::ASTU_PlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTU_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(SpringArmComponent);
	check(CameraComponent);

	check(GetCharacterMovement());
	MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ASTU_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTU_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTU_PlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTU_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTU_PlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTU_PlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTU_PlayerCharacter::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTU_PlayerCharacter::RunReleased);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::FireStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::FireStop);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
}


void ASTU_PlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;

	if (IsRunning() && !IsMovingForward) RunReleased();

	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTU_PlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTU_PlayerCharacter::RunPressed()
{
	IsAboutToRun = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed * MoveSpeedMultiplier;
}

void ASTU_PlayerCharacter::RunReleased()
{
	IsAboutToRun = false;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void ASTU_PlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}