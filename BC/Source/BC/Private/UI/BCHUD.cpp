// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "BC/Public/Player/BCPlayerController.h"
#include "BC/Public/UI/BCHUD.h"

const float ABCHUD::MinHudScale = 0.5f;

ABCHUD::ABCHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UI/HUD/HUDMain"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDAssets02TextureOb(TEXT("/Game/UI/HUD/HUDAssets02"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDAssets03TextureOb(TEXT("/Game/UI/HUD/ScrapTags"));

	static ConstructorHelpers::FObjectFinder<UFont> BigFontOb(TEXT("/Game/UI/HUD/Roboto51"));
	static ConstructorHelpers::FObjectFinder<UFont> NormalFontOb(TEXT("/Game/UI/HUD/Roboto18"));
	BigFont = BigFontOb.Object;
	NormalFont = NormalFontOb.Object;


	HUDMainTexture = HUDMainTextureOb.Object;
	HUDAssets02Texture = HUDAssets02TextureOb.Object;
	HUDAssets03Texture = HUDAssets03TextureOb.Object;

	KillsBg = UCanvas::MakeIcon(HUDMainTexture, 15, 16, 235, 62);
	TimePlaceBg = UCanvas::MakeIcon(HUDMainTexture, 550, 16, 255, 62);
	
	KillsIcon = UCanvas::MakeIcon(HUDMainTexture, 318, 93, 24, 24);
	TimerIcon = UCanvas::MakeIcon(HUDMainTexture, 381, 93, 24, 24);
	KilledIcon = UCanvas::MakeIcon(HUDMainTexture, 425, 92, 38, 36);
	PlaceIcon = UCanvas::MakeIcon(HUDMainTexture, 250, 468, 21, 28);
	WaveNumIcon = UCanvas::MakeIcon(HUDMainTexture, 200, 93, 30, 24);
	ScrapIcon = UCanvas::MakeIcon(HUDAssets03Texture, 0, 0, 50, 38);

	Offset = 20.0f;
	HUDLight = FColor(175, 202, 213, 255);
	HUDDark = FColor(110, 124, 131, 255);
	ShadowedFont.bEnableShadow = true;
}

void ABCHUD::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas == nullptr)
	{
		return;
	}
	ScaleUI = Canvas->ClipY / 1080.0f;

	float TextScale = 1.0f;
	// enforce min
	ScaleUI = FMath::Max(ScaleUI, MinHudScale);

	float MessageOffset = (Canvas->ClipY / 4.0)* ScaleUI;

	ABCPlayerController* MyPC = Cast<ABCPlayerController>(PlayerOwner);
	if (MyPC)
	{
		DrawKills();
		DrawWaveNumber();
		DrawScrapCollected();
	}
}

FString ABCHUD::GetTimeString(float TimeSeconds)
{
	// only minutes and seconds are relevant
	const int32 TotalSeconds = FMath::Max(0, FMath::TruncToInt(TimeSeconds) % 3600);
	const int32 NumMinutes = TotalSeconds / 60;
	const int32 NumSeconds = TotalSeconds % 60;

	const FString TimeDesc = FString::Printf(TEXT("%02d:%02d"), NumMinutes, NumSeconds);
	return TimeDesc;
}

void ABCHUD::DrawMatchTimerAndPosition()
{
	//Place Holder
}

void ABCHUD::DrawKills()
{
	ABCPlayerController* MyPC = Cast<ABCPlayerController>(PlayerOwner);


	Canvas->SetDrawColor(FColor::Red);
	float KillsPosX = Canvas->OrgX + Offset * ScaleUI;
	float KillsPosY = Canvas->ClipY - (Offset * ScaleUI + KillsBg.VL);
	Canvas->DrawIcon(KillsBg, KillsPosX, KillsPosY, ScaleUI);

	Canvas->DrawIcon(KillsIcon, KillsPosX + Offset * ScaleUI, KillsPosY + ((KillsBg.VL - KillsIcon.VL) / 2) * ScaleUI, ScaleUI);
	float TextScale = 0.57f;
	FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	TextItem.EnableShadow(FLinearColor::Black);

	float SizeX, SizeY;
	FString Text = "KILLS:";
	Canvas->StrLen(BigFont, Text, SizeX, SizeY);

	TextItem.Text = FText::FromString(Text);
	TextItem.Scale = FVector2D(TextScale * ScaleUI, TextScale * ScaleUI);
	TextItem.FontRenderInfo = ShadowedFont;
	TextItem.SetColor(HUDDark);
	Canvas->DrawItem(TextItem, KillsPosX + Offset * ScaleUI + KillsIcon.UL * 1.5f * ScaleUI,
		KillsPosY + (KillsBg.VL * ScaleUI - SizeY * TextScale * ScaleUI) / 2);

	Text = FString("0");

	TextScale = 0.7f;
	float BoxWidth = 135.0f * ScaleUI;
	Canvas->StrLen(BigFont, Text, SizeX, SizeY);
	TextItem.Text = FText::FromString(Text);
	TextItem.Scale = FVector2D(TextScale * ScaleUI, TextScale * ScaleUI);
	Canvas->DrawItem(TextItem, KillsPosX + KillsBg.UL * ScaleUI - (BoxWidth + SizeX * TextScale * ScaleUI) / 2,
		KillsPosY + (KillsBg.VL* ScaleUI - SizeY * TextScale * ScaleUI) / 2);

}

void ABCHUD::DrawWaveNumber()
{
	ABCPlayerController* MyPC = Cast<ABCPlayerController>(PlayerOwner);
	Canvas->SetDrawColor(FColor::Black);

	float KillsPosX = Canvas->OrgX + Offset * ScaleUI;
	float KillsPosY = Canvas->ClipY - (Offset * ScaleUI + 2 * KillsBg.VL);
	Canvas->DrawIcon(KillsBg, KillsPosX, KillsPosY, ScaleUI);

	Canvas->DrawIcon(WaveNumIcon, KillsPosX + Offset * ScaleUI, KillsPosY + ((KillsBg.VL - KillsIcon.VL) / 2) * ScaleUI, ScaleUI);
	float TextScale = 0.57f;
	FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	TextItem.EnableShadow(FLinearColor::Black);

	float SizeX, SizeY;
	FString Text = "WAVE:";
	Canvas->StrLen(BigFont, Text, SizeX, SizeY);

	TextItem.Text = FText::FromString(Text);
	TextItem.Scale = FVector2D(TextScale * ScaleUI, TextScale * ScaleUI);
	TextItem.FontRenderInfo = ShadowedFont;
	TextItem.SetColor(HUDLight);
	Canvas->DrawItem(TextItem, KillsPosX + Offset * ScaleUI + KillsIcon.UL * 1.5f * ScaleUI,
		KillsPosY + (KillsBg.VL * ScaleUI - SizeY * TextScale * ScaleUI) / 2);

	Text = FString("1");
	TextScale = 0.7f;
	float BoxWidth = 135.0f * ScaleUI;
	Canvas->StrLen(BigFont, Text, SizeX, SizeY);
	TextItem.Text = FText::FromString(Text);
	TextItem.Scale = FVector2D(TextScale * ScaleUI, TextScale * ScaleUI);
	Canvas->DrawItem(TextItem, KillsPosX + KillsBg.UL * ScaleUI - (BoxWidth + SizeX * TextScale * ScaleUI) / 2,
		KillsPosY + (KillsBg.VL* ScaleUI - SizeY * TextScale * ScaleUI) / 2);
}

void ABCHUD::DrawScrapCollected()
{
	Canvas->SetDrawColor(FColor::Black);
	const float ScrapPosX = Canvas->ClipX - Canvas->OrgX - (TimePlaceBg.UL + Offset) * ScaleUI;
	const float ScrapPosY = Canvas->OrgY + Offset * ScaleUI;

	Canvas->DrawIcon(TimePlaceBg, ScrapPosX, ScrapPosY, ScaleUI);

	Canvas->SetDrawColor(FColor::Silver);
	Canvas->DrawIcon(ScrapIcon, ScrapPosX + Offset * ScaleUI, ScrapPosY + ((TimePlaceBg.VL - ScrapIcon.VL) / 2) * ScaleUI, ScaleUI);

	float TextScale = 0.57f;
	FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	TextItem.EnableShadow(FLinearColor::Black);

	float SizeX, SizeY;
	FString Text = "GEARS:";
	Canvas->StrLen(BigFont, Text, SizeX, SizeY);

	TextItem.Text = FText::FromString(Text);
	TextItem.Scale = FVector2D(TextScale * ScaleUI, TextScale * ScaleUI);
	TextItem.FontRenderInfo = ShadowedFont;
	TextItem.SetColor(HUDLight);
	Canvas->DrawItem(TextItem, ScrapPosX + Offset * ScaleUI + ScrapIcon.UL * 1.0f * ScaleUI,
		ScrapPosY + (TimePlaceBg.VL * ScaleUI - SizeY * TextScale * ScaleUI) / 2);

	Text = FString("0");
	TextScale = 0.7f;
	float BoxWidth = 135.0f * ScaleUI;
	Canvas->StrLen(BigFont, Text, SizeX, SizeY);
	TextItem.Text = FText::FromString(Text);
	TextItem.Scale = FVector2D(TextScale * ScaleUI, TextScale * ScaleUI);
	Canvas->DrawItem(TextItem, ScrapPosX + TimePlaceBg.UL * ScaleUI - (BoxWidth + SizeX * TextScale * ScaleUI) / 2,
		ScrapPosY + (TimePlaceBg.VL* ScaleUI - SizeY * TextScale * ScaleUI) / 2);
}