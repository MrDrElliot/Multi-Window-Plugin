// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_CallFunction.h"
#include "K2Node_MultiWindowNode.generated.h"


UCLASS()
class UK2Node_MultiWindowNode : public UK2Node_CallFunction
{
	GENERATED_BODY()

	UK2Node_MultiWindowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
	:Super(ObjectInitializer)
	{
	}
	
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(0.0f, 255.0f, 95.0f); }
	virtual FLinearColor GetNodeBodyTintColor() const override { return FLinearColor(0.0f, 255.0f, 125.0f); }
	virtual FLinearColor GetNodeCommentColor() const override { return FLinearColor::Red; }
	virtual FText GetFunctionContextString() const override;
		
};
