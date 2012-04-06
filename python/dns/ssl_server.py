import socket, ssl, imaplib

s = socket.socket()
s.bind( (socket.gethostname(), 1234) )
s.listen(5)

while True:
    newsocket, fromaddr = s.accept()
    conn = ssl.wrap_socket(newsocket,
                           server_side=True,
                           certfile="cert.pem")
    try:
        serve_client(conn)
    finally:
        conn.shutdown(socket.SHUT_RDWR)
        conn.close()

def serve_client(conn):
    m = imaplib.IMAP4_SSL('imap.gmail.com', '993')
    m.login(GMAIL_USER, GMAIL_PW)
    m.select('INBOX', readonly=True)
    msgs = m.search(None, 'UNSEEN')[1][0].split()
    count = len(msgs)
    subjects = m.fetch(','.join(msgs), '(BODY.PEEK[HEADER.FIELDS (SUBJECT)])')[1]
    subjects = [ subject[1].strip() for subject in subjects ]
    



