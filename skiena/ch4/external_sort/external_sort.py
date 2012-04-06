# how to sort shitloads of data (on the HD) if we have a small amount of RAM
# a trivial way to generate some MBs of ints is to use dd:
# 
# dd if=/dev/urandom of=foobar obs=20000000 ibs=$(( 1024 * 1024 )) count=512 
#
# for 512 MB of shit. The total number of bytes should be a multiple of 4 (for 32 bits anyway)
#
# Once we have that, a generator that'd return ints in batches would come in handy.
# Namely, the size of the buffer we can allocate. We'll sort each of these buffers in-memory
# (using quicksort) and write them back to the file in the same position. 
#
# At this point we have n/m (for n the size of the data and m the size of the buffer) subblocks
# of sorted data. Let's keep an array with the position of the seek pointer for the top
# of each of these. Then we'll add this top (smallest) element to a heap of size n/m. 
#
# We'll then extract the min from the heap n times, just retrieving the whole sorted
# array. Each time we extract one min, we check its chunk of origin and, using the saved
# seek pointer, insert the next element (if it exists) in the heap and naturally advance 
# the seek pointer.
# (alternatively to using seek pointers, we can just create a bunch of temp files)
#
# sorting n/m elements of size m = n/m * O(m lg m) = O(n lg m)
#
# creating heap of size n/m = O(n/m * lg( n/m ))
# extracting the min of the heap n times = n * O( lg(n/m) ) = O( n lg(n/m) )
# TOTAL = O( n lg(n/m) )
#
# SORTING + MERGING = O(n lg m) + O(n lg(n/m)) = 
#                   = O(n lg m) + O(n (lg n - lg m)) =
#                   = O(n lg m) + O(n lg n - n lg m) =  
#                   = O(n lg m) + O(n lg n) - O(n lg m) =
#                   = #########             ############ =
#                   = O(n lg n)
#

import array
import struct
import heapq
import tempfile
import logging
import sys
import os.path
import pdb

logging.basicConfig(level=logging.INFO)

def readChunk(f, m):
    chunk = f.read(m)
    a = array.array('i')
    a.fromstring(chunk)
    return a

def writeChunk(f, sorted_chunk_list):
    # sorted_chunk_list is a list, sorted
    logging.info("Writing to file %s", f.name)
    a = array.array('i')
    a.fromlist(sorted_chunk_list)
    f.write(a.tostring())

def partition(datafile, num_chunks):
    tmp_files = [tempfile.NamedTemporaryFile() for _ in range(num_chunks)]

    with open(datafile, 'rb') as f:
        for i in range(num_chunks):
            chunk_list = readChunk(f,m).tolist()
            chunk_list.sort()
            #write the chunk to a tempfile
            writeChunk(tmp_files[i], chunk_list)

    return tmp_files

def merge_from_files(res_path, tmp_files):
    # have a heap with one value from each of the files. We'll extract the min from this heap
    # every iteration, writing it to the result file of sorted values
    
    heap = []  # a Python heap is simply a list that's manipulated via the heapq.* methods
    
    # insert one value from each file
    for (i,f) in enumerate(tmp_files):
        f.seek(0)
        v = f.read(4)
        v = struct.unpack('i', v )[0]
        heapq.heappush(heap, (v, i))

    
    with open(res_path, 'wb') as out:
        while heap:
            (v, i) = heapq.heappop(heap)
            logging.debug('Min. value: %d', v)
            out.write( struct.pack('i', v ))

            # push new value from f into heap, if any left
            f = tmp_files[i]
            v = f.read(4)
            if(v):
                v = struct.unpack('i', v )[0]
                heapq.heappush(heap, (v, i))

    
def test(n, datafile, sorted_datafile):
    with open(datafile, 'rb') as data, open(sorted_datafile, 'rb') as sorted_data:
        a = array.array('i')
        a.fromfile(data, n)
        a = sorted(a)

        b = array.array('i')
        b.fromfile(sorted_data, n)
    
        for i in range(len(a)):
            if a[i] != b[i]:
                print( "%d != %d at index %d" % (a[i], b[i], i) )
                return False
        else:
            print("Compared %d values successfully" % n)
            return True



if __name__ == "__main__":
    datafile = sys.argv[1]
    outfile = sys.argv[2]
    m = int(sys.argv[3]) * 1024 * 1024 #size given in MB at command line

    n = os.path.getsize(datafile)
    num_chunks = ((n-1) // m)+1 #ceil(n,m)

    tmp_files = partition(datafile, num_chunks)

    merge_from_files(outfile, tmp_files)

    [ f.close() for f in tmp_files ]

    print( "Did it work?", test(n//4, datafile, outfile) and "Yes!" or "Nope" )
    

