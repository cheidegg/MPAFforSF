/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef DEBUG_HH
#define DEBUG_HH

#define DUMP(x) std::cout << #x << " = " << x << std::endl

#define DUMPVECTOR(x) for(int i = 0; i < x.size(); ++i) std::cout << #x << "[" << i << "] = " << x[i] << std::endl


#endif