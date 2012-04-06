import couch
from pprint import pprint
from collections import OrderedDict

def get_user(email, **kwargs):
    user_document = OrderedDict(
                    {'_id': email,
                     'first_name': kwargs.get('first_name'),
                     'last_names': kwargs.get('last_names'),
                     'gender':  kwargs.get('gender'),
                     'age': int(kwargs.get('age')),
                     'from': {'hood': kwargs.get('hood'),
                              'city': kwargs.get('city'),
                              'country': kwargs.get('country')},
                     'contact': {'email': email,
                                 'twitter': kwargs.get('twitter'),
                                 'facebook': kwargs.get('facebook')},
                     })
    return user_document

by_age_view_map = """
function(doc) {
    if (doc.age){
        emit(doc.age, doc.age)
    }
}
"""
agesum_view_reduce = """
function(keys, values){
    return sum(values);
}
"""

user_validation_func = """
function(ndoc, odoc, userctx, secobj){
    if(ndoc.age){
        var age_i = parseInt(ndoc.age);
        if( age_i > 120 || age_i < 0 ){
            throw({forbidden: "Given age '"+age_i+"' is invalid"});
        }
    }

    if(ndoc.gender){
        if( ndoc.gender !== 'male' && ndoc.gender !== 'female' ){
            throw({forbidden: "Invalid gender '" + ndoc.gender + "'" });
        }
    }
}
"""


user_show_func = """
function(doc, req) {
    return {
        json: {from: doc.from, age: doc.age}
    }
}
"""

user_list_func = r"""
function(head, req) {
    var row;
    while( row = getRow() ){
        var foo = row.key+'\n';
        send(foo);
    }
    return "S'acabo";
}
"""

by_age_view = { '_id': '_design/users',
                'language': 'javascript',
                'views': {'age':    {'map': by_age_view_map},
                         'agesum':  {'map': by_age_view_map, 
                                     'reduce': agesum_view_reduce}},
                'validate_doc_update': user_validation_func, 
                'shows': {
                    'user_show': user_show_func,
                    },
                'lists': {
                    'user_list': user_list_func,
                    }
                }

user1 = get_user('uno@example.com', age=3, first_name='Numero', last_names="Uno One", 
        gender='female', city='pumata', country='ES')
user2 = get_user('dos@example.com', age=14,first_name='Number', last_names="Zwei")
user3 = get_user('tres@example.com', age='33', first_name='Nombre', last_names="Quatre")
userwrong = get_user('xxx@example.com', age=-1, first_name='Nombre', last_names="Quatre")

DB_NAME = 'testing-tornado-couch'

db = couch.BlockingCouch(DB_NAME)
try:
    db.create_db()
except:
    db.delete_db() 
    db.create_db()

print("Saving users design doc...", db.save_doc(by_age_view))

users = (user1,user2,user3)
users_rbs = [ db.save_doc(u) for u in users ] # rev, id

try:
    db.save_doc(userwrong)
except Exception as e:
    print(e)

for user_rb in users_rbs:
    user_from_db = db.get_doc(user_rb['id'])
    pprint( user_from_db )

print()

pprint(db.view('users', 'age', ))
pprint(db.view('users', 'agesum', ))


