#include "deploy.h"

#include "log.h"
#include "util.h"

static void CopyDlls(const Char* key, const void* value, void* param);

void Deploy(U64 app_code, const SOption* option, SDict* dlls)
{
#if defined(_DEBUG)
	// When doing tests, the program uses debugging Dlls so do not copy these.
	UNUSED(app_code);
	UNUSED(dlls);
#else
	{
		Char path[1024];
		wcscpy(path, option->OutputDir);
		wcscat(path, L"data/");
		if (!DelDir(path))
			Err(L"EK0011", NULL, path);
		if (CreateDirectory(path, NULL) == 0)
			Err(L"EK0012", NULL, path);
	}
	DictForEach(dlls, CopyDlls, (void*)option);
	// TODO: Deploy the resource folder.
#endif

	// Copy the manifest.
	if (option->Env == Env_Wnd)
	{
		Char src[MAX_PATH];
		Char dst[MAX_PATH];
		wcscpy(src, option->SysDir);
		wcscat(src, L"manifest.xml");
		wcscpy(dst, option->OutputFile);
		wcscat(dst, L".manifest");
		if (CopyFile(src, dst, FALSE) == 0)
			Err(L"EK0013", NULL, src, dst);
	}
}

static void CopyDlls(const Char* key, const void* value, void* param)
{
	UNUSED(value);
	{
		const SOption* option = (SOption*)param;
		Char src[MAX_PATH];
		Char dst[MAX_PATH];
		wcscpy(src, option->SysDir);
		if (option->Rls)
			wcscat(src, L"rls/");
		else
			wcscat(src, L"dbg/");
		wcscat(src, key);
		wcscpy(dst, option->OutputDir);
		wcscat(dst, L"data/");
		wcscat(dst, key);
		if (CopyFile(src, dst, FALSE) == 0)
			Err(L"EK0013", NULL, src, dst);
	}
}
