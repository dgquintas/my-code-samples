
l = [{'uno': 1, 'dos':2}, {'three': 3, 'four': 4}]

def mod(d):
    for k in d:
        d[k] = d[k]+1
       # d['bar'] = 666 # this would break it with a RuntimeError: dictionary changed size during iteration

for d in l:
    mod(d)

print(l)
