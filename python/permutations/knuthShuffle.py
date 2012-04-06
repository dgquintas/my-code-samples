from random import randint

def knuthShuffle(l):
    k = len(l)-1
    while k > 0:
        i = randint(0,k)
        if i != k:
            l[i], l[k] = l[k], l[i]
        k = k-1
    return l

def knuthStats(listOfPerms, total):
    m = len(listOfPerms[0])
    
    stats = [ ([0] * m)[:] for i in xrange(m)]
    ps = [ ([0] * m)[:] for i in xrange(m)]
    
    for perm in listOfPerms:
        for j,num in enumerate(perm):
            stats[j][num] += 1

    for i,row in enumerate(stats):
        for j,count in enumerate(row):
            ps[i][j] = count/float(total);
            
            
    return stats, ps
        
        
        
        
    
