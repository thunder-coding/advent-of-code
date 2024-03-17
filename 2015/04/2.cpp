#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <openssl/md5.h>
#include <string>

int main() {
  auto input = std::ifstream("./2015/04/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/04/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  const auto size = std::filesystem::file_size("./2015/04/input.txt");
  std::string secret(size, '\0');
  input.read(secret.data(), size);

  for (uint64_t answer = 1; answer != std::numeric_limits<uint64_t>::max();
       answer++) {
    std::string secretString = secret + std::to_string(answer);
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, secretString.data(), secretString.size());
    unsigned char md5sum[16];
    MD5_Final(md5sum, &ctx);
    if (md5sum[0] == 0 && md5sum[1] == 0 && md5sum[2] == 0) {
      std::cout << answer << std::endl;
      return EXIT_SUCCESS;
    }
  }
  std::cerr << "No answer in the limits of uint64_t" << std::endl;
  return EXIT_FAILURE;
}
