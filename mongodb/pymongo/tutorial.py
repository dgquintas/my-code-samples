# -*- coding: utf-8 -*- 
from __future__ import print_function
from pprint import pformat, pprint
import pymongo

connection = pymongo.Connection() #to localhost by default

#access to a db. it doesnt have to exist already
DB = 'foobar_database'
connection.drop_database(DB)
db = connection[DB] # or connection.foobar_database 


import datetime
post = {'author': 'Foo',
        'text': 'Mierda pa ti y pa toda tu peña',
        'tags': ["uno", "que va"],
        'date': datetime.datetime.utcnow()}

#and for the collection (~table)
posts = db.posts # same, db['...']

# insert that shit
print("About to insert: ", pformat(post))
posts.insert(post)

#check it
assert( 'posts' in db.collection_names() )

# now for queries
a_post = posts.find_one()
print("\nRead back: ", pformat(a_post))

# bulk inserts
new_posts = [{"author": "Mike",
               "text": "Another post!",
               "tags": ["bulk", "insert"],
               "date": datetime.datetime(2009, 11, 12, 11, 14)},
              {"author": "Eliot",
               "title": "MongoDB is fun",
               "text": "and pretty easy too!",
               "date": datetime.datetime(2009, 11, 10, 10, 45)}]

print("\nAbout to insert new posts, in bulk")
print(posts.insert(new_posts))

print("\nAll posts:")
for post in posts.find(): #post is a Cursor
    pprint(post)

print("\nPosts by 'Mike'")
for post in posts.find({'author': 'Mike'}):
    pprint(post)

# Range queries
# limit results by date and sort by author
d = datetime.datetime(2009, 11, 12,12)
print("\nPosts before", str(d), "and sorted by author")
for post in posts.find({"date": {"$lt": d}}).sort("author"):
    pprint(post)


# Indexing
# To make the above query fast we can add a compound index on "date" and
# "author". To start, lets use the explain() method to get some information
# about how the query is being performed without the index:
print("\nBy default, using cursor", \
        posts.find({"date": {"$lt": d}}).sort("author").explain()['cursor'])
nscanned = posts.find({"date": {"$lt": d}}).sort("author").explain()['nscanned']
print("By default, scanning %d documents" % nscanned)
print()
print("Gonna add an index on 'date' and 'author' now")
posts.create_index( [ ('date', pymongo.DESCENDING), ('author', pymongo.ASCENDING) ] )
print("With indices, using cursor", \
        posts.find({"date": {"$lt": d}}).sort("author").explain()['cursor'])
nscanned = posts.find({"date": {"$lt": d}}).sort("author").explain()['nscanned']
print("With indices, scanning %d documents" % nscanned)



