f=open("RULES.txt", "r")
g=open("rules.txt", "w")

while(1):
	a=f.readline().split()
	if not a:
		break
	for i in range(len(a)):
		if a[i].isupper():print "chut"
		else: a[i] = a[i].lower()
	a = " ".join(a)
	a+= " ."
	a += "\n"
	g.write(a)