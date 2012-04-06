import itertools

muls = map( lambda i: lambda x: x*i, range(2,6+1) )

for i in itertools.count(1):
  nums = map( lambda f: sorted(str(f(i))), muls )
  if nums[0] == nums[1] == nums[2] == nums[3] == nums[4]:
    print nums, i
    break

