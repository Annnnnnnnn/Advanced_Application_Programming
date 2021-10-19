
#include <emscripten.h>
#include <stddef.h>
extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.

EM_JS(void, array_bounds_check_error, (size_t idx, size_t size), {
  throw 'Array index ' + idx + ' out of bounds: [0,' + size + ')';
});

void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    array_bounds_check_error(array_idx, array_size);
  }
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

// Solution

Solution* EMSCRIPTEN_KEEPALIVE emscripten_bind_Solution_Solution_0() {
  return new Solution();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_Solution_getTime_0(Solution* self) {
  return self->getTime();
}

char* EMSCRIPTEN_KEEPALIVE emscripten_bind_Solution_grayCode_1(Solution* self, int val) {
  return self->grayCode(val);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_Solution___destroy___0(Solution* self) {
  delete self;
}

}

