# PuddleJump

PuddleJump is a lightweight, dynamic SOCKS4 proxy wrapper for Linux written in C. It intercepts standard TCP network connections initiated by applications using `LD_PRELOAD` and transparently routes them through a local SOCKS4 proxy (such as Tor running on port `9050`).

This allows you to "proxy-ize" CLI tools and legacy applications without modifying their source code.

---

## How It Works

PuddleJump uses dynamic linking manipulation:

1. It overrides the standard `connect()` system function provided by `libc`.
2. When an application attempts to establish a network connection, PuddleJump intercepts the call.
3. It opens a socket to the specified SOCKS4 proxy (`127.0.0.1:9050` by default).
4. It performs a SOCKS4 handshake (`VN=4`, `CD=1`) to request a connection to the application's original intended destination.
5. Once the proxy confirms traversal (`CD=90`), PuddleJump replaces the application's socket descriptor with the proxy socket using `dup2()`, seamlessly passing control back to the application.

---

## Project Structure

```
.
├── PuddleJump.c      # Core implementation
├── PuddleJump.h      # Header definitions and configuration
├── Makefile          # Build instructions
└── README.md
```

| File | Description |
|------|-------------|
| `PuddleJump.c` | Core implementation intercepting `connect()` and managing the SOCKS4 handshake. |
| `PuddleJump.h` | Configuration constants, packed SOCKS4 request/response structures, and header definitions. |
| `Makefile` | Build instructions for compiling the shared library (`PuddleJump.so`). |

---

## Prerequisites

Before compiling, ensure you have:

- Linux
- `gcc`
- `make`
- A running SOCKS4 proxy service (default: Tor listening on `127.0.0.1:9050`)

---

## Installation & Compilation

Clone the repository:

```bash
git clone https://github.com/SV13/PuddleJump.git
cd PuddleJump
```

Compile the project:

```bash
make
```

This will generate:

```text
PuddleJump.so
```

---

## Usage

To force an application's network traffic through the proxy, preload the shared library using `LD_PRELOAD`.

### General Syntax

```bash
LD_PRELOAD=./PuddleJump.so <command>
```

### Example: curl

```bash
LD_PRELOAD=./PuddleJump.so curl https://icanhazip.com
```

### Example: wget

```bash
LD_PRELOAD=./PuddleJump.so wget http://example.com
```

---

## Configuration

If your SOCKS4 proxy is running on another host or port, modify the values inside `PuddleJump.h` before compiling.

```c
#define PROXY        "127.0.0.1"
#define PROXYPORT    9050
#define USERNAME     "Puddlejumper"
```

After making changes, rebuild the project:

```bash
make clean
make
```

---

## Notes

- Works by intercepting the `connect()` system call.
- Designed for dynamically linked Linux executables.
- Uses `LD_PRELOAD`, so statically linked binaries cannot be intercepted.
- Compatible with SOCKS4-compatible proxies such as Tor (with SOCKS4 support enabled).

---

## License

This project is licensed under the MIT License.