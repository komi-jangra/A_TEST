/*******************************************************************************
**      FILE NAME:
**          bssap_port.c
**
**      DESCRIPTION:
**              This files defines the encoding & decoding of the called & calling party address used **              by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#include <time.h>
#include <stdlib.h>
#include <sl.h>
#include <s7_typ.h>
#include <s7_api.h>
#include <s7_def.h>
#include <s7_error.h>
#include <bs_stgl.h>
#include <bs_msgst.h>
#include <bs_api.h>
#include <bs_prov.h>
#include <bssap_port.h>
#include <bssapcom.h>

#include "bssap.h"

extern unsigned char msc_vlr_bssapp_ssn;
extern sl_pool_t ss7_pool;
extern int scf_dpc;
gt_info scf_gt_info;

extern return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
			      src_id_t src_id, dst_id_t dst_id,
			      error_t *p_ecode);

extern void ss7_send_to_m3ua (unsigned char *buf, unsigned int len);

U8bit sccp_assign_sls (const sccp_addr_t *p_cg_addr,
		       const sccp_addr_t *p_cd_addr,
		       U8bit incom_sls, U8bit proto_class)
{
#ifdef MTP3
	if (proto_class && sccp_self_pc!=p_cd_addr->pc)
		return incom_sls;
	else
		return (U8bit) rand () % 16;
#endif
    return 0;
}


#define	MAXFIELDS	64

#ifdef SCCP_BROADBAND
sc_opt_t sc_opt = { STACK_ITU, SCCP_DEFAULT_SEG_SIZE, SS7_BROADBAND_NETWORK  };
#else
sc_opt_t sc_opt = { STACK_ITU, SCCP_DEFAULT_SEG_SIZE, SS7_NARROWBAND_NETWORK  };
#endif

typedef struct	matchcmd_s {
	unsigned int	type;
	unsigned int	value;
	char	*first, 
		*last;
} matchcmd_t;

#define	__M_NULL	0
#define	__M_DIGIT	1
#define	__M_FIELD	2
#define	__M_REST	3

#define	__S_BASE	0
#define	__S_FIELD	1
#define	__S_DONE	2


void sccp_memmove (U8bit *dest, U8bit *src, s7_len_t noctets)
{
    memmove (dest, src, noctets);
}

/*****************************************************************************
**
**  FUNCTION NAME
**     sccp_deinit_complete_indication 
**
******************************************************************************
**
**  DESCRIPTION
**
**  INPUTS
**
**  RETURNS
**
*****************************************************************************/
return_t
sccp_deinit_complete_indication(void)
{
    return SS7_SUCCESS;
}

char* Prnt_Dtap(char val,int str)
{
 switch((val & 0x0F))
{
 case 3:
       return(BS_DTAP_MSG_TYPE_STR_CC((str & 0x3F)));
       break;
 case 5:
       return(BS_DTAP_MSG_TYPE_STR_MM(str));
       break;
 case 9:
       return(BS_DTAP_MSG_TYPE_STR_SMS(str));
       break;
 default:
       printf("BS: Prnt_Dtap:Def case reached\n");
       break;
}
       return("UNKNOWN_DTAP_MSG");
}	

/***************************************************************************
**
**      FUNCTION :
**         calculates SCCP address length
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U8bit
sccp_addr_len
#ifdef ANSI_PROTO
  (sccp_addr_t * p_addr)
#else
  (p_addr)
  sccp_addr_t * p_addr ;
#endif
{
  U8bit len = ADDR_IND_LEN;

  if (p_addr->ssn_ind) len++;
  if (p_addr->pc_ind)  len += PC_SIZE;
  if (p_addr->gti)     len += p_addr->gt_len;

  return len;
}

/***************************************************************************
**
**      FUNCTION :
**         encodes sccp address
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U8bit *
sccp_encode_sccp_addr
#ifdef ANSI_PROTO
  (U8bit * p_elem, sccp_addr_t * p_addr)
#else
  (p_elem, p_addr)
  U8bit * p_elem ;
  sccp_addr_t * p_addr ;
#endif
{
  U8bit len = ADDR_IND_LEN, * p_len;
  U8bit addr_ind = 0, * p_addr_ind;

  p_len = p_elem; p_elem++;
  p_addr_ind = p_elem; p_elem++;
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
    if (p_addr->pc_ind)
    {
      PUT_PC(p_elem, p_addr->pc);
      p_elem += PC_SIZE;
      len += PC_SIZE;
      addr_ind |= ADDR_IND_PC_MASK;
    }

    if (p_addr->ssn_ind)
    {
      *p_elem++ = p_addr->ssn;
      len++;
      addr_ind |= ADDR_IND_SSN_MASK;
    }
  }
#endif
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
    if (p_addr->ssn_ind)
    {
      *p_elem++ = p_addr->ssn;
      len++;
      addr_ind |= ADDR_IND_SSN_MASK;
    }

    if (p_addr->pc_ind)
    {
      PUT_PC(p_elem, p_addr->pc);
      p_elem += PC_SIZE;
      len += PC_SIZE;
      addr_ind |= ADDR_IND_PC_MASK;
    }
  }
#endif
if (p_addr->gti)
  {
    ss7_memcpy (p_elem, &p_addr->gt[0], p_addr->gt_len);
    p_elem += p_addr->gt_len;
    len += p_addr->gt_len;
    addr_ind |= (p_addr->gti & 0xf) << 2;
  }

  addr_ind |= (p_addr->rout_ind & 0x1) << 6;
  addr_ind |= (p_addr->nat_ind & 0x1) << 7;

  *p_len = len;
  *p_addr_ind = addr_ind;

  return p_elem;
}


/***************************************************************************
**
**      FUNCTION :
**           decodes SCCP address
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t
sccp_decode_sccp_addr
#ifdef ANSI_PROTO
  (U8bit * p_addr, sccp_addr_t * p_sc_addr)
#else
  (p_addr, p_sc_addr)
  U8bit * p_addr ;
  sccp_addr_t * p_sc_addr ;
#endif
{
  U8bit min_len = 0, addr_len, addr_ind, * p_byte;

  p_sc_addr->pc_ind = SS7_FALSE;
  p_sc_addr->ssn_ind = SS7_FALSE;
  p_sc_addr->gti = 0;
  p_sc_addr->pc = 0;
  p_sc_addr->ssn = 0;
  p_sc_addr->gt_len = 0;

  p_byte = p_addr;
  addr_len = *p_byte++;
  addr_ind = *p_byte++;
  min_len++;

  /* Check the length of the address */
  if (addr_ind & ADDR_IND_PC_MASK)
    min_len += PC_SIZE;

  if (addr_ind & ADDR_IND_SSN_MASK)
    min_len++;

  if (min_len > addr_len)
  {
    /* Address length does not conform to the address indicator
       indicated length */
    return SS7_FAILURE;
  }
         if (ROUTE_ON_SSN == ((addr_ind >> 6) & 0x1)) /* routing on SSN */
         {
           if (!(addr_ind & ADDR_IND_SSN_MASK))
           {
                /* SSN absent - invalid address */
                return SS7_FAILURE;
           }

         }

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
    if (addr_ind & ADDR_IND_PC_MASK)
    {
      p_sc_addr->pc_ind = SS7_TRUE;
      p_sc_addr->pc = GET_PC(p_byte);
      p_byte += PC_SIZE;
    }
    else p_sc_addr->pc_ind = SS7_FALSE;
if (addr_ind & ADDR_IND_SSN_MASK)
    {
      p_sc_addr->ssn_ind = SS7_TRUE;
      p_sc_addr->ssn = *p_byte++;
    }
    else p_sc_addr->ssn_ind = SS7_FALSE;
  }
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
    if (addr_ind & ADDR_IND_SSN_MASK)
    {
      p_sc_addr->ssn_ind = SS7_TRUE;
      p_sc_addr->ssn = *p_byte++;
    }
    else p_sc_addr->ssn_ind = SS7_FALSE;

    if (addr_ind & ADDR_IND_PC_MASK)
    {
      p_sc_addr->pc_ind = SS7_TRUE;
      p_sc_addr->pc = GET_PC(p_byte);
      p_byte += PC_SIZE;
    }
    else p_sc_addr->pc_ind = SS7_FALSE;
  }
#endif

if (addr_ind & ADDR_IND_GTI_MASK)
  {
    p_sc_addr->gti = (addr_ind & ADDR_IND_GTI_MASK) >> 2;

/* Check if gti is not 0100 */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) && defined (SCCP_ERICSSON_ITU)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
  {
                if (!(p_sc_addr->gti & 0x4))
                      return SS7_FAILURE;
  }
#endif
p_sc_addr->gt_len = (U8bit)((p_addr + *p_addr + 1) - p_byte);

    /* Check if gl is present */
    if (p_sc_addr->gt_len == 0)
      return SS7_FAILURE;

    if (p_sc_addr->gt_len >= MAX_GT_LEN)
      return SS7_FAILURE;

    ss7_memcpy (p_sc_addr->gt, p_byte, p_sc_addr->gt_len);
  }
  else p_sc_addr->gti = 0;

  p_sc_addr->rout_ind = (addr_ind >> 6) & 0x1;
  p_sc_addr->nat_ind = (addr_ind >> 7) & 0x1;

  return SS7_SUCCESS;
}

	
