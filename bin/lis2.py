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
	f = open ('G:\\bioinf\\bio_inf_projekt\src\u.txt','r')
	str = f.read()	
	array = [int(x) for x in str.split(',')]	
	start = time.clock()
	lis = longest_increasing_subsequence(array)
	end = time.clock()
	print "LIS niza je :  "
	print lis

	
	print "algoritam se vrtio : %f sekundi" %(end-start)
	
	from guppy import hpy
        h = hpy()
        print h.heap()	

	