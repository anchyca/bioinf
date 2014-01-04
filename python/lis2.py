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
	f = open ('u.txt','r')
	str = f.read()	
	array = [int(x) for x in str.split(',')]	
	start = time.clock()
	lis = longest_increasing_subsequence(array)
	end = time.clock()
	print "LIS niza je :  "
	print lis

	
	print "algoritam se vrtio : %f sekundi" %(end-start)
	
	import os

	_proc_status = '/proc/%d/status' % os.getpid()

	_scale = {'kB': 1024.0, 'mB': 1024.0*1024.0,
          	'KB': 1024.0, 'MB': 1024.0*1024.0}

	def _VmB(VmKey):
    		'''Private.'''
    		global _proc_status, _scale
     		# get pseudo file  /proc/<pid>/status
    		try:
        		t = open(_proc_status)
        		v = t.read()
        		t.close()
    		except:
        		return 0.0  # non-Linux?
     		# get VmKey line e.g. 'VmRSS:  9999  kB\n ...'
    		i = v.index(VmKey)
    		v = v[i:].split(None, 3)  # whitespace
    		if len(v) < 3:
        		return 0.0  # invalid format?
     		# convert Vm value to bytes
    		return float(v[1]) * _scale[v[2]]


	def memory(since=0.0):
    		'''Return memory usage in bytes.'''
    		return _VmB('VmSize:') - since	

	print "zauzece u bytovima %f" %memory()
	
