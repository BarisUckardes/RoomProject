#include "PathUtils.h"
#include <stdlib.h>
#include <shlwapi.h>
#include <Windows.h>

namespace Engine
{
	unsigned int get_char_ptr_length(const char* target)
	{
		unsigned int size = 0;
		while (target[size] != '\0')
			size++;
		return size;
	}
	String PathUtils::get_relative_path(const String& path)
	{
		HINSTANCE hInstance = GetModuleHandle(0);
		char* Filename = (char*)malloc(sizeof(char) * 1000); //this is a char buffer
		GetModuleFileNameA(hInstance, Filename, sizeof(char) * 1000);
		PathRemoveFileSpecA(Filename);

		const unsigned int targetLength = path.get_cursor();
		const unsigned int pathLength = get_char_ptr_length(Filename);

		for (unsigned int i = 0; i < targetLength; i++)
		{
			Filename[pathLength + i] = path[i];
		}
		Filename[pathLength + targetLength] = '\0';

		return Filename;
	}
}