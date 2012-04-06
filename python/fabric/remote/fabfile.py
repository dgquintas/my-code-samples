from fabric.api import run, env
import pdb 

env.shell = '/bin/bash -c'
env.hosts = ['lumi', 'access.als' ]

def uname():
  res = run('uname -a')
  pdb.set_trace()
  print res

def ls():
  res = run('ls -Rl')
  pdb.set_trace()
  print res


def myCmd(cmd):
  run(cmd)
