import time

def longest_increasing_subsequence(input):
        n = len(input)
        input = [None] + input
        M = [None]*(n+1)
        P = [None]*(n+1)
        L = 0
        
        for i in range(1,n+1):
                if L == 0 or input[M[1]] >= input[i]:
                        j = 0
                else:
                        lower = 1
                        higher = L+1
                        while lower < higher - 1:
                                middle = (lower + higher)/2
                                if input[M[middle]] < input[i]:
                                        lower = middle
                                else :
                                        higher = middle
                        j = lower
                        
                P[i] = M[j]
                if j == L or input[i] < input[M[j+1]]:
                        M[j+1] = i
                        L = max(L,j+1)
                
        output = []
        position = M[L]
        while L > 0:
                output.append(input[position])
                position = P[position]
                L -= 1
                
        output.reverse()
        return output
                
if __name__ == '__main__':
        f1 = open ('u.txt','r')
	f2 = open ('izlaz.txt','w')
        str = f1.read()  
        array = [int(x) for x in str.split(',')]
	f1.close()
	
        start = time.clock()
        lis = longest_increasing_subsequence(array)	
        end = time.clock()        
        
        f2.write('%s'%lis[0])
	for i in range(1,len(lis)):
	   f2.write(', %s'%lis[i])
	f2.close()        
	
        print "Time[s]:%.3f " %(end-start)
        
        from guppy import hpy
        h = hpy()
        print 'Memory[B]:%d' %h.heap().size
		
        
