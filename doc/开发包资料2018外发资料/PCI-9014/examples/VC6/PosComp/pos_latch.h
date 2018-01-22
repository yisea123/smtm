/*! \file  pos_latch.h
 *  \brief driver code of pci-9014 feedback position latch module
 *  \author  yuanxiaowei
 *  \version
 *  \date    2013-8-29
 */

#ifndef __POSITION_LATCH_H__
#define __POSITION_LATCH_H__

#define RC_FEATURE_NOT_SUPPORTED	500		//feature not supported
#define RC_FIFO_EMPTY				501		//no more data in hardware FIFO

#ifdef __cplusplus
extern "C" {
#endif
/*! \fn int lt_init(int card_no,  int enable)
 *  \brief 初始化位置锁存模块，并设置使能
 *
 *  FPGA Revision号为0x11的版本提供了X轴位置比较及Y轴位置锁存功能，当X轴位置
    比较成功时，可以将此时的Y轴编码器位置写到深度为512的硬件FIFO中，供用户读取
    
 *	该函数会检查硬件逻辑的版本修改号(Revision)，如果版本号不对，会返回RC_FEATURE_NOT_SUPPORTED错误
 *
 *  \param card_no - 卡号
 *  \param enable - 禁止或者使能位置锁存模块, 0 - 禁止位置锁存模块； 非0 - 使能位置锁存模块
 *
 *  \return 0表示成功， 非0表示失败
 */
int lt_init(int card_no,  int enable);

/*! \fn int lt_clr_fifo(int card_no)
 *  \brief 清除位置锁存模块硬件FIFO里面的内容
 *
 *	不管位置锁存模块使能与否，该函数都可以清除FIFO内容
 *
 *  \param card_no - 卡号
 *
 *  \return 0表示成功， 非0表示失败
 */

int lt_clr_fifo(int card_no);

/*! \fn int lt_get_fifo_status(int card_no, unsigned int* pFifo_status)
 *  \brief 获取位置锁存模块硬件FIFO的状态(空标记、满标记)
 *
 *
 *
 *  \param card_no - 卡号
 *  \param pFifo_status - FIFO的状态, bit[0] - empty, bit[1] - almost empty, bit[2] - almost full, bit[3] - full
 *
 *  \return 0表示成功， 非0表示失败
 */

int lt_get_fifo_status(int card_no, unsigned int* pFifo_status);

/*! \fn int lt_get_latch_count(int card_no, unsigned int* pCount)
 *  \brief 查询位置锁存模块锁存到的位置数据个数
 *
 *  该函数可以查询到锁存到FIFO中的位置数据个数，当通过lt_get_data函数
    来读取锁存数据后，该数值会减少；当硬件FIFO中没有数据时，查询到
    的个数为0

    硬件FIFO的深度为512，因此该值不会超过512.

 *
 *  \param card_no - 卡号
 *  \param pCount - 实际锁存到的位置个数
 *
 *  \return 0表示成功， 非0表示失败
 */

int lt_get_latch_count(int card_no, unsigned int* pCount);

/*! \fn int lt_get_data((int card_no, int* pData)
 *  \brief 从位置锁存模块的FIFO中读取锁存到的位置数据
 *
 *  注意：当FIFO中没有数据时，pCount返回的位置值将无效；
    因此用户在使用之前，需要用lt_get_latch_count查询FIFO中的数据个数，或者
    检查函数返回值
 *
 *  \param card_no - 卡号
 *  \param pData - 读到的位置数据
 *
 *  \return 0表示成功， 非0表示失败
 */

int lt_get_data(int card_no, int* pData);

#ifdef __cplusplus
}
#endif
#endif