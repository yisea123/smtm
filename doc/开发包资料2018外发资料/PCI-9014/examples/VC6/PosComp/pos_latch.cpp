/*! \file    pos_latch.cpp
 *  \brief   driver code of pci-9014 feedback position latch module
 *  \author  yuanxiaowei
 *  \version 1.00
 *  \date    2013-8-29
 */
#include <windows.h>
#include "pci9014.h"
#include "pos_latch.h"

#define CARD_NO_MAX		16

#ifdef __cplusplus
extern "C" {
#endif

PCI9014_API int WINAPI p9014_outpd(I32 card_no, U32 offset, U32 data);
PCI9014_API int WINAPI p9014_inpd(I32 card_no, U32 offset, U32* pData);

#ifdef __cplusplus
}
#endif

static int latch_not_supported[CARD_NO_MAX];

int lt_init(int card_no,  int enable)
{
	int rc = 0, i;
	unsigned int rev = 0;

	if((card_no >= CARD_NO_MAX) || (card_no < 0))
		return 1;	//invalid parameter

	for(i = 0; i < CARD_NO_MAX; i ++)
	{
		latch_not_supported[i] = 1;
	}

	for(i = 0; i < CARD_NO_MAX; i ++)
	{
		rev = 0;
		rc = p9014_inpd(card_no, 0xb4, &rev);
		if(!rc && (rev >= 0x11))
			latch_not_supported[i] = 0;
	}
	if(latch_not_supported[card_no])
		return RC_FEATURE_NOT_SUPPORTED;
	else
	{
		p9014_outpd(card_no, 0xb8, enable? 0x1 : 0x0);
		return 0;
	}
}

int lt_clr_fifo(int card_no)
{
	int count = 0, i;
	unsigned int reg = 0;
	int rc = 0;
	
	if((card_no >= CARD_NO_MAX) || (card_no < 0))
		return 1;	//invalid parameter

	if(latch_not_supported[card_no])
		return RC_FEATURE_NOT_SUPPORTED;

	count = 512;
	lt_get_latch_count(card_no, (unsigned int*)&count);
	if(count > 512)
		count = 512;

	for(i = 0; i < count; i ++)
	{
		rc = p9014_outpd(card_no, 0xbc, 0x1);
		rc = p9014_inpd(card_no, 0xbc, &reg);
	}
	return 0;
}

int lt_get_fifo_status(int card_no, unsigned int* pFifo_status)
{
	unsigned int reg = 0;
	int rc = 0;
	if((card_no >= CARD_NO_MAX) || (card_no < 0))
		return 1;	//invalid parameter

	if(latch_not_supported[card_no])
		return RC_FEATURE_NOT_SUPPORTED;

	rc = p9014_inpd(card_no, 0xb8, &reg);
	if(pFifo_status)
		*pFifo_status = ((reg >> 4) & 0xf);
	return rc;
}
int lt_get_latch_count(int card_no, unsigned int* pCount)
{
	unsigned int reg = 0;
	int rc = 0;

	if((card_no >= CARD_NO_MAX) || (card_no < 0))
		return 1;	//invalid parameter

	if(latch_not_supported[card_no])
		return RC_FEATURE_NOT_SUPPORTED;

	rc = p9014_inpd(card_no, 0xb8, &reg);
	if(pCount)
		*pCount = ((reg >> 16));
	return rc;
}

int lt_get_data(int card_no, int* pData)
{
	unsigned int reg = 0, fifo_sts = 0;
	int rc = 0;
	if((card_no >= CARD_NO_MAX) || (card_no < 0))
		return 1;	//invalid parameter

	if(latch_not_supported[card_no])
		return RC_FEATURE_NOT_SUPPORTED;

	fifo_sts = 0x1;
	rc = lt_get_fifo_status(card_no, &fifo_sts);
	if(rc)
		return rc;

	if(fifo_sts & 0x1)
		return RC_FIFO_EMPTY;

	rc = p9014_outpd(card_no, 0xbc, 0x1);
	rc = p9014_inpd(card_no, 0xbc, &reg);
	if(pData)
		*pData = (int)reg;
	return rc;
}