#pragma once

#include "RTSPluginPrivatePCH.h"

#include "GameFramework/Actor.h"

#include "RTSProjectile.generated.h"


class UProjectileMovementComponent;


/**
* Projectile with RTS features, such as following a target and dealing damage.
*/
UCLASS()
class ARTSProjectile : public AActor
{
	GENERATED_BODY()

public:
	/** Squared distance at which this projectile is detonated, in cm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS")
	float ImpactThresholdSquared;


	ARTSProjectile();


	/** Locks on to the specified target, dealing damage on impact. */
	UFUNCTION(BlueprintCallable)
	void FireAt(AActor* Target, float Damage, TSubclassOf<class UDamageType> DamageType, AController* EventInstigator, AActor* DamageCauser);

	virtual void Tick(float DeltaSeconds) override;


	/** Event when this projectile hits its target. */
	virtual void NotifyOnProjectileDetonated(AActor* Target, float Damage, TSubclassOf<class UDamageType> DamageType, AController* EventInstigator, AActor* DamageCauser);

	/** Event when this projectile hits its target. */
	UFUNCTION(BlueprintImplementableEvent, Category = "RTS", meta = (DisplayName = "OnProjectileDetonated"))
	void ReceiveOnProjectileDetonated(AActor* Target, float Damage, TSubclassOf<class UDamageType> DamageType, AController* EventInstigator, AActor* DamageCauser);

private:
	AActor* Target;
	float Damage;
	TSubclassOf<class UDamageType> DamageType;
	AController* EventInstigator;
	AActor* DamageCauser;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
};