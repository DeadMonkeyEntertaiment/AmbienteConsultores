// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionNode.h"


UMissionNode::UMissionNode()
{
#if WITH_EDITOR
	ChildrenLimitType = ENodeLimit::Limited;
	ParentLimitType = ENodeLimit::Limited;
	ChildrenLimit = 1;
	ParentLimit = 1;
#endif
}

#if WITH_EDITOR
FText UMissionNode::GetNodeTitle() const
{
	return FText().FromString(GetClass()->GetName());
}
#endif
