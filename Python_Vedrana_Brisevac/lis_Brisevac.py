# Program implements patience sorting algorithm for finding longest increasing subsequence
# Algorithm taken from http://en.wikipedia.org/wiki/Patience_sorting
 
import bisect
import time

def patienceSorting(dataList):
    # patienceSorting(dataList) creates heapCurrent and heaps list
    # heapCurrent is the number of heap on which the current integer from the dataList is being stored
    # every integer is being placed on the top of one of the heaps, like in solitaire card game
    heaps = list()
    for x in dataList:
        heapCurrent = bisect.bisect_left(heaps, x)
        if heapCurrent == len(heaps):
            heaps.append(x)
        else:
            heaps[heapCurrent] = x
        yield x, heapCurrent

def findLongestIncreasingSubsequence(dataList):
    heaps = [[]] 
    # patience sorting of dataList and storing entrance data on heaps
    # indexing elements on the top of preceding heap
    for x, y in patienceSorting(dataList):
        if y + 1 == len(heaps):
            heaps.append([])
        heaps[y + 1].append((x, len(heaps[y]) - 1)) 
    # following sequence from the top card in the last pile (in program heap) towards the first pile
    # its reverse is an answer to the longest increasing subsequence algorithm.
    lis = list()
    pred = 0
    for heap in range((len(heaps) - 1), 0, -1):
        x, pred = heaps[heap][pred]
        lis.append(x)
    lis.reverse()
    # longest increasing subsequence is being stored in output file in same format as the input file
    # integers are stored in .txt file, separated with commas
    # findLongestIncreasingSubsequence(dataList) returns only one correct answer
    foutput = open ('output.txt','w')
    for i in range(0,len(lis)-1):
        foutput.write('%s,'%lis[i])
    foutput.write('%s'%lis[len(lis)-1])
    foutput.close()
    return 0

if __name__ == '__main__':
    #
    begin = time.clock()
    fInput = open ('u.txt','r')
    dataString = fInput.read()
    fInput.close()
    dataList=[int(i) for i in dataString.split(",")]
    findLongestIncreasingSubsequence(dataList)        
    stop = time.clock() 
    print ("Time[ms]:%.3f " %((stop-begin)*1000))

    from guppy import hpy
    h = hpy()
    print 'Memory[B]:%d' %h.heap().size    
        