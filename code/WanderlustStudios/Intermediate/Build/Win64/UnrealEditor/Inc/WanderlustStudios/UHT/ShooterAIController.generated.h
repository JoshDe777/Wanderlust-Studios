// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Shooter/AI/ShooterAIController.h"

#ifdef WANDERLUSTSTUDIOS_ShooterAIController_generated_h
#error "ShooterAIController.generated.h already included, missing '#pragma once' in ShooterAIController.h"
#endif
#define WANDERLUSTSTUDIOS_ShooterAIController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
struct FAIStimulus;

// ********** Begin Class AShooterAIController *****************************************************
#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnPerceptionForgotten); \
	DECLARE_FUNCTION(execOnPerceptionUpdated); \
	DECLARE_FUNCTION(execOnPawnDeath);


struct Z_Construct_UClass_AShooterAIController_Statics;
WANDERLUSTSTUDIOS_API UClass* Z_Construct_UClass_AShooterAIController(ETypeConstructPhase);

#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_22_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AShooterAIController_Statics; \
	friend WANDERLUSTSTUDIOS_API UClass* ::Z_Construct_UClass_AShooterAIController(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AShooterAIController, AAIController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/WanderlustStudios"), Z_Construct_UClass_AShooterAIController) \
	DECLARE_SERIALIZER(AShooterAIController)


#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AShooterAIController(AShooterAIController&&) = delete; \
	AShooterAIController(const AShooterAIController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShooterAIController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShooterAIController); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AShooterAIController) \
	NO_API virtual ~AShooterAIController();


#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_19_PROLOG
#define FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_22_INCLASS_NO_PURE_DECLS \
	FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AShooterAIController;

// ********** End Class AShooterAIController *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_repositories_personal_Wanderlust_Studios_code_WanderlustStudios_Source_WanderlustStudios_Variant_Shooter_AI_ShooterAIController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
