# The goal is selecting the k-th element from the array IF IT WERE SORTED. 
# Of course we can do that sorting the array and then going for its k-th index
# ((k-1)th maybe). That's attainable in O(n lg n). 
#
# We can do it in linear time tho. This is the randomized way of doing it, which
# is based on quicksort's partitioning algorithm (which was linear). 
