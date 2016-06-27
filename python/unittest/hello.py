def Factorial(n):
    if n < 0:
        raise ValueError("Can't calculate negative factorials!")
    if n == 0:
        return 1
    else:
        return n * Factorial(n-1)
