from itertools import permutations, count
import pdb

def digitalRoot(n):
    while True:
        digits = [int(i) for i in str(n)]
        n = sum(digits)
        if n < 10:
            return n

def isPerfectCube(n):
    #pachangueoooo
    croot_approx = n**(1.0/3)
    fractional = croot_approx % 1
    return fractional >= 0.9999999

for n in count(5196):
    num_perm_cubes = 0
    diff_cube_perms = set()
    cube = n**3
    if( digitalRoot(cube) in (1,8,9) ): #candidate
        diff_cube_perms.add(cube)
        for p in permutations(str(cube)):
            pi = int(''.join(p))
            if( pi > 41063625 and 
                    isPerfectCube(pi) and 
                    pi not in diff_cube_perms):
                print(n, pi)
                diff_cube_perms.add(pi)

            if len(diff_cube_perms) == 5:
                break
    if len(diff_cube_perms) > 1:
        print()
    if len(diff_cube_perms) == 5:
        break


            



