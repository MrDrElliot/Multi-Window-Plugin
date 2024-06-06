// Copyright 2023 TheOtherSideGame. All Rights Reserved.

#pragma once



class SMultiWindow final : public SWindow
{
	SLATE_BEGIN_ARGS(SMultiWindow) {}
	SLATE_ARGUMENT(FName, WindowTitle);
	SLATE_ARGUMENT(FVector2D, WindowPosition);
	SLATE_ARGUMENT(FVector2D, WindowSize);
	SLATE_ARGUMENT(bool, SupportsMaximize);
	SLATE_ARGUMENT(bool, SupportsMinimize);
	SLATE_ARGUMENT(ESizingRule, SizingRool);
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs);


private:

};