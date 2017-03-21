/*******************************************************************************
**      FILE NAME:
**          bs_trace.h
**
**      DESCRIPTION:
**              Trace related defines required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#define DEFAULT                              0x00
#define DEBUG                                0x01
#define INFO                                 0x02
#define CRITICAL                             0x03  
#define CONFIG                               0x04  

#define BSCONF_CORE_GENCFG                   0x10 
#define BSCONF_CORE_LWRSAP                   0x11 
#define BSCONF_CORE_UPRSAP                   0x12
#define BSCONF_CORE_INFCFG                   0x13
#define BSCONF_CORE_CICCFG                   0x14


#define BSCNTRL_CORE_ENBSAP                  0x20 
#define BSCNTRL_CORE_DISSAP                 0x21 
#define BSCNTRL_CORE_DELLOWRSAP              0x22
#define BSCNTRL_CORE_DELUPPRSAP              0x23


#define BSDATA_CORE_SEND                     0x25
#define BSDATA_CORE_RECV                     0x26
#define BSDATA_CORE_GEN                      0x27
#define BSDATA_TIMEREXP_RECV                 0x28   

#define BSERR_CORE_SAPID                     0x30
#define BSERR_CORE_CICID                     0x31
#define BSERR_CORE_CFGDONE                   0x32
#define BSERR_CORE_GETMEM                    0x33
#define BSERR_CORE_GETBUF                    0x34
#define BSERR_CORE_SWTCH                     0x35
#define BSERR_CORE_SAPSTATE                  0x36
#define BSERR_CORE_INFID                     0x37
#define  BSERR_CORE_INTFID                   0x37
#define BSERR_CORE                           0x38  
#define BSERR_CORE_NONE                      0x39
#define BSERR_CORE_TMR_RMV                   0x3a
#define BSERR_CORE_DPC                       0x11 
#define BSERR_CORE_CALLREF                   0x12
#define BSERR_CORE_RET                       0x13
#define BSERR_CORE_SSN                       0x14
#define BSERR_CORE_SWITCH                    0x15
#define BSERR_CORE_BSCID                     0x16
#define BSERR_CORE_APPID                     0x17
#define BSERR_CORE_MSGTYPE                     0x18
#define BSERR_CORE_DISC                     0x19
#define BSERR_CORE_MSGTAG                   0xea
#define BSERR_CORE_SWICTH                   0xeb


#define BSDATA_DPC_OPC_NI_INF_CIC_BSCID         0x40
#define BSDATA_DPC_OPC_NI_INF_BSCID             0x41
#define BSDATA_DPC_OPC_NI_BSCID                 0x42
#define BSDATA_DPC_OPC_INF_BSCID                0x43
#define BSDATA_DPC_NI_INF_BSCID                 0x44
#define BSDATA_OPC_NI_INF_BSCID                 0x45
#define BSDATA_DPC_OPC_NI_INF_CIC_BSCID_CALLREF 0x46
#define BSDATA_DPC_NI_INF_CIC_BSCID             0x47
#define BSDATA_OPC_NI_INF_CIC_BSCID             0x48
#define BSDATA_DPC_OPC_CIC_BSCID                0x49
/*#define BSDATA_DPC_OPC_NI_INF_BSCID             0x50*/
#define BSDATA_DPC_OPC_NI_INF                   0x51
#define BSDATA_DPC_OPC_NI_CIC                   0x52
#define BSDATA_DPC_OPC_INF                      0x53
#define BSDATA_DPC_OPC_CIC                      0x54
#define BSDATA_DPC_OPC_NI                       0x55 
#define BSDATA_DPC_OPC                          0x56
#define BSDATA_DPC_INF                          0x57
#define BSDATA_DPC_CIC                          0x58 
#define BSDATA_DPC_NI                           0x59
#define BSDATA_OPC_NI                           0x60
#define BSDATA_OPC_INTF                         0x61
#define BSDATA_OPC_CIC                          0x62
#define BSDATA_INTF                             0x63
#define BSDATA_CIC                              0x64
#define BSDATA_BSCID                            0x65
/*#define BSDATA_OPC_CIC                          0x66*/
#define BSDATA_DPC_OPC_NI_BSCID_INFID_CALLREF   0x67
#define BSDATA_DPC_OPC_NI_BSCID_INFID           0x68
#define BSDATA_DPC_OPC_NI_BSCID_CALLREF         0x69
#define BSDATA_DPC_OPC_NI_INFID_CALLREF         0x70
#define BSDATA_DPC_OPC_NI_INFID                 0x71
#define BSDATA_DPC_OPC_NI_CALLREF               0x72
#define BSDATA_DPC_OPC_BSCID_INFID_CALLREF      0x73
#define BSDATA_DPC_OPC_INFID_CALLREF            0x74
#define BSDATA_DPC_OPC_INFID                    0x75
#define BSDATA_DPC_OPC_CALLREF                  0x76
#define BSDATA_DPC_NI_BSCID_INFID_CALLREF       0x77
#define BSDATA_DPC_BSCID_INFID_CALLREF          0x78
#define BSDATA_DPC_INFID_CALLREF                0x79
#define BSDATA_DPC_CALLREF                      0x80
#define BSDATA_DPC_BSCID                        0x81
#define BSDATA_DPC_BSCID_CALLREF                0x82
/*#define BSDATA_DPC_INFID_CALLREF                0x83*/
#define BSDATA_DPC_INFID                        0x84
/*#define BSDATA_DPC_NI_BSCID_INFID_CALLREF       0x85*/
#define BSDATA_DPC_NI_INFID_CALLREF             0x86
#define BSDATA_DPC_NI_BSCID_CALLREF             0x87
#define BSDATA_DPC_NI_CALLREF                   0x88
#define BSDATA_DPC_NI_INFID                     0x89
#define BSDATA_DPC_NI_BSCID                     0x90
#define BSDATA_OPC_NI_BSCID_INFID_CALLREF       0x91
#define BSDATA_NI_BSCID_INFID_CALLREF           0x92
#define BSDATA_BSCID_INFID_CALLREF              0x93
#define BSDATA_INFID_CALLREF                    0x94
#define BSDATA_CALLREF                          0x95
#define BSDATA_BSCID_INFID                      0x96
#define BSDATA_SAPID_PLCASS                     0x97
#define BSDATA_SPID_SUID_SUINST_SPINST          0x98
#define BSDATA_SSN_SUID_SPID                    0x99
#define BSDATA_BSCID_CALLREF_APPID              0xaa
#define BSDATA_BSCID_CIC_APPID                  0xab
#define BSDATA_HEXDUMP                          0xac  
#define BSDATA_DPC_OPC_SSN_BSCID_SWITCH         0xad 
#define BSDATA_DPC_OPC_BSCID_SWITCH             0xae
#define BSDATA_APPID_BSCID_INFID_CALLREF_DISC   0xaf
#define BSDATA_SSN_PC                           0xb0
#define BSDATA_PC_PCSTATUS                       0xb1
#define BSDATA_PC_SSN_SSNSTATUS                  0xb2
#define BSDATA_SSN_BSCID_SWITCH_DPC             0xb3
#define BSDATA_APPID_BSCID_INFID_CALLREF_DISC_CIC 0xb4
#define BSDATA_SAPID_PLCLASS                      0xb5 
#define BSDATA_APPID_BSCID_CALLREF_DISC_CIC 0xb6
#define BSDATA_SUID_SPID_INSTID_PST         0xb7
#define BSDATA_APPID_BSCID_CALLREF_DISC     0xb8
#define BSDATA_EVENT                        0xb9 
#define BSDATA_AMF                          0xba
#define BSDATA_QUEUE                        0xbc
#define BSDATA_RSET                         0xbd
#define BSDATA_EVENTPUB                     0xde
#define BSDATA_RESET_TIMER                  0xc0 
#define BSDATA_RESETCKT_TIMER               0xc1
#define BSDATA_BLOCK_TIMER                  0xc2
#define BSDATA_ASSIGNMENT_TIMER             0xc3
#define BSDATA_BIND_TIMER                   0xc4
#define BSDATA_BLOCK_TIMER                  0xc5
#define BSDATA_UNBLOCK_TIMER                0xc6
#define BSDATA_GRPBLOCK_TIMER               0xc7
#define BSDATA_GRPUNBLOCK_TIMER             0xc8
#define BSDATA_RESETIP_TIMER                0xc9
#define BSDATA_RESETGUARD_TIMER             0xca

#define BS_CORE_NOARGS                      0x100
#define BS_CORE_CALLCKPT_ID                 0x101
