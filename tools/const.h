#ifndef __CONST__H
#define __CONST__H

#define SECTOR_SIZE     512         // Bytes
#define SIGNATURE       "PFSv0100"  
#define FILE_ENTRY_SIZE 256         // Bytes
#define FILENAME_SIZE   32
#define INDEX_SIZE      (FILE_ENTRY_SIZE - FILENAME_SIZE)

#endif
