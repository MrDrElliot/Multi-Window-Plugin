// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/K2Node_MultiWindowNode.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "Subsystem/MultiWindowSubsystem.h"

void UK2Node_MultiWindowNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);
	

	if(const UClass* TargetClass = UMultiWindowSubsystem::StaticClass())
	{
		if (TargetClass && ActionRegistrar.IsOpenForRegistration(TargetClass))
		{
			for (TFieldIterator<UFunction> FuncIt(TargetClass, EFieldIteratorFlags::IncludeSuper); FuncIt; ++FuncIt)
			{
				UFunction* Function = *FuncIt;
				if (Function && Function->HasMetaData(TEXT("MultiWindow")))
				{
					UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create<UK2Node_MultiWindowNode>(Function);
					check(Spawner);
					Spawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateWeakLambda(this, [Function](UEdGraphNode* InNode, bool bInIsTemplate)
					{
						UK2Node_MultiWindowNode* NodeReference = CastChecked<UK2Node_MultiWindowNode>(InNode);
						NodeReference->FunctionReference.SetFromField<UFunction>(Function, false);
					});
				

					ActionRegistrar.AddBlueprintAction(TargetClass, Spawner);
				}
			}
		}
	}
}

FText UK2Node_MultiWindowNode::GetFunctionContextString() const
{
	return FText::FromString("Multi Window");

}
