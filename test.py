#!/usr/bin/env python

from socket import getaddrinfo
from os import environ

ip = environ['OVERRIDE_HOSTS_TO']

for host in environ['OVERRIDE_HOSTS_FROM'].split(','):
    msg = ' %s resolves to %s' % (host, ip)
    assert getaddrinfo(host, 'http')[0][4][0] == ip, '[FAIL]' + msg
    print '[PASS]' + msg
