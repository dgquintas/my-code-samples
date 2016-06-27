function count_heads(n)
    c::Int = 0
    for i = 1:n
        c += randbool()
    end
    c
end

# Then, from a julia cli launched with "julia -p <n>" do:
#
# require("count_heads)
# a = @spawn count_heads(100000000)
# b = @spawn count_heads(100000000)
# fetch(a)+fetch(b)
