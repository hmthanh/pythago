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
 * @file fx_process.h
 * @brief Header file for Process & thread related definitions and classes.
 */

/**
 * @addtogroup FXCRT
 * @{
 */

#ifndef _FX_PROCESS_H_
#define _FX_PROCESS_H_

#ifndef _FX_BASIC_H_
  #include "fx_basic.h"
#endif

#if _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_LINUX_EMBEDDED_ || _FX_OS_ == _FX_ANDROID_ || _FX_OS_ == _FX_MACOSX_ || _FX_OS_ == _FX_IOS_
  #include <time.h>
  #include <sys/time.h>
  #include <pthread.h>
  #include <unistd.h>
#endif

//external classes
class CFX_ProcessContext;
class CFX_ThreadContext;
class CFX_ExceptionContext;

//*****************************************************************************
//* Time
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Time
 */
/*@{*/

/** @brief Structure of system time. */
typedef struct _FX_SYSTEMTIME
{
  FX_WORD wYear;      //Year
  FX_WORD wMonth;      //Month, 1 - 12
  FX_WORD wDayOfWeek;    //Day of week, Sunday is 0, Monday is 1, ...
  FX_WORD wDay;      //Day of month, start from 1 - 31
  FX_WORD wHour;      //Hour, 0 - 23
  FX_WORD wMinute;    //Minute, 0 - 59
  FX_WORD wSecond;    //Second, 0 - 59
  FX_WORD wMilliseconds;  //Millisecond, 0 - 999
} FX_SYSTEMTIME;

/**
 * @brief Retrieve the current system date and time.
 *
 * @param[in,out] pSystemTime  Pointer to a FX_SYSTEMTIME to receive the current system data and time.
 *
 * @return None.
 */
void    FX_Time_GetSystemTime(FX_SYSTEMTIME* pSystemTime);
/**
 * @brief Retrieve the current local date and time.
 *
 * @param[in,out] pSystemTime  Pointer to a FX_SYSTEMTIME to receive the current local data and time.
 *
 * @return None.
 */void    FX_Time_GetLocalTime(FX_SYSTEMTIME* pSystemTime);
/**
 * @brief Get the clock ticks elapsed by calling process.
 *
 * @return Elapsed time in milliseconds.
 */
FX_DWORD  FX_Time_GetClock();
/**
 * @brief Delay the current running for specified milliseconds.
 *
 * @param[in] dwMilliseconds  Time in milliseconds to delay.
 *
 * @return Remained time has not elapsed, 0 if time interval expired.
 */
FX_DWORD  FX_Time_Sleep(FX_DWORD dwMilliseconds);

/** @brief Structure for date and time. */
typedef struct _FXCRT_DATETIMEZONE
{
  /** @brief Year, a four-digit number, such as 2014. */
  FX_WORD    year;
  /** @brief Month, from 1 to 12. */
  FX_WORD    month;
  /** @brief Day of month, from 1 to 31. */
  FX_WORD    day;
  /** @brief Day of week, from 0 to 6. PDF standard doesn't support now, you can omit this field if it is not applicable. */
  FX_WORD    dayOfWeek;
  /** @brief Hour, from 0 to 23. */
  FX_WORD    hour;
  /** @brief Minute, from 0 to 59. */
  FX_WORD    minute;
  /** @brief Second, from 0 to 60. 60 for leap second. */
  FX_WORD    second;
  /** @brief Millisecond, from 0 to 999. PDF standard doesn't support now, you can omit this field if it is not applicable. */
  FX_WORD    milliseconds;
  /**
   * @brief Hour of time zone, from -12 to 12.
   *
   * @details  Positive value for the eastern time zone, and negative value for the western time zone.
   */
  FX_INT32  tzHour;//TESTDOC: BUG#CORE-2923
  /** @brief Minute of time zone, from 0 to 59. */
  FX_WORD    tzMinute;
} FXCRT_DATETIMEZONE;

 /**
  * @brief Get current system date,time and timezone information.
  *
  * @param[in,out] dt  Structure to receive the current system date,time and timezone information.
  *
  * @return None.
  */
void    FXCRT_GetCurrentSystemTime(FXCRT_DATETIMEZONE& dt);

/*@}*/

#ifdef __cplusplus
}
#endif

//*****************************************************************************
//* Process
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Type for process ID
 */
/*@{*/

#if _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_MACOSX_ || _FX_OS_ == _FX_IOS_
  /** @brief Process ID. */
  typedef  pid_t    FX_PROCESSID;
#else
  /** @brief Process ID. */
  typedef FX_DWORD  FX_PROCESSID;
#endif

/*@}*/

/**
 * @name Process management
 */
/*@{*/

/**
 * @brief Initialize process.
 *
 * @return None.
 *
 * @note Application should call this function after initializes memory management.
 *         This function will prepare some global resources which are used in application.
 */
void        FX_Process_Initialize();
/**
 * @brief Finalize process.
 *
 * @return None.
 *
 * @note Application should call this function before release memory management when application stops running.
 */
void        FX_Process_Finalize();
/**
 * @brief Get the current process ID
 *
 * @return The current process ID
 */
FX_PROCESSID    FX_Process_GetID();

/**
 * @brief Get private data in the current process.
 *
 * @param[in] key  Key value to specify private data to be retrieved.
 *
 * @return Pointer to private data, NULL if failure.
 */
FX_LPVOID      FX_Process_GetPrivateData(FX_LPVOID key);
/**
 * @brief Set private data in the current process.
 *
 * @param[in] key       Key value to specify private data to be set.
 * @param[in] data      Pointer to private data.
 * @param[in] callback  Callback function address which is used to free private data,
 *                      pass NULL if need no additional process to free private data.
 *
 * @return None.
 */
void        FX_Process_SetPrivateData(FX_LPVOID key, FX_LPVOID data, PD_CALLBACK_FREEDATA callback);
/**
 * @brief Remove private data in the current process.
 *
 * @param[in] key  Key value to specify private data to be removed.
 *
 * @return None.
 */
void        FX_Process_RemovePrivateData(FX_LPVOID key);

/**
 * @brief Retrieve process context.
 *
 * @return The current process context object.
 *
 * @note This function is used internally.
 */
CFX_ProcessContext*  FX_Process_GetContext();

/*@}*/

#ifdef __cplusplus
}
#endif

//*****************************************************************************
//* Thread
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Type for thread ID
 */
/*@{*/

/** @brief Type definition of mutex handle. */
FX_DEFINEHANDLE(FX_HTHREAD);

/*
#if _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_MACOSX_ || _FX_OS_ == _FX_IOS_
  typedef pthread_t  FX_THREADID;
#else
  typedef FX_DWORD  FX_THREADID;
#endif
*/

/*@}*/

/**
 * @name Flags for thread priorities
 */
/*@{*/

/** @brief Lowest priority. */
#define FX_THREADPRIORITY_Lowest  -2
/** @brief Lower priority. */
#define FX_THREADPRIORITY_Lower    -1
/** @brief Normal priority. */
#define FX_THREADPRIORITY_Normal  0
/** @brief Higher priority. */
#define FX_THREADPRIORITY_Higher  1
/** @brief Highest priority. */
#define FX_THREADPRIORITY_Highest  2

/*@}*/

/**
 * @name Flags for thread priorities
 */
/*@{*/

#if _FXM_PLATFORM_ == _FXM_PLATFORM_WINDOWS_
typedef DWORD FX_ThreadResult;
#   define THREAD_CALL_CONVENTION WINAPI
#else
typedef FX_LPVOID FX_ThreadResult;
#   define THREAD_CALL_CONVENTION
#endif

/**
 * @brief Callback function of thread procedure.
 *
 * param[in] param  Thread parameter transfered when create thread.
 *
 * @return None.
 */
typedef FX_ThreadResult (THREAD_CALL_CONVENTION *FX_CALLBACK_ThreadProc)(FX_LPVOID param);

/*@}*/

/**
 * @brief Callback function of thread proxy procedure.
 *
 * param[in] param  Thread parameter transfered when create thread.
 *
 * @return None.
 */
typedef FX_ThreadResult (THREAD_CALL_CONVENTION *FX_CALLBACK_ThreadProxyProc)(FX_CALLBACK_ThreadProc threadProc, FX_LPVOID param);

/*@}*/

/**
 * @name Thread handler
 */
/*@{*/

/**
 * @brief Thread handler for application extension.
 *
 * @note This feature is disabled under single-thread mode or _FPDFAPI_MT_ isn't defined.
 */
typedef struct _FX_THREADHANDLER
{
  /** @brief Pointer to user data. */
  FX_LPVOID    pUserData;

  /**
   * @brief Callback function to create a thread.
   *
   * @param[in] pUserData      Pointer to user data.
   * @param[in] nPriority      Thread priority, set to 0 at default.
   * @param[in] szStack        Stack size for thread, set to 0 at default.
   * @param[in] lpfThreadProc  Function address for thread procedure.
   * @param[in] param          User parameters passed to thread procedure.
   *
   * @return Handle of thread, NULL if failure.
   */
  FX_HTHREAD    (*CreateThread)(FX_LPVOID pUserData, FX_INT32 nPriority, size_t szStack, FX_CALLBACK_ThreadProc lpfThreadProc, FX_LPVOID param);
  /**
   * @brief Callback function to exit from the current thread.
   *
   * @param[in] pUserData  Pointer to user data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL      (*ExitThread)(FX_LPVOID pUserData);
  /**
   * @brief Callback function to get handle of the current thread.
   *
   * @param[in] pUserData  Pointer to user data.
   *
   * @return Thread handle. <b>NULL</b> means error occurs.
   */
  FX_HTHREAD    (*GetCurrentThread)(FX_LPVOID pUserData);
  /**
   * @brief Callback function to change CPU time to another thread.
   *
   * @param[in] pUserData  Pointer to user data.
   *
   * @return None.
   *
   * @note Call this function to alternate to another thread if caller wants to break the current thread running.
   *         Calling thread will be awoken in next thread polling.
   */
  void      (*Yield)(FX_LPVOID pUserData);
  /**
   * @brief Callback function to get thread priority.
   *
   * @param[in] pUserData  Pointer to user data.
   * @param[in] hThread    Thread handle specifies a thread to retrieve its priority.
   *
   * @return Thread priority code, refers to FX_THREADPRIORITY_XXX macros.
   */
  FX_INT32    (*GetThreadPriority)(FX_LPVOID pUserData, FX_HTHREAD hThread);
  /**
   * @brief Callback function to set thread priority.
   *
   * @param[in] pUserData  Pointer to user data.
   * @param[in] hThread    Thread handle specifies a thread to set its priority.
   * @param[in] nPriority  Thread priority code.
   *
   * @return None.
   */
  void      (*SetThreadPriority)(FX_LPVOID pUserData, FX_HTHREAD hThread, FX_INT32 nPriority);
  /**
   * @brief Wait for termination of a single thread.
   *
   * @param[in] pUserData  Pointer to user data.
   * @param[in] hThread    Thread handle specifies a thread to wait.
   *
   * @return 0 means thread terminates successfully, other value means failure.
   */
  FX_INT32    (*WaitForSingleThread)(FX_LPVOID pUserData, FX_HTHREAD hThread);
  /**
   * @brief Wait for termination of multiple threads.
   *
   * @param[in] pUserData  Pointer to user data.
   * @param[in] pThreads   Pointer to array of thread handles.
   * @param[in] nCount     Number of threads in array.
   *
   * @return 0 means all threads terminates successfully, other value means failure.
   */
  FX_INT32    (*WaitForMultipleThreads)(FX_LPVOID pUserData, const FX_HTHREAD* pThreads, FX_INT32 nCount);
}FX_THREADHANDLER;

/**
 * @brief Get the current thread handler.
 *
 * @return The current thread handler. <b>NULL</b> means no thread handler has been set.
 *
 * @note This function returns <b>NULL</b> always under single-thread mode or _FPDFAPI_MT_ isn't defined.
 */
FX_THREADHANDLER*    FX_Thread_GetHandler();
/**
 * @brief Set the current thread handler.
 *
 * @param[in] pThreadHandler  Pointer to external thread handler.
 *
 * @return None.
 *
 * @note This function is disabled under single-thread mode or _FPDFAPI_MT_ isn't defined.
 */
void          FX_Thread_SetHandler(FX_THREADHANDLER* pThreadHandler);

/*@}*/

/**
 * @name Thread functions
 */
/*@{*/

/**
 * @brief Create a new thread.
 *
 * @param[in] nPriority   Thread priority.
 * @param[in] szStack     Stack size of thread, set to 0 for default stack size.
 * @param[in] threadProc  Thread callback function.
 * @param[in] param       Parameter passed to thread procedure.
 *
 * @return Thread handle. <b>NULL</b> means failure.
 */
FX_HTHREAD        FX_Thread_Create(FX_INT32 nPriority, size_t szStack, FX_CALLBACK_ThreadProc threadProc, FX_LPVOID param);

/**
 * @brief Exit from the current thread.
 *
 * @return None.
 */
void          FX_Thread_Exit();

/**
 * @brief Get the current thread handle.
 *
 * @return The current thread handle, NULL if failure.
 */
FX_HTHREAD        FX_Thread_GetHandle();

/**
 * @brief Yield the processor to another thread.
 *
 * @return None.
 */
void          FX_Thread_Yield();

/**
 * @brief Get the last error code in the current thread.
 *
 * @return The last error code.
 */
FX_INT32        FX_Thread_GetLastError();
/**
 * @brief Set the last error code in the current thread.
 *
 * @param[in] nErr  The last error code to be set.
 *
 * @return None.
 */
void          FX_Thread_SetLastError(FX_INT32 nErr);

/**
 * @brief Get private data in the current thread.
 *
 * @param[in] key  Key value to specify private data to be retrieved.
 *
 * @return Pointer to private data, NULL if failure.
 */
FX_LPVOID        FX_Thread_GetPrivateData(FX_LPVOID key);
/**
 * @brief Set private data in the current thread.
 *
 * @param[in] key       Key value to specify private data to be set.
 * @param[in] data      Pointer to private data.
 * @param[in] callback  Callback function address which is used to free private data.
 *                      Pass <b>NULL</b> if need no additional process to free private data.
 *
 * @return None.
 */
void          FX_Thread_SetPrivateData(FX_LPVOID key, FX_LPVOID data, PD_CALLBACK_FREEDATA callback);
/**
 * @brief Remove private data in the current thread.
 *
 * @param[in] key  Key value to specify private data to be removed.
 *
 * @return None.
 */
void          FX_Thread_RemovePrivateData(FX_LPVOID key);

/**
 * @brief Get thread priority.
 *
 * @param[in] hThread  Thread handle specifies a thread to retrieve its priority.
 *
 * @return Priority code of thread.
 */
FX_INT32        FX_Thread_GetPriority(FX_HTHREAD hThread);
/**
 * @brief Set thread priority.
 *
 * @param[in] hThread    Thread handle specifies a thread to change its priority.
 * @param[in] nPriority  Thread priority code.
 *
 * @return None.
 */
void          FX_Thread_SetPriority(FX_HTHREAD hThread, FX_INT32 nPriority);

/**
 * @brief Wait for termination of a single thread.
 *
 * @param[in] hThread  Thread handle specifies a thread to wait.
 *
 * @return 0 means thread terminates successfully, other value means failure.
 */
FX_INT32        FX_Thread_WaitForSingleThread(FX_HTHREAD hThread);
/**
 * @brief Wait for termination of multiple threads.
 *
 * @param[in] pThreads  Pointer to array of thread handles.
 * @param[in] nCount    Number of threads in array.
 *
 * @return 0 means all threads terminates successfully, other value means failure.
 */
FX_INT32        FX_Thread_WaitForMultipleThreads(const FX_HTHREAD* pThreads, FX_INT32 nCount);

/*@}*/

/**
 * @name Context access
 */
/*@{*/

/**
 * @brief Get the current thread context.
 *
 * @return The current thread context. <b>NULL</b> means failure.
 */
CFX_ThreadContext*    FX_Thread_GetContext();

/**
 * @brief Get the current thread exception context.
 *
 * @return The current thread exception context. <b>NULL</b> means failure.
 */
CFX_ExceptionContext*  FX_Thread_GetExceptionContext();

/*@}*/

#ifdef __cplusplus
}
#endif

//*****************************************************************************
//* Cocurrency controls
//*****************************************************************************
/**
 * @name Mutex
 *
 * @note Mutex is disabled under single-thread mode or _FPDFAPI_MT_ isn't defined,
 *         do not call the following functions under this condition. Mutex supports recursive calls in same thread.
 */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a mutex.
 *
 * @param[in] pMutex  Pointer to a mutex which need to be initialized. Must be not a NULL pointer.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL      FX_Mutex_Initialize(FX_MUTEX* pMutex);
/**
 * @brief Destroy a mutex.
 *
 * @param[in] pMutex  Pointer to a mutex to be destroyed. Must be not a NULL pointer.
 *
 * @return None.
 */
void      FX_Mutex_Destroy(FX_MUTEX* pMutex);
/**
 * @brief Try to lock a mutex.
 *
 * @param[in] pMutex  Pointer to a mutex. Must be not a NULL pointer.
 *
 * @return <b>true</b> means the given mutex object is locked successfully or the current thread already owns the mutex,
 *         while <b>false</b> means another thread owns the mutex already or other error occurs.
 */
FX_BOOL      FX_Mutex_TryLock(FX_MUTEX* pMutex);
/**
 * @brief Lock a mutex.
 *
 * @param[in] pMutex  Pointer to a mutex. Must be not a NULL pointer.
 *
 * @return None.
 *
 * @note If another thread owns the mutex when calls this function, this function won't return
 *      until the current thread obtains the ownership of the mutex.
 */
void      FX_Mutex_Lock(FX_MUTEX* pMutex);
/**
 * @brief Unlock a mutex.
 *
 * @param[in] pMutex  Pointer to a mutex. Must be not a NULL pointer.
 *
 * @return None.
 */
void      FX_Mutex_Unlock(FX_MUTEX* pMutex);

#ifdef __cplusplus
}
#endif

/*@}*/

/**
 * @name Spin Lock
 *
 * @note Spin Lock is disabled under single-thread mode or _FPDFAPI_MT_ isn't defined, do not call the following
 *         functions under this condition. Spin Lock is a light-weight cocurrency mechanism for synchronizing access.
 *         Spin Lock doesn't support recursive calls in same thread.
 */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a spin lock.
 *
 * @param[in] pSpinLock  Pointer to a spin lock to be initialized.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL      FX_SpinLock_Initialize(FX_SPINLOCK* pSpinLock);
/**
 * @brief Destroy a spin lock.
 *
 * @param[in] pSpinLock  Pointer to a spin lock to be destroyed.
 *
 * @return None.
 */
void      FX_SpinLock_Destroy(FX_SPINLOCK* pSpinLock);
/**
 * @brief Try to lock a spin lock.
 *
 * @param[in] pSpinLock  Pointer to a spin lock.
 *
 * @return <b>true</b> means the given spin lock object is locked successfully or
 *         current thread already owns the spin lock, while <b>false</b> means another thread owns the spin lock already
 *         or other error occurs.
 */
FX_BOOL      FX_SpinLock_TryLock(FX_SPINLOCK* pSpinLock);
/**
 * @brief Lock a spin lock.
 *
 * @param[in] pSpinLock  Pointer to a spin lock.
 *
 * @return None.
 *
 * @note If another thread owns the spin lock when calls this function, this function won't return until
 *         the current thread obtains the ownership of the spin lock.
 */
void      FX_SpinLock_Lock(FX_SPINLOCK* pSpinLock);
/**
 * @brief Unlock a spin lock.
 *
 * @param[in] pSpinLock  Pointer to a spin lock.
 *
 * @return None.
 */
void      FX_SpinLock_Unlock(FX_SPINLOCK* pSpinLock);
/**
 * @brief Determine whether specified spin lock is locked or not.
 *
 * @param[in] pSpinLock  Pointer to a spin lock.
 *
 * @return <b>true</b> means spin lock is locked, while <b>false</b> means spin lock is unlocked.
 */
FX_BOOL      FX_SpinLock_IsLocked(FX_SPINLOCK* pSpinLock);

#ifdef __cplusplus
}
#endif

#ifdef _FPDFAPI_MT_

/** @brief Spin Lock short-class. */
class CFX_SpinLock
{
 public:
  CFX_SpinLock() : m_pSpinLock(NULL) {}
  CFX_SpinLock(FX_SPINLOCK* pSpinLock) : m_pSpinLock(pSpinLock) {if (m_pSpinLock) FX_SpinLock_Lock(m_pSpinLock);}
  ~CFX_SpinLock() {if (m_pSpinLock) FX_SpinLock_Unlock(m_pSpinLock);}

  /** @brief Try to lock. For separating control. */
  FX_BOOL    TryLock() {return FX_SpinLock_TryLock(m_pSpinLock);}
  /** @brief Lock. For separating control. */
  void    Lock() {FX_SpinLock_Lock(m_pSpinLock);}
  /** @brief Unlock. For separating control. */
  void    Unlock() {FX_SpinLock_Unlock(m_pSpinLock);}
  /** @brief Determine whether the current spin lock is locked or not. For separating control. */
  FX_BOOL    IsLocked() {return FX_SpinLock_IsLocked(m_pSpinLock);}

  FX_SPINLOCK*  m_pSpinLock;
};

/**
 * @brief A macro means defining a lock operation with this pointer.
 * @hideinitializer
 */
#define FXMT_SPLOCK_THIS CFX_SpinLock _fx_splock((FX_SPINLOCK*)this)
/**
 * @brief A macro means defining a lock operation with a lock object.
 * @hideinitializer
 */
#define FXMT_SPLOCK_OBJ(lock) CFX_SpinLock _fx_splock(lock)

#else

/** @brief Under non-threading mode, defines as empty implementation. */
class CFX_SpinLock {};
#define FXMT_SPLOCK_THIS
#define FXMT_SPLOCK_OBJ(lock)

#endif

/*@}*/

/**
 * @name Read-Write lock
 *
 * @note Read-Write Lock is disabled under single-thread mode or _FPDFAPI_MT_ isn't defined,
 *      do not call the following functions under this condition.
 */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a read-write lock.
 *
 * @param[in] pRWLock  Pointer to a read-write lock which need to be initialized. Must be not a NULL pointer.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL      FX_RWLock_Initialize(FX_RWLOCK* pRWLock);
/**
 * @brief Destroy a read-write lock.
 *
 * @param[in] pRWLock  Pointer to a read-write lock to be destroyed. Must be not a NULL pointer.
 *
 * @return None.
 */
void      FX_RWLock_Destroy(FX_RWLOCK* pRWLock);
/**
 * @brief Try to lock for share read.
 *
 * @param[in] pRWLock  Pointer to a read-write lock. Must be not a NULL pointer.
 *
 * @return <b>true</b> means the given read-write lock object is locked successfully or
 *         current thread already owns the read-write lock, <b>false</b> means another thread owns
 *         the read-write lock already or other error occurs.
 */
FX_BOOL      FX_RWLock_TryReadLock(FX_RWLOCK* pRWLock);
/**
 * @brief Lock for share read.
 *
 * @param[in] pRWLock  Pointer to a read-write lock. Must be not a NULL pointer.
 *
 * @return None.
 *
 * @note If another thread owns the read-write lock when calls this function, this function won't return
 *         until the current thread obtains the ownership of the read-write lock.
 */
void      FX_RWLock_ReadLock(FX_RWLOCK* pRWLock);
/**
 * @brief Unlock for share read.
 *
 * @param[in] pRWLock  Pointer to a read-write lock. Must be not a NULL pointer.
 *
 * @return None.
 */
void      FX_RWLock_ReadUnlock(FX_RWLOCK* pRWLock);
/**
 * @brief Try to lock for exclusive write.
 *
 * @param[in] pRWLock  Pointer to a read-write lock. Must be not a NULL pointer.
 *
 * @return <b>true</b> if the given read-write lock object is locked successfully or
 *         current thread already owns the read-write lock, <b>false</b> means another thread owns
 *         the read-write lock already or other error occurs.
 */
FX_BOOL      FX_RWLock_TryWriteLock(FX_RWLOCK* pRWLock);
/**
 * @brief Lock for exclusive write.
 *
 * @param[in] pRWLock  Pointer to a read-write lock. Must be not a NULL pointer.
 *
 * @return None.
 *
 * @note If another thread owns the read-write lock when calls this function, this function won't return
 *         until the current thread obtains the ownership of the read-write lock.
 */
void      FX_RWLock_WriteLock(FX_RWLOCK* pRWLock);
/**
 * @brief Unlock for exclusive write.
 *
 * @param[in] pRWLock  Pointer to a read-write lock. Must be not a NULL pointer.
 *
 * @return None.
 */
void      FX_RWLock_WriteUnlock(FX_RWLOCK* pRWLock);

#ifdef __cplusplus
}
#endif

#ifdef _FPDFAPI_MT_

class CFX_RWLockObject : public CFX_Object
{
 public:
  /** @brief Construct a lock object. */
  CFX_RWLockObject() {FX_RWLock_Initialize(&m_Lock);}
  /** @brief Destruct a lock object. */
  ~CFX_RWLockObject() {FX_RWLock_Destroy(&m_Lock);}

  /** @brief Try to lock. For separating control. */
  FX_BOOL    TryReadLock()  {return FX_RWLock_TryReadLock(&m_Lock);}
  /** @brief Lock. For separating control. */
  void    ReadLock()    {FX_RWLock_ReadLock(&m_Lock);}
  /** @brief Unlock. For separating control. */
  void    ReadUnlock()  {FX_RWLock_ReadUnlock(&m_Lock);}
  /** @brief Try to lock. For separating control. */
  FX_BOOL    TryWriteLock()  {return FX_RWLock_TryWriteLock(&m_Lock);}
  /** @brief Lock. For separating control. */
  void    WriteLock()    {FX_RWLock_WriteLock(&m_Lock);}
  /** @brief Unlock. For separating control. */
  void    WriteUnlock()  {FX_RWLock_WriteUnlock(&m_Lock);}

 protected:
  /* Critical section. */
  FX_RWLOCK  m_Lock;
  friend class CFX_RWLock;
};

class CFX_RWLock
{
 public:
  CFX_RWLock() : m_pRWLock(NULL), m_nStatus(0) {}
  CFX_RWLock(FX_RWLOCK* pRWLock, FX_INT32 nStatus) : m_pRWLock(NULL), m_nStatus(0)
  {
    Init(pRWLock, nStatus);
  }
  CFX_RWLock(CFX_RWLockObject* pRWLockObj, FX_INT32 nStatus) : m_pRWLock(NULL), m_nStatus(0)
  {
    Init(&pRWLockObj->m_Lock, nStatus);
  }
  ~CFX_RWLock()
  {
    if (!m_pRWLock || !m_nStatus) return;
    if (m_nStatus < 0)
      FX_RWLock_ReadUnlock(m_pRWLock);
    else
      FX_RWLock_WriteUnlock(m_pRWLock);
  }

  /** @brief Try to lock for share read. For separating control. */
  FX_BOOL    TryReadLock()
  {
    if (FX_RWLock_TryReadLock(m_pRWLock))
    {
      m_nStatus = -1;
      return true;
    }
    return false;
  }
  /** @brief Lock for share read. For separating control. */
  void    ReadLock()
  {
    FX_RWLock_ReadLock(m_pRWLock);
    m_nStatus = -1;
  }
  /** @brief Unlock for share read. For separating control. */
  void    ReadUnlock()
  {
    m_nStatus = 0;
    FX_RWLock_ReadUnlock(m_pRWLock);
  }
  /** vTry to lock for exclusive write. For separating control. */
  FX_BOOL    TryWriteLock()
  {
    if (FX_RWLock_TryWriteLock(m_pRWLock))
    {
      m_nStatus = 1;
      return true;
    }
    return false;
  }
  /** @brief Lock for exclusive write. For separating control. */
  void    WriteLock()
  {
    FX_RWLock_WriteLock(m_pRWLock);
    m_nStatus = 1;
  }
  /** @brief Unlock for exclusive write. For separating control. */
  void    WriteUnlock()
  {
    m_nStatus = 0;
    FX_RWLock_WriteUnlock(m_pRWLock);
  }

 protected:
  FX_RWLOCK*  m_pRWLock;
  FX_INT32  m_nStatus;

  void  Init(FX_RWLOCK* pRWLock, FX_INT32 nStatus)
  {
    m_pRWLock = pRWLock, m_nStatus = nStatus;
    if (!m_pRWLock || !m_nStatus) return;
    if (m_nStatus < 0)
      FX_RWLock_ReadLock(m_pRWLock);
    else
      FX_RWLock_WriteLock(m_pRWLock);
  }
};

/** @brief A macro defines a lock operation with this pointer. */
#define FXMT_RWLOCK_THIS            CFX_RWLock _fx_rwlock((CFX_RWLock*)this)
/** @brief A macro defines a lock operation with a lock object and status. */
#define FXMT_RWLOCK_OBJ(lock, s)        CFX_RWLock _fx_rwlock(lock, s)
/** @brief A macro defines a named lock operation with a lock object. */
#define FXMT_RWLOCK_DEFINEOBJ(rwLock, lock, s)  CFX_RWLock rwLock(lock, s)

/** @brief A macro defines a lock object. */
#define FXMT_RWLOCKOBJECT_DEFINE(rwLockObj)    CFX_RWLockObject rwLockObj
/** @brief A macro tries to lock. */
#define FXMT_RWLOCKOBJECT_TRYREADLOCK(lockObj)  (lockObj)->TryReadLock()
/** @brief A macro tries to lock with if. */
#define FXMT_RWLOCKOBJECT_TRYREADLOCK_IF(lockObj)  if ((lockObj)->TryReadLock())
/** @brief A macro locks. */
#define FXMT_RWLOCKOBJECT_READLOCK(lockObj)    (lockObj)->ReadLock()
/** @brief A macro unlocks. */
#define FXMT_RWLOCKOBJECT_READUNLOCK(lockObj)    (lockObj)->ReadUnlock()
/** @brief A macro tries to lock. */
#define FXMT_RWLOCKOBJECT_TRYWRITELOCK(lockObj)  (lockObj)->TryWriteLock()
/** @brief A macro tries to lock with if. */
#define FXMT_RWLOCKOBJECT_TRYWRITELOCK_IF(lockObj)  if ((lockObj)->TryWriteLock())
/** @brief A macro locks. */
#define FXMT_RWLOCKOBJECT_WRITELOCK(lockObj)    (lockObj)->WriteLock()
/** @brief A macro unlocks. */
#define FXMT_RWLOCKOBJECT_WRITEUNLOCK(lockObj)    (lockObj)->WriteUnlock()
#else

/** @brief Under non-threading mode, defines as empty implementation. */
class CFX_RWLock {};
#define FXMT_RWLOCK_THIS
#define FXMT_RWLOCK_OBJ(lock, s)
#define FXMT_RWLOCK_DEFINEOBJ(rwLock, lock, s)

#define FXMT_RWLOCKOBJECT_DEFINE(rwLockObj)
#define FXMT_RWLOCKOBJECT_TRYREADLOCK(lockObj)
#define FXMT_RWLOCKOBJECT_TRYREADLOCK_IF(lockObj)
#define FXMT_RWLOCKOBJECT_READLOCK(lockObj)
#define FXMT_RWLOCKOBJECT_READUNLOCK(lockObj)
#define FXMT_RWLOCKOBJECT_TRYWRITELOCK(lockObj)
#define FXMT_RWLOCKOBJECT_TRYWRITELOCK_IF(lockObj)
#define FXMT_RWLOCKOBJECT_WRITELOCK(lockObj)
#define FXMT_RWLOCKOBJECT_WRITEUNLOCK(lockObj)
#endif

/*@}*/

//*****************************************************************************
//* Atomic Count
//*****************************************************************************
/**
 * @name Atomic Count
 *
 * @note Atomic Count provides an atomic mechanism to access integer value between multiple threads.
 *      Following functions also work under single-thread mode.
 */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Increase 32-bits integer value.
 *
 * @param[in,out] pAddend  Pointer to 32-bits integer to increase value.
 * @param[in] nIncrement   Increment value to be added to pAddend.
 *
 * @return New increment value.
 */
FX_INT32  FX_Atom_Add32(volatile FX_INT32* pAddend, FX_INT32 nIncrement);
/**
 * @brief Decrease 32-bits integer value.
 *
 * @param[in,out] pAddend  Pointer to 32-bits integer to decrease value.
 * @param[in] nDecrement   Decrement value to be subtracted from pAddend.
 *
 * @return New decrement value.
 */
FX_INT32  FX_Atom_Subtract32(volatile FX_INT32* pAddend, FX_INT32 nDecrement);
/**
 * @brief Increase 64-bits integer value.
 *
 * @param[in,out] pAddend  Pointer to 64-bits integer to increase value.
 * @param[in] nIncrement   Increment value to be added to pAddend.
 *
 * @return New increment value.
 */
FX_INT64  FX_Atom_Add64(volatile FX_INT64* pAddend, FX_INT64 nIncrement);
/**
 * @brief Decrease 64-bits integer value.
 *
 * @param[in,out] pAddend  Pointer to 64-bits integer to decrease value.
 * @param[in] nDecrement   Decrement value to be subtracted from pAddend.
 *
 * @return New decrement value.
 */
FX_INT64  FX_Atom_Subtract64(volatile FX_INT64* pAddend, FX_INT64 nDecrement);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif  /* _FX_PROCESS_H_ */

/** @} */
