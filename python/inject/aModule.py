import inject
from db import Database

class A(object):

  @inject.param('db', Database)
  def __init__(self, db):
    self.db = db


