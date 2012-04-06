import pycassa
import pycassa.system_manager as SM

import uuid

KEYSPACE = 'TwitterStream'

# 1) create the CF
sys = SM.SystemManager(server='localhost:9160')
#if KEYSPACE in sys.list_keyspaces():
#    sys.drop_keyspace(KEYSPACE)
if KEYSPACE not in sys.list_keyspaces():
    sys.create_keyspace(KEYSPACE, replication_factor=2)
    sys.create_column_family(KEYSPACE, 'Users', comparator_type=SM.UTF8_TYPE, default_validation_class=SM.UTF8_TYPE, key_validation_class=SM.UTF8_TYPE)
    sys.create_column_family(KEYSPACE, 'Tweets', comparator_type=SM.UTF8_TYPE, default_validation_class=SM.UTF8_TYPE, key_validation_class=SM.ASCII_TYPE)
    sys.create_column_family(KEYSPACE, 'Counters', comparator_type=SM.UTF8_TYPE, default_validation_class=SM.COUNTER_COLUMN_TYPE, key_validation_class=SM.UTF8_TYPE)

POOL = pycassa.connect(KEYSPACE)

sys.alter_column(KEYSPACE, 'Users', 'id', SM.INT_TYPE);
USERS = pycassa.ColumnFamily(POOL, 'Users')

TWEETS = pycassa.ColumnFamily(POOL, 'Tweets')

COUNTERS = pycassa.ColumnFamily(POOL, 'Counters')

# 2) reader methods
#def get_user_tweets(user):


# 3) writer methods
def insert_user(name, id_, location, lang):
    username = name.encode('utf-8')
    USERS.insert(username, {'id': id_, 
                        'location': location or 'None',
                        'lang': lang or 'None'})
    COUNTERS.add('Users', lang)
    COUNTERS.add('Users', 'total')


def insert_tweet(user, text, geo, when):
    tweet_id = str(uuid.uuid1())
    TWEETS.insert(tweet_id, {'user': user, 'text': text, 'geo': geo, 'when': when} )


