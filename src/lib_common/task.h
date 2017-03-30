#pragma once

#include "..\common.h"

// 'task'
EXPORT SClass* _makeProcess(SClass* me_, const U8* path);
EXPORT void _processDtor(SClass* me_);
EXPORT S64 _processRun(SClass* me_, Bool waitUntilExit);
EXPORT void _processRunAsync(SClass* me_, void* func);
