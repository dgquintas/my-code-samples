# Given a fairly large number of integers (4e9 32-bit integers), point
# out one of the missing ones. These integers are given in random order.
#
# If we have plenty of space, we can use a bitvector. It'd however take 
# 4e9 bits ~= 500 MB. If we just have access to a little bit of memory
# but can use scratch files, we can do it differently taking advantage
# of **binary search**. Three things are needed to implement binary search
# (and straightforward ordering of the elements isn't one of it)
# 1) A range.
# 2) A representation for the elements within the range (where and how to
#    store the elements).
# 3) A probing method to determine which half of a range holds what we
#    are looking for.
#
# The difficulty is thinking outside the box and being really flexible
# regarding what a range is (especially when are are talking numbers, it's
# so easy to just think about range of the numbers we are dealing with).
#
# What we are looking for is a missing integer. We need to come up with
# a way to define a range so that we KNOW how to tell which half of the
# range has this missing integer. This range can't have anything to do with
# the given numbers *in the usual fashion*, as we have no way of coming up
# with ranges encompasing the whole domain such that we can confidently
# have the probing method. 
# The key point is to look for characteristics that'd partition the domain
# regardless of the order of the actual numbers. Some sort of intrinsic 
# characteristic that'd as evenly as possible divide the domain whilst still
# allowing us to probe which half has what we want. 
#
# Let's consider the bit value of the most significant bit. Going through 
# the given values, we place the ones with a leading bit 0 in one scratch file,
# the ones with 1 in another one. Between these two sets, the one with the lesser
# number of elements is bound to have at least a missing value. We make this one
# the input for the next iteration and we then consider the 2nd bit (from the left)
# as differentiator. That way, we'll eventually get to a point where one of the 
# sets will be empty. And that's the missing one. 
import random

numbers = list(range(2**16) )
random.shuffle(numbers)

del numbers[random.randint(0,2**16-1)]
del numbers[random.randint(0,2**16-2)]
del numbers[random.randint(0,2**16-3)]
del numbers[random.randint(0,2**16-4)]

original = list(numbers)

mask = 1 << 15
while mask > 0: 
    zeros = set()
    ones = set()

    for n in numbers:
        if n & mask:
            ones.add(n)
        else:
            zeros.add(n)

    if len(zeros) <= len(ones):
        numbers = zeros
    else:
        numbers = ones

    if len(numbers) == 0:
        # the missing number is any from the complementary 
        # set with the i-th bit flipped
        if numbers is zeros:
            missing = ones.pop() ^ mask
        else:
            missing = zeros.pop() | mask
        print(missing)
        assert missing not in original
        break
    else:
        mask >>= 1
else:
    print("Nothing is missing!")





