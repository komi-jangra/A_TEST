#ifndef __CPM2_MISC_H
#define __CPM2_MISC_H

/* Missing macros in CPM2.h */

#define CPM_CR_MCC2_SBLOCK	(0x1D)

/* Table 20-11 */
#define CPM_CR_STOP_MCC_TX	((ushort)0x0004)
#define CPM_CR_INIT_MCC_TX      ((ushort)0x0005)
#define CPM_CR_INIT_MCC_RX      ((ushort)0x0006)
#define CPM_CR_STOP_MCC_RX      ((ushort)0x0009)
#define CPM_CR_MCC_RST          ((ushort)0x0007)
/* Figure 21-7 */
#define CPM_MCC1_INT_PEND_ENABLE  (1U<<27)
#define CPM_MCC2_INT_PEND_ENABLE  (1U<<26)
#define CPM_MCC1_INT_MASK_ENABLE  (1U<<27)
#define CPM_MCC2_INT_MASK_ENABLE  (1U<<26)

/* Table 25.2.2 */
#define CPM_TIMER_GCR_CAS_NORMAL   (0<<7)
#define CPM_TIMER_GCR_CAS_32bit    (1<<7)
#define CPM_TIMER_GCR_STP2_NORMAL  (0<<5)
#define CPM_TIMER_GCR_STP2_POWER   (1<<5)
#define CPM_TIMER_GCR_RST2_RESET   (0<<4)
#define CPM_TIMER_GCR_RST2_ENABLE  (1<<4)
#define CPM_TIMER_GCR_GM1_RGM      (0<<3) /* Restart Gate Mode */
#define CPM_TIMER_GCR_GM1_NORMAL   (1<<3) /* Normal gate mode  */
#define CPM_TIMER_GCR_STP1_NORMAL  (0<<1)
#define CPM_TIMER_GCR_STP1_POWER   (1<<1)
#define CPM_TIMER_GCR_RST1_RESET   (0<<0)
#define CPM_TIMER_GCR_RST1_ENABLE  (1<<0)

#define CPM_TMR_PRESCALER_DIV1_VAL 0
/* Section 25.2.3 */
#define CPM_TMR_PS_VALUE_SHIFT     8      /* Prescale value shift               */
#define CPM_TMR_CE_DISABLE         (0<<6) /* Disable interrupt on capture event */
#define CPM_TMR_CE_RISING_EDGE     (1<<6) /* Capture on rising TINxedge         */
#define CPM_TMR_CE_FALLING_EDGE    (2<<6) /* Capture on falling TINx edge       */
#define CPM_TMR_CE_ANY_EDGE        (3<<6) /* Capture on any TINx edge           */

#define CPM_TMR_OM_ACTIVE          (0<<5) /* Output Mode */
#define CPM_TMR_OM_TOGGLE          (1<<5)

#define CPM_TMR_ORI_DISABLE        (0<<4) /* Output Reference Interrupt Enable */
#define CPM_TMR_ORI_ENABLE         (1<<4)

#define CPM_TMR_FRR_FREE           (0<<3) /* Free run/restart */
#define CPM_TMR_FRR_RESTART        (1<<3)

#define CPM_TMR_ICLK_INTRL_CAS          (0<<1)
#define CPM_TMR_ICLK_INTRL_BUS          (1<<1)
#define CPM_TMR_ICKL_INTRL_DIV16        (2<<1)
#define CPM_TMR_ICLK_INTRL_FALLING_TINX (3<<1)
#define CPM_TMR_GE_IGNORE               (0<<0)
#define CPM_TMR_GE_ENABLE               (1<<0)

/* Table 24-2 from MPC8560RM  */
#define CPM_BRGC_CD_SET_VAL(x)          (x<<1)

#endif

