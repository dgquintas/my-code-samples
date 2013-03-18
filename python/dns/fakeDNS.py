import socket, struct, imaplib, sys

def getMsgsFromGmail():
  m = imaplib.IMAP4_SSL('imap.gmail.com', 993)
  m.login(sys.argv[1], sys.argv[2])
  m.select('INBOX', readonly=True)
  msgs = m.search(None, 'UNSEEN')[1][0].split()
  count = len(msgs)
  if msgs:
    fetchs = m.fetch(','.join(msgs), '(BODY.PEEK[HEADER.FIELDS (SUBJECT)])')[1]
    raw_fetch_entries = [ item for fetch in fetchs for item in fetch ]
    subjects = [ entry.strip() for entry in raw_fetch_entries if entry[:7] == 'Subject']
    subjects_str = ". ".join(subjects)
  else:
    subjects_str = ""

  return (count, subjects_str)


class Query(object):

  class Header(object):
    def __init__(self, data):
      (self.ID, self.FLAGS, self.NQUERIES, self.NREPLIES, self.NNS, self.NADDRES) = \
          struct.unpack('!6H', data)

      self.FLAGS = self._parseFlags(self.FLAGS)

    def _parseFlags(self, flags):
      d = dict()
      d['RCODE'] = flags & 0xf; flags >>= 4
      d['Z'] = flags & 0x7; flags >>= 3
      d['RA'] = flags & 0x1; flags >>= 1
      d['RD'] = flags & 0x1; flags >>= 1
      d['TC'] = flags & 0x1; flags >>= 1
      d['AA'] = flags & 0x1; flags >>= 1
      d['OPCODE'] = flags & 0xf; flags >>= 4
      d['QR'] = flags & 0x1; flags >>= 1

      assert(flags == 0)

      return d

  class Question(object):
    def __init__(self, data, QDCOUNT):
      self.data = data
      self.QNAMES = []

      for q in range(QDCOUNT):
        p = 0
        fqdn = ''
        length = struct.unpack("!b", data[p])[0]
        labels = []
        while length:
          labels.append(data[p+1:p+length+1])
          p += length + 1
          length = struct.unpack("!b", data[p])[0]
        self.QNAMES.append( '.'.join(labels) )
        data = data[p+1:]

      self.QTYPE, self.QCLASS = struct.unpack("!HH", data)
      
      #QTYPE should be 16 (TXT)
      #QTYPE should be 1 (IN)


  def __init__(self, data):
    self.header = Query.Header(data[:12])
    self.question = Query.Question(data[12:], self.header.NQUERIES)

  def getResponse(self): 
    #res = "yo yo yo 'sup %s" % self.question.QNAMES[0].split('.')[0]

    count, subjects = getMsgsFromGmail()
    res = "%d Unread. %s" % (count, subjects)

    #ID, FLAGS, NQUERIES, NREPLIES, NNS, NADDRES
    resHeader = struct.pack('!6H', self.header.ID, 0x8000, 1, 1, 0, 0)
    resOrigQuery = self.question.data
    #NAME, TYPE: txt #CLASS: internet #TTL: no cache #RDLENGTH: length of next field
    resBody = struct.pack('!HHHIHB%ds' % len(res), 0xc00c, 16,1,0,len(res)+1,len(res),res)
    
    resParts =  resHeader + resOrigQuery + resBody 
    resData = ''.join(resParts)
    return resData

if __name__ == "__main__":
  if len(sys.argv) < 3:
    print("Usage: %s <gmail user> <gmail pw>" % sys.argv[0])
  else:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(('0.0.0.0', 53))

    try:
      while True:
        (data, frm) = s.recvfrom(1024)
        query = Query(data)
        response = query.getResponse()
        s.sendto(response, frm)
    finally:
      s.close()


