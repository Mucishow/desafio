maxValue = 0
flow = []
maxFlow = []

def recursive(a, dictio, chain):
	global maxValue
	global maxFlow

	if(chain == 994):
		return chain
	if(chain > maxValue):
		maxValue = chain
		maxFlow = flow.copy()
		#print(maxFlow)
		#print(flow)
	#print(chain)
	#print(dictio)
	if(not a in dictio):
		return -1
	if(not dictio):
		return maxValue
		
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

		flow.remove(possible)
		dictio[a][possible][0] = dictio[a][possible][0] + 1
		#print(dictio)
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
		flow.remove(value)

dict = {}



with open('test06.txt') as f:
	for line in f.readlines():
		line = line.lower()
		if(not line[0] in dict):
			dict[line[0]] = {}
		if(not line[-2] in dict[line[0]]):
			dict[line[0]][line[-2]] = [1, [line[:-1]]] 
			#dict[line[0]][line[-2]] = [1] 
		else:
			dict[line[0]][line[-2]][0] = dict[line[0]][line[-2]][0] + 1
			dict[line[0]][line[-2]][1].append(line[:-1])

solve(dict) 
count = 0;
initial = maxFlow[0]
for a in maxFlow:
	count = count+1
	if(count == 1):
		continue
	print(dict[initial][a][1][0])
	dict[initial][a][1][0]
	del dict[initial][a][1][0]
	initial = a

