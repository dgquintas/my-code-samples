from couchdb import Server
from couchdb.mapping import TextField, IntegerField, DateTimeField, Document

from datetime import datetime

server = Server()
try:
    db = server.create('python-tests')
except:
    db = server['python-tests']

class Person(Document):
    name = TextField()
    age = IntegerField()
    added = DateTimeField(default=datetime.now)

person = Person(name="John doe", age=33)
print "Stored: ", person.store(db)
person2 = Person.load(db, person.id)
print "Retrieved: ", person2


