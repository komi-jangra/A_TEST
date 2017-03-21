/** ts=3 ******************************************************* File Header **
 FILE NAME         :  oamsxxx_treedatastruct.h
 PURPOSE           :  Contains abisE1node and Bicnode data structure
 PROJECT           :  BSS CS2.2
 SUBSYSTEM         :  OAMS
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/
#ifndef __OAMS_BICH_TREEDATASTRUCT_H
#define __OAMS_BICH__TREEDATASTRUCT_H

/* Purpose : This is the list data structure - an object of this type is needed to 
 * represent an abis e1 node and is attached to the abis e1 list
 */

typedef struct bichAbisE1Node
{
        I_U32                   e1Id;
        OamsTsList              abisChainList;  /* first BIC connected with E1 */
        OamsList                e1List; //points to the next abis e1 node
}AbisE1Node;

typedef struct bichE1TsNode
{
        I_U8                    timeSlot;
        I_U8                    tei;
        I_U8                    status;  /*value ABIS_E1_STATUS*   */
        OamsTree                bicTreeRoot;
        OamsTsList              tsList;
}AbisE1TsNode;


/* Purpose : This is the tree data structure - an object of this type is needed to represent a 
*	bic node and is attached to the tree list
*/

typedef struct bichBicNode
{
	I_U32			bicId;
	OamsTree		bicTree;
}BicNode;

/* Changes for issue #19948*/
typedef struct bichLapdDiscCntxt
{
	I_U8			  bicTei;
	I_U8        bmHelloCnt;
}LapdDiscCntxt;

LapdDiscCntxt lapdDiscCntxt[50];

#endif /*__OAMS_BICH_TREEDATASTRUCT_H*/

/********************************* Change History ***********************

 Revision
 initial version


 *************************************************************************/


