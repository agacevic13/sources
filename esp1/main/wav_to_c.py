# Konverzija WAV datoteke u C byte array
import sys

def wav_to_c_array(wav_file):
    with open(wav_file, "rb") as f:
        data = f.read()

    half_data = data[:len(data) // 2]

    c_array = "const uint8_t wav_data[] = {"
    for i in range(0, len(half_data), 16):
        c_array += ", ".join(f"0x{half_data[j]:02x}" for j in range(i, min(i + 16, len(half_data))))
        c_array += ",\n"
    c_array += "};\n"
    c_array += f"const size_t wav_data_size = {len(half_data)};"

    return c_array

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python wav_to_c_array.py <wav_file>")
        sys.exit(1)
    
    wav_file = sys.argv[1]
    c_array = wav_to_c_array(wav_file)
    print(c_array)
