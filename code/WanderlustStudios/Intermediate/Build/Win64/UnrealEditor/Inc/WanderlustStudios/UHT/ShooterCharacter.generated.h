// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Shooter/ShooterCharacter.h"

#ifdef WANDERLUSTSTUDIOS_ShooterCharacter_generated_h
#error "ShooterCharacter.generated.h already included, missing '#pragma once' in ShooterCharacter.h"
#endif
#define WANDERLUSTSTUDIOS_ShooterCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AShooterCharacter ********************************************************
#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoSwitchWeapon); \
	DECLARE_FUNCTION(execDoStopFiring); \
	DECLARE_FUNCTION(execDoStartFiring);


#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_CALLBACK_WRAPPERS
struct Z_Construct_UClass_AShooterCharacter_Statics;
WANDERLUSTSTUDIOS_API UClass* Z_Construct_UClass_AShooterCharacter(ETypeConstructPhase);

#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AShooterCharacter_Statics; \
	friend WANDERLUSTSTUDIOS_API UClass* ::Z_Construct_UClass_AShooterCharacter(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AShooterCharacter, AWanderlustStudiosCharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/WanderlustStudios"), Z_Construct_UClass_AShooterCharacter) \
	DECLARE_SERIALIZER(AShooterCharacter) \
	[[deprecated("Do not call _getUObject(), use Cast.")]] virtual UObject* _getUObject() const override { return const_cast<AShooterCharacter*>(this); }


#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AShooterCharacter(AShooterCharacter&&) = delete; \
	AShooterCharacter(const AShooterCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShooterCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShooterCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AShooterCharacter) \
	NO_API virtual ~AShooterCharacter();


#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_23_PROLOG
#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_CALLBACK_WRAPPERS \
	FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_INCLASS_NO_PURE_DECLS \
	FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AShooterCharacter;

// ********** End Class AShooterCharacter **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_ShooterCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
