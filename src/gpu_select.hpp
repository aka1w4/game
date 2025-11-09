#ifndef GPU_SELECT_H
#define GPU_SELECT_H

#ifdef _WIN32
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#elif defined(__linux__)
#include <stdlib.h>
static inline void enable_nvidia_gpu(void) {
  setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 1);
  setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 1);
}
#endif

#endif
