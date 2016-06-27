# compute the singular values of several random matrices in parallel:

M = {rand(1000, 1000) for i=1:10}
pmap(svd, M)
