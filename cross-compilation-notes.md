
### Debian Sid Repository Conflicts

- The cpp-dev base container uses bleeding-edge Debian "Sid" (unstable) for its core amd64 C libraries.

- Standard apt-get attempts to pull arm64 cross-compilation packages from Debian "Trixie" (testing), causing catastrophic version mismatches (e.g., libgcc-s1 conflicts).

- The Fix: Multiarch target libraries (:arm64) must always be explicitly installed using the -t sid flag so their versions perfectly align with the host environment.

### Host Pollution & EM:62 Linker Errors

- The base container author manually installed custom x86_64 versions of gRPC, Protobuf, RE2, and Abseil into the /usr/local/ directory.

- When cross-compiling, CMake will aggressively default to finding these x86_64 libraries instead of your arm64 target libraries, resulting in Relocations in generic ELF (EM: 62) format errors.

- The Fix: The Dockerfile must physically purge these local files (rm -rf /usr/local/lib/libgrpc*, etc.) to prevent CMake from discovering them.

### Custom Protoc Compiler Mismatch

- A custom-built protoc executable was left in /usr/local/bin/. This generated C++ headers (like runtime_version.h) that were too new for the standard Debian sid target libraries.

- The Fix: Purge /usr/local/bin/protoc and rely strictly on the official protobuf-compiler from the Debian package manager to ensure the generated code matches the linked libraries.

### Strict CMake Path Routing

- Even with clean containers, CMake will search the host's /usr/lib/x86_64-linux-gnu/ path by default.

- The Fix: Your CMakeLists.txt must explicitly contain set(CMAKE_IGNORE_PATH ...) to blind CMake to /usr/local and x86_64 folders, and link_directories("/usr/lib/aarch64-linux-gnu") to force it into the multiarch target directory.
