/*error code returned from ISUP in response to SCM commands */
#define   EISUP_CIC_PROV_OR_CONF_EXCEEDED     0x0601 + 0x08
#define   EISUP_STACK_NOT_INITIALIZED         0x8A5 + 0x05
#define   EISUP_STACK_ALREADY_INITIALIZED     0x8AB 
#define   EISUP_INVALID_COMMAND_CAT_COM	      0x0601 + 0x78
#define   EISUP_INVALID_NUM_ELEM	      0x0601 + 0x16
#define   EISUP_STATS_DISABLED		      0x0601 + 0x72
#define   EISUP_INVALID_STATS_TYPE	      0x0601 + 0x0D
#define   EISUP_TRACES_DISABLED		      0x0601 + 0x09
#define   EISUP_ERRORS_DISABLED		      0x0601 + 0x0C
#define   EISUP_REDN_DISABLED		      0x0601 + 0x77
#define   EISUP_SAP_ID_NOT_PRESENT	      0x0601 + 0x12F
#define   EISUP_INVALID_POINT_CODE_VAL	      0x0601 + 0x13C
#define   EISUP_MEMORY_ALLOCATION_FAILURE      0x0001 + 21
#define   EISUP_INVALID_NUM_TIMERS	      0x0601 + 0x0F
#define   EISUP_INVALID_TIMER_ID	      0x0601 + 0x10
#define   EISUP_LESS_NUM_ELEMENTS	      0x0601 + 0x11
#define   EISUP_API_LENGTH_MISMATCH	      0x0601 + 0x13
#define   EISUP_INVALID_RANGE_VALUE	      0x0601 + 0x28
#define   EISUP_CKT_GRP_CONF_EXCEEDED         0x0601 + 0x8F
#define   EISUP_CIC_NOT_CONFIGURED	      0x0601 + 0x05
#define   EISUP_NUM_ELEMENTS_MISMATCH	      0x0601 + 0x04
#define   EISUP_INVALID_TIMER_TYPE	      0x0601 + 0x01
#define   EISUP_OPC_DPC_CONF_EXCEEDED         0x0601 + 0x07
#define   EISUP_MAX_USERS_EXCEEDED            0x0601 + 0x141
#define   EISUP_INVALID_LOG_USER_ID           0x0601 + 0x142
#define   EISUP_INVALID_VERSION		      0x0601 + 0x144
#define   EISUP_INVALID_MSG_LENGTH	      0x0601 + 0x06
#define   EISUP_INVALID_TRACE_FLAG	      0x0601 + 0x0A
#define   EISUP_INVALID_ERROR_FLAG	      0x0601 + 0x0B
#define   EISUP_UNSUPPORTED_STACK_TYPE	      0x0601 + 0x0E
#define   EISUP_INVALID_TRACE_LEVEL	      0x0601 + 0x79
#define   EISUP_INVALID_ERROR_LEVEL	      0x0601 + 0x7A
#define   EISUP_INVALID_REDN_TYPE             0x0601 + 0x7B
#define   EISUP_BUFFER_LENGTH_OUT_OF_RANGE     0x0001 + 24
#define   EISUP_DPC_NOT_CONFIGURED	      0x0601 + 0x74
#define   EISUP_NO_STABLE_CICS                0x087F + 0x22
#define   EISUP_VAL_OUT_OF_RANGE	      0x0601 + 0x75
#define   EISUP_CIC_UNEQUIP		      0x087F + 0x0E
#define   EISUP_USER_NOT_REGISTERED	      0x0601 + 0x138
#define   EISUP_INVALID_VERSION		      0x0601 + 0x144
#define   EISUP_INVALID_RED_INFO_LEN	      0x0601 + 0x38
#define   EISUP_INVALID_RED_INFO_VALUE	      0x0601 + 0x39
#define   EISUP_MAX_CDPN_FILTERS_EXCEEDED       0x0601 + 0x126
#define   EISUP_MAX_CGPN_FILTERS_EXCEEDED       0x0601 + 0x127
#define   EISUP_MAX_CIC_FILTERS_EXCEEDED        0x0601 + 0x128
#define   EISUP_SELECTIVE_TRACING_DISABLED      0x0601 + 0x129
#define   EISUP_INVALID_OPC_VAL		      0x0601 + 0x7C
#define   EISUP_INVALID_DPC_VAL		      0x0601 + 0x7D
#define   EISUP_INVALID_ISUP_HEADER	      0x0601 + 0xBE
















/* Added by Amaresh for MAP error code towards SCM */

#define  MAP_SYSMG_ERR_INVALID_MODULE 								13000
  /*invoked api is invalid*/
#define  MAP_SYSMG_ERR_INVALID_API										13001     
#define  MAP_SYSMG_ERR_DISABLED_API										13002
#define  MAP_SYSMG_ERR_INVALID_STAT_TYPE							13003
/*api_id given as parameter is invalid*/
#define  MAP_SYSMG_ERR_INVALID_API_ID									13004
#define  MAP_SYSMG_ERR_INVALID_USER_ID								13005
#define  MAP_SYSMG_ERR_INVALID_SERVICE_ID							13006
#define  MAP_SYSMG_ERR_INVALID_SSN										13007
#define  MAP_SYSMG_ERR_INVALID_TIMER_ID								13008
#define  MAP_SYSMG_ERR_INVALID_TIMER_DURATION					13009
#define  MAP_SYSMG_ERR_RESOURCE_UNAVAILABLE						13010
#define  MAP_SYSMG_ERR_INVALID_ERR_TYPE								13011
#define  MAP_SYSMG_ERR_INVALID_ERR_LEVEL							13012
#define  MAP_SYSMG_ERR_INVALID_TRACE_LEVEL						13013
#define  MAP_SYSMG_ERR_DUPLICATE_SSN									13014
#define  MAP_SYSMG_ERR_NO_FREE_USER_ID								13015
#define  MAP_SYSMG_ERR_INVALID_OVERLOAD_LEVEL					13016
#define  MAP_SYSMG_ERR_INVALID_OVERLOAD_PERCENT				13017
#define  MAP_SYSMG_ERR_INVALID_AC_SUPPORT							13018
#define  MAP_SYSMG_ERR_DUPLICATE_SSN_AC								13019
#define  MAP_SYSMG_ERR_PURGE_DLG_FAILED								13020
#define  MAP_SYSMG_ERR_DUPLICATE_USER_ID							13021
#define  MAP_SYSMG_ERR_INVALID_AC_COUNT								13022
#define  MAP_SYSMG_ERR_INVALID_AC_DROP_LIST						13023
#define  MAP_SYSMG_ERR_STATE_ALREADY_ACTIVE						13024
#define  MAP_SYSMG_ERR_INVALID_INIT_DATA							13025
#define	 MAP_PM_E_HASH_TBL_INSERT_FAILED              13035 
#define  MAP_E_MEMPOOL_ALLOC_FAILED                   13036
#define  MAP_E_FREE_BLK_FAILED                        13038
#define  MAP_E_LINKED_LIST_INSERT_FAILED							13039 
#define MAP_E_SEC_DB_ENTRY_NOT_FOUND									13225
#define MAP_E_SEC_INVALID_HARD_EXPIRY_TIME						13226
#define MAP_E_SEC_SA_WITH_SAME_SOFT_EXP_ALREADY_EXISTS	13227  	
#define MAP_E_SEC_SA_FOR_UNSECURED_PLMN_NOT_PERMITTED	13237
#define MAP_E_SEC_SA_WITH_SAME_SPI_ALREADY_EXISTS			13238
#define MAP_E_SEC_UNABLE_TO_DELETE_SA									13239
#define MAP_E_SEC_INVALID_SRC_AND_DEST_PLMN						13240
#define MAP_E_SEC_INVALID_PLMN												13241
#define MAP_E_SEC_DB_ENTRY_ALREADY_EXISTS							13243
#define MAP_E_SEC_GET_TIME_OF_DAY_FAILED							13244

/* Addition completed  by Amaresh for MAP error code towards SCM */



/* Addition completed  by Amaresh for MAP error code towards SCM */
/* Added by Amaresh for CAP error code towards SCM */
#define	CSSF_SM_ERROR_BASE               71
#define CSSF_SM_ERR_INSUFFICIENT_MEMORY   CSSF_SM_ERROR_BASE + 0x00
#define CSSF_SM_ERR_TRACES_DISABLED     CSSF_SM_ERROR_BASE + 0x01
#define CSSF_SM_ERR_STATS_DISABLED      CSSF_SM_ERROR_BASE + 0x02
#define CSSF_SM_ERR_ERROR_DISABLED      CSSF_SM_ERROR_BASE + 0x03
#define CSSF_SM_ERR_INVALID_API       CSSF_SM_ERROR_BASE + 0x04
#define CSSF_SM_ERR_INVALID_TIMER_TYPE    CSSF_SM_ERROR_BASE + 0x05
#define CSSF_SM_ERR_INVALID_TIMER_DURATION  CSSF_SM_ERROR_BASE + 0x06

#define CSSF_STATS_ERR_DISABLED_API_STATS       CSSF_SM_ERROR_BASE + 0x07
#define CSSF_STATS_ERR_DISABLED_DIALOG_STATS      CSSF_SM_ERROR_BASE + 0x08
#define CSSF_STATS_ERR_DISABLED_PROTOCOL_EXPTN_STATS  CSSF_SM_ERROR_BASE + 0x09
#define CSSF_STATS_ERR_DISABLED_ERROR_STATS       CSSF_SM_ERROR_BASE + 0x0A
#define CSSF_STATS_ERR_DISABLED_ALL_STATS       CSSF_SM_ERROR_BASE + 0x0B
#define CSSF_STATS_ERR_INVALID_STATS_TYPE       CSSF_SM_ERROR_BASE + 0x0C

#define CSSF_TRACE_ERR_INVALID_TRACE_TYPE       CSSF_SM_ERROR_BASE + 0x0D
#define CSSF_TRACE_ERR_INVALID_TRACE_LEVEL        CSSF_SM_ERROR_BASE + 0x0E

#define CSSF_ERROR_ERR_INVALID_ERROR_TYPE       CSSF_SM_ERROR_BASE + 0x0F
#define CSSF_ERROR_ERR_INVALID_ERROR_LEVEL        CSSF_SM_ERROR_BASE + 0x10

/* Addition completed by Amaresh for CAP error code towards SCM */




/* TCAP ERROR CODES */
/* Added by Amaresh for TCAP error code send towards SCM */
#define SS7_GLOBAL_ERR_START	           0x0001
#define ESS7_INVALID_MODULE_ID		       (SS7_GLOBAL_ERR_START + 0)
#define ESS7_INVALID_STATS_TYPE		       (SS7_GLOBAL_ERR_START + 1)
#define ESS7_STATS_DISABLED		           (SS7_GLOBAL_ERR_START + 2)
#define ESS7_INVALID_TRACE_FLAG		       (SS7_GLOBAL_ERR_START + 3)
#define ESS7_TRACES_DISABLED		         (SS7_GLOBAL_ERR_START + 4)
#define ESS7_INVALID_ERROR_ALRAM	       (SS7_GLOBAL_ERR_START + 5)
#define ESS7_ERRORS_DISABLED		         (SS7_GLOBAL_ERR_START + 6)
#define ESS7_INVALID_ERROR_ALARM_LEVEL	 (SS7_GLOBAL_ERR_START + 7)
#define ESS7_INVALID_STATE		           (SS7_GLOBAL_ERR_START + 8)
#define ESS7_INVALID_API_ID              (SS7_GLOBAL_ERR_START + 9)
#define ESS7_INVALID_LENGTH              (SS7_GLOBAL_ERR_START + 10)
#define ESS7_INVALID_EVENT               (SS7_GLOBAL_ERR_START + 11)
#define ESS7_QUEUE_FULL                  (SS7_GLOBAL_ERR_START + 12)
#define EVERSION_ID                      (SS7_GLOBAL_ERR_START + 13)

#define ESS7_INVALID_NUM_API_ELEMENTS    (SS7_GLOBAL_ERR_START + 14)
#define ESS7_MISSING_API_ELEMENT         (SS7_GLOBAL_ERR_START + 15)
#define ESS7_UNKNOWN_API_ELEMENT         (SS7_GLOBAL_ERR_START + 16)
#define ESS7_INVALID_API_ELEMENT_LENGTH  (SS7_GLOBAL_ERR_START + 17)
#define ESS7_INVALID_API_ELEMENT         (SS7_GLOBAL_ERR_START + 18)

#define ESS7_FAILURE_TO_SEND_FROM_STACK_ENTITY     (SS7_GLOBAL_ERR_START + 19) 
#define ESS7_FAILURE_TO_SEND_TO_LOWER_LAYER        (SS7_GLOBAL_ERR_START + 20) 
#define ESS7_MEMORY_ALLOCATION_FAILURE             (SS7_GLOBAL_ERR_START + 21) 
#define ESS7_MEMORY_DEALLOCATION_FAILURE           (SS7_GLOBAL_ERR_START + 22) 
#define ESS7_FAILURE_TO_START_TIMER                (SS7_GLOBAL_ERR_START + 23) 
#define ESS7_BUFFER_LENGTH_OUT_OF_RANGE            (SS7_GLOBAL_ERR_START + 24) 
#define ESS7_BUFFER_OVERFLOW                       (SS7_GLOBAL_ERR_START + 25) 

#define ESYS_ERROR                                 (SS7_GLOBAL_ERR_START + 26) 
#define EAPI_ERROR                                 (SS7_GLOBAL_ERR_START + 27) 

#define	ESS7_INVALID_TRACE_LEVEL	                 (SS7_GLOBAL_ERR_START + 28)
#define	ESS7_INVALID_ERROR_FLAG	  	               (SS7_GLOBAL_ERR_START + 29)
#define	ESS7_INVALID_ERROR_LEVEL	                 (SS7_GLOBAL_ERR_START + 30)
#define	ESS7_INVALID_STANDARD	 	                   (SS7_GLOBAL_ERR_START + 31)
#define ESS7_INVALID_EVENT_OBJ_ID                  (SS7_GLOBAL_ERR_START + 32)
#define ESS7_INVALID_EVENT_LEVEL                   (SS7_GLOBAL_ERR_START + 33)

#define ESS7_STATS_ALREADY_ENABLED                 (SS7_GLOBAL_ERR_START + 34)
#define ESS7_STATS_ALREADY_DISABLED                (SS7_GLOBAL_ERR_START + 35)
#define ESS7_STATS_ALREADY_DISABLED                (SS7_GLOBAL_ERR_START + 35)
#define ESS7_MESSAGE_IN_INVALID_STATE      		     (SS7_GLOBAL_ERR_START + 36)
#define ESS7_INVALID_RESET_FLAG                    (SS7_GLOBAL_ERR_START + 37)
#define ETCAP_OUT_OF_MEMORY                        3085
/* Addition completed by Amaresh for TCAP error code send towards SCM */

