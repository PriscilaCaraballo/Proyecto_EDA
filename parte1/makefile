compilador = g++
flags = -std=c++17 -Wall -Wextra -Wpedantic -O2

SRC = editor.cpp impl_editor.cpp
EXE = editor

salida = mi_salida.txt
all:
	$(compilador) $(flags) -o $(EXE) $(SRC)

test_ejemplo:
	./$(EXE) < tests/ejemplo_obligatorio.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/ejemplo_obligatorio.out.txt $(salida)

test_alias:
	./$(EXE) < tests/test_alias.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_alias.out.txt $(salida)

test_basico:
	./$(EXE) < tests/test_basico.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_basico.out.txt $(salida)

test_casos_limite:
	./$(EXE) < tests/test_casos_limite.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_casos_limite.out.txt $(salida)

test_completo:
	./$(EXE) < tests/test_completo.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_completo.out.txt $(salida)

test_consecutivo:
	./$(EXE) < tests/test_consecutivo.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_consecutivo.out.txt $(salida)

test_contar:
	./$(EXE) < tests/test_contar.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_contar.out.txt $(salida)

test_errores:
	./$(EXE) < tests/test_errores.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_errores.out.txt $(salida)

test_limites:
	./$(EXE) < tests/test_limites.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_limites.out.txt $(salida)	

test_memoria:
	./$(EXE) < tests/test_memoria.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_memoria.out.txt $(salida)

test_multiple_archivos:
	./$(EXE) < tests/test_multiple_archivos.in.txt > $(salida)
	diff -u --strip-trailing-cr tests/test_multiple_archivos.out.txt $(salida)
	
tests: all
	make test_ejemplo
	make test_alias
	make test_basico
	make test_casos_limite
	make test_completo
	make test_consecutivo
	make test_contar
	make test_errores
	make test_limites
	make test_memoria
	make test_multiple_archivos
	
clean:
	rm -f $(EXE) $(salida)