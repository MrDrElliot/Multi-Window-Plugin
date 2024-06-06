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

#include "Subsystem/MultiWindowSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Windows/MW_Window.h"

DEFINE_LOG_CATEGORY(LogMultiWindow);

void UMultiWindowSubsystem::Deinitialize()
{
	for (auto KVP : ActiveWindows)
	{
		KVP.Value->Shutdown();
	}
	
	Super::Deinitialize();
}

UMW_Window* UMultiWindowSubsystem::CreateMultiWindow(FName InTitle, UUserWidget* Widget, EMultiWidgetDependencyType DependencyType, FVector2D WindowPosition, FVector2D WindowSize, UObject* DependencyObject, EBPSizingRule SizingRule, bool bSupportsMaximize, bool bSupportsMinimize)
{
	UMW_Window* NewWindow = NewObject<UMW_Window>(Get(), UMW_Window::StaticClass());
	NewWindow->WindowTitle = InTitle;
	NewWindow->WindowPosition = WindowPosition;
	NewWindow->WindowSize = WindowSize;
	NewWindow->SizingRule = SizingRule;
	NewWindow->bSupportsMaximize = bSupportsMaximize;
	NewWindow->bSupportsMinimize = bSupportsMinimize;
	NewWindow->DependencyType = DependencyType;
	NewWindow->DependencyObject = DependencyObject;
	NewWindow->Init();
	
	ActiveWindows.Add(InTitle, NewWindow);

	if(IsValid(Widget))
	{
		AddWidgetToWindow(NewWindow, Widget);
	}
	
	return NewWindow;
}

bool UMultiWindowSubsystem::ShutdownWindowByName(FName WindowTitle)
{
	if(UMW_Window* Window = ActiveWindows.FindRef(WindowTitle))
	{
		Window->Shutdown();
		ActiveWindows.Remove(WindowTitle);
		return true;
	}
	return false;
}

bool UMultiWindowSubsystem::ShutdownWindowByObjectReference(UMW_Window* Window)
{
	Window->Shutdown();
	ActiveWindows.Remove(Window->WindowTitle);

	return true;
}

UMW_Window* UMultiWindowSubsystem::AddWidgetToWindow(UMW_Window* InWindow, UUserWidget* InWidget)
{
	InWindow->AddWidgetToWindow(InWidget);
	return InWindow;
}

bool UMultiWindowSubsystem::IsWindowActive(FName Name) const
{
	return ActiveWindows.Contains(Name);
}

void UMultiWindowSubsystem::NotifyWindowClosedExternally_Internal(const UMW_Window* Window, bool bForced)
{
	ActiveWindows.Remove(Window->WindowTitle);

	UE_LOG(LogMultiWindow, Verbose, TEXT("Window: [%s] closing from external sources..."), *Window->WindowTitle.ToString());
}
