import resource
from operator import sub

r1 = resource.getrusage( resource.RUSAGE_SELF )

import json
import os
import xmlrpclib
import math
import httplib

r2 = resource.getrusage( resource.RUSAGE_SELF )

def diff_rusage( r1, r2 ):
  return resource.struct_rusage(map( sub , r2, r1 ))

def rusage_to_dict( r ):
  fields= ('ru_utime', 	'ru_stime',	  'ru_maxrss',  'ru_ixrss',
           'ru_idrss',	'ru_isrss',	  'ru_minflt',  'ru_majflt',
           'ru_nswap',	'ru_inblock', 'ru_oublock', 'ru_msgsnd', 
           'ru_msgrcv', 'ru_nsignals','ru_nvcsw',	  'ru_nivcsw' )
  res = {}
  for (i,f) in enumerate(fields):
    res[f] = r[i]
  return res


r3 = diff_rusage(r1, r2)

print r1
print r2
print r3

print rusage_to_dict(r3)

