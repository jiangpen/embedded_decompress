# embedded_decompress
The fastLZ lib used in embedded system to compress/decompress the data.
Flash:<500 bytes in flash usage.
RAM: depends on block size, 2K is good one. The bigger block size, the better compress performance.
Speed: Decompressing a 187K file takes <80ms running on a 60M hz ARM MCU.
