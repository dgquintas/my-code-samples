# Ex1.
#  Go into iex. Create and run the functions that do the following:
# – list_concat.([:a, :b], [:c, :d]) #=> [:a, :b, :c, :d]
list_concat = fn a, b -> a ++ b end

# – sum.(1, 2, 3) #=> 6
sum = fn a, b, c -> a + b + c end

# – pair_tuple_to_list.( { 1234, 5678 } ) #=> [ 1234, 5678 ]
pair_tuple_to_list = fn {a, b} -> [a, b] end


# Ex2.
# Write a function that takes three arguments. If the first two are zero,
# return “FizzBuzz.” If the first is zero, return “Fizz.” If the second is
# zero, return “Buzz.” Otherwise return the third argument. Do not use any lan-
# guage features that we haven’t yet covered in this book.
ex2 = fn
  0, 0, _ -> "FizzBuzz"
  0, _, _ -> "Fizz"
  _, 0, _ -> "Buzz"
  _, _, c -> c
end


# Ex3.
# The operator rem(a, b) returns the remainder after dividing a by b . Write a
# function that takes a single integer ( n ) and calls the function in the
# previous exercise, passing it rem(n,3) , rem(n,5) , and n . Call it seven
# times with the arguments 10, 11, 12, and so on. You should get “Buzz, 11,
# Fizz, 13, 14, FizzBuzz, 16.” (Yes, it’s a FizzBuzz solution with no
# conditional logic.)
ex3 = fn n -> ex2.(rem(n,3), rem(n, 5), n) end


# Ex4.
# Write a function prefix that takes a string. It should return a new function
# that takes a second string. When that second function is called, it will
# return a string containing the first string, a space, and the second string.
ex4 = fn prefix ->
  fn suffix ->
    "#{prefix} #{suffix}"
  end
end


# Ex5.
# Use the & ... notation to rewrite the following.
# – Enum.map [1,2,3,4], fn x -> x + 2 end
Enum.map [1,2,3,4], &(&1 + 2)

# – Enum.each [1,2,3,4], fn x -> IO.inspect x end
Enum.each [1,2,3,4], &IO.inspect(&1)
