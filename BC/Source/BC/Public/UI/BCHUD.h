// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "BCHUD.generated.h"


/**
 * 
 */
UCLASS()
class ABCHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:
	/** Main HUD update loop. */
	virtual void DrawHUD() override;	
	
protected:
	/** Lighter HUD color. */
	FColor HUDLight;

	/** Darker HUD color. */
	FColor HUDDark;

	/** Floor for automatic hud scaling. */
	static const float MinHudScale;

	/** kills background icon. */
	UPROPERTY()
	FCanvasIcon KillsBg;

	/** Kills icon. */
	UPROPERTY()
	FCanvasIcon KillsIcon;

	/** Wave Number icon. */
	UPROPERTY()
	FCanvasIcon WaveNumIcon;

	/** Bigger killed icon. */
	UPROPERTY()
	FCanvasIcon KilledIcon;

	/** Match timer and player position background icon. */
	UPROPERTY()
	FCanvasIcon TimePlaceBg;

	/** Timer icon. */
	UPROPERTY()
	FCanvasIcon TimerIcon;

	/** Scrap icon. */
	UPROPERTY()
	FCanvasIcon ScrapIcon;

	/** Podium icon. */
	UPROPERTY()
	FCanvasIcon PlaceIcon;

	/** UI scaling factor for other resolutions than Full HD. */
	float ScaleUI;

	/** texture for HUD elements. */
	UPROPERTY()
	UTexture2D* HUDMainTexture;

	/** Texture for HUD elements. */
	UPROPERTY()
	UTexture2D* HUDAssets02Texture;

	/** Texture for Scraps */
	UPROPERTY()
	UTexture2D* HUDAssets03Texture;

	/** Large font - used for ammo display etc. */
	UPROPERTY()
	UFont* BigFont;

	/** Normal font - used for death messages and such. */
	UPROPERTY()
	UFont* NormalFont;

	/** FontRenderInfo enabling casting shadow.s */
	FFontRenderInfo ShadowedFont;

	/** General offset for HUD elements. */
	float Offset;

	/** Draws kills information. */
	void DrawKills();

	/** Draws Wave Number information. */
	void DrawWaveNumber();

	/** Draws the amount of Scrap Collected. */
	void DrawScrapCollected();

	/** Draws match timer and player position. */
	void DrawMatchTimerAndPosition();

	/**
	* Converts floating point seconds to MM:SS string.
	*
	* @param TimeSeconds		The time to get a string for.
	*/
	FString GetTimeString(float TimeSeconds);
};
