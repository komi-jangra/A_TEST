/***************************************************************************
 * Old pepy stuff
 */

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * common definitions for the pepsy driver routines
 */
#define PEPSY_VERSION	2

/* find the default entry for this entry - for decoding
 * - assumes its the next or the one after or the one after that.
 * old version
#define FDFLT_B(p)	((((p) + 1)->pe_type == DFLT_B) ? ((p) + 1) : \
			((((p) + 2)->pe_type == DFLT_B) ? ((p) + 2): ((p) + 3)))
 */
#define FDFLT_B(p)	fdflt_b(p)	/* try a function */

/* find the entry for this default entry - for encoding
 * call a function - to keep looking till it finds it, this is the
 * alternative to the above scheme.
 */
#define FDFLT_F(p)	fdflt_f(p)	/* have to use a function */

/* assumes encoding tables */
#define OPT_PRESENT(p, parm)	(BITTEST(parm + p->pe_ucode, p->pe_tag))

/* assumes decoding tables */
#define SET_OPT_PRESENT(p, parm)	(BITSET(*parm + p->pe_ucode, p->pe_tag))
#define CLR_OPT_PRESENT(p, parm)	(BITCLR(*parm + p->pe_ucode, p->pe_tag))

#define NO_DATA_USED	(OK + 1)

#if defined(__cplusplus)
}
#endif

/****************************************************************************
 *
 * The ISODE is openly available but is NOT in the public domain.  You
 * are allowed and encouraged to take this software and build commercial
 * products.  However, as a condition of use, you are required to ``hold
 * harmless'' all contributors.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that this notice and the reference to this notice appearing in each
 * software module be retained unaltered, and that the name of any
 * contributors shall not be used in advertising or publicity pertaining
 * to distribution of the software without specific written prior permission.
 * No contributor makes any representations about the suitability of this
 * software for any purpose.  It is provided ``as is'' without express or
 * implied warranty.
 * 
 *      ALL CONTRIBUTORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 *      SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 *      AND FITNESS FOR THE PARTICULAR PURPOSE, TITLE, AND NON-INFRINGEMENT.
 *
 *      IN NO EVENT SHALL ANY CONTRIBUTOR BE LIABLE FOR ANY SPECIAL,
 *      INDIRECT OR CONSEQUENTIAL DAMAGES, WHETHER IN CONTRACT, TORT, OR
 *      OTHER FORM OF ACTION, ARISING OUT OF OR IN CONNECTION WITH, THE
 *      USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ***************************************************************************/

