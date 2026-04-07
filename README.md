# Estrategias de Ordenamiento — 100,000 Palabras

Ordena un dataset grande de palabras usando tres algoritmos diferentes y compara sus tiempos de ejecución.

## Algoritmos

| # | Algoritmo    | Estructura              | Complejidad                 |
|---|--------------|-------------------------|-----------------------------|
| 1 | QuickSort    | `std::vector`           | O(n log n) promedio         |
| 2 | HeapSort     | Max-Heap Binario        | O(n log n) siempre          |
| 3 | Árbol AVL    | ABB Auto-balanceado     | O(n log n) + O(n) recorrido |

## Estructura del Proyecto

```
Sorting-large-DataSet/
├── CMakeLists.txt       ← Archivo de build para CLion
├── README.md
├── .gitignore
├── main.cpp             ← Punto de entrada principal
├── avl_tree.h           ← Implementación del Árbol AVL
├── heapsort.h           ← Implementación del HeapSort
├── quicksort.h          ← Implementación del QuickSort
└── dataset.h            ← Lectura, conversión y escritura de archivos
```

## Requisitos

- g++ con soporte C++17 (`g++ --version`)
- Archivo `words_alpha.txt` con al menos 100,000 palabras (proporcionado por el profesor)

---

## Compatibilidad de archivos

El programa detecta y convierte automáticamente cualquier codificación:

| Codificación        | Compatible |
|---------------------|------------|
| UTF-8               | ✅          |
| UTF-8 con BOM       | ✅          |
| UTF-16 Little Endian| ✅          |
| UTF-16 Big Endian   | ✅          |

No es necesario convertir el archivo antes de usarlo — el programa lo maneja solo.

---

## Cómo compilar y ejecutar

### Opción A — CLion (recomendado)

1. **File → Open** → selecciona la carpeta `Sorting-large-DataSet`
2. CLion detecta el `CMakeLists.txt` automáticamente → clic en **OK / Trust**
3. Ve a **Run → Edit Configurations...**
4. En el campo **"Program arguments"** escribe la ruta completa al archivo de entrada:
   ```
   /Users/tu_usuario/Downloads/words_alpha.txt
   ```
5. Clic en **OK** y presiona ▶ **Run**

> **Nota:** Para obtener tiempos reales de ejecución, cambia el modo de **Debug** a **Release** en la barra superior de CLion antes de correr.

---

### Opción B — Terminal

```bash
# 1. Compilar
g++ -std=c++17 -O2 -o sorting main.cpp

# 2. Ejecutar pasando el archivo como argumento
./sorting /ruta/a/words_alpha.txt
```

---

## Archivos de salida

Los archivos se generan automáticamente en la **misma carpeta donde está el archivo de entrada**:

| Archivo                 | Contenido                               |
|-------------------------|-----------------------------------------|
| `dataset.txt`           | 100,000 palabras seleccionadas al azar  |
| `output_quicksort.txt`  | Palabras ordenadas por QuickSort        |
| `output_heapsort.txt`   | Palabras ordenadas por HeapSort         |
| `output_avl.txt`        | Palabras ordenadas por Árbol AVL        |

---

## Salida esperada en terminal

```
╔══════════════════════════════════════════════╗
║       SORTING STRATEGIES — 100k WORDS        ║
║  QuickSort | HeapSort | AVL Tree (inorder)   ║
╚══════════════════════════════════════════════╝

  Archivo de entrada : /Users/juanjo/Downloads/words_alpha.txt
  Carpeta de salida  : /Users/juanjo/Downloads

[ STEP 1 ] Construyendo dataset
  Loading : words_alpha.txt ...
  Created : dataset.txt  (100000 randomised words)

[ STEP 2 ] QuickSort
  Ordenadas 100000 palabras en 42.31 ms
  Saved   : output_quicksort.txt  (100000 words)

[ STEP 3 ] HeapSort
  Ordenadas 100000 palabras en 79.14 ms
  Saved   : output_heapsort.txt  (100000 words)

[ STEP 4 ] AVL Tree
  Insertadas y recorridas 100000 palabras en 72.55 ms
  Saved   : output_avl.txt  (100000 words)

┌──────────────────────────────────────────────┐
│              TIMING RESULTS                  │
├─────────────────────┬────────────────────────┤
│ Algorithm           │ Time                   │
├─────────────────────┼────────────────────────┤
│ QuickSort           │      42.31 ms          │
│ HeapSort            │      79.14 ms          │
│ AVL Tree (inorder)  │      72.55 ms          │
└─────────────────────┴────────────────────────┘
```

---

## Notas

- El dataset siempre se genera con semilla `42` para garantizar reproducibilidad.
- El Árbol AVL ignora palabras duplicadas (comportamiento estándar de un ABB).
- QuickSort puede verse lento en modo Debug de CLion — usar modo **Release** para tiempos reales.
- El programa soporta archivos UTF-16 (como los que provee el profesor) sin necesidad de conversión manual.
