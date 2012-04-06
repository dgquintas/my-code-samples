import inject
from config import config
from db import Database, connect_to_db

injector = inject.Injector()
injector.bind('config', to=config)
injector.bind(Database, to=connect_to_db, scope=inject.appscope)
inject.register(injector)

from aModule import A

a = A()
print a.db.user
