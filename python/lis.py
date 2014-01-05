import time


#Function that finds longest increasing subsequence
def longest_increasing_subsequence(input):

        """
        Algorithm is based on simple binary search
        It processes each member from input array one by one 
        After processing member input[i], in auxiliary arrays M[] and P[] appropriate
        values are stored:  
              M[j] - stores position(index) p of smallest value from input array
                 such that value input[p] is ending value of increasing subsequence of 
                 length j, where j<=p<=i (i is index of a value currently in analysis) 
              P[p] - stores position of predecessor of member input[i] which is located 
                 in longest subsequence that ends with value input[i]
        L - length of longest subsequence found at some point of algorithm
        """

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
        
        """
        Reading found members of longest increasing subsequence
        backwards using arrays M[] and P[]
        """     
        
        output = []
        position = M[L]
        while L > 0:
                output.append(input[position])
                position = P[position]
                L -= 1
                
        output.reverse()
        return output

#Main function      
if __name__ == '__main__':
        f1 = open ('u.txt','r')
        f2 = open ('izlaz.txt','w')
    
        """
        Reading input file as a string and transforming it into an array of 
        integers for further processing
        """
        
        str = f1.read()  
        array = [int(x) for x in str.split(',')]
        f1.close()
    
        """
        Start measuring time required for running of algorithm
        Call for algorithm function 
        """ 
        
        start = time.clock()
        lis = longest_increasing_subsequence(array) 
        end = time.clock()        
        
        """
        Writing result into output file
        """
        
        f2.write('%s'%lis[0])
        for i in range(1,len(lis)):
            f2.write(', %s'%lis[i])
        f2.close()        
    
        """
        Print measured running time 
        Estimate and print used memory
        """
    
        print "Time[s]:%.3f " %(end-start)
        
        from guppy import hpy
        h = hpy()
        print 'Memory[B]:%d' %h.heap().size     
        
