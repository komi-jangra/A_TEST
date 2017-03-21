#include <sys/stat.h>
#include <oamsswmh_swmhlib.h>



struct stat fileStats ;

I_S8 getSoftwareVersionFileSize(I_S8 *binaryPath,  I_U32 *fileSize)
{
  I_S8 n ;
  n = stat(binaryPath, &fileStats) ;
  *fileSize = fileStats.st_size ;
  return n ; 
}


