# gabarit_tp4_log2400

Gabarit du TP4 de LOG2400 !!!

## Prerequis

- CMake 3.15 ou plus recent
- Un compilateur compatible C++17 :
  - Windows : MSVC (Visual Studio 2022)
  - Linux/macOS : `g++` ou `clang++`

## Structure du projet

- `include/` : fichiers d'en-tete
- `src/` : fichiers source (`.cpp`)
- `CMakeLists.txt` : configuration de compilation

## Compiler et executer (Windows / PowerShell)

1. Generer les fichiers de build :

```powershell
cmake -S . -B build
```

2. Compiler en mode Debug :

```powershell
cmake --build build --config Debug
```

3. Executer :

```powershell
.\build\Debug\TonYogourt.exe
```

Option Release :

```powershell
cmake --build build --config Release
.\build\Release\TonYogourt.exe
```

## Compiler et executer (Linux / macOS)

1. Generer + configurer (Debug) :

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

2. Compiler :

```bash
cmake --build build
```

3. Executer :

```bash
./build/TonYogourt
```

Option Release :

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/TonYogourt
```

## Nettoyer le build

Windows (PowerShell) :

```powershell
Remove-Item -Recurse -Force build
```

Linux/macOS :

```bash
rm -rf build
```
