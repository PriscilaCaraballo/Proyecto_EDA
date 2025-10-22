#!/usr/bin/env bash

tests=(
  "test_alias_completo"
  "test_basico_versiones"
  "test_ejemplo_letra"
  "test_comparar_versiones"
  "test_completo_final"
  "test_restricciones_comandos"
  "test_casos_error"
)

total_tests=${#tests[@]}
tests_exitosos=0
tests_fallidos=()

for test in "${tests[@]}"; do
  if [ -f "tests/${test}.in.txt" ] && [ -f "tests/${test}.out.txt" ]; then
    # Comparar con salida esperada
    ./menu_editor <"tests/${test}.in.txt" >"temp_output.txt" 2>&1

    if diff -q --strip-trailing-cr "tests/${test}.out.txt" "temp_output.txt" >/dev/null; then
      ((tests_exitosos++))
    else
      tests_fallidos+=("$test")
    fi

    rm -f "temp_output.txt"
  else
    tests_fallidos+=("$test")
  fi
done

# Solo mostrar output si hay tests fallidos
if [ ${#tests_fallidos[@]} -gt 0 ]; then
  echo "=== Tests Fallidos ==="
  for test in "${tests_fallidos[@]}"; do
    echo "✗ Test $test FALLÓ"

    if [ -f "tests/${test}.in.txt" ] && [ -f "tests/${test}.out.txt" ]; then
      echo "  Salida generada:"
      ./menu_editor <"tests/${test}.in.txt" 2>&1 | head -10

      echo "  Diferencias encontradas:"
      ./menu_editor <"tests/${test}.in.txt" >"temp_output.txt" 2>&1
      diff --color=always --strip-trailing-cr "tests/${test}.out.txt" "temp_output.txt" | head -15
      rm -f "temp_output.txt"
    else
      echo "  ✗ Archivos de test no encontrados"
    fi
    echo ""
  done

  echo "=== Resumen ==="
  echo "Tests ejecutados: $tests_exitosos/$total_tests"
  echo "✗ Algunos tests fallaron"
  exit 1
else
  exit 0
fi
