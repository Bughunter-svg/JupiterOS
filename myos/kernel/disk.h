// kernel/disk.h
void read_disk(int sector, void* buffer);
void write_disk(int sector, void* buffer);
void format_fs();  // FAT12 or simple FS
