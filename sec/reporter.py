from __future__ import print_function
import string
import sys
import argparse # needs python 2.7 or argparse mod manually installed
from datetime import datetime

import socket
import smtplib

MAILSERVER = 'csg.lbl.gov'

TEMPLATE="""
Description: ${description}

System:      ${system}
Service:     ${service}
Timestamp:   ${timestamp}

Relevant log information
${logline}
"""

def send_mail(to_list, subject, text):
    frm = "loganalyzer@%s" % socket.gethostname()
    to_commas = ','.join(to_list)
    body = '\r\n'.join((
            "From: %s" % frm,
            "To: %s" % to_commas,
            "Subject: %s" % subject,
            "",
            text
            ))
    server = smtplib.SMTP(MAILSERVER)
    try:
        failed = server.sendmail(frm, to_list, body)
        if failed:
            print("Couldn't email report to '%s'" % failed , file=sys.stderr)
    finally:
        server.quit()


def get_report(template, **kwargs):
    t = string.Template(template)
    res = t.substitute(kwargs)
    return res

if __name__ == "__main__":
    # need: service, timestamp, header, logline
    parser = argparse.ArgumentParser(description='Generate and process event reports')

    
    parser.add_argument('-d', metavar='description', dest='description', 
            default='N/A', help='description of the event')
    parser.add_argument('-s', metavar='service', dest='service', 
            help='Service (daemon) responsible for the event', required=True )
    parser.add_argument('--email', metavar='emailaddr', dest='emails', 
            help='Send report by email', action='append' )
    parser.add_argument('logline')
    
    args_dict = vars(parser.parse_args())
    report = get_report(TEMPLATE, timestamp=datetime.now(), 
                                system=socket.gethostname(), 
                                **args_dict) 
    subject = '[%(service)s] %(description)s' % args_dict
    send_mail( args_dict['emails'], subject, report)


