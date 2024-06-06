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

#include "Windows/MW_Window.h"

#include "Editor.h"
#include "GameDelegates.h"
#include "Blueprint/UserWidget.h"
#include "Slate/SlateMultiWindow.h"
#include "Subsystem/MultiWindowSubsystem.h"

ESizingRule Convert(const EBPSizingRule SizingRule)
{
	switch (SizingRule)
	{
		case EBPSizingRule::Autosized:		return ESizingRule::Autosized;
		case EBPSizingRule::FixedSize:		return ESizingRule::FixedSize;
		case EBPSizingRule::UserSized:		return ESizingRule::UserSized;
	}
	return ESizingRule::Autosized;
}

UMW_Window::UMW_Window()
	: SizingRule(EBPSizingRule::UserSized), bSupportsMaximize(true), bSupportsMinimize(true), DependencyType(EMultiWidgetDependencyType::Engine), bCurrentlyShuttingDown(false)
{
}

UMW_Window::~UMW_Window()
{
}

void UMW_Window::Tick(float DeltaTime)
{
	if(DependencyType == EMultiWidgetDependencyType::Object)
	{
		if(DependencyObject.IsValid() == false)
		{
			 bCurrentlyShuttingDown = true;
			UMultiWindowSubsystem::Get()->NotifyWindowClosedExternally_Internal(this, true);
		}
	}
}


void UMW_Window::Init()
{
	SlateWindow = SNew(SMultiWindow)
		.WindowTitle(WindowTitle)
		.WindowPosition(WindowPosition)
		.WindowSize(WindowSize)
		.SupportsMaximize(bSupportsMaximize)
		.SupportsMinimize(bSupportsMinimize)
		.SizingRool(Convert(SizingRule));

	SlateWindow->GetOnWindowClosedEvent().AddWeakLambda(this, [this](const TSharedRef<SWindow>& Window)
	{
		UMultiWindowSubsystem::Get()->NotifyWindowClosedExternally_Internal(this, true);
	});

	if(DependencyType == EMultiWidgetDependencyType::World)
	{
		FWorldDelegates::OnWorldBeginTearDown.AddWeakLambda(this, [this](UWorld* World)
		{
			UMultiWindowSubsystem::Get()->ShutdownWindowByObjectReference(this);
		});
	}

	if(DependencyType == EMultiWidgetDependencyType::PIE)
	{
		FGameDelegates::Get().GetEndPlayMapDelegate().AddWeakLambda(this, [this]
		{
			UMultiWindowSubsystem::Get()->ShutdownWindowByObjectReference(this);
		});
	}
	
	FSlateApplication::Get().AddWindow(SlateWindow.ToSharedRef());
}

void UMW_Window::Shutdown(bool bForced)
{
	bCurrentlyShuttingDown = true;
	
	if(bForced == false)
	{
		FSlateApplication::Get().RequestDestroyWindow(SlateWindow.ToSharedRef());
	}
	
	if(UserWidget.IsValid())
	{
		UserWidget->RemoveFromParent();
		UserWidget->ReleaseSlateResources(true);
		UserWidget = nullptr;
	}

	UE_LOG(LogMultiWindow, Verbose, TEXT("Shutdown called on window: [%s]"), *WindowTitle.ToString());
}

void UMW_Window::AddWidgetToWindow(UUserWidget* InWidget)
{
	if (InWidget)
	{
		InWidget->Rename(nullptr, this);
		
		/* Needed something to wrap around the user widget */
		const TSharedPtr<SWidget> WidgetWrapper = SNew(SBox)
			.WidthOverride(WindowSize.X)
			.HeightOverride(WindowSize.Y)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					InWidget->TakeWidget()
				]
			];

		/* Set the Slate widget as the content of the Slate window */
		SlateWindow->SetContent(WidgetWrapper.ToSharedRef());

		/* Make the underlying widget scale to fit the window */
		InWidget->SetAnchorsInViewport(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		InWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
		InWidget->SetDesiredSizeInViewport(FVector2D(1.0f, 1.0f));
	}
}