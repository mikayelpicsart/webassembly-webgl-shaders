# WebAssembly WebGL Shaders

Example project for using WebGL shaders in a WebAssembly program.

---
## Article link
https://medium.freecodecamp.org/how-to-use-webgl-shaders-in-webassembly-1e6c5effc813

---

Run ```npm install```, for dependencies, ```node server``` to serve files, and ```grunt``` for compiling changes.

To compile:

`emcc --bind -o ./dist/appWASM.js ./dev/cpp/emscripten.cpp -O3 -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 -s NO_EXIT_RUNTIME=1 -std=c++17 -s EXPORTED_RUNTIME_METHODS="['stringToUTF8']" -s ASSERTIONS=1 -s USE_PTHREADS=1 -s -s PTHREAD_POOL_SIZE=4 -Wno-pthreads-mem-growth`

or compile with DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 ([Thank you veslam](https://github.com/DanRuta/webassembly-webgl-shaders/pull/2))
