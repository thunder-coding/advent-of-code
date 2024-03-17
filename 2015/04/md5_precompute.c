#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  FILE *output_file = fopen("./2015/04/md5_precompute.h", "w");
  fprintf(output_file, "#include <stdint.h>\n\n");
  fprintf(output_file, "const static uint32_t T[64] = {\n");
  for (int i = 0; i < 64; i++) {
    fprintf(output_file, "  0x%08x,\n",
            (uint32_t)fabs((((uint64_t)1 << 32) * sin(i + 1))));
  }
  fprintf(output_file, "};");
  fclose(output_file);
}
