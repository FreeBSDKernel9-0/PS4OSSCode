# PlayStation 4 Open Source Software - Massive Collection

This archive contains a consolidated collection of open-source software source code used in the PlayStation 4 (Orbis OS).

## Contents

### 1. Sony-Hosted Source Code (`/sony_hosted`)
These are the files directly provided by Sony Interactive Entertainment on their official OSS portal.
- **WebKit**: Multiple versions for different system firmware.
- **FFmpeg**: The specific version used by Sony.
- **Other Libraries**: Various small components hosted by Sony.

### 2. External Source Code (`/external`)
These are the source codes for major components that Sony uses but does not host directly. These have been fetched from official archives based on the versions used in the PS4.
- **FreeBSD 9.0 Kernel & Userland**: The foundation of Orbis OS.
- **Lua 5.2.4**: Scripting engine.
- **OpenSSL 1.0.1**: Cryptography library.
- **zlib 1.2.8**: Compression library.
- **SQLite 3.7.17**: Database engine.

### 3. Documentation (`/docs`)
- **OSS Notices**: License information and acknowledgments.

## Disclaimer
This collection is for educational and research purposes. All software is subject to its respective original licenses (GPL, LGPL, BSD, MIT, etc.). Sony's modifications to the FreeBSD kernel are proprietary and are NOT included in the standard FreeBSD source code provided here.
