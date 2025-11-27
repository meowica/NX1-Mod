#pragma once

#include "IPhysPreset.h"
#include "IMaterial.h"
#include "ISndAliasList.h"
#include "IWeaponCompleteDef.h"

namespace IVehicleDef
{
	enum VehicleType
	{
		VEH_WHEELS_4,
		VEH_TANK,
		VEH_TANK_WHEELS_4,
		VEH_PLANE,
		VEH_BOAT,
		VEH_ARTILLERY,
		VEH_HELICOPTER,
		VEH_SNOWMOBILE,
		VEH_LUNAR_ROVER,
		VEH_TYPE_COUNT,
	};

	enum VehicleAxleType
	{
		VEH_AXLE_FRONT,
		VEH_AXLE_REAR,
		VEH_AXLE_ALL,
		VEH_AXLE_COUNT,
	};

	struct VehiclePhysDef
	{
		int physicsEnabled;
		const char* physPresetName;
		const IPhysPreset::PhysPreset* physPreset;
		const char* accelGraphName;
		VehicleAxleType steeringAxle;
		VehicleAxleType powerAxle;
		VehicleAxleType brakingAxle;
		float topSpeed;
		float reverseSpeed;
		float maxVelocity;
		float maxPitch;
		float maxRoll;
		float suspensionTravelFront;
		float suspensionTravelRear;
		float suspensionStrengthFront;
		float suspensionDampingFront;
		float suspensionStrengthRear;
		float suspensionDampingRear;
		float frictionBraking;
		float frictionCoasting;
		float frictionTopSpeed;
		float frictionSide;
		float frictionSideRear;
		float velocityDependentSlip;
		float rollStability;
		float rollResistance;
		float pitchResistance;
		float yawResistance;
		float uprightStrengthPitch;
		float uprightStrengthRoll;
		float targetAirPitch;
		float airYawTorque;
		float airPitchTorque;
		float minimumMomentumForCollision;
		float collisionLaunchForceScale;
		float wreckedMassScale;
		float wreckedBodyFriction;
		float minimumJoltForNotify;
		float slipThresholdFront;
		float slipThresholdRear;
		float slipFricScaleFront;
		float slipFricScaleRear;
		float slipFricRateFront;
		float slipFricRateRear;
		float slipYawTorque;
	};

	struct VehicleDef
	{
		const char* name;
		VehicleType type;
		const char* useHintString;
		int health;
		int quadBarrel;
		float texScrollScale;
		float topSpeed;
		float accel;
		float rotRate;
		float rotAccel;
		float maxBodyPitch;
		float maxBodyRoll;
		float collisionRadius;
		int enableReticleColoring;
		float fakeBodyAccelPitch;
		float fakeBodyAccelRoll;
		float fakeBodyVelPitch;
		float fakeBodyVelRoll;
		float fakeBodySideVelPitch;
		float fakeBodyPitchStrength;
		float fakeBodyRollStrength;
		float fakeBodyPitchDampening;
		float fakeBodyRollDampening;
		float fakeBodyBoatRockingAmplitude;
		float fakeBodyBoatRockingPeriod;
		float fakeBodyBoatRockingRotationPeriod;
		float fakeBodyBoatRockingFadeoutSpeed;
		float boatBouncingMinForce;
		float boatBouncingMaxForce;
		float boatBouncingRate;
		float boatBouncingFadeinSpeed;
		float boatBouncingFadeoutSteeringAngle;
		float collisionDamage;
		float collisionSpeed;
		float killcamOffset[3];
		int playerProtected;
		int bulletDamage;
		int armorPiercingDamage;
		int grenadeDamage;
		int projectileDamage;
		int projectileSplashDamage;
		int heavyExplosiveDamage;
		int hasSplitShrouds;
		float shroudTravelUp;
		float shroudTravelDown;
		VehiclePhysDef vehPhysDef;
		float boostDuration;
		float boostRechargeTime;
		float boostAcceleration;
		float suspensionTravel;
		float maxSteeringAngle;
		float steeringLerp;
		float minSteeringScale;
		float minSteeringSpeed;
		int camLookEnabled;
		float camLerp;
		float camPitchInfluence;
		float camRollInfluence;
		float camFovIncrease;
		float camFovOffset;
		float camFovSpeed;
		const char* turretWeaponName;
		IWeaponCompleteDef::WeaponCompleteDef* turretWeapon;
		float turretHorizSpanLeft;
		float turretHorizSpanRight;
		float turretVertSpanUp;
		float turretVertSpanDown;
		float turretRotRate;
		ISndAliasList::SndAliasList* turretSpinSnd;
		ISndAliasList::SndAliasList* turretStopSnd;
		int trophyEnabled;
		int trophyIsTurret;
		float trophyRadius;
		float trophyInactiveRadius;
		int trophyAmmoCount;
		float trophyReloadTime;
		float trophyMaximumAngle;
		unsigned char trophyTags[4];
		IMaterial::Material* compassFriendlyIcon;
		IMaterial::Material* compassEnemyIcon;
		int compassIconWidth;
		int compassIconHeight;
		IMaterial::Material* nx_compassFriendlyIcon;
		IMaterial::Material* nx_compassEnemyIcon;
		int nx_compassIconWidth;
		int nx_compassIconHeight;
		ISndAliasList::SndAliasList* idleLowSnd;
		ISndAliasList::SndAliasList* idleHighSnd;
		ISndAliasList::SndAliasList* engineLowSnd;
		ISndAliasList::SndAliasList* engineHighSnd;
		float engineSndSpeed;
		ISndAliasList::SndAliasList* engineStartUpSnd;
		int engineStartUpLength;
		ISndAliasList::SndAliasList* engineShutdownSnd;
		ISndAliasList::SndAliasList* engineIdleSnd;
		ISndAliasList::SndAliasList* engineSustainSnd;
		ISndAliasList::SndAliasList* engineRampUpSnd;
		int engineRampUpLength;
		ISndAliasList::SndAliasList* engineRampDownSnd;
		int engineRampDownLength;
		ISndAliasList::SndAliasList* suspensionSoftSnd;
		float suspensionSoftCompression;
		ISndAliasList::SndAliasList* suspensionHardSnd;
		float suspensionHardCompression;
		ISndAliasList::SndAliasList* collisionSnd;
		float collisionBlendSpeed;
		ISndAliasList::SndAliasList* speedSnd;
		float speedSndBlendSpeed;
		const char* surfaceSndPrefix;
		ISndAliasList::SndAliasList* surfaceSnds[31];
		float surfaceSndBlendSpeed;
		float speedOfSound;
		int useDoppler;
		float slideVolume;
		float slideBlendSpeed;
		float inAirPitch;
	};

#ifdef IS_MP
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif IS_SP
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
