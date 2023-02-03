maxValue = 0
flow = []
maxFlow = []

def recursive(a, dictio, chain):
	global maxValue
	global maxFlow

	if(chain == 10):
		return -1
	if(chain > maxValue):
		maxValue = chain
		maxFlow = flow.copy()
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
			print(a + " " + possible + " empty")
			continue

		dictio[a][possible][0] = dictio[a][possible][0] - 1
		flow.append(possible)
		valor = recursive(possible, dictio, chain+1)
		flow.remove(possible)
		if(valor != -1):
			return valor
		dictio[a][possible][0] = dictio[a][possible][0] + 1
		#print(dictio)
	return -1

def solve(a):
	valor = 0
	print(len(a.keys()))
	for value in a.keys():
		print(value)
		flow.append(value)
		aux = recursive(value, a , 0)
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
			#dict[line[0]][line[-2]] = [1, [line]] 
			dict[line[0]][line[-2]] = [1] 
		else:
			dict[line[0]][line[-2]][0] = dict[line[0]][line[-2]][0] + 1
			#dict[line[0]][line[-2]][1].append(line)

print(dict)
solve(dict) 
count = 0;
initial = maxFlow[0]

for a in maxFlow:
	count = count+1
	if(count == 1):
		continue
	#print(dict[initial][a][1][0])
	initial = a

