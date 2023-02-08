import sys

#REMOVE RECURSIVE AND TEST OTHER LIMITS
maxValue = 0
flow = []
maxFlow = []
maxInputChain = 0
inputSize = 0
operations = 0

def recursive(a, dictio, chain):
	global maxValue
	global maxFlow
	global maxInputChain
	global inputSize
	global operations

	if(chain > maxValue):
		maxValue = chain
		maxFlow = flow.copy()
	if(chain >= maxInputChain):
		return maxInputChain

	#print(chain)
	#print(dictio)
	if(not a in dictio):
		return -1
	if(not dictio):
		return len(maxFlow)
		
	edges = filter(lambda posib: dictio[a][posib][0] > 0, dictio[a].keys())
	
	for possible in edges:
		#print(possible)

		if(dictio[a][possible][0] == 0):
			continue

		dictio[a][possible][0] = dictio[a][possible][0] - 1
		flow.append(possible)
		#print(a + " " + possible + " " +str(dictio[a][possible][0]))
		valor = recursive(possible, dictio, chain+1)
		if(valor != -1):
			return valor

		flow.pop()
		dictio[a][possible][0] = dictio[a][possible][0] + 1
		#print(dictio)

	
	if(inputSize > 50):
		operations = operations + 1 
	if(operations == 10000):
		operations = 0
		maxInputChain = maxInputChain - 1

	return -1

def solve(a):
	valor = 0
	for value in a.keys():
		flow.append(value)
		aux = recursive(value, a , 0)
		if(aux != -1):
			return
		if(maxValue > valor):
			valor = maxValue
		flow.pop()

dict = {}
inputSize = 0;

for line in sys.stdin.readlines():
	firstLetter = line[0].lower()
	lastLetter = line[-2].lower()
	if(not firstLetter in dict):
		dict[firstLetter] = {}
	if(not lastLetter in dict[firstLetter]):
		dict[firstLetter][lastLetter] = [1, [line[:-1]]] 
		#dict[line[0]][line[-2]] = [1] 
	else:
		dict[firstLetter][lastLetter][0] = dict[firstLetter][lastLetter][0] + 1
		dict[firstLetter][lastLetter][1].append(line[:-1])
	inputSize = inputSize + 1

if(inputSize == 0):
	exit()

sys.setrecursionlimit(inputSize + 1000)

maxInputChain = inputSize
	
solve(dict) 
count = 0;
initial = maxFlow[0]
for a in maxFlow:
	count = count+1
	if(count == 1):
		continue
	print(dict[initial][a][1][0])
	del dict[initial][a][1][0]
	initial = a
