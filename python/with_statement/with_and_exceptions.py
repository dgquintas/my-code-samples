try:
    with open('foo', 'r') as f:
        pass
except Exception as e:
    print "FOO", str(e)

