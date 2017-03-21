#ifndef _CFG_E1_OBJECT_HANDLER_H_
#define _CFG_E1_OBJECT_HANDLER_H_

void insertIntoE1Table( I_U16 e1Id, I_U32 adminState);
void removeFromE1Table(I_U16 e1Id);
void setUsageTypeInE1Table(I_U16 e1Id, I_U32 usageType);
void CfgE1ObjHndlr1();
void CfgE1ObjHndlr2();
void CfgE1ObjHndlr3();
void CfgE1ObjHndlr4();
#endif
