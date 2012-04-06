from __future__ import print_function
# in this case the cyphertext is shorter than the key, so we don't
# have to worry about reading the key circularly

ALPHABET = [ chr(c) for c in range(ord('a'), ord('z')+1) ]

key = [ int(c) for c in '61803398874' ]
ct = [ ord(c)-ord('a') for c in 'xfbhlqtlj' ]

# the default behavior for negative indices comes in handy once
# we've defined the alphabet as a list
print(''.join(ALPHABET[c-k] for c,k in zip(ct,key) ))
