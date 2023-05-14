#pragma once

int mymemcpy(void *dest, const void *src, int n) {
  char *csrc = (char *)src;
  char *cdest = (char *)dest;
  for (int i = 0; i < n; i++) {
    cdest[i] = csrc[i];
  }
  return 0;
}
