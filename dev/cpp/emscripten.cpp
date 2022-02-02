#include <emscripten.h>
#include <emscripten/bind.h>
#include <string>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "emscripten/html5.h"
#include "Context.cpp"

Context* contexts[2];

int main(int argc, char const *argv[]) {
    printf("[WASM] Loaded\n");

    EM_ASM(
        if (typeof window!="undefined") {
            window.dispatchEvent(new CustomEvent("wasmLoaded"))
        } else {
            global.onWASMLoaded && global.onWASMLoaded()
        }
    );

    return 0;
}

void clearContexts() {
    if (contexts[0]) delete contexts[0];
    if (contexts[1]) delete contexts[1];
}

void createContext(int width, int height, long id, int index) {
    char* idc = reinterpret_cast<char*>(id);
    contexts[index] = new Context(width, height, idc);
    free(idc);
}

void loadTexture (long buf, int bufSize) {
    printf("[WASM] Loading Texture \n");
    uint8_t* bufId = reinterpret_cast<uint8_t*>(buf);
    contexts[0]->run(bufId);
    free(bufId);
}

void detectEdges (long buf, int bufSize) {
    printf("[WASM] Detecting edges \n");
    uint8_t* bufId = reinterpret_cast<uint8_t*>(buf);
    contexts[1]->run(bufId);
    free(bufId);
}

EMSCRIPTEN_BINDINGS(SHADAERS) {
    using namespace emscripten;

    function("clearContexts", &clearContexts);
    function("createContext", &createContext, allow_raw_pointers());
    function("loadTexture", &loadTexture, allow_raw_pointers());
    function("detectEdges", &detectEdges, allow_raw_pointers());

}
    