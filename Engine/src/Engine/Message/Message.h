#pragma once
#include <Engine/Core/Symbols.h>
#include <stdio.h>
#include <assert.h>
namespace Engine
{
	#define MESSAGE(title,content,...) printf("[%s]: ",title); printf(content,__VA_ARGS__); printf("\n");
	#define ASSERT(expression,title,content,...) if(!(expression)) { MESSAGE(title,content,__VA_ARGS__) assert(1==0);}
}