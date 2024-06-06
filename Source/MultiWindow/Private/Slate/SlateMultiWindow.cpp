// Copyright 2023 TheOtherSideGame. All Rights Reserved.


#include "Slate/SlateMultiWindow.h"

void SMultiWindow::Construct(const FArguments& InArgs)
{
	SWindow::Construct(
		SWindow::FArguments()
		.Title(FText::FromName(InArgs._WindowTitle))
		.ScreenPosition(InArgs._WindowPosition)
		.ClientSize(InArgs._WindowSize)
		.SupportsMaximize(InArgs._SupportsMaximize)
		.SupportsMinimize(InArgs._SupportsMinimize)
		.SizingRule(InArgs._SizingRool)
		[
			// Add your UI widgets here
			SNew(SVerticalBox)
		]
	);
}