// Shoot Them Up Game. All Rights Reserved


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUBaseCharacter, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	check(SpringArmComponent);
	check(GetRootComponent());
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	check(CameraComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	check(HealthComponent);
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	check(HealthTextComponent);
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

float ASTUBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	
	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetCharacterMovement());
	MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
	OnHealthChanged(HealthComponent->GetHealth());
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	TakeDamage(0.1f, FDamageEvent(), Controller, this);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::RunReleased);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
	if (isRunning) return;

	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::RunPressed()
{
	if (!IsMovingForward) return;

	isRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed * MoveSpeedMultiplier;
	UE_LOG(LogSTUBaseCharacter, Error, TEXT("Shift is pressed. MaxWalkSpeed = %f"), GetCharacterMovement()->MaxWalkSpeed);
}

void ASTUBaseCharacter::RunReleased()
{
	isRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
//	UE_LOG(LogSTUBaseCharacter, Error, TEXT("Shift is Released. MaxWalkSpeed = %f"), GetCharacterMovement()->MaxWalkSpeed);
}

void ASTUBaseCharacter::OnDeath()
{
	UE_LOG(LogSTUBaseCharacter, Error, TEXT("Character %s is DEAD!"), *GetName());

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);
}

void ASTUBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Health)));
}

