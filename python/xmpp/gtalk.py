import xmpp
import time

login = raw_input("User: ")
pwd   = raw_input("Pass: ")

cnx = xmpp.Client('gmail.com')
cnx.connect( server=('talk.google.com',5223) )

cnx.auth(login,pwd, 'botty')

while True:
    cnx.send( xmpp.Message( "vamsi.vytla@gmail.com" ,"fuck you" ) )
    time.sleep(1)



