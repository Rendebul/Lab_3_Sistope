# Esta es la target que se ejecuta por defecto si se escribe "make" en la consola
all: dev

# Compilación principal del ejecutable
dev:
	@echo 'Compilando'
	gcc wave.c funciones.c -o wave -lm -lpthread
	@echo "Ejecute el programa haciendo: ./wave -n Ni -h Hi -i iteraciones -d"
	@echo "Donde  archivo: nombre del archivo junto a su extension. Ej: ejemplo1.txt"
	@echo "       Ni: tamaño de la matriz."
	@echo "       Hi: cantidad de hebras de la matriz."
	@echo "		  iteraciones: numero de iteraciones."
	@echo "       -d: (opcional) Si desea resultado por pantallas."
	