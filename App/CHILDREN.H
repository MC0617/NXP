#ifndef __CHILDREN_H__
#define __CHILDREN_H__

//#define __SON__
#define __DAUGHTER__

#define BT_PORT UART5
#define BT_BAUD 115200

#ifdef __SON__

#define GO_FLAG TIME1flag_2s
#define STOP_FLAG TIME1flag_500ms

#elif defined __DAUGHTER__

#define GO_FLAG TIME1flag_2s5
#define STOP_FLAG TIME1flag_250ms

#endif	//__SON__?__DAUGHTER__

#endif	//__CHILDREN_H__