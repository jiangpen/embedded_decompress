# embedded_decompress
The fastLZ lib used in embedded system to compress/decompress the data.<br />
The typical scenario is compressing in PC side and decompressing in embedded side.<br />
The decompress performance, test in GCC/ARM achitecture.<br />
* Code size:<500 bytes in flash usage.
* RAM usage: depends on block size, 2K is good one. The bigger block size, the better compress performance.
* Speed: Decompressing a 187K file takes <80ms running on a 60M hz ARM MCU.
