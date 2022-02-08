

onmessage = function(evt) {
    debugger

    (async () => {
      debugger
      const importObject = {
        module: {},
        env: {
          memory: new WebAssembly.Memory({ initial: 256 }),
        }
      };
      const response = await fetch('./dist/appWASM.wasm');
      const buffer = await response.arrayBuffer();
      const module = await WebAssembly.compile(buffer);
      const instance = new WebAssembly.instantiate(module, importObject);
      const result = instance.exports.fibonacci(42);
      console.log(result);
    })();

    var canvas = evt.data.canvas;
    var gl = canvas.getContext("webgl");
    const imageData = evt.data.imageData;

    // Pass the imageData to the C++ code
    let bufferArray = new Uint8Array(imageData);
    const numBytes = bufferArray.length * bufferArray.BYTES_PER_ELEMENT;
    const dataPtr = Module._malloc(numBytes);
    const dataOnHeap = Module.HEAPU8.subarray(dataPtr, dataPtr + numBytes);
    dataOnHeap.set(bufferArray);
    Module.loadTexture(dataPtr, numBytes);
    Module.detectEdges(dataPtr, numBytes);
  
    // ... some drawing using the gl context ...
};