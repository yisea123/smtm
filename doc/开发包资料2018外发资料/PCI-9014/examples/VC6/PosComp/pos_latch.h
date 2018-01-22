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
 *  \brief ��ʼ��λ������ģ�飬������ʹ��
 *
 *  FPGA Revision��Ϊ0x11�İ汾�ṩ��X��λ�ñȽϼ�Y��λ�����湦�ܣ���X��λ��
    �Ƚϳɹ�ʱ�����Խ���ʱ��Y�������λ��д�����Ϊ512��Ӳ��FIFO�У����û���ȡ
    
 *	�ú�������Ӳ���߼��İ汾�޸ĺ�(Revision)������汾�Ų��ԣ��᷵��RC_FEATURE_NOT_SUPPORTED����
 *
 *  \param card_no - ����
 *  \param enable - ��ֹ����ʹ��λ������ģ��, 0 - ��ֹλ������ģ�飻 ��0 - ʹ��λ������ģ��
 *
 *  \return 0��ʾ�ɹ��� ��0��ʾʧ��
 */
int lt_init(int card_no,  int enable);

/*! \fn int lt_clr_fifo(int card_no)
 *  \brief ���λ������ģ��Ӳ��FIFO���������
 *
 *	����λ������ģ��ʹ����񣬸ú������������FIFO����
 *
 *  \param card_no - ����
 *
 *  \return 0��ʾ�ɹ��� ��0��ʾʧ��
 */

int lt_clr_fifo(int card_no);

/*! \fn int lt_get_fifo_status(int card_no, unsigned int* pFifo_status)
 *  \brief ��ȡλ������ģ��Ӳ��FIFO��״̬(�ձ�ǡ������)
 *
 *
 *
 *  \param card_no - ����
 *  \param pFifo_status - FIFO��״̬, bit[0] - empty, bit[1] - almost empty, bit[2] - almost full, bit[3] - full
 *
 *  \return 0��ʾ�ɹ��� ��0��ʾʧ��
 */

int lt_get_fifo_status(int card_no, unsigned int* pFifo_status);

/*! \fn int lt_get_latch_count(int card_no, unsigned int* pCount)
 *  \brief ��ѯλ������ģ�����浽��λ�����ݸ���
 *
 *  �ú������Բ�ѯ�����浽FIFO�е�λ�����ݸ�������ͨ��lt_get_data����
    ����ȡ�������ݺ󣬸���ֵ����٣���Ӳ��FIFO��û������ʱ����ѯ��
    �ĸ���Ϊ0

    Ӳ��FIFO�����Ϊ512����˸�ֵ���ᳬ��512.

 *
 *  \param card_no - ����
 *  \param pCount - ʵ�����浽��λ�ø���
 *
 *  \return 0��ʾ�ɹ��� ��0��ʾʧ��
 */

int lt_get_latch_count(int card_no, unsigned int* pCount);

/*! \fn int lt_get_data((int card_no, int* pData)
 *  \brief ��λ������ģ���FIFO�ж�ȡ���浽��λ������
 *
 *  ע�⣺��FIFO��û������ʱ��pCount���ص�λ��ֵ����Ч��
    ����û���ʹ��֮ǰ����Ҫ��lt_get_latch_count��ѯFIFO�е����ݸ���������
    ��麯������ֵ
 *
 *  \param card_no - ����
 *  \param pData - ������λ������
 *
 *  \return 0��ʾ�ɹ��� ��0��ʾʧ��
 */

int lt_get_data(int card_no, int* pData);

#ifdef __cplusplus
}
#endif
#endif