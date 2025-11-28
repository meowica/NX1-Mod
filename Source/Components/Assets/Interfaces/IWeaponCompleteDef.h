#pragma once

#include "IMaterial.h"
#include "IFxEffectDef.h"
#include "ISndAliasList.h"
#include "IPhysCollmap.h"
#include "ITracerDef.h"
#include "ILaserDef.h"
#include "IXModel.h"

namespace IWeaponCompleteDef
{
	enum ImpactType
	{
		IMPACT_TYPE_NONE,
		IMPACT_TYPE_BULLET_SMALL,
		IMPACT_TYPE_BULLET_LARGE,
		IMPACT_TYPE_BULLET_HEAVY,
		IMPACT_TYPE_BULLET_AP,
		IMPACT_TYPE_BULLET_EXPLODE,
		IMPACT_TYPE_SHOTGUN,
		IMPACT_TYPE_SHOTGUN_EXPLODE,
		IMPACT_TYPE_GRENADE_BOUNCE,
		IMPACT_TYPE_GRENADE_EXPLODE,
		IMPACT_TYPE_ROCKET_EXPLODE,
		IMPACT_TYPE_PROJECTILE_DUD,
		IMPACT_TYPE_LASER,
		IMPACT_TYPE_STREAMGUN,
		IMPACT_TYPE_RAILGUN,
		IMPACT_TYPE_EXPLODE_SML,
		IMPACT_TYPE_EXPLODE_MED,
		IMPACT_TYPE_EXPLODE_LRG,
		IMPACT_TYPE_VACUUM_BULLET_SMALL,
		IMPACT_TYPE_VACUUM_BULLET_LARGE,
		IMPACT_TYPE_VACUUM_BULLET_HEAVY,
		IMPACT_TYPE_VACUUM_BULLET_AP,
		IMPACT_TYPE_VACUUM_BULLET_EXPLODE,
		IMPACT_TYPE_VACUUM_SHOTGUN,
		IMPACT_TYPE_VACUUM_SHOTGUN_EXPLODE,
		IMPACT_TYPE_VACUUM_GRENADE_BOUNCE,
		IMPACT_TYPE_VACUUM_GRENADE_EXPLODE,
		IMPACT_TYPE_VACUUM_ROCKET_EXPLODE,
		IMPACT_TYPE_VACUUM_PROJECTILE_DUD,
		IMPACT_TYPE_VACUUM_LASER,
		IMPACT_TYPE_VACUUM_STREAMGUN,
		IMPACT_TYPE_VACUUM_RAILGUN,
		IMPACT_TYPE_VACUUM_EXPLODE_SML,
		IMPACT_TYPE_VACUUM_EXPLODE_MED,
		IMPACT_TYPE_VACUUM_EXPLODE_LRG,
		IMPACT_TYPE_COUNT,
	};

	enum weapType_t
	{
		WEAPTYPE_BULLET,
		WEAPTYPE_GRENADE,
		WEAPTYPE_PROJECTILE,
		WEAPTYPE_RIOTSHIELD,
		WEAPTYPE_NUM,
	};

	enum weapClass_t
	{
		WEAPCLASS_RIFLE,
		WEAPCLASS_SNIPER,
		WEAPCLASS_MG,
		WEAPCLASS_SMG,
		WEAPCLASS_SPREAD,
		WEAPCLASS_PISTOL,
		WEAPCLASS_MINI,
		WEAPCLASS_GRENADE,
		WEAPCLASS_ROCKETLAUNCHER,
		WEAPCLASS_TURRET,
		WEAPCLASS_THROWINGKNIFE,
		WEAPCLASS_NON_PLAYER,
		WEAPCLASS_NON_PLAYER_SPREAD,
		WEAPCLASS_ITEM,
		WEAPCLASS_NUM,
	};

	enum PenetrateType
	{
		PENETRATE_TYPE_NONE,
		PENETRATE_TYPE_SMALL,
		PENETRATE_TYPE_MEDIUM,
		PENETRATE_TYPE_LARGE,
		PENETRATE_TYPE_COUNT,
	};

	enum weapInventoryType_t
	{
		WEAPINVENTORY_PRIMARY,
		WEAPINVENTORY_OFFHAND,
		WEAPINVENTORY_ITEM ,
		WEAPINVENTORY_ALTMODE,
		WEAPINVENTORY_EXCLUSIVE,
		WEAPINVENTORY_SCAVENGER,
		WEAPINVENTORY_ALTAMMOMODE,
		WEAPINVENTORYCOUNT,
	};

	enum weapFireType_t
	{
		WEAPON_FIRETYPE_FULLAUTO,
		WEAPON_FIRETYPE_CONTINUOUS,
		WEAPON_FIRETYPE_SINGLESHOT,
		WEAPON_FIRETYPE_BURSTFIRE2,
		WEAPON_FIRETYPE_BURSTFIRE3,
		WEAPON_FIRETYPE_BURSTFIRE4,
		WEAPON_FIRETYPE_DOUBLEBARREL,
		WEAPON_FIRETYPECOUNT,
		WEAPON_FIRETYPE_BURSTFIRE_FIRST,
		WEAPON_FIRETYPE_BURSTFIRE_LAST,
		WEAPON_FIRETYPE_BURSTFIRE_FIRST_COUNT,
	};

	enum OffhandClass
	{
		OFFHAND_CLASS_NONE,
		OFFHAND_CLASS_FRAG_GRENADE,
		OFFHAND_CLASS_SMOKE_GRENADE,
		OFFHAND_CLASS_FLASH_GRENADE,
		OFFHAND_CLASS_THROWINGKNIFE,
		OFFHAND_CLASS_GAS,
		OFFHAND_CLASS_EMP,
		OFFHAND_CLASS_LIDAR,
		OFFHAND_CLASS_OTHER,
		OFFHAND_CLASS_COUNT,
	};

	enum weapStance_t
	{
		WEAPSTANCE_STAND,
		WEAPSTANCE_DUCK,
		WEAPSTANCE_PRONE,
		WEAPSTANCE_NUM,
	};

	enum activeReticleType_t
	{
		VEH_ACTIVE_RETICLE_NONE,
		VEH_ACTIVE_RETICLE_PIP_ON_A_STICK,
		VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND,
		VEH_ACTIVE_RETICLE_COUNT,
	};

	enum weaponIconRatioType_t
	{
		WEAPON_ICON_RATIO_1TO1,
		WEAPON_ICON_RATIO_2TO1,
		WEAPON_ICON_RATIO_4TO1,
		WEAPON_ICON_RATIO_COUNT,
	};

	enum ammoCounterClipType_t
	{
		AMMO_COUNTER_CLIP_NONE,
		AMMO_COUNTER_CLIP_MAGAZINE,
		AMMO_COUNTER_CLIP_SHORTMAGAZINE,
		AMMO_COUNTER_CLIP_SHOTGUN,
		AMMO_COUNTER_CLIP_ROCKET,
		AMMO_COUNTER_CLIP_BELTFED,
		AMMO_COUNTER_CLIP_ALTWEAPON,
		AMMO_COUNTER_CLIP_COUNT,
	};

	enum weapOverlayReticle_t
	{
		WEAPOVERLAYRETICLE_NONE,
		WEAPOVERLAYRETICLE_CROSSHAIR,
		WEAPOVERLAYRETICLE_NUM,
	};

	enum WeapOverlayInteface_t
	{
		WEAPOVERLAYINTERFACE_NONE,
		WEAPOVERLAYINTERFACE_JAVELIN,
		WEAPOVERLAYINTERFACE_TURRETSCOPE,
		WEAPOVERLAYINTERFACECOUNT,
	};

	enum weapProjExposion_t
	{
		WEAPPROJEXP_GRENADE,
		WEAPPROJEXP_ROCKET,
		WEAPPROJEXP_FLASHBANG,
		WEAPPROJEXP_NONE,
		WEAPPROJEXP_DUD,
		WEAPPROJEXP_SMOKE,
		WEAPPROJEXP_HEAVY,
		WEAPPROJEXP_BOUNCE,
		WEAPPROJEXP_NUM,
	};

	enum WeapStickinessType
	{
		WEAPSTICKINESS_NONE,
		WEAPSTICKINESS_ALL,
		WEAPSTICKINESS_ALL_ORIENT,
		WEAPSTICKINESS_GROUND,
		WEAPSTICKINESS_GROUND_WITH_YAW,
		WEAPSTICKINESS_KNIFE,
		WEAPSTICKINESS_COUNT,
	};

	enum guidedMissileType_t
	{
		MISSILE_GUIDANCE_NONE,
		MISSILE_GUIDANCE_SIDEWINDER,
		MISSILE_GUIDANCE_HELLFIRE,
		MISSILE_GUIDANCE_JAVELIN,
		MISSILE_GUIDANCE_AIRBURSTGRENADE,
		MISSILE_GUIDANCE_COUNT,
	};

	enum airBurstGrenadeHUD_t
	{
		AIR_BURST_GRENADE_HUD_NONE,
		AIR_BURST_GRENADE_HUD_FULL,
		AIR_BURST_GRENADE_HUD_LITE,
		AIR_BURST_GRENADE_HUD_COUNT,
	};

	struct WeaponDef
	{
		const char* szOverlayName;
		IXModel::XModel** gunXModel;
		IXModel::XModel* handXModel;
		const char** szXAnimsRightHanded;
		const char** szXAnimsLeftHanded;
		const char* szModeName;
		unsigned short* notetrackSoundMapKeys;
		unsigned short* notetrackSoundMapValues;
		unsigned short* notetrackRumbleMapKeys;
		unsigned short* notetrackRumbleMapValues;
		int playerAnimType;
		weapType_t weapType;
		weapClass_t weapClass;
		PenetrateType penetrateType;
		weapInventoryType_t inventoryType;
		weapFireType_t fireType;
		OffhandClass offhandClass;
		weapStance_t stance;
		const IFxEffectDef::FxEffectDef* viewFlashEffect;
		const IFxEffectDef::FxEffectDef* worldFlashEffect;
		ISndAliasList::SndAliasList* pickupSound;
		ISndAliasList::SndAliasList* pickupSoundPlayer;
		ISndAliasList::SndAliasList* ammoPickupSound;
		ISndAliasList::SndAliasList* ammoPickupSoundPlayer;
		ISndAliasList::SndAliasList* projectileSound;
		ISndAliasList::SndAliasList* pullbackSound;
		ISndAliasList::SndAliasList* pullbackSoundPlayer;
		ISndAliasList::SndAliasList* fireSound;
		ISndAliasList::SndAliasList* fireSoundPlayer;
		ISndAliasList::SndAliasList* fireSoundPlayerAkimbo;
		ISndAliasList::SndAliasList* fireStartSound;
		ISndAliasList::SndAliasList* fireStartSoundPlayer;
		ISndAliasList::SndAliasList* fireLoopSound;
		ISndAliasList::SndAliasList* fireLoopSoundPlayer;
		ISndAliasList::SndAliasList* fireStopSound;
		ISndAliasList::SndAliasList* fireStopSoundPlayer;
		ISndAliasList::SndAliasList* fireLastSound;
		ISndAliasList::SndAliasList* fireLastSoundPlayer;
		ISndAliasList::SndAliasList* emptyFireSound;
		ISndAliasList::SndAliasList* emptyFireSoundPlayer;
		ISndAliasList::SndAliasList* fireSoundVacuum;
		ISndAliasList::SndAliasList* fireSoundPlayerVacuum;
		ISndAliasList::SndAliasList* fireSoundPlayerAkimboVacuum;
		ISndAliasList::SndAliasList* fireStartSoundVacuum;
		ISndAliasList::SndAliasList* fireStartSoundPlayerVacuum;
		ISndAliasList::SndAliasList* fireLoopSoundVacuum;
		ISndAliasList::SndAliasList* fireLoopSoundPlayerVacuum;
		ISndAliasList::SndAliasList* fireStopSoundVacuum;
		ISndAliasList::SndAliasList* fireStopSoundPlayerVacuum;
		ISndAliasList::SndAliasList* fireLastSoundVacuum;
		ISndAliasList::SndAliasList* fireLastSoundPlayerVacuum;
		ISndAliasList::SndAliasList* emptyFireSoundVacuum;
		ISndAliasList::SndAliasList* emptyFireSoundPlayerVacuum;
		ISndAliasList::SndAliasList* meleeSwipeSound;
		ISndAliasList::SndAliasList* meleeSwipeSoundPlayer;
		ISndAliasList::SndAliasList* meleeHitSound;
		ISndAliasList::SndAliasList* meleeMissSound;
		ISndAliasList::SndAliasList* rechamberSound;
		ISndAliasList::SndAliasList* rechamberSoundPlayer;
		ISndAliasList::SndAliasList* reloadSound;
		ISndAliasList::SndAliasList* reloadSoundPlayer;
		ISndAliasList::SndAliasList* reloadEmptySound;
		ISndAliasList::SndAliasList* reloadEmptySoundPlayer;
		ISndAliasList::SndAliasList* reloadStartSound;
		ISndAliasList::SndAliasList* reloadStartSoundPlayer;
		ISndAliasList::SndAliasList* reloadEndSound;
		ISndAliasList::SndAliasList* reloadEndSoundPlayer;
		ISndAliasList::SndAliasList* rechargeSound;
		ISndAliasList::SndAliasList* rechargeSoundPlayer;
		ISndAliasList::SndAliasList* rechargeStartSound;
		ISndAliasList::SndAliasList* rechargeStartSoundPlayer;
		ISndAliasList::SndAliasList* rechargeEndSound;
		ISndAliasList::SndAliasList* rechargeEndSoundPlayer;
		ISndAliasList::SndAliasList* detonateSound;
		ISndAliasList::SndAliasList* detonateSoundPlayer;
		ISndAliasList::SndAliasList* nightVisionWearSound;
		ISndAliasList::SndAliasList* nightVisionWearSoundPlayer;
		ISndAliasList::SndAliasList* nightVisionRemoveSound;
		ISndAliasList::SndAliasList* nightVisionRemoveSoundPlayer;
		ISndAliasList::SndAliasList* altSwitchSound;
		ISndAliasList::SndAliasList* altSwitchSoundPlayer;
		ISndAliasList::SndAliasList* raiseSound;
		ISndAliasList::SndAliasList* raiseSoundPlayer;
		ISndAliasList::SndAliasList* firstRaiseSound;
		ISndAliasList::SndAliasList* firstRaiseSoundPlayer;
		ISndAliasList::SndAliasList* putawaySound;
		ISndAliasList::SndAliasList* putawaySoundPlayer;
		ISndAliasList::SndAliasList* scanSound;
		ISndAliasList::SndAliasList** bounceSound;
		const IFxEffectDef::FxEffectDef* viewShellEjectEffect;
		const IFxEffectDef::FxEffectDef* worldShellEjectEffect;
		const IFxEffectDef::FxEffectDef* viewLastShotEjectEffect;
		const IFxEffectDef::FxEffectDef* worldLastShotEjectEffect;
		IMaterial::Material* laserMaterial;
		IMaterial::Material* laserEndPointMaterial;
		IMaterial::Material* reticleCenter;
		IMaterial::Material* reticleSide;
		int iReticleCenterSize;
		int iReticleSideSize;
		int iReticleMinOfs;
		activeReticleType_t activeReticleType;
		IMaterial::Material* remoteTurretReticleSide;
		IMaterial::Material* remoteTurretLockOnReticle;
		IMaterial::Material* remoteTurretOutOfSightReticle;
		int remoteTurretReticleSideSize;
		int remoteTurretLockOnReticleSize;
		int remoteTurretOutOfSightReticleSize;
		int remoteTurretReticleMinOfs;
		float remoteTurretReticleSidePos;
		bool useRemoteTurretReticle;
		float vStandMove[3];
		float vStandRot[3];
		float strafeMove[3];
		float strafeRot[3];
		float vDuckedOfs[3];
		float vDuckedMove[3];
		float vDuckedRot[3];
		float vProneOfs[3];
		float vProneMove[3];
		float vProneRot[3];
		float fPosMoveRate;
		float fPosProneMoveRate;
		float fStandMoveMinSpeed;
		float fDuckedMoveMinSpeed;
		float fProneMoveMinSpeed;
		float fPosRotRate;
		float fPosProneRotRate;
		float fStandRotMinSpeed;
		float fDuckedRotMinSpeed;
		float fProneRotMinSpeed;
		float vDtpOfs[3];
		float vDtpRot[3];
		float vDtpBob[2];
		float fDtpCycleScale;
		IXModel::XModel** worldModel;
		IXModel::XModel* worldClipModel;
		IXModel::XModel* rocketModel;
		IXModel::XModel* knifeModel;
		IXModel::XModel* worldKnifeModel;
		IMaterial::Material* hudIcon;
		weaponIconRatioType_t hudIconRatio;
		IMaterial::Material* pickupIcon;
		weaponIconRatioType_t pickupIconRatio;
		IMaterial::Material* ammoCounterIcon;
		weaponIconRatioType_t ammoCounterIconRatio;
		ammoCounterClipType_t ammoCounterClip;
		int iStartAmmo;
		const char* szAmmoName;
		int iAmmoIndex;
		const char* szClipName;
		int iClipIndex;
		int iMaxAmmo;
		int shotCount;
		const char* szSharedAmmoCapName;
		int iSharedAmmoCapIndex;
		int iSharedAmmoCap;
		int damage;
		int playerDamage;
		int iMeleeDamage;
		int iDamageType;
		int iFireDelay;
		int iMeleeDelay;
		int meleeChargeDelay;
		int iDetonateDelay;
		int iRechamberTime;
		int rechamberTimeOneHanded;
		int iRechamberBoltTime;
		int iHoldFireTime;
		int iDetonateTime;
		int iMeleeTime;
		int meleeChargeTime;
		int iReloadTime;
		int reloadShowRocketTime;
		int iReloadEmptyTime;
		int iReloadAddTime;
		int iReloadStartTime;
		int iReloadBulletAnimTime;
		int iReloadStartAddTime;
		int iReloadEndTime;
		int iDropTime;
		int iRaiseTime;
		int iAltDropTime;
		int quickDropTime;
		int quickRaiseTime;
		int iBreachRaiseTime;
		int iEmptyRaiseTime;
		int iEmptyDropTime;
		int sprintInTime;
		int sprintLoopTime;
		int sprintOutTime;
		int stunnedTimeBegin;
		int stunnedTimeLoop;
		int stunnedTimeEnd;
		int nightVisionWearTime;
		int nightVisionWearTimeFadeOutEnd;
		int nightVisionWearTimePowerUp;
		int nightVisionRemoveTime;
		int nightVisionRemoveTimePowerDown;
		int nightVisionRemoveTimeFadeInStart;
		int fuseTime;
		int aiFuseTime;
		int contFireInTime;
		int contFireOutTime;
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
		float aimPadding;
		float enemyCrosshairRange;
		float moveSpeedScale;
		float adsMoveSpeedScale;
		float sprintDurationScale;
		float fAdsZoomInFrac;
		float fAdsZoomOutFrac;
		IMaterial::Material* overlayMaterial;
		IMaterial::Material* overlayMaterialLowRes;
		IMaterial::Material* overlayMaterialEMP;
		IMaterial::Material* overlayMaterialEMPLowRes;
		weapOverlayReticle_t overlayReticle;
		WeapOverlayInteface_t overlayInterface;
		float overlayWidth;
		float overlayHeight;
		float overlayWidthSplitscreen;
		float overlayHeightSplitscreen;
		float fAdsBobFactor;
		float fAdsViewBobMult;
		float fHipSpreadStandMin;
		float fHipSpreadDuckedMin;
		float fHipSpreadProneMin;
		float hipSpreadStandMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float fHipSpreadDecayRate;
		float fHipSpreadFireAdd;
		float fHipSpreadTurnAdd;
		float fHipSpreadMoveAdd;
		float fHipSpreadDuckedDecay;
		float fHipSpreadProneDecay;
		float fHipReticleSidePos;
		float fAdsIdleAmount;
		float fHipIdleAmount;
		float adsIdleSpeed;
		float hipIdleSpeed;
		float fIdleCrouchFactor;
		float fIdleProneFactor;
		float fGunMaxPitch;
		float fGunMaxYaw;
		float adsIdleLerpStartTime;
		float adsIdleLerpTime;
		float swayMaxAngle;
		float swayLerpSpeed;
		float swayPitchScale;
		float swayYawScale;
		float swayHorizScale;
		float swayVertScale;
		float swayShellShockScale;
		float adsSwayMaxAngle;
		float adsSwayLerpSpeed;
		float adsSwayPitchScale;
		float adsSwayYawScale;
		float adsSwayHorizScale;
		float adsSwayVertScale;
		float adsViewErrorMin;
		float adsViewErrorMax;
		IPhysCollmap::PhysCollmap* physCollmap;
		float dualWieldViewModelOffset;
		weaponIconRatioType_t killIconRatio;
		int iReloadAmmoAdd;
		int iReloadStartAdd;
		int ammoDropStockMin;
		int ammoDropClipPercentMin;
		int ammoDropClipPercentMax;
		int ammoRechargeTime;
		int ammoRechargeAmount;
		int ammoRechargeDelay;
		int iExplosionRadius;
		int iExplosionRadiusMin;
		int iExplosionInnerDamage;
		int iExplosionOuterDamage;
		float damageConeAngle;
		float bulletExplDmgMult;
		float bulletExplRadiusMult;
		int iProjectileSpeed;
		int iProjectileSpeedUp;
		int iProjectileSpeedForward;
		int iProjectileActivateDist;
		float projLifetime;
		float timeToAccelerate;
		float projectileCurvature;
		IXModel::XModel* projectileModel;
		weapProjExposion_t projExplosion;
		const IFxEffectDef::FxEffectDef* projExplosionEffect;
		const IFxEffectDef::FxEffectDef* projDudEffect;
		ISndAliasList::SndAliasList* projExplosionSound;
		ISndAliasList::SndAliasList* projDudSound;
		ISndAliasList::SndAliasList* projExplosionSoundVacuum;
		ISndAliasList::SndAliasList* projDudSoundVacuum;
		WeapStickinessType stickiness;
		float lowAmmoWarningThreshold;
		float ricochetChance;
		float grenadeAirBurstTraceOffset;
		float grenadeAirBurstTraceRange;
		float grenadeAirBurstExtraDistance;
		float* parallelBounce;
		float* perpendicularBounce;
		const IFxEffectDef::FxEffectDef* projTrailEffect;
		const IFxEffectDef::FxEffectDef* projBeaconEffect;
		float vProjectileColor[3];
		guidedMissileType_t guidedMissileType;
		float maxSteeringAccel;
		int projIgnitionDelay;
		const IFxEffectDef::FxEffectDef* projIgnitionEffect;
		ISndAliasList::SndAliasList* projIgnitionSound;
		float fAdsAimPitch;
		float fAdsCrosshairInFrac;
		float fAdsCrosshairOutFrac;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float fAdsGunKickPitchMin;
		float fAdsGunKickPitchMax;
		float fAdsGunKickYawMin;
		float fAdsGunKickYawMax;
		float fAdsGunKickAccel;
		float fAdsGunKickSpeedMax;
		float fAdsGunKickSpeedDecay;
		float fAdsGunKickStaticDecay;
		float fAdsViewKickPitchMin;
		float fAdsViewKickPitchMax;
		float fAdsViewKickYawMin;
		float fAdsViewKickYawMax;
		float fAdsViewScatterMin;
		float fAdsViewScatterMax;
		float fAdsSpread;
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float fHipGunKickPitchMin;
		float fHipGunKickPitchMax;
		float fHipGunKickYawMin;
		float fHipGunKickYawMax;
		float fHipGunKickAccel;
		float fHipGunKickSpeedMax;
		float fHipGunKickSpeedDecay;
		float fHipGunKickStaticDecay;
		float fHipViewKickPitchMin;
		float fHipViewKickPitchMax;
		float fHipViewKickYawMin;
		float fHipViewKickYawMax;
		float fHipViewScatterMin;
		float fHipViewScatterMax;
		float fightDist;
		float maxDist;
		const char *accuracyGraphName[2];
		float(*originalAccuracyGraphKnots[2])[2];
		unsigned short originalAccuracyGraphKnotCount[2];
		int iPositionReloadTransTime;
		float leftArc;
		float rightArc;
		float topArc;
		float bottomArc;
		float accuracy;
		bool preferManualTarget;
		float aiSpread;
		float playerSpread;
		float minTurnSpeed[2];
		float maxTurnSpeed[2];
		float pitchConvergenceTime;
		float yawConvergenceTime;
		float suppressTime;
		float maxRange;
		float fAnimHorRotateInc;
		float fPlayerPositionDist;
		const char* szUseHintString;
		const char* dropHintString;
		int iUseHintStringIndex;
		int dropHintStringIndex;
		float horizViewJitter;
		float vertViewJitter;
		float scanSpeed;
		float scanAccel;
		int scanPauseTime;
		const char* szScript;
		const char* szScriptModelAmmo;
		float fOOPosAnimLength[2];
		int minDamage;
		int minPlayerDamage;
		int closeDamage;
		float fMinCloseDamageRange;
		float fMaxCloseDamageRange;
		float fMaxDamageRange;
		float fMinDamageRange;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		float* locationDamageMultipliers;
		const char* fireRumble;
		const char* meleeImpactRumble;
		ITracerDef::TracerDef* tracerType;
		ILaserDef::LaserDef* laserType;
		float turretScopeZoomRate;
		float turretScopeZoomMin;
		float turretScopeZoomMax;
		float turretOverheatUpRate;
		float turretOverheatDownRate;
		float turretOverheatPenalty;
		ISndAliasList::SndAliasList* turretOverheatSound;
		const IFxEffectDef::FxEffectDef* turretOverheatEffect;
		const char* turretBarrelSpinRumble;
		float turretBarrelSpinSpeed;
		float turretBarrelSpinUpTime;
		float turretBarrelSpinDownTime;
		bool turretBarrelSpinDownAfterEveryShot;
		ISndAliasList::SndAliasList* turretBarrelSpinMaxSnd;
		ISndAliasList::SndAliasList* turretBarrelSpinUpSnd[4];
		ISndAliasList::SndAliasList* turretBarrelSpinDownSnd[4];
		ISndAliasList::SndAliasList* missileConeSoundAlias;
		ISndAliasList::SndAliasList* missileConeSoundAliasAtBase;
		float missileConeSoundRadiusAtTop;
		float missileConeSoundRadiusAtBase;
		float missileConeSoundHeight;
		float missileConeSoundOriginOffset;
		float missileConeSoundVolumescaleAtCore;
		float missileConeSoundVolumescaleAtEdge;
		float missileConeSoundVolumescaleCoreSize;
		float missileConeSoundPitchAtTop;
		float missileConeSoundPitchAtBottom;
		float missileConeSoundPitchTopSize;
		float missileConeSoundPitchBottomSize;
		float missileConeSoundCrossfadeTopSize;
		float missileConeSoundCrossfadeBottomSize;
		float laserBeamRadius;
		float laserEndPointRadius;
		bool sharedAmmo;
		bool lockonSupported;
		bool requireLockonToFire;
		bool bigExplosion;
		bool noAdsWhenMagEmpty;
		bool avoidDropCleanup;
		bool inheritsPerks;
		bool showLaserWhileFiring;
		bool useContinuousAudio;
		bool crosshairColorChange;
		bool bRifleBullet;
		bool armorPiercing;
		bool bBoltAction;
		bool disableBob;
		bool overheats;
		bool aimDownSight;
		bool bRechamberWhileAds;
		bool bBulletExplosiveDamage;
		bool bCookOffHold;
		bool bClipOnly;
		bool noAmmoPickup;
		bool adsFireOnly;
		bool cancelAutoHolsterWhenEmpty;
		bool disableSwitchToWhenEmpty;
		bool suppressAmmoReserveDisplay;
		bool ammoRecharges;
		bool laserSightDuringNightvision;
		bool markableViewmodel;
		bool noDualWield;
		bool flipKillIcon;
		bool bNoPartialReload;
		bool bSegmentedReload;
		bool blocksProne;
		bool silenced;
		bool isRollingGrenade;
		bool explodesOnGround;
		bool projExplosionEffectForceNormalUp;
		bool bProjImpactExplode;
		bool stickToPlayers;
		bool hasDetonator;
		bool disableFiring;
		bool timedDetonation;
		bool projectileCrumples;
		bool rotate;
		bool holdButtonToThrow;
		bool freezeMovementWhenFiring;
		bool thermalScope;
		bool xRay;
		bool altModeSameWeapon;
		bool turretBarrelSpinEnabled;
		bool missileConeSoundEnabled;
		bool missileConeSoundPitchshiftEnabled;
		bool missileConeSoundCrossfadeEnabled;
		bool offhandHoldIsCancelable;
		airBurstGrenadeHUD_t airBurstGrenadeHUD;
		int dtpInTime;
		int dtpLoopTime;
		int dtpOutTime;
		float xrayConeAngle;
		float xrayConeLength;
		bool doGibbing;
		float maxGibDistance;
	};

	struct WeaponCompleteDef
	{
		const char* szInternalName;
		WeaponDef* weapDef;
		const char* szDisplayName;
		unsigned short* hideTags;
		const char** szXAnims;
		float fAdsZoomFov;
		int iAdsTransInTime;
		int iAdsTransOutTime;
		int iClipSize;
		ImpactType impactType;
		int iFireTime;
		float shotsPerSecondAi;
		weaponIconRatioType_t dpadIconRatio;
		float penetrateMultiplier;
		float fAdsViewKickCenterSpeed;
		float fHipViewKickCenterSpeed;
		const char* szAltWeaponName;
		unsigned int altWeaponIndex;
		int iAltRaiseTime;
		IMaterial::Material* killIcon;
		IMaterial::Material* dpadIcon;
		int fireAnimLength;
		int iFirstRaiseTime;
		int ammoDropStockMax;
		float adsDofStart;
		float adsDofEnd;
		unsigned short accuracyGraphKnotCount[2];
		float(*accuracyGraphKnots[2])[2];
		bool motionTracker;
		bool enhanced;
		bool dpadIconShowsAmmo;
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
