# Problem Name: The Aliens

# Problem Description: You are given a string of digits, you have to find out how many digits are in the range 1 to 26

# Solution: The most simplest solution explains it the best. This is from @Annaray.

n=str(input())
k=0
for i in range(1,27):
	if str(i) in n:
		k+=1
print (k)