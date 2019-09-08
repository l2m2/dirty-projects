#ifndef CALCHOOKPROCESS_H
#define CALCHOOKPROCESS_H

#include "calc-hook-process_global.h"
#include <windows.h>

extern "C" {
    CALCHOOKPROCESSSHARED_EXPORT LRESULT hookProcedure(int nCode, WPARAM wParam, LPARAM lParam);
}
extern HHOOK gHook;

#endif // CALCHOOKPROCESS_H
