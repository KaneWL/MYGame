// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHelper.h"

DEFINE_LOG_CATEGORY(LogMyGame);

TSharedPtr<DebugHelper> DebugHelper::debugHelper = nullptr;

TSharedPtr<DebugHelper> DebugHelper::Get()
{
	if (!debugHelper)
	{
		debugHelper = MakeShareable(new DebugHelper());
	}
	return debugHelper;
}
