// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ELoGTypeExtern :uint8
{
	None,
	Normal,
	Warning,
	Error,
};

DECLARE_LOG_CATEGORY_EXTERN(LogMyGame, Log, All);

class MYGAME_API DebugHelper
{
private:
	static TSharedPtr<DebugHelper> debugHelper;
	FString outStr;
	float showTime;
	FColor showColor;

public:
	ELoGTypeExtern logType;

	inline DebugHelper()
	{
	}

	~DebugHelper()
	{
	}

	static TSharedPtr<DebugHelper> Get();

	inline void InitParam(float time = 10, FColor color = FColor::Green)
	{
		showTime = time;
		showColor = color;
	}

	inline void Print()
	{
		switch (logType)
		{
		case ELoGTypeExtern::Normal:
			UE_LOG(LogMyGame, Log, TEXT("%s"), *outStr);
			break;
		case ELoGTypeExtern::Warning:
			UE_LOG(LogMyGame, Warning, TEXT("%s"), *outStr);
			break;
		case ELoGTypeExtern::Error:
			UE_LOG(LogMyGame, Error, TEXT("%s"), *outStr);
			break;
		case ELoGTypeExtern::None: break;
		default: ;
		}
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, showTime, showColor, outStr);
		outStr.Empty();
	}

	inline void operator<<(DebugHelper& Value) const
	{
		Value.Print();
	}

	inline DebugHelper& operator<<(int32 Value)
	{
		outStr.Append(FString::FromInt(Value));
		return *this;
	}

	FString operator<<(float Value)
	{
		outStr.Append(FString::SanitizeFloat(Value));
		return outStr;
	}

	FString operator<<(double Value)
	{
		outStr.Append(FString::SanitizeFloat(Value));
		return outStr;
	}

	FString operator<<(bool Value)
	{
		outStr.Append(Value ? "true" : "false");
		return outStr;
	}

	inline DebugHelper& operator<<(FString Value)
	{
		outStr.Append(Value);
		return *this;
	}

	inline DebugHelper& operator<<(const char* Value)
	{
		outStr.Append(Value);
		return *this;
	}

	inline DebugHelper& operator<<(FName Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FText Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FVector Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FVector2D Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FRotator Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FQuat Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FTransform Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FMatrix Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(UObject Value)
	{
		outStr.Append(Value.GetFName().ToString());
		return *this;
	}

	inline DebugHelper& operator<<(AActor* Value)
	{
		outStr.Append(Value->GetFName().ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FColor Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}

	inline DebugHelper& operator<<(FLinearColor Value)
	{
		outStr.Append(Value.ToString());
		return *this;
	}
};

namespace DebugHeader
{
	inline DebugHelper& Debug(float time = 10, FColor color = FColor::Green)
	{
		DebugHelper::Get()->InitParam(time, color);
		DebugHelper::Get()->logType = ELoGTypeExtern::Normal;
		return *DebugHelper::Get();
	}

	inline DebugHelper& Debug(FColor color)
	{
		DebugHelper::Get()->InitParam(10.0f, color);
		DebugHelper::Get()->logType = ELoGTypeExtern::Normal;
		return *DebugHelper::Get();
	}

	inline DebugHelper& Warning()
	{
		DebugHelper::Get()->InitParam(10.0f, FColor::Green);
		DebugHelper::Get()->logType = ELoGTypeExtern::Warning;
		return *DebugHelper::Get();
	}

	inline DebugHelper& Log()
	{
		DebugHelper::Get()->InitParam(10.0f, FColor::Green);
		DebugHelper::Get()->logType = ELoGTypeExtern::Normal;
		return *DebugHelper::Get();
	}

	inline DebugHelper& Error()
	{
		DebugHelper::Get()->InitParam(10.0f, FColor::Green);
		DebugHelper::Get()->logType = ELoGTypeExtern::Error;
		return *DebugHelper::Get();
	}

	inline DebugHelper& Endl()
	{
		return *DebugHelper::Get();
	}
}
