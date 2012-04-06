import ctypes
import my_debugger_defines as defs

kernel32 = ctypes.windll.kernel32

class debugger(object):
    def __init__(self):
        pass

    def load(self, path_to_exe):
        creation_flags = defs.DEBUG_PROCESS

        startupinfo = defs.STARTUPINFO()
        process_information = defs.PROCESS_INFORMATION()

        startupinfo.dwFlags = 0x1
        startupinfo.wShowWindow = 0x0
        startupinfo.cb = ctypes.sizeof(startupinfo)

        if kernel32.CreateProcessA(path_to_exe, 
                None, None, None, None,
                creation_flags, 
                None, None,
                ctypes.byref(startupinfo), 
                ctypes.byref(process_information)):
            print "[*] We have successfully launched the process!" 
            print "[*] PID: %d" % process_information.dwProcessId
        else:
            print "[*] Error: 0x%08x." % kernel32.GetLastError()




