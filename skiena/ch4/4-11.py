# Design an O(n) algorithm that, given a list of n elements, finds all the
# elements that appear more than n/2 times in the list. Then, design an O(n)
# algorithm that, given a list of n elements, finds all the elements that appear
# more than n/4 times.
#
# If we could sort the lists, detecting the (single) element that happens more than 
# n/2 times would be trivial, as it'd happen either at 0 and n/2 or n/2 and last elem.
#
# On an n element array, only one element can happen more than n/2 times. This element
# will cross the "middle" boundary. 
