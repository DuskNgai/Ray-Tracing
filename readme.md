# C++17-based Ray Tracing

The project is based on the book [Ray Tracing in One Weekend](https://raytracing.github.io/).

**On Unix-like systems**:

```bash
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build --parallel
./bin/Release/Ray-Tracing --config-file-path config/weekend/sky.json --output-file-path result/weekend/sky.png
```

**On Windows**:

```powershell
cmake -S . -B ./build
cmake --build ./build --config Release --parallel
.\bin\Release\Ray-Tracing.exe --config-file-path config\weekend\sky.json --output-file-path result\weekend\sky.png
```
