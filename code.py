maxValue = 0
def recursive(a, dictio, chain):
	global maxValue
	if(chain > maxValue):
		print(maxValue)
		maxValue = chain
	#print(chain)
	#print(dictio)
	if(not a in dictio):
		return -1
	if(not dictio):
		return maxValue
	for possible in dictio[a].keys():
		#print(possible)
		if(dictio[a][possible] == 0):
			continue

		dictio[a][possible] = dictio[a][possible] -1
		#print("REMOVE " + a + " - " + possible)
		#print(dictio)
		valor = recursive(possible, dictio, chain+1)
		maxValue = maxValue + 1
		if(valor != -1):
			return valor
		maxValue = maxValue - 1
		dictio[a][possible] = dictio[a][possible] + 1
		#print("ADD " + a + " - " + possible)
		#print(dictio)
	return -1

def solve(a):
	valor = 0
	for value in a.keys():
		print("NEW " + value)
		aux = recursive(value, a , 0)
		if(maxValue > valor):
			valor = maxValue
		print(valor)

	print(valor)
	print(maxValue)
dict = {}

with open('test02.txt') as f:
	for line in f.readlines():
		line = line.lower()
		if(not line[0] in dict):
			dict[line[0]] = {}
		if(not line[-2] in dict[line[0]]):
			dict[line[0]][line[-2]] = 1 
		else:
			dict[line[0]][line[-2]] = dict[line[0]][line[-2]] + 1

print(dict)
solve(dict)
