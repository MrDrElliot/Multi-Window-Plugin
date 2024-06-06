// Copyright 2023 TheOtherSideGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/MultiWindowSubsystem.h"
#include "UObject/Object.h"
#include "MW_Window.generated.h"

enum class EMultiWidgetDependencyType : uint8;
enum class EBPSizingRule : uint8;

class SMultiWindow;
/**
 * Container Object for a new slate window.
 */
UCLASS(DisplayName = "Multi Window Object", NotBlueprintable)
class MULTIWINDOW_API UMW_Window : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	
	UMW_Window();
	~UMW_Window();

	//~ Begin FTickableGameObjectInterface
	virtual bool IsTickable() const override { return true; }
	virtual bool IsAllowedToTick() const override{ return DependencyType == EMultiWidgetDependencyType::Object && bCurrentlyShuttingDown == false; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual TStatId GetStatId() const override { return TStatId(); }
	virtual void Tick(float DeltaTime) override;
	//~ End FTickableGameObjectInterface

	void Init();
	void Shutdown(bool bForced = false);

	void AddWidgetToWindow(UUserWidget* InWidget);


	TSharedPtr<UUserWidget> UserWidget;
	TSharedPtr<SMultiWindow> SlateWindow;
	FName WindowTitle;
	FVector2D WindowPosition;
	FVector2D WindowSize;
	EBPSizingRule SizingRule;
	bool bSupportsMaximize;
	bool bSupportsMinimize;
	EMultiWidgetDependencyType DependencyType;
	TWeakObjectPtr<> DependencyObject;
	bool bCurrentlyShuttingDown;
};
