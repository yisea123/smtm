/*! \file    poscompdemo.cpp
 *  \brief   demo of position comparasion
 *  \author  yuanxiaowei
 *  \version 1.01
 *  \date    2013-7-26	create, v1.00
 *			 2013/8/29  add axis[1] feedback-position latch code, v1.01
 *						connect PUL/DIR output of Y to EA/EB input of Y,  
 *				PUL/DIR output of X to EA/EB input of X to run this demo code
 */

#include <windows.h>
#include "pci9014.h"
#include "pos_latch.h"
#include <iostream>
#include <vector>
using namespace std;

//threshold for position check
#define LATCH_POS_CHECK_THRESHOLD   10
#define ENABLE_LATCH_POS_CHECK	1

void comp_demo(int ref_source);

int main(int argc, char* argv[])
{
	int ref_source = 0;
	int arg1 = 0;
	if(argc > 1)
		arg1 = atoi(argv[1]);
	
	if(arg1) 
		ref_source = 1;
	else
		ref_source = 0;
	cout <<"Position Comparasion Demo, Reference Source: " << ref_source <<endl;
	comp_demo( ref_source );
	return 0;
}


int comp_show_fifo_sts(int card_no)
{
	int rc = 0;
	unsigned int fifo_sts = 0, fifo_flag = 0, fifo_wcnt = 0;
	
	rc = p9014_comp_get_fifoStatus(card_no, &fifo_sts);

	fifo_flag = fifo_sts  & 0xf;		//bit[3:0] indicate FULL/ALMOST FULL/ALMOST EMPTY/EMPTY
	fifo_wcnt = fifo_sts >> 16;		//items left in FIFO
	cout << "\tcmp fifo_flag: 0x" <<hex << fifo_flag <<", fifo_wcnt: " << dec << fifo_wcnt <<endl;
	
	rc = lt_get_fifo_status(card_no, &fifo_sts);
	rc = lt_get_latch_count(card_no, &fifo_wcnt);
	cout <<"\tlatch fifo status: 0x" <<hex<< fifo_sts <<", item count: " <<dec << fifo_wcnt <<endl;
	return rc;
}
/*! \fn void comp_demo(int ref_source)
 *  \brief position comparasion demo
 *
 *
 *
 *  \param ref_source = 0 command position acts as reference
 *  \param ref_source = 1 feedback position acts as reference
 *
 *  \return none
 */

void comp_demo(int ref_source)
{
	int count = 0, board_id[16], rc = 0;
	int axis, card_no, pos = 0, axis_lt;
	unsigned int status = 0, status_1 = 0, reg = 0;
	int i;
	int curr_ref, curr_pos = 0;
	unsigned int match_count, fifo_sts = 0; 
	unsigned int ver[] = {0,0,0,0};
	unsigned int rev = 0;
	vector <int> v_ref_pos;
	int latch_count;
	int lt_data = 0;
	int err = 0;
	
	rc = p9014_initial(&count, board_id);
	if(0 != rc)
	{
		cerr <<"open card fail" <<endl;
		return;
	}

	if(count < 1)
	{
		cerr <<"find no card" <<endl;
		p9014_close();
		return;
	}

	card_no = board_id[0];
	axis = card_no*4 + 0;
	axis_lt = axis + 1;
	p9014_get_version(card_no, ver, ver+0, ver+1);
	rev = 0;
	p9014_get_revision(card_no, &rev);	//revision number: 0x10 or larger is expected
	cout <<"Logic Version: 0x" << hex << ver[1] <<", Revision: 0x" << hex << rev << endl;
	
	p9014_set_t_profile(axis, 1000, 1e5, 1e6, 1e6);	//set acc/dec/start vel/max vel
	p9014_set_pls_iptmode(axis, 0); //PUL/DIR input
	p9014_set_t_profile(axis_lt, 1000, 1e5, 1e6, 1e6);	//set acc/dec/start vel/max vel
	p9014_set_pls_iptmode(axis_lt, 0); //PUL/DIR input
	
	curr_pos = -60000;
	p9014_set_pos(axis, 0, curr_pos);	//set command position register
	p9014_set_pos(axis, 1, curr_pos);	//set feedback position register
	p9014_get_pos(axis, 1, &pos);
	cout <<"\tBefore driving forward, current pos: " << dec << pos <<endl;
	p9014_set_pos(axis_lt, 0, curr_pos);	//set command position register
	p9014_set_pos(axis_lt, 1, curr_pos);	//set feedback position register
		
	rc = p9014_comp_clr_fifo(card_no);
	if(rc) cerr <<"\tERROR: clear FIFO fail" <<endl;
	
	rc = p9014_comp_clr_matchCount(card_no);
	if(rc)	cerr << "\tERROR: clear match counter fail" <<endl;

	rc = p9014_comp_enable(card_no, 1, 0, ref_source, 100000);
	if(rc) cerr <<"\tERROR: enable comparator fail" <<endl;
	
	rc = lt_init(card_no, 1);
	if(rc) cerr <<"\tERROR: enable position latch fail" <<endl;

	rc = lt_clr_fifo(card_no);
	if(rc) cerr <<"\tERROR: clr position latch fifo fail" <<endl;
		
	for(i = 1; i <= 10; i ++)
	{
		rc = p9014_comp_add_ref(card_no, curr_pos + i*10000);
		if(rc)
		{
			cerr << "\tERROR: add reference point fail" <<endl;
		}
		v_ref_pos.push_back(curr_pos + i*10000);	//store reference position for later use
	}
	cout <<"After setting reference point for driving forward..." <<endl;
	comp_show_fifo_sts(card_no);

	rc = p9014_comp_get_curRef(card_no, &curr_ref);
	if(rc)
	{
		cerr <<"\tERROR: get first reference position fail" << endl;
	}
	else
	{
		cout << "\tThe first reference position is: " << curr_ref << endl;
	}
	rc = p9014_pmove(axis, 12*10000, 0, 2);
	rc = p9014_pmove(axis_lt, 12*10000, 0, 2);
	if(rc)
		cerr <<"\tERROR: axis_1 move fail, rc: "<< dec <<rc <<endl;
	while(true)
	{
		pos = 0;
		status = 0;
		status_1 = 0;
		p9014_get_pos(axis, 0, &pos);
		cout <<"\tcurrent pos: " << dec <<pos <<"\r";

		p9014_get_motion_status(axis, &status);
		p9014_get_motion_status(axis_lt, &status_1);
		if((0 == status ) && (0 == status_1))
		{
			break;
		}
		Sleep(10);
	}
	p9014_get_pos(axis, 0, &pos);
	cout <<"\tAfter driving farward, current pos: " << pos <<endl;
	rc = p9014_comp_get_matchCount(card_no,  &match_count);
	if(0 == rc)
	{
		if(match_count != 10)
			cerr << "\tERROR: match count check fail, expect: 10, in fact: " << match_count <<endl;
		else
			cout << "\tmatch count check pass" <<endl;

	}
	else
	{
		cerr <<"\tERROR: get match count fail" <<endl;
	}

	cout <<"after move forward..." <<endl;
	
	//check latched position
#ifdef ENABLE_LATCH_POS_CHECK	
	comp_show_fifo_sts(card_no);
	rc = lt_get_latch_count(card_no, (unsigned int*)&latch_count);
	if(rc)
		cerr <<"\tERROR: get latch count fail, rc: " <<rc <<endl;
	else
	{
		cout <<"\tLatch count: " <<latch_count <<endl;
		if(latch_count != match_count)
		{
			cerr <<"\tERROR: latch count check fail, expect: " << match_count <<", real: " <<latch_count <<endl;
		}
		else
		{
			err = 0;
			for(i = 0; i < latch_count; i ++)
			{
				lt_get_data(card_no, &lt_data);
				if(abs(lt_data - v_ref_pos.at(i)) >= LATCH_POS_CHECK_THRESHOLD)
				{
					cerr <<"\tERROR: latch position check fail, expect: "<<v_ref_pos.at(i) <<", real: " << lt_data  <<endl;
					err ++;
				}				
			}
			
			if(!err)
				cout << "\tlatch position check pass" <<endl;
		}
	}
#endif	
	//move backward
	v_ref_pos.clear();	//clear reference position in vector
	for(i = 1; i <= 10; i ++)
	{
		rc = p9014_comp_add_ref(card_no, pos - i*10000);
		if(rc)
		{
			cerr << "\tERROR: add reference point fail" <<endl;
		}
		v_ref_pos.push_back(pos - i*10000);	//store reference position for later use
	}
	cout <<"After setting reference point for driving backward..." <<endl;
	comp_show_fifo_sts(card_no);

	rc = p9014_comp_get_curRef(card_no, &curr_ref);
	if(rc)
	{
		cerr <<"\tERROR: get first reference position fail" << endl;
	}
	else
	{
		cout << "\tThe first reference position is: " << curr_ref << endl;
	}
	rc = p9014_pmove(axis, -12*10000, 0, 2);
	rc = p9014_pmove(axis_lt, -12*10000, 0, 2);
	if(rc)
		cerr <<"\tERROR: axis_1 move fail, rc: "<< dec <<rc <<endl;
	while(true)
	{
		pos = 0;
		status = 0;
		status_1 = 0;
		p9014_get_pos(axis, 0, &pos);
		cout <<"\tcurrent pos: " << dec <<pos <<"\r";

		p9014_get_motion_status(axis, &status);
		p9014_get_motion_status(axis_lt, &status_1);
		if((0 == status ) && (0 == status_1))
		{
			break;
		}
		Sleep(10);
	}

	p9014_get_pos(axis, 0, &pos);
	cout <<"\tAfter driving backward, current pos: " << pos <<endl;

	rc = p9014_comp_get_matchCount(card_no,  &match_count);
	if(0 == rc)
	{
		if(match_count != 20)
			cerr << "\tERROR: match count check fail, expect: 20, in fact: " << match_count <<endl;
		else
			cout << "\tmatch count check pass" <<endl;
	}
	else
	{
		cerr <<"\tERROR: get match count fail" <<endl;
	}

	cout <<"After driving backward..." <<endl;
	comp_show_fifo_sts(card_no);
	
#ifdef ENABLE_LATCH_POS_CHECK
	rc = lt_get_latch_count(card_no, (unsigned int*)&latch_count);
	if(rc)
		cerr <<"\tERROR: get latch count fail, rc: " <<rc <<endl;
	else
	{
		cout <<"\tLatch count: " <<latch_count <<endl;
		if(latch_count != 10)
		{
			cerr <<"\tERROR: latch count check fail, expect: " << 10 <<", real: " <<latch_count <<endl;
		}
		else
		{
			err = 0;
			for(i = 0; i < latch_count; i ++)
			{
				lt_get_data(card_no, &lt_data);
				if(abs(lt_data - v_ref_pos.at(i)) >= LATCH_POS_CHECK_THRESHOLD)
				{
					cerr <<"\tERROR: latch position check fail, expect: "<<v_ref_pos.at(i) <<", real: " << lt_data  <<endl;
					err ++;
				}				
			}
			
			if(!err)
				cout << "\tlatch position check pass" <<endl;
		}
	}	
#endif	
	#if 1
	rc = p9014_comp_get_matchCount(card_no,  &match_count);
	cout <<"\tbefore clear, match count: " << match_count <<endl;
	
	rc = p9014_comp_clr_matchCount(card_no);
	if(rc)	cerr << "\tERROR: clear match counter fail" <<endl;

	rc = p9014_comp_get_matchCount(card_no,  &match_count);
	cout <<"\tafter clear, match count: " << match_count <<endl;
	
	#endif
	
	//disable comparator module
	p9014_comp_enable(card_no, 0, 0, ref_source, 100000);

	p9014_comp_clr_fifo(card_no);
	
	lt_init(card_no, 0);
	lt_clr_fifo(card_no);
	
	//close all card
	p9014_close();
}

