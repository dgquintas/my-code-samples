function sortdigits(s)
    return ASCIIString(sort(string(s).data))
end

function constant_diff(a, b, c)
    return (b - a) == (c - b)
end

function solve()
    ps = filter(p -> p > 1000, primes(9999))
    digit_classes = Dict()
    for p in ps
        p_class = sortdigits(p)
        if !haskey(digit_classes, p_class)
            digit_classes[p_class] = Int[]
        end
        push!(digit_classes[p_class], p)
    end

    candidate_classes = filter(v -> length(v) >= 3, values(digit_classes))
    for class_primes in candidate_classes
        combs = combinations(class_primes, 3)
        for comb in combs
            if constant_diff(comb...)
                print(comb[2] - comb[1], " ")
                println(join([string(c) for c in comb],""))
            end
        end
    end
end

@time solve()
