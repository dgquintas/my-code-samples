# the point is to extract a random sample of n elements from a potentially infinite 
# stream of incoming data. Meaning that we have to be ready to stop at any time 
# (any incoming element can be the last) and have our sample ready, verifying that
# any of the incoming items had the same chance of being included in the sample.
#
# The usual condition applies: the probability of an element being in the sample is
# n / #-of-elements-to-that-point. For the first n elements, they all go to the sample,
# obviously. For the (n+1)-th element, we thus include it in the sample with probability
# n/(n+1). But we'll have to expel one of the already present elements. If we choose one
# of them at random, would that still maintain the invariant? Let's see, by induction:
#
# (a) Pr{ be in the sample after i values } = n/i (induction hypothesis)
# (b) Pr{ stay in the sample after i+1 values } = 1-Pr{removed at i+1-th step}
#
# Pr{removed at i+1-th step} = n/(i+1) * 1/n ( select the new element AND expel one already present)
#                            = 1/(i+1)
#
# So Pr{ stay in the sample after i+1 values } = 1-Pr{removed at i+1-th step}
#                                              = 1-(1/(i+1)) = i/(i+1)
#
# The total probability would then be: (a) * (b) = n/i * i/(i+1) = n/(i+1) TADAAAAAA



