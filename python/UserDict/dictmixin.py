from collections import Mapping 

class kindaDict(Mapping):

  def __init__(self):
    self._dict = dict(('a', 1), ('b', 2))

  def __getitem__(self, key):
    return self._dict[key]



kd = kindaDict()
print kd['a']
