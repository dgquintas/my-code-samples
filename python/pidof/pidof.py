import os, sys

pidName = sys.argv[1]

procEntries = os.listdir('/proc')
pids = filter( lambda pid: str.isdigit(pid) and len(pid) > 3, procEntries )
for pid in pids:
  f = file(os.path.join('/proc', pid, 'cmdline'), 'r')
  cmdline = f.read()
  f.close()
  cmd = os.path.basename(cmdline).split('\x00')[0]
  if cmd == pidName:
    print pid, '->', cmd



