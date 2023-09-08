nombre_archivo = 'trama.bin'

contador = 0

with open(nombre_archivo, 'wb') as f:
    for n in range(45000):
        frame = [27, contador, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
        f.write(bytearray(frame))

        if(contador == 255):
            contador = 0
        else:
            contador = contador + 1