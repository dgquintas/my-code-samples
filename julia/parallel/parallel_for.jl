println("Number of workers: $(length(workers()))")
@time nheads = @parallel (+) for i = 1:200000000
    int(randbool())
end
