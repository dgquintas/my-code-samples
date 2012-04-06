from numpy import *

def generateIdGMatrix(n,m):
    assert m > n
    ident = mat(identity(n,dtype='b'))
    gColumns = m-n
    randomArray = random.random_integers(0,1,gColumns*n)
    rnd = mat(reshape(randomArray, (n,gColumns)),dtype='b')

    return concatenate((ident, rnd),1)

###################################################

n = input("n? ")
m = input("m? ")
a = generateIdGMatrix(n,m)

print "Id|G = \n", a
idBis = a[0:n][:,0:n]
print "Id = \n" , idBis
rndBis = a[0:n][:,n:]
print "G = \n", rndBis
