import os
import sys
if len(sys.argv) < 3:
	print("Usage: bin2c.py <input_file> <output file>")
in_file = open(sys.argv[1], 'rb')

# Get filelen
in_file.seek(0, os.SEEK_END)
length = in_file.tell()
in_file.seek(0, 0)

out_file = open(sys.argv[2], 'w')
out_file.write("uint32_t input_file_len = ")
out_file.write(str(length))
out_file.write(";\n")
out_file.write("uint8_t input_file[] = {")
for b in range(0, length):
	out_file.write(hex(int.from_bytes(in_file.read(1), 'big')))
	if b < (length-1): out_file.write(",\t")
	if (b % 6 == 0):
		out_file.write("\n\t")
out_file.write("};")
in_file.close()
out_file.close()


