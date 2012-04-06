import inject

class C(object):
  @inject.param('x',bindto=1)
  def __init__(self, x):
    print x


C()

#the following wont work
C(2)


