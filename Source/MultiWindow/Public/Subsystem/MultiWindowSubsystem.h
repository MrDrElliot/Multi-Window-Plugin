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
#include "Subsystems/EngineSubsystem.h"
#include "MultiWindowSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiWindow, Verbose, Verbose);

UENUM(BlueprintType)
enum class EBPSizingRule : uint8
{
	/* The windows size fixed and cannot be resized **/
	FixedSize,

	/** The window size is computed from its content and cannot be resized by users */
	Autosized,

	/** The window can be resized by users */
	UserSized,
};

UENUM(BlueprintType)
enum class EMultiWidgetDependencyType : uint8
{
	Engine,
	Editor,
	World,
	Object,
	PIE,
};

class UMW_Window;
/**
 * Create multiple slate widgets and apply UMG widgets to them, works in both editor and standalone.
 */
UCLASS()
class MULTIWINDOW_API UMultiWindowSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	static UMultiWindowSubsystem* Get() { return GEngine->GetEngineSubsystem<UMultiWindowSubsystem>(); }

	virtual void Deinitialize() override;

	/* Creates a Multi Window and displays it*/
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (AdvancedDisplay = 4))
	UMW_Window* CreateMultiWindow(FName InTitle = "New Window", UUserWidget* Widget = nullptr, EMultiWidgetDependencyType DependencyType = EMultiWidgetDependencyType::World, FVector2D WindowPosition = FVector2D(0.0f, 0.0f), FVector2D WindowSize = FVector2D(800.0f, 600.0f), UObject* DependencyObject = nullptr, EBPSizingRule SizingRule = EBPSizingRule::UserSized, bool bSupportsMaximize = true, bool bSupportsMinimize = true);

	/* Tries to find an active window, and shuts it down */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	bool ShutdownWindowByName(FName WindowTitle);

	/* Directly shuts down a window by object reference */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	bool ShutdownWindowByObjectReference(UMW_Window* Window);

	/* Adds a UMG widget to a Multi Window */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	UMW_Window* AddWidgetToWindow(UMW_Window* InWindow, UUserWidget* InWidget);

	UFUNCTION(BlueprintPure)
	bool IsWindowActive(FName Name) const;


	void NotifyWindowClosedExternally_Internal(const UMW_Window* Window, bool bForced);


private:

	UPROPERTY()
	TMap<FName, UMW_Window*> ActiveWindows;
	
};
