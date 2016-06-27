function solve(n)
    ws = Dict{Int, Int32}()
    ps = primes(1000000)
    ws[1] = 0
    for p in ps
        ws[p] = 1
    end

    num_consecutive_ns = 0 
    i = 1
    while true
        mi = i
        w_i = 0
        for p in ps
            # remove all prime powers, starting from the smallest primes.
            if rem(mi, p) == 0
                w_i += 1
                while rem(mi, p) == 0; mi = div(mi, p); end
            end
            # do we have the value for the multiple's w?
            # this will eventually be true for all i. Worst case
            # scenario, when it arrives at the last prime multiple.
            if haskey(ws, mi)
                ws[i] = w_i + ws[mi]
                break
            end
        end
        if ws[i] == 4
            num_consecutive_ns += 1
            if num_consecutive_ns == n
                return i-(n-1)
            end
        else
            num_consecutive_ns = 0
        end
    i += 1
    end
end

@time solution = solve(4)
println(solution)
