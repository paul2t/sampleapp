#pragma once


#include <stdio.h>
#include <windows.h>
#include <intrin.h>
#include "imgui/src.cpp"
#define FSTRING_IMPLEMENTATION 1
#include "4coder_string.h"
#include "macros.h"
#include "utils.cpp"
#include "directory.h"
#include "threads.h"


#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_MAXIMIZED 1
#define DEFAULT_FONT_NAME "liberation-mono.ttf"
#define APPLICATION_NAME "Foosball Manager"

struct Config
{
#define CONFIG_LATEST_VERSION 0
	String content;
	i32 version = 0;

	i32 width = DEFAULT_WINDOW_WIDTH, height = DEFAULT_WINDOW_HEIGHT;
	b32 maximized = DEFAULT_MAXIMIZED;

	String fontFile = {};
	float fontSize = 20.0f;

};

struct State
{
	MemoryArena arena = {};
	Config config = {};

	b32 running = true;
	b32 shouldWaitForEvent = false;
	b32 showAbout = false;


};

#if APP_INTERNAL
internal volatile u64 indexTimeStart = 0;
internal volatile u64 indexTime = 0;
internal volatile u64 treeTraversalTimeStart = 0;
internal volatile u64 treeTraversalTime = 0;
internal volatile u64 searchTimeStart = 0;
internal volatile u64 searchTime = 0;
#endif

#include "imgui_utils.cpp"

