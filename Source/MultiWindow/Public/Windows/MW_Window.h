/*
MIT License

Copyright (c) DrElliot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
