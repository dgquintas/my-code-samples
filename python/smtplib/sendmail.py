import smtplib
import string
import pdb
 
SERVER = 'csg.lbl.gov'

SUBJECT = "Test email from Python"
TO = "dgquintas@gmail.com"
FROM = "dgarciaquintas@lbl.gov"
text = "blah blah blah"
BODY = string.join((
        "From: %s" % FROM,
        "To: %s" % TO,
        "Subject: %s" % SUBJECT ,
        "",
        text
        ), "\r\n")
server = smtplib.SMTP(SERVER)
try:
    res = server.sendmail(FROM, [TO], BODY)
    print("Result: ", res)
finally:
    server.quit()
