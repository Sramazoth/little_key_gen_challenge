#!/usr/bin/python3.10

years = ["2023", "2024", "2025"]
second_part = ["kco", "koc", "okc", "ock", "cko", "cok"]

available_checksums = dict()

def third_part():
	for x in range(13, 10000, 13):
		if x < 10:
			yield '000' + str(x)
		elif x < 100:
			yield '00' + str(x)
		elif x < 1000:
			yield '0' + str(x)
		else:
			yield str(x)

if __name__ == "__main__":
	for x in third_part():
		for y in second_part:
			for z in years:
				first_key = z + y + x
				csum = 0
				for c in first_key:
					csum += ord(c)
					# print(f"{c} = {ord(c)}")
				# print(csum)
				if csum not in available_checksums:
					available_checksums[csum] = first_key
	# print(available_checksums)
	for cs in available_checksums:
		for x in range(4095):
			hex_cs = "{:03x}".format(x)
			# print(hex_cs)
			csum_cs = 0
			for c in hex_cs:
				csum_cs += ord(c)
			if cs + csum_cs == x:
				print(f"{available_checksums[cs]}{hex_cs} : {cs} {csum_cs} : {x}")
		# print(f"{cs} == {hex(cs)}")

