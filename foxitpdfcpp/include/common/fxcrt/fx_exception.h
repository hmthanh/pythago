/**
 * Copyright (C) 2003-2020, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fx_exception.h
 * @brief Header file for exception class.
 */

/**
 * @addtogroup FXCRT
 * @{
 */

#ifndef _FX_EXCEPTION_H_
#define _FX_EXCEPTION_H_

#define FX_SETJMP(BUF)      setjmp(BUF)
#define FX_LONGJMP(BUF, VAL)  longjmp(BUF, VAL)
#define FX_JMP_BUF        jmp_buf

/* @brief JMP depth default 512.*/
#define FX_JMP_DEPTH      512

#ifndef _FX_ERROR_H_
#include "fx_error.h"
#endif

#ifndef _FX_SYSTEM_H_
#include "fx_system.h"
#endif

#ifndef _FX_BASIC_H_
#include "fx_basic.h"
#endif

class CFX_Exception;
class CFX_JmpStack;

/**
 * The class represents jump stack class.
 */
class CFX_JmpStack : public CFX_Object
{
 public:
  CFX_JmpStack() : code(0) 
  {
    FXSYS_memset(&buffer, 0 ,sizeof(buffer));
  }

  int code;
  FX_JMP_BUF buffer;
};

class CFX_Exception : public CFX_Object
{
 public:
  CFX_Exception();
  ~CFX_Exception();

  FX_BOOL Catch(int value);
  FX_BOOL CatchAll();
  void  EndTry();

 protected:
  FX_BOOL  m_bCatched;
};

#ifdef _FX_SUPPORT_EXCEPTION_
//*****************************************************************************
//* Exception macro.
//*****************************************************************************
/**
 * @brief Exception macro.
 *
 * @note IMPORTANT: Between FX_TRY and FX_ALWARYS or FX_CATCH or FX_CATCHALL must't use the return or goto or longjmp instructor.
 *
 *       usage:
 *            FX_TRY {
 *                   ...
 *            } FX_ALWAYS() {
 *                   ...
 *            } [ FX_CATCHALL() | FX_CATCH(1) ] {
 *                   ...
 *            } FX_ENDTYR
 */
/*@{*/

#define FX_TRY \
  { \
  CFX_Exception __exception; \
  if (FX_Push_Try(FX_Thread_GetExceptionContext()->m_pErrContext) && (FX_Thread_GetExceptionContext()->m_pErrContext->stack[FX_Thread_GetExceptionContext()->m_pErrContext->top].code = \
    FX_SETJMP(FX_Thread_GetExceptionContext()->m_pErrContext->stack[FX_Thread_GetExceptionContext()->m_pErrContext->top].buffer)) == 0)

#define FX_ALWAYS() \
    if (1)

#define FX_CATCH(value) \
    if (__exception.Catch(value))

#define FX_CATCHALL() \
    if (__exception.CatchAll())

#define FX_ENDTRY \
    __exception.EndTry(); \
  }

//This will throw before throw error value.
#define FX_CONTINUETHROW FX_ContinueThrow()

//This will get current catch error value.
#define FX_GETCATCHCODE FX_GetCatchCode()

/*@}*/

/**
 * Throw an exception with a error code.
 *
 * @param[in] iErrCode  The error code.
 */
void FX_Throw(int iErrCode);
void FX_ContinueThrow();

/**
 * Get current catch error code.
 *
 */
int FX_GetCatchCode();

#endif //_FX_SUPPORT_EXCEPTION_

/** Exception class.*/
class CFX_ExceptionErrorContext : public CFX_Object
{
 public:
  CFX_ExceptionErrorContext();

  void  Initialize();
  void  Finalize();

  int top;
  CFX_JmpStack *stack;
};

class CFX_ExceptionContext : public CFX_Object
{
 public:
  CFX_ExceptionContext() : m_pErrContext(NULL) {}

  void  Initialize();
  void  Finalize();

  CFX_ExceptionErrorContext* m_pErrContext;
};

//*****************************************************************************
//* The following function will be implicit called by previous macros.
//* Please don't direct use.
//*****************************************************************************
FX_BOOL FX_Push_Try(CFX_ExceptionErrorContext* pErrContext);

#endif //_FX_EXCEPTION_H_

/** @} */
