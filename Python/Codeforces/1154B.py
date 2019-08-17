n = int(input());
a = [int(i) for i in input().split()]

uniq = sorted(list(set(a)))

if len(uniq) == 1:
	print(0)
elif len(uniq) == 2:
	diff = uniq[1] - uniq[0]
	print("%d" % (diff//2 if diff % 2 == 0 else diff))
elif len(uniq) == 3:
	diff = uniq[2] - uniq[0];
	if diff % 2 == 0:
		if uniq[0] + diff//2 == uniq[1]:
			print(diff//2)
		else:
			print(-1)
	else:
		print(-1)
else:
	print(-1)