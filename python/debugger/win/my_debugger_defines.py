import ctypes

WORD    = ctypes.c_ushort #unsigned short
DWORD   = ctypes.c_ulong  #unsigned long (same as int on 32bits)
LPBYTE  = ctypes.POINTER(ctypes.c_ubyte) # POINTER() creates a new pointer *type*
LPTSTR  = ctypes.POINTER(ctypes.c_char)
HANDLE  = ctypes.c_void_p

DEBUG_PROCESS = 0x00000001
CREATE_NEW_CONSOLE = 0x00000010

# structs for CreateProcessA()
class STARTUPINFO(ctypes.Structure):
    _fields_ = [("cb",          DWORD),
                ("lpReserved",  LPTSTR),
                ("lpDesktop",   LPTSTR),
                ("lpTitle",       LPTSTR),
                ("dwX",           DWORD),
                ("dwY",           DWORD),
                ("dwXSize",       DWORD),
                ("dwYSize",       DWORD),
                ("dwXCountChars", DWORD),
                ("dwYCountChars", DWORD),
                ("dwFillAttribute",DWORD),
                ("dwFlags",       DWORD),
                ("wShowWindow",   WORD),
                ("cbReserved2",   WORD),
                ("lpReserved2",   LPBYTE),
                ("hStdInput",     HANDLE),
                ("hStdOutput",    HANDLE),
                ("hStdError",     HANDLE)]

class PROCESS_INFORMATION(ctypes.Structure):
    _fields_ = [("hProcess",    HANDLE),
                ("hThread",     HANDLE),
                ("dwProcessId", DWORD),
                ("dwThreadId",  DWORD)]




