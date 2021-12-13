/**
 * @file assert_m.h
 * @author BrigitteLPB
 * @brief this file implement a file which throw message and kill
 * @date 2021-12-03 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ASSERT_M_H_
	#define ASSERT_M_H_

	#include <stdbool.h>

	/**
	 * @brief throw the message if the condition is false
	 * 
	 * @param [in] condition the condition to test
	 * @param [in] message the message to throw
	 */
	void assert_m(bool condition, const char* message);

#endif