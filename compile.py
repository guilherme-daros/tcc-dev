import os
import subprocess

line_width  = [4, 8, 16, 32, 64]
model_depth = [1, 2, 4, 8]
data_width  = [54, 108, 216, 432]

last_model = "lw4_md1"
last_dw = "54"

for lw in line_width:
    for md in model_depth:
        for dw in data_width:
            print(f"compiling lw{lw}_md{md}_{dw}.elf\n")
            
            with open("./apps/tcc_final/src/models/CMakeLists.txt", "w+") as file:
                file.write(f'''target_sources(tcc_final PUBLIC ${{CMAKE_CURRENT_LIST_DIR}}/lw{lw}_md{md}.cc)''')

            with open("./apps/tcc_final/main.cpp", "r") as file:
                data = file.read()
                data = data.replace(last_model, f"lw{lw}_md{md}")             
            with open("./apps/tcc_final/main.cpp", "w") as file:
                file.write(data)

            with open("./apps/tcc_final/src/server_functions.cpp", "r") as file:
                data = file.read()
                data = data.replace(last_dw, str(dw)) 
            with open("./apps/tcc_final/src/server_functions.cpp", "w") as file:
                file.write(data)

            subprocess.run(f'cmake --build ./build --config Release --target install -j 10 --'.split(' '),
                                  stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

            subprocess.run(f'mv ./images/tcc_final.elf ./images/tcc_lw{lw}_md{md}_{dw}.elf'.split(' '),
                                  stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            
            last_dw = str(dw)
            last_model = f"lw{lw}_md{md}"

            print(f"last -> {last_model}_{last_dw}.elf")



            
