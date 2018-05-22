import shlex,subprocess

with open ("blastQueryFull.txt", "r") as ifile:
	for line in ifile:
      		if not line.strip():
      			break
   		#print line
		args = shlex.split(line)
		output = subprocess.Popen(line, stdout=subprocess.PIPE,shell=True).communicate()[0]
		if output: print output.strip()
