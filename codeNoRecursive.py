import sys
import time
#REMOVE RECURSIVE AND TEST OTHER LIMITS
maxValue = 0
flow = []
maxFlow = []
maxInputChain = 0
inputSize = 0
operations = 0
	
def recursive(a, dictio, chain, startTime):
	global maxValue
	global maxFlow
	global maxInputChain
	global inputSize
	global operations
	memoryStack = []

	edges = list(filter(lambda posib: dictio[a][posib][0] > 0, dictio[a].keys()))
	i = 0
	memoryStack.append([edges, 0, a, 0])
	while(len(memoryStack) > 0):
		edges, i, a, chain = memoryStack.pop()
		if(time.time() - startTime > 29.1):
			return len(maxFlow)
		flag = False
		while i < len(edges):
			possible = edges[i]
			i = i + 1
			if(dictio[a][possible][0] == 0):
				continue

			dictio[a][possible][0] = dictio[a][possible][0] - 1
			flow.append(possible)
			if(possible in dictio):
				aux_edges = sorted(list(filter(lambda posib: dictio[possible][posib][0] > 0, dictio[possible].keys())))
			else:
				aux_edges = []

			if(not possible in dictio or len(aux_edges) == 0):
				if(chain + 1 > maxValue):
					maxValue = chain + 1
					maxFlow = flow.copy()
				if(not dictio):
					return len(maxFlow)

				dictio[a][possible][0] = dictio[a][possible][0] + 1
				flow.pop()

			else:
				memoryStack.append([edges, i, a, chain])
				memoryStack.append([aux_edges, 0, possible, chain + 1])
				flag = True	
				if(chain + 1> maxValue):
					maxValue = chain + 1
					maxFlow = flow.copy()
				if(not dictio):
					return len(maxFlow)

				break
		if(not flag):
			if(len(memoryStack) > 0):
				possible = flow[-1]
				dictio[flow[-2]][flow[-1]][0] = dictio[flow[-2]][flow[-1]][0] + 1
				possible = flow.pop()
	return -1

def solve(a, startTime):
	valor = 0
	for value in sorted(list(a.keys())):
		flow.append(value)
		#print(a)
		aux = recursive(value, a , 0, startTime)
		if(aux != -1):
			return
		if(maxValue > valor):
			valor = maxValue
		flow.pop()

dict = {}
inputSize = 0;

startTime = time.time()
for line in sys.stdin.readlines():
	firstLetter = line[0].lower()
	lastLetter = line[-2].lower()
	if(not firstLetter in dict):
		dict[firstLetter] = {}
	if(not lastLetter in dict[firstLetter]):
		dict[firstLetter][lastLetter] = [1, [line[:-1]]] 
	else:
		dict[firstLetter][lastLetter][0] = dict[firstLetter][lastLetter][0] + 1
		dict[firstLetter][lastLetter][1].append(line[:-1])
	inputSize = inputSize + 1

if(inputSize == 0):
	exit()

maxInputChain = inputSize
	
solve(dict, startTime) 
count = 0;
initial = maxFlow[0]
for a in maxFlow:
	count = count+1
	if(count == 1):
		continue
	print(dict[initial][a][1][0])
	del dict[initial][a][1][0]
	initial = a
