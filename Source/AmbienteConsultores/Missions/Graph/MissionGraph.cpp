// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionGraph.h"

UMissionGraph::UMissionGraph()
{
	NodeType = TSubclassOf<UMissionNode>();
#if WITH_EDITORONLY_DATA
	bCanRenameNode = true;
	bCanBeCyclical = false;
#endif
}

TArray<UMissionNode*> UMissionGraph::GetOrderedList()
{
	TArray<UMissionNode*> ReturnList;
	check(!RootNodes.IsEmpty())
	UGenericGraphNode* VisitingNode = RootNodes[0];
	while (true)
	{
		ReturnList.Push(Cast<UMissionNode>(VisitingNode));
		if(VisitingNode->ChildrenNodes.Num() > 0)
		{
			VisitingNode = VisitingNode->ChildrenNodes[0];
			continue;
		}
		break;
	}

	return ReturnList;
}

FString UMissionGraph::ToString()
{
#if WITH_EDITOR
	const auto List = GetOrderedList();

	FString ResultString;
	for (auto MissionNode : List)
	{
		ResultString.Append(MissionNode->GetNodeTitle().ToString());
		ResultString.Append("-> ");
	}
	ResultString.RemoveFromEnd("-> ");
	return ResultString;
#endif
	return "";
}