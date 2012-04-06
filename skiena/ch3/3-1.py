# A common problem for compilers and text editors is determining whether the
# parentheses in a string are balanced and properly nested. For example, the
# string ((())())() contains properly nested pairs of parentheses, which the
# strings )()( and ()) do not. Give an algorithm that returns true if a string
# contains properly nested and balanced parentheses, and false if otherwise.
# For full credit, identify the position of the first offending parenthesis if
# the string is not properly nested and balanced.

#idea: use a stack. A ( pops sth in, while a ) pops it out. In the end, we must end up
# with an empty stack.

from __future__ import print_function

def checkParenthesis(s):
    stack = []
    for (i,c) in enumerate(s):
        if c == '(':
            stack.append(i)
        elif c == ')':
            try:
                stack.pop()
            except IndexError:
                print("Offending parenthesis at", i)
                return False

    if len(stack) == 0:
        return True
    else:
        print("Offending parenthesis at", stack.pop())
        return False


print( checkParenthesis('((())())()') )
print( checkParenthesis('((())())()') )

print( checkParenthesis(')()(') )
print( checkParenthesis('())') )



