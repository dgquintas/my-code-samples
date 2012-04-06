import inject
from config import config

@inject.param('config')
def connect_to_db(config):
    '''Get database config and return its instance.'''
    dbconfig = config['db']
    host = dbconfig['host']
    port = dbconfig['port']
    user = dbconfig['user']
    password = dbconfig['password']
    
    return Database(host, port, user, password)


@inject.appscope        # By default, use application scope when the class
class Database(object): # is injected. In other words, instantiate it only
                        # once for the whole application.

    '''Fake database stores all messages in a list.'''
    
    def __init__(self, host, port, user, password):
        self.host = host
        self.port = port
        self.user = user
        self.password = password
        self.messages = []
    
    def insert(self, message):
        self.messages.append(message)
    
    def select(self, order_by_date=False):
        messages = list(self.messages)
        if order_by_date:
            messages.reverse()
        return messages



