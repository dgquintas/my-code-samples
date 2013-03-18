h = [('Name', 16), ('Running', 10), ('Parameters', 32), ('Statistics', 50)]
fields = ['{0:^{1}}'.format(a,b) for a,b in h]
header = '| '.join(fields)
print(header)
print('-'*len(header))

