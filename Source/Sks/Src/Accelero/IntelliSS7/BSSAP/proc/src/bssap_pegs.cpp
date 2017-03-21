#include <bssap_pegs.h>
#include <its_hash.h>
#include <BSSAP++.h>
#include <bssap.h>
extern  HASH_Table BSCID_Table;

//BSSAPPEG_Manager BSSAP_Pegs;
#define _BSCID_ENT   0xab
#define FIX         0x60U
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

int
BSSAPPEG_IncrPeg(int p,char bscid)
{
BSSAPPEG_Manager *findpeg=NULL;
BSSAPPEG_Manager *Addpeg=NULL;

ITS_UINT key=bscid|FIX <<8;
// BSSAP_DEBUG(("BSSAP_PEG: key=%d",key));

      //  Addpeg=(BSSAPPEG_Manager *)malloc(sizeof(BSSAPPEG_Manager));

      //  memset(Addpeg,0,sizeof(BSSAPPEG_Manager));

        if(HASH_FindEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER *)&findpeg)==ITS_SUCCESS)
        {
       //    memcpy(Addpeg,findpeg,sizeof(BSSAPPEG_Manager));
             findpeg->pegs[p]+=1;
             if (HASH_AddEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER)findpeg)!= ITS_SUCCESS)
             {
                  BSSAP_ERROR(("BSSAP_PEG:Add Entry Fail"));
                  return !ITS_SUCCESS;
             }
        }
        else
        {
//           BSSAP_DEBUG(("New entry for bscId %d", bscid));
           Addpeg=(BSSAPPEG_Manager *)malloc(sizeof(BSSAPPEG_Manager));
           memset(Addpeg,0,sizeof(BSSAPPEG_Manager));
           Addpeg->pegs[p]+=1;
           Addpeg->bscid=bscid;
           Addpeg->numPegs=PEG_BSSAP_NUM_PEGS;

          if (HASH_AddEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER)Addpeg)!= ITS_SUCCESS)
          {
             BSSAP_ERROR(("BSSAP_PEG:Add Entry Fail"));
             return !ITS_SUCCESS;

          }
       }

     return ITS_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

int
BSSAPPEG_DecPeg(int p,char bscid)
{

BSSAPPEG_Manager *peg=NULL;
ITS_UINT key=bscid|FIX <<8;


   if (HASH_FindEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER*)&peg)!= ITS_SUCCESS)
       {
        BSSAP_ERROR(("BSSAP_PEG: Entry not found"));
        return 0;  

       }
    else
       {

        peg->pegs[p]-=1;
        if (HASH_AddEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER)peg)!= ITS_SUCCESS)
         {
            BSSAP_ERROR(("BSSAP_PEG:Add Entry Fail"));

          }
       } 
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

int
BSSAPPEG_GetPeg(int p,char bscid)
{

BSSAPPEG_Manager *findpeg=NULL;

ITS_UINT key=bscid|FIX <<8;


//        BSSAP_DEBUG(("BSSAP_PEG: key=%d",key));
   if (HASH_FindEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER*)&findpeg)!= ITS_SUCCESS)
       {
        BSSAP_ERROR(("BSSAP_PEG: Entry not found"));
        return 0;  

       }
    else
       {
//        BSSAP_DEBUG(("BSSAP_PEG: peg=%d",findpeg->pegs[p]));
//        BSSAP_DEBUG(("BSSAP_PEG: bscid=%d",findpeg->bscid));

        return findpeg->pegs[p];
       }
}

/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

int
BSSAPPEG_ClearPeg(int p,char bscid)
{

BSSAPPEG_Manager *peg=NULL;
ITS_UINT key=bscid|FIX <<8;

   if (HASH_FindEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER*)&peg)!= ITS_SUCCESS)
       {
        BSSAP_DEBUG(("BSSAP_PEG: Entry not found"));
        return 0;  

       }
    else
       {

         peg->pegs[p]=0;
         if (HASH_AddEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER)peg)!= ITS_SUCCESS)
          {
            BSSAP_DEBUG(("BSSAP_PEG:Add Entry Fail"));

          }
       } 
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

int
BSSAPPEG_ClearBlockPeg(char bscid)
{

BSSAPPEG_Manager *peg=NULL;

ITS_UINT key=bscid|FIX <<8;

   if (HASH_FindEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER*)&peg)!= ITS_SUCCESS)
       {
        BSSAP_DEBUG(("BSSAP_PEG: Entry not found"));
        return 0;  

       }
    else
       {
     
         if (peg->numPegs > 0)
         {
            BSSAP_DEBUG(("Clearing BSSAP Peg"));
            memset(peg->pegs, 0, peg->numPegs * sizeof(ITS_UINT));
         }

         if (HASH_AddEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER)peg)!= ITS_SUCCESS)
          {
            BSSAP_DEBUG(("BSSAP_PEG:Add Entry Fail"));

          }
       } 
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

int 
BSSAPPEG_DeletePegNode(char bscid)
{


BSSAPPEG_Manager *peg=NULL;

ITS_UINT key=bscid|FIX <<8;

   if (HASH_FindEntry(BSCID_Table,_BSCID_ENT,key,(ITS_POINTER*)&peg)!= ITS_SUCCESS)
       {
        BSSAP_DEBUG(("BSSAP_PEG: Entry not found"));
        return 0;  

       }
  else
   {

     if( HASH_DeleteEntry(BSCID_Table,_BSCID_ENT,key)!=ITS_SUCCESS)
     {
        BSSAP_DEBUG(("BSSAP_PEG: Entry not Delete"));
        return 0;  
     }
     if(peg)
     {
      free(peg);

     }
   }

}
