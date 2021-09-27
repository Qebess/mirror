class Calculator(object):
	
	def evaluate(self,obj):
		print(obj)
		def simple_calc(arr):
			if arr[0] == "(":
				del arr[0]
				del arr[-1]
			flag = 1
			while flag == 1:
				flag = 0
				for i in range(len(arr)):
					if arr[i] == "*":
						arr[i-1] = arr[i-1]* arr[i+1]
						del arr[i]
						del arr[i]
						flag = 1
						break
					if arr[i] == "/":
						arr[i-1] = arr[i-1] / arr[i+1]
						del arr[i]
						del arr[i]
						flag = 1
						break
			flag = 1
			while flag == 1:
				flag = 0
				for  i in range(len(arr)):
					if arr[i] == "+":
						arr[i-1] = arr[i-1] + arr[i+i]
						del arr[i]
						del arr[i]
						flag = 1
						break
					if arr[i] == "-":
						arr[i-1] = arr[i-1] - arr[i+1]
						del arr[i]
						del arr[i]
						flag = 1
						break
			if type(arr[0]) == type(.0):
				if arr[0].is_integer:
					return int(arr[0])
			return arr[0]

		arr = obj.split()
		for i in range(len(arr)):
			if arr[i].isalnum():
				arr[i] = int(arr[i])
		flag = 1
		while flag == 1:
			flag = 0
			max_depth = -1
			current_depth = 0
			pos_s = 0
			pos_e = -1
			for i in range(len(arr)):
				if arr[i] == "(":
					current_depth +=1
					if current_depth > max_depth:
						max_depth = current_depth
						pos_s = i
				if arr[i] == ")":
					current_depth -=1
			for i in range(pos_s,len(arr),1):
				if arr[i] == ")":
					pos_e = i
					break
			if pos_e == -1:
				arr[0] = simple_calc(arr)
				del arr[1::]
				break
			else:
				arr[pos_s] = simple_calc(arr[pos_s:pos_e+1:])
				del arr[pos_s+1:pos_e+1:]
				flag = 1

		return arr[0]

