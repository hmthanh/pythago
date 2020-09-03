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
 * @file fx_memory.h
 * @brief Header file for  Memory management related definitions and classes.
 */
//<<<+++OPENSOURCE
//<<<+++OPENSOURCE_LICENSE
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT||LIC==GOOGLE

/**
 * @addtogroup FXCRT
 * @{
 */

/*
 *
 * FPDFAPI may be using different heap as the application (in case of DLL version of FPDFAPI),
 * therefore, the application should use the following memory allocation and free functions
 * in order to exchange pointers between the API and application.
 *
 *
 * There are two layers of memory manager in FOXIT API:
 *
 *  1. System level memory manager. This level is system dependant.
 *    The API provides a default system memory manager (which uses CRT malloc/free functions),
 *    but application can implement their own manager to cater to different system environment.
 *
 *  2. Foxit memory manager. This level is system independant, but it relies on a system level manager.
 *    The API provides a default Foxit memory manager, which relies on the default system manager.
 *    Applications can not customize the Foxit memory manager, but they can create different
 *    Foxit memory manager instance, that rely on different underlying system manager
 *    (for example, each system manager may use a different heap, then, different Foxit manager
 *    will be able to use separate heaps.)
 *
 *
 *  Foxit memory manager also provide sub-heap feature for aggregating objects together to
 *  avoid memory fragmentation.
 */

//<<<+++OPENSOURCE_MUST_BEGIN
#ifndef _FX_MEMORY_H_
#define _FX_MEMORY_H_

#ifndef _FX_SYSTEM_H_
  #include "fx_system.h"
#endif
//<<<+++OPENSOURCE_MUST_END

/** @brief Flag for no calling OOM-handler when memory allocation failed. */
#define FXMEM_NONLEAVE      1
/** @brief Flag for allocate movable memory. */
#define FXMEM_MOVABLE      2
/** @brief Flag for allocate discardable memory. */
#define FXMEM_DISCARDABLE    4

// Base memory routines
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief System level memory manager. Application can implement their own system memory manager.
 */
typedef struct _FXMEM_SystemMgr {
  /**
   * @brief A pointer type to an allocation function.
   *
   * @details The function prototype is:<br>
   *          void* Alloc(FXMEM_SystemMgr* pMgr, size_t size, int flags);
   *
   * @param[in] pMgr   A pointer to a FXMEM_SystemMgr object.
   * @param[in] size   The size in bytes to allocate.
   * @param[in] flags  Memory allocation attributes.
   *
   * @return Address of new memory block.
   */
  void* (*Alloc)(struct _FXMEM_SystemMgr* pMgr, size_t size, int flags);
  /**
   * @brief A pointer type to a debug-mode allocation function.
   *
   * @details The function prototype is:<br>
   *          void* AllocDebug(FXMEM_SystemMgr* pMgr, size_t size, int flags, FX_LPCSTR file, int line);
   *
   * @param[in] pMgr   A pointer to a FXMEM_SystemMgr object.
   * @param[in] size   The size in bytes to allocate.
   * @param[in] flags  Memory allocation attributes.
   * @param[in] file   The name of the current source file.
   * @param[in] line   The line number in the current source file.
   *
   * @return Address of new memory block.
   */
  void* (*AllocDebug)(struct _FXMEM_SystemMgr* pMgr, size_t size, int flags, FX_LPCSTR file, int line);
  /**
   * @brief A pointer type to a reallocation function.
   *
   * @details  The function prototype is:<br>
   *           void* Realloc(FXMEM_SystemMgr* pMgr, void* pointer, size_t size, int flags);
   *
   * @param[in] pMgr     A pointer to a FXMEM_SystemMgr object.
   * @param[in] pointer  A pointer to a memory block.
   * @param[in] size     The size in bytes to reallocate.
   * @param[in] flags    Memory allocation attributes.
   *
   * @return Address of new memory block.
   */
  void* (*Realloc)(struct _FXMEM_SystemMgr* pMgr, void* pointer, size_t size, int flags);
  /**
   * @brief A pointer type to a debug-mode reallocation function.
   *
   * @details The function prototype is:<br>
   *          void ReallocDebug(FXMEM_SystemMgr* pMgr, void* pointer, size_t size, int flags, FX_LPCSTR file, int line);
   *
   * @param[in] pMgr     A pointer to a FXMEM_SystemMgr object.
   * @param[in] pointer  A pointer to a memory block.
   * @param[in] size     The size in bytes to reallocate.
   * @param[in] flags    Memory allocation attributes.
   * @param[in] file     The name of the current source file.
   * @param[in] line     The line number in the current source file.
   *
   * @return Address of new memory block.
   */
  void* (*ReallocDebug)(struct _FXMEM_SystemMgr* pMgr, void* pointer, size_t size, int flags, FX_LPCSTR file, int line);
  /**
   * @brief A pointer type to a lock function.
   *
   * @details The function prototype is:<br>
   *          void Lock(FXMEM_SystemMgr* pMgr, void* handle);
   *
   * @param[in] pMgr    A pointer to a FXMEM_SystemMgr object.
   * @param[in] handle  A handle to a memory block.
   *
   * @return A pointer to the locked memory block.
 */
  void* (*Lock)(struct _FXMEM_SystemMgr* pMgr, void* handle);
  /**
   * @brief A pointer type to a unlock function.
   *
   * @details The function prototype is:<br>
   *          void Unlock(FXMEM_SystemMgr* pMgr, void* handle);
   *
   * @param[in] pMgr    A pointer to a FXMEM_SystemMgr object.
   * @param[in] handle  A handle to a memory block.
   *
   * @return A pointer to the unlocked memory block.
   */
  void  (*Unlock)(struct _FXMEM_SystemMgr* pMgr, void* handle);
  /**
   * @brief A pointer type to a free function.
   *
   * @details The function prototype is:<br>
   *          void Free(FXMEM_SystemMgr* pMgr, void* pointer, int flags);
   *
   * @param[in] pMgr     A pointer to a FXMEM_SystemMgr object.
   * @param[in] pointer  A pointer to a memory block.
   * @param[in] flags    Memory allocation attributes.
   *
   * @return None.
   */
  void  (*Free)(struct _FXMEM_SystemMgr* pMgr, void* pointer, int flags);
  /**
   * @brief A pointer type to a purge function, which can be used to purge excessive memory without
   *        touching any used memory.
   *
   * @details The function prototype is:<br>
   *          void Purge(FXMEM_SystemMgr* pMgr);
   *
   * @param[in] pMgr  A pointer to a FXMEM_SystemMgr object.
   *
   * @return None.
   */
  void  (*Purge)(struct _FXMEM_SystemMgr* pMgr);
  /**
   * @brief A pointer type to a memory-collection function.
   *
   * @details The function prototype is:<br>
   *          void CollectAll(FXMEM_SystemMgr* pMgr);
   *
   * @param[in] pMgr  A pointer to a FXMEM_SystemMgr object.
   *
   * @return None.
   */
  void  (*CollectAll)(struct _FXMEM_SystemMgr* pMgr);

  /** @brief A generic typeless pointer for user data. */
  void* user;
} FXMEM_SystemMgr;

/**
 * @brief Foxit memory manager.
 *
 * @details Application can create different instances; Data members are hidden.
 */
FX_DEFINEHANDLE(FXMEM_FoxitMgr)

/**
 * @brief Create a Foxit manager. A system manager must be provided for actual allocation.
 *
 * @details On desktop platforms, you don't have to create a Foxit manager to use memory allocation,
 *          because FPDFAPI comes with a default Foxit manager (and underlying default system manager).
 *          But if your application uses non-default system manager, you will have to create a
 *          new Foxit manager that makes use of the custom system manager.
 *
 * @param[in] pSystemMgr  A pointer to a FXMEM_SystemMgr object.
 *
 * @return A pointer to a FXMEM_FoxitMgr object.
*/
FXMEM_FoxitMgr*  FXMEM_CreateFoxitMgr(FXMEM_SystemMgr* pSystemMgr);

/**
 * @brief Fixed memory manager.
 */
typedef struct _FXMEM_SystemMgr2
{
  /**
   * @brief Called when fixed memory manager needs more memory.
   *
   * @param[in] pMgr         A pointer to a FXMEM_SystemMgr2 object.
   * @param[in] alloc_size   The size that API is trying to allocate.
   * @param[out] new_memory  It receives the newly allocated memory.
   * @param[out] new_size    It receives the newly allocated size. The newly allocated size should be at least alloc_size + 32.
   *
   * @return Nonzero if the function is successful; otherwise 0.
   */
  FX_BOOL  (*More)(struct _FXMEM_SystemMgr2* pMgr, size_t alloc_size, void** new_memory, size_t* new_size);
  /**
   * @brief Called when an addition memory pool becomes empty.
   *
   * @param[in] pMgr    A pointer to a FXMEM_SystemMgr2 object.
   * @param[in] memory  A pointer to a memory block.
   *
   * @return None.
   */
  void  (*Free)(struct _FXMEM_SystemMgr2* pMgr, void* memory);
} FXMEM_SystemMgr2;

/**
 * @brief Create a Foxit manager from a pre-allocated, fixed memory buffer.
 *
 * @details This form of Foxit manager is typically used on embedded systems where memory is limited and
 *          can be dedicated to single task. The application is responsible to allocate and free the fixed memory buffer.
 *          Buffer size can't be lower than 512KB, there is no upper limit.
 *          Now the fixed memory manager supports extensible pool. If parameter <i>pExtender</i> is not <b>NULL</b>,
 *          then when current memory pool runs out, it will ask for more from the system.
 *
 * @param[in] pMemory    A pointer to a memory block.
 * @param[in] size       The size in bytes of the memory block pointed by parameter <i>pMemory</i>.
 * @param[in] pExtender  A pointer to a FXMEM_SystemMgr2 object.
 *
 * @return A pointer to a FXMEM_FoxitMgr object.
*/
FXMEM_FoxitMgr*  FXMEM_CreateFixedMgr(void* pMemory, size_t size, FXMEM_SystemMgr2* pExtender);

/**
 * @brief Create a fixed memory manager as default implementation.
 *
 * @param[in] size        Initial size of memory pool, in bytes. It should be not less than 8MB(1024 * 1024 * 8).
 * @param[in] extensible  If it's <b>true</b>, memory pool will extend if need more space.
 *                        And <b>false</b> means memory cannot be extended.
 *
 * @return A pointer to a FXMEM_FoxitMgr object.
 *
 * @note If parameter <i>extensible</i> is <b>false</b> and there is no enough space to allocate,
 *       <b>FX_Alloc</b> or <b>FX_Realloc</b> will return <b>NULL</b> directly.
 *       For extensible memory manager, it will try to request more memory pools to allocate.
 */
FXMEM_FoxitMgr* FXMEM_CreateMemoryMgr(size_t size, FX_BOOL extensible);

/**
 * @brief Get the size of a memory block to which <i>ptr</i> points.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object, it should be created as fixed memory manager.
 * @param[in] ptr        A pointer to a memory block.
 *
 * @return Memory block size in bytes if parameter <i>ptr</i> locates in fixed memory manager, or 0 returns.
 */
size_t FXMEM_GetBlockSizeInFixedMgr(FXMEM_FoxitMgr* pFoxitMgr, void* ptr);

/**
 * @brief Get default memory manager for current module.
 *
 * @return The default FXMEM_FoxitMgr pointer.
 */
FXMEM_FoxitMgr* FXMEM_GetDefaultMgr();

/**
 * @brief Set default Foxit manager for current compile module (EXE, DLL, etc.).
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @return None.
 */
void  FXMEM_SetDefaultMgr(FXMEM_FoxitMgr* pFoxitMgr);

/**
 * @brief Destroy a Foxit manager instance. If the platform supports auto-collection,
 *        then all allocated memory blocks will be released.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @return None.
 */
void  FXMEM_DestroyFoxitMgr(FXMEM_FoxitMgr* pFoxitMgr);

/**
 * @name Basic memory operations
 */
 /*@{*/

/**
 * @brief Foxit basic memory allocation function.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @param[in] size       The size in bytes to allocate.
 * @param[in] flags      Memory allocation attributes.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_Alloc(FXMEM_FoxitMgr* pFoxitMgr, size_t size, int flags);
/**
 * @brief Foxit basic memory allocation function in debug-mode.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @param[in] size       The size in bytes to allocate.
 * @param[in] flags      Memory allocation attributes.
 * @param[in] file       The name of the current source file.
 * @param[in] line       The line number in the current source file.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_AllocDebug(FXMEM_FoxitMgr* pFoxitMgr, size_t size, int flags, FX_LPCSTR file, int line);
/**
 * @brief Foxit basic memory reallocation function.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @param[in] pointer    A pointer to a memory block.
 * @param[in] new_size   The size in bytes to reallocate.
 * @param[in] flags      Memory allocation attributes.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_Realloc(FXMEM_FoxitMgr* pFoxitMgr, void* pointer, size_t new_size, int flags);
/**
 * @brief Foxit basic memory reallocation function in debug-mode.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @param[in] pointer    A pointer to a memory block.
 * @param[in] new_size   The size in bytes to reallocate.
 * @param[in] flags      Memory allocation attributes.
 * @param[in] file       The name of the current source file.
 * @param[in] line       The line number in the current source file.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_ReallocDebug(FXMEM_FoxitMgr* pFoxitMgr, void* pointer, size_t new_size, int flags, FX_LPCSTR file, int line);
/**
 * @brief Foxit basic memory free function.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @param[in] pointer    A pointer to a memory block.
 * @param[in] flags      Memory allocation attributes.
 *
 * @return None.
 */
void  FXMEM_Free(FXMEM_FoxitMgr* pFoxitMgr, void* pointer, int flags);

/*@}*/

/**
 * @brief Release all memory blocks allocated by a Foxit manager. This function is only supported on embedded systems.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 *
 * @return None.
 */
void  FXMEM_CollectAll(FXMEM_FoxitMgr* pFoxitMgr);

/**
 * @brief Release all excessive memory without touching any used memory. 
 *        This is useful for extensible fixed memory manager (FXMEM_SystemMgr2),
 *        because we never free those additional memory pool until the memory manager destroyed.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 *
 * @return None.
 */
void  FXMEM_PurgeMgr(FXMEM_FoxitMgr* pFoxitMgr);

/**
 * @brief Report Out-of-memory (OOM).
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 *
 * @return None.
 */
void  FXMEM_ReportOOM(FXMEM_FoxitMgr* pFoxitMgr);

/**
 * @brief Memory debugger interface. All functions must be implemented.
 */
typedef struct {
  /**
   * @brief A pointer type to an allocation-callback function.
   *
   * @details The function prototype is:<br>
   *          void OnAlloc(FXMEM_FoxitMgr* pMgr, void* p, size_t size, int flags);
   *
   * @param[in] pMgr    A pointer to a FXMEM_FoxitMgr object.
   * @param[in] p       Address of the allocated memory block.
   * @param[in] size    The size in bytes allocated.
   * @param[in] flags   Memory allocation attributes.
   *
   * @return None.
   */
  void  (*OnAlloc)(FXMEM_FoxitMgr* pMgr, void* p, size_t size, int flags);
  /**
   * @brief A pointer type to a debug-mode allocation-callback function.
   *
   * @details The function prototype is:<br>
   *          void OnAllocDebug(FXMEM_FoxitMgr* pMgr, void* p, size_t size, int flags, FX_LPCSTR file, int line);
   *
   * @param[in] pMgr   A pointer to a FXMEM_FoxitMgr object.
   * @param[in] p      Address of the allocated memory block.
   * @param[in] size   The size in bytes allocated.
   * @param[in] flags  Memory allocation attributes.
   * @param[in] file   The name of the current source file.
   * @param[in] line   The line number in the current source file.
   *
   * @return None.
   */
  void  (*OnAllocDebug)(FXMEM_FoxitMgr* pMgr, void* p, size_t size, int flags, FX_LPCSTR file, int line);
  /**
   * @brief A pointer type to a reallocation-callback function.
   *
   * @details The function prototype is:<br>
   *          void OnRealloc(FXMEM_FoxitMgr* pMgr, void* old_p, void* new_p, size_t size, int flags);
   *
   * @param[in] pMgr   A pointer to a FXMEM_FoxitMgr object.
   * @param[in] old_p  Address of the old memory block.
   * @param[in] new_p  Address of the new memory block.
   * @param[in] size   The size in bytes reallocated.
   * @param[in] flags  Memory allocation attributes.
   *
   * @return None.
   */
  void  (*OnRealloc)(FXMEM_FoxitMgr* pMgr, void* old_p, void* new_p, size_t size, int flags);
  /**
   * @brief A pointer type to a debug-mode reallocation-callback function.
   *
   * @details The function prototype is:<br>
   *          void OnReallocDebug(FXMEM_FoxitMgr* pMgr, void* old_p, void* new_p, size_t size, int flags, FX_LPCSTR file, int line);
   *
   * @param[in] pMgr   A pointer to a FXMEM_FoxitMgr object.
   * @param[in] old_p  Address of the old memory block.
   * @param[in] new_p  Address of the new memory block.
   * @param[in] size   The size in bytes reallocated.
   * @param[in] flags  Memory allocation attributes.
   * @param[in] file   The name of the current source file.
   * @param[in] line   The line number in the current source file.
   *
   * @return None.
   */
  void  (*OnReallocDebug)(FXMEM_FoxitMgr* pMgr, void* old_p, void* new_p, size_t size, int flags, FX_LPCSTR file, int line);
  /**
   * @brief A pointer type to a free-callback function.
   *
   * @details The function prototype is:<br>
   *          void OnFree(FXMEM_FoxitMgr* pMgr, void* p, int flags);
   *
   * @param[in] pMgr   A pointer to a FXMEM_FoxitMgr object.
   * @param[in] p      Address of the memory block to be freed.
   * @param[in] flags  Memory allocation attributes.
   *
   * @return None.
   */
  void  (*OnFree)(FXMEM_FoxitMgr* pMgr, void* p, int flags);
  /**
   * @brief A pointer type to a tag-callback function.
   *
   * @details The function prototype is:<br>
   *          void OnTag(FXMEM_FoxitMgr* pMgr, FX_LPCSTR tag);
   *
   * @param[in] pMgr  A pointer to a FXMEM_FoxitMgr object.
   * @param[in] tag   Tag string.
   *
   * @return None.
   */
  void  (*OnTag)(FXMEM_FoxitMgr* pMgr, FX_LPCSTR tag);
} FXMEM_Debugger;

/**
 * @brief Use a memory debugger which capturing all memory activities. Use <b>NULL</b> for parameter <i>pDebugger</i> to stop debugging.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object to be debugged.
 * @param[in] pDebugger  A pointer to a FXMEM_Debugger object.
 *
 * @return None.
 */
void  FXMEM_UseDebugger(FXMEM_FoxitMgr* pFoxitMgr, FXMEM_Debugger* pDebugger);

/**
 * @brief Output a memory debug tag.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @param[in] tag        Tag string.
 *
 * @return None.
 */
void  FXMEM_OutputDebugTag(FXMEM_FoxitMgr* pFoxitMgr, FX_LPCSTR tag);

/**
 * @brief the prototype of the Out-Of-Memory handler.
 *
 * @param[in] pFoxitMgr  A pointer to a FXMEM_FoxitMgr object.
 * @param[in] param      A generic typeless pointer for user data.
 *
 * @return None.
 */
typedef void (*FPDF_OOM_Handler)(FXMEM_FoxitMgr* pFoxitMgr, void* param);

/**
 * @brief Setup A Out-Of-Memory handler for a Foxit memory manager.
 *
 * @param[in] pFoxitMgr       A pointer to a FXMEM_FoxitMgr object.
 * @param[in] pOOMReportFunc  A pointer a Out-Of-Memory handler.
 * @param[in] param           A generic typeless pointer for user data to be called back.
 *
 * @return None.
 */
void  FXMEM_SetOOMHandler(FXMEM_FoxitMgr* pFoxitMgr, FPDF_OOM_Handler pOOMReportFunc, void* param);

/**
 * @name Following base memory functions use default Foxit manager for current module
 */
/*@{*/

/**
 * @brief Default allocation function using default Foxit memory manager for current module.
 *
 * @param[in] byte_size  The size in bytes to allocate.
 * @param[in] flags      Memory allocation attributes.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultAlloc(size_t byte_size, int flags);
/**
 * @brief Default allocation function using default Foxit memory manager for current module.
 *
 * @param[in] units      Number of units to allocate.
 * @param[in] unit_size  The byte size of each unit.
 * @param[in] flags      Memory allocation attributes.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultAlloc2(size_t units, size_t unit_size, int flags);
/**
 * @brief Default debug-mode allocation function using default Foxit memory manager for current module.
 *
 * @param[in] size   The size in bytes to allocate.
 * @param[in] flags  Memory allocation attributes.
 * @param[in] file   The name of the current source file.
 * @param[in] line   The line number in the current source file.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultAllocDebug(size_t size, int flags, FX_LPCSTR file, int line);
/**
 * @brief Default debug-mode allocation function using default Foxit memory manager for current module.
 *
 * @param[in] units      Number of units to allocate.
 * @param[in] unit_size  The byte size of each unit.
 * @param[in] flags      Memory allocation attributes.
 * @param[in] file       The name of the current source file.
 * @param[in] line       The line number in the current source file.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultAllocDebug2(size_t units, size_t unit_size, int flags, FX_LPCSTR file, int line);
/**
 * @brief Default reallocation function using default Foxit memory manager for current module.
 *
 * @param[in] pointer   Address of the memory block to be reallocated.
 * @param[in] new_size  The new size in bytes to reallocate.
 * @param[in] flags     Memory allocation attributes.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultRealloc(void* pointer, size_t new_size, int flags);
/**
 * @brief Default reallocation function using default Foxit memory manager for current module.
 *
 * @param[in] pointer    Address of the memory block to be reallocated.
 * @param[in] units      Number of units to allocate.
 * @param[in] unit_size  The byte size of each unit.
 * @param[in] flags      Memory allocation attributes.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultRealloc2(void* pointer, size_t units, size_t unit_size, int flags);
/**
 * @brief Default debug-mode reallocation function using default Foxit memory manager for current module.
 *
 * @param[in] pointer   Address of the memory block to be reallocated.
 * @param[in] new_size  The new size in bytes to reallocate.
 * @param[in] flags     Memory allocation attributes.
 * @param[in] file      The name of the current source file.
 * @param[in] line      The line number in the current source file.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultReallocDebug(void* pointer, size_t new_size, int flags, FX_LPCSTR file, int line);
/**
 * @brief Default debug-mode reallocation function using default Foxit memory manager for current module.
 *
 * @param[in] pointer    Address of the memory block to be reallocated.
 * @param[in] units      Number of units to allocate.
 * @param[in] unit_size  The byte size of each unit.
 * @param[in] flags      Memory allocation attributes.
 * @param[in] file       The name of the current source file.
 * @param[in] line       The line number in the current source file.
 *
 * @return Address of new memory block.
 */
void*  FXMEM_DefaultReallocDebug2(void* pointer, size_t units, size_t unit_size, int flags, FX_LPCSTR file, int line);
/**
 * @brief Default free function using default Foxit memory manager for current module.
 *
 * @param[in] pointer  Address of a memory block.
 * @param[in] flags    Memory allocation attributes.
 *
 * @return None.
 */
void  FXMEM_DefaultFree(void* pointer, int flags);

/*@}*/

/* FPDFAPI applications should use the FX_Alloc macro for non-class data types */
#ifdef _DEBUG
  #define FX_Alloc(type, size) (type*)FXMEM_DefaultAllocDebug2(size, sizeof(type), 0, __FILE__, __LINE__)
  #define FX_Realloc(type, ptr, new_size) (type*)FXMEM_DefaultReallocDebug2(ptr, new_size, sizeof(type), 0, __FILE__, __LINE__)
#else
  /**
   * @brief A macro for Foxit memory allocation operation.
   * @hideinitializer
   */
  #define FX_Alloc(type, size) (type*)FXMEM_DefaultAlloc2(size, sizeof(type), 0)
  /**
   * @brief A macro for Foxit memory reallocation operation.
   * @hideinitializer
   */
  #define FX_Realloc(type, ptr, size) (type*)FXMEM_DefaultRealloc2(ptr, size, sizeof(type), 0)
#endif

#ifdef _DEBUG
  #define FX_AllocNL(type, size) (type*)FXMEM_DefaultAllocDebug2(size, sizeof(type), FXMEM_NONLEAVE, __FILE__, __LINE__)
  #define FX_ReallocNL(type, ptr, new_size) (type*)FXMEM_DefaultReallocDebug2(ptr, new_size, sizeof(type), FXMEM_NONLEAVE, __FILE__, __LINE__)
#else
  /**
   * @brief A macro for Foxit memory allocation operation with non-leaving (return NULL if OOM).
   * @hideinitializer
   */
  #define FX_AllocNL(type, size) (type*)FXMEM_DefaultAlloc2(size, sizeof(type), FXMEM_NONLEAVE)
  /**
   * @brief A macro for Foxit memory reallocation operation with non-leaving (return NULL if OOM).
   * @hideinitializer
   */
  #define FX_ReallocNL(type, ptr, size) (type*)FXMEM_DefaultRealloc2(ptr, size, sizeof(type), FXMEM_NONLEAVE)
#endif

/** @brief A macro for Foxit memory free operation. */
#define FX_Free(pointer) FXMEM_DefaultFree(pointer, 0)

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <memory>
#include <algorithm>
#include <utility>

#if __cplusplus >= 201103L
#define FX_EQDELETE = delete
#define FX_NOEXCEPT noexcept
#define FX_EXPLICIT_OPERATOR explicit
#else
#define FX_EQDELETE //= delete
#define FX_NOEXCEPT //noexcept
#define FX_EXPLICIT_OPERATOR //explicit
#endif
// A template that can hold either owned or unowned references, and cleans up
// appropriately.  Possibly the most pernicious anti-pattern imaginable, but
// it crops up throughout the codebase due to a desire to avoid copying-in
// objects or data.
template <typename T, typename D = std::default_delete<T>>
class CFX_MaybeOwned {
 public:
  CFX_MaybeOwned() : m_pObj(nullptr) {}
  explicit CFX_MaybeOwned(T* ptr) : m_pObj(ptr) {}
  explicit CFX_MaybeOwned(std::unique_ptr<T, D> ptr)
    : m_pOwnedObj(std::move(ptr)), m_pObj(m_pOwnedObj.get()) {}

  CFX_MaybeOwned(CFX_MaybeOwned&& that) FX_NOEXCEPT
    : m_pOwnedObj(that.m_pOwnedObj.release()), m_pObj(that.m_pObj) {
    that.m_pObj = nullptr;
  }

  void Reset(std::unique_ptr<T, D> ptr) {
    m_pOwnedObj = std::move(ptr);
    m_pObj = m_pOwnedObj.get();
  }
  void Reset(T* ptr = nullptr) {
    m_pOwnedObj.reset();
    m_pObj = ptr;
  }

  bool IsOwned() const { return !!m_pOwnedObj; }
  T* Get() const { return m_pObj; }
  std::unique_ptr<T, D> Release() {
    ASSERT(IsOwned());
    return std::move(m_pOwnedObj);
  }

  CFX_MaybeOwned& operator=(CFX_MaybeOwned&& that) {
    m_pOwnedObj = std::move(that.m_pOwnedObj);
    m_pObj = that.m_pObj;
    that.m_pObj = nullptr;
    return *this;
  }
  CFX_MaybeOwned& operator=(T* ptr) {
    Reset(ptr);
    return *this;
  }
  CFX_MaybeOwned& operator=(std::unique_ptr<T, D> ptr) {
    Reset(std::move(ptr));
    return *this;
  }

  bool operator==(const CFX_MaybeOwned& that) const {
    return Get() == that.Get();
  }
  bool operator==(const std::unique_ptr<T, D>& ptr) const {
    return Get() == ptr.get();
  }
  bool operator==(T* ptr) const { return Get() == ptr; }

  bool operator!=(const CFX_MaybeOwned& that) const { return !(*this == that); }
  bool operator!=(const std::unique_ptr<T, D> ptr) const {
    return !(*this == ptr);
  }
  bool operator!=(T* ptr) const { return !(*this == ptr); }

  FX_EXPLICIT_OPERATOR operator bool() const { return !!m_pObj; }
  T& operator*() const { return *m_pObj; }
  T* operator->() const { return m_pObj; }
 private:
  CFX_MaybeOwned(const CFX_MaybeOwned& that) FX_EQDELETE;
  CFX_MaybeOwned& operator=(const CFX_MaybeOwned& that) FX_EQDELETE;

 private:
  std::unique_ptr<T, D> m_pOwnedObj;
  T* m_pObj;
};

// Used with std::unique_ptr to FX_Free raw memory.
struct CFX_FreeDeleter {
  inline void operator()(void* ptr) const { FX_Free(ptr); }
};
/**
 * @brief BASE CLASS FOR (ALMOST) ALL OTHER CLASSES IN FPDFAPI.
 *
 * This class is created for centralizing memory management.
 * It uses default memory manager to allocator and free memory, if your module uses
 * a separate memory manager, you will need to derive your class from CFX_AllocObject.
 */
class CFX_Object
{
 public:
  /**
   * @brief "new" operator for debug mode.
   *
   * @param[in] size  The size in bytes to allocate.
   * @param[in] file  The name of the current source file.
   * @param[in] line  The line number in the current source file.
   *
   * @return Address of a new memory block.
   */
  void*      operator new (size_t size, FX_LPCSTR file, int line);
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief delete" operator for debug mode.
   *
   * @param[in] p      The Address of a memory block to be deleted.
   * @param[in] file  The name of the current source file.
   * @param[in] line  The line number in the current source file.
   *
   * @return None.
   */
  void      operator delete (void* p, FX_LPCSTR file, int line);
#endif

  /**
   * @brief "new" operator for release mode.
   *
   * @param[in] size  The size in bytes to allocate.
   *
   * @return Address of a new memory block.
   */
  void*      operator new (size_t size);
  /**
   * @brief "delete" operator for release mode.
   *
   * @param[in] p  The Address of a memory block to be deleted.
   *
   * @return None.
   */
  void      operator delete (void* p);

  /**
   * @brief "new" operator of vector for debug mode.
   *
   * @param[in] size  The size in bytes to allocate.
   * @param[in] file  The name of the current source file.
   * @param[in] line  The line number in the current source file.
   *
   * @return Address of a new memory block.
   */
  void*      operator new[] (size_t size, FX_LPCSTR file, int line);
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief "delete" operator of vector for debug mode.
   *
   * @param[in] p     The Address of a memory block to be deleted.
   * @param[in] file  The name of the current source file.
   * @param[in] line  The line number in the current source file.
   *
   * @return None.
   */
  void      operator delete[] (void* p, FX_LPCSTR file, int line);
#endif

  /**
   * @brief "new" operator of vector for non-debug mode.
   *
   * @param[in] size  The size in bytes to allocate.
   *
   * @return Address of a new memory block.
   */
  void*      operator new[] (size_t size);
  /**
   * @brief "delete" operator of vector for non-debug mode.
   *
   * @param[in] p  The Address of a memory block to be deleted.
   *
   * @return None.
   */
  void      operator delete[] (void* p);

  /**
   * @brief placement new operator.
   */
  void*      operator new (size_t, void* buf) { return buf; }
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief placement delete operator.
   */
  void      operator delete (void*, void*) {}
#endif
 protected:
  /** The destructor. */
  ~CFX_Object() {}
};

/**
 * @brief   Placement new override.
 * @note  Some platforms might have global placement new definition, such as STL, MFC.
 */
#if (_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_) && !defined(__PLACEMENT_NEW_INLINE) && !defined(_MFC_VER) && !defined(_NEW)
  #define __PLACEMENT_NEW_INLINE

  inline void* operator new(size_t size, void* pos)
  {
    return pos;
  }

  inline void operator delete(void* ptr, void* pos)
  {
  }
#endif //__PLACEMENT_NEW_INLINE

#endif //__cplusplus

//<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#ifdef __cplusplus

#if defined(_DEBUG)
  #define FX_NEW new(__FILE__, __LINE__)
#else
  /**
   * @brief FPDFAPI applications should use the FX_NEW macro in place of "new" operator.
   * @hideinitializer
   */
  #define FX_NEW new
#endif
//<<<+++OPENSOURCE_MUST_END

#ifndef _FPDFAPI_MINI_
  //<<<+++OPENSOURCE_BEGIN LIC==FOXIT
  /** @brief Vector allocator. Some platform doesn't provide clean vector allocator (like ADS). */
  #define FX_NEW_VECTOR(Pointer, Class, Count) Pointer = FX_NEW Class[Count]
  /** @brief Vector destroyer. */
  #define FX_DELETE_VECTOR(Pointer, Class, Count) delete[] Pointer
  //<<<+++OPENSOURCE_END
#else
  //<<<+++OPENSOURCE_BEGIN LIC==GOOGLE
  #define FX_NEW_VECTOR(Pointer, Class, Count) \
    { \
      Pointer = FX_Alloc(Class, Count); \
      if (Pointer) { \
        for (int i = 0; i < (Count); i ++) new (Pointer + i) Class; \
      } \
    }
  #define FX_DELETE_VECTOR(Pointer, Class, Count) \
    { \
      for (int i = 0; i < (Count); i ++) Pointer[i].~Class(); \
      FX_Free(Pointer); \
    }
  //<<<+++OPENSOURCE_END
#endif

//<<<+++OPENSOURCE_MUST_BEGIN
/**
 * @brief Destructable objects: you can always safely delete an object derived from this class,
 * using its base class pointer.
 */
class CFX_DestructObject : public CFX_Object
{
 public:
  /** @brief virtual destructor */
  virtual ~CFX_DestructObject() {}
};
//<<<+++OPENSOURCE_MUST_END
#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Foxit allocator interface.
 */
typedef struct _IFX_Allocator
{
  /**
   * @brief A pointer type to a debug-mode allocation function.
   *
   * @details The function prototype is:<br>
   *          void* AllocDebug(IFX_Allocator* pAllocator, size_t size, FX_LPCSTR filename, int line);
   *
   * @param[in] pAllocator  A pointer to a IFX_Allocator object.
   * @param[in] size        The size in bytes to allocate.
   * @param[in] file        The name of the current source file.
   * @param[in] line        The line number in the current source file.
   *
   * @return Address of new memory block.
   */
  void*  (*m_AllocDebug)(struct _IFX_Allocator* pAllocator, size_t size, FX_LPCSTR file, int line);
  /**
   * @brief A pointer type to an allocation function.
   *
   * @details The function prototype is:<br>
   *          void* Alloc(IFX_Allocator* pAllocator, size_t size);
   *
   * @param[in] pAllocator  A pointer to a IFX_Allocator object.
   * @param[in] size        The size in bytes to allocate.
   *
   * @return Address of new memory block.
   */
  void*  (*m_Alloc)(struct _IFX_Allocator* pAllocator, size_t size);
  /**
   * @brief A pointer type to a debug-mode re-allocation function.
   *
   * @details The function prototype is:<br>
   *          void* ReallocDebug(IFX_Allocator* pAllocator, void* p, size_t size, FX_LPCSTR filename, int line);
   *
   * @param[in] pAllocator  A pointer to a IFX_Allocator object.
   * @param[in] p           Pointer to reallocate.
   * @param[in] size        The new size in bytes to reallocate.
   * @param[in] file        The name of the current source file.
   * @param[in] line        The line number in the current source file.
   *
   * @return Address of new pointer.
   */
  void*  (*m_ReallocDebug)(struct _IFX_Allocator* pAllocator, void* p, size_t size, FX_LPCSTR file, int line);
  /**
   * @brief A pointer type to a re-allocation function.
   *
   * @details The function prototype is:<br>
   *          void* Realloc(IFX_Allocator* pAllocator, void* p, size_t size);
   *
   * @param[in] pAllocator  A pointer to a IFX_Allocator object.
   * @param[in] p           Pointer to reallocate.
   * @param[in] size        The new size in bytes to reallocate.
   *
   * @return Address of new pointer.
   */
  void*  (*m_Realloc)(struct _IFX_Allocator* pAllocator, void* p, size_t size);
  /**
   * @brief A pointer type to a free function.
   *
   * @details The function prototype is:<br>
   *          void free(IFX_Allocator* pAllocator, void* p);
   *
   * @param[in] pAllocator  A pointer to a IFX_Allocator object.
   * @param[in] p           Address of a memory block.
   *
   * @return None.
   */
  void  (*m_Free)(struct _IFX_Allocator* pAllocator, void* p);
} IFX_Allocator;

/**
 * @brief Get default allocator used by the library.
 *
 * @return The default IFX_Allocator pointer.
 */
IFX_Allocator* FXMEM_GetDefAllocator();

#ifdef __cplusplus
}
#endif

#ifdef _DEBUG
  /** @brief Debug-mode allocation on an allocator. */
  #define FX_Allocator_Alloc(fxAllocator, type, size) \
    ((fxAllocator) ? (type*)(fxAllocator)->m_AllocDebug((fxAllocator), (size) * sizeof(type), __FILE__, __LINE__) : (FX_Alloc(type, size)))
  /** @brief Debug-mode re-allocation on an allocator. */
  #define FX_Allocator_Realloc(fxAllocator, type, ptr, new_size) \
    ((fxAllocator) ? (type*)(fxAllocator)->m_ReallocDebug((fxAllocator), (ptr), (new_size) * sizeof(type), __FILE__, __LINE__) : (FX_Realloc(type, ptr, new_size)))
#else
  /** @brief Release-mode allocation on an allocator. */
  #define FX_Allocator_Alloc(fxAllocator, type, size) \
    ((fxAllocator) ? (type*)(fxAllocator)->m_Alloc((fxAllocator), (size) * sizeof(type)) : (FX_Alloc(type, size)))
  /** @brief Release-mode re-allocation on an allocator. */
  #define FX_Allocator_Realloc(fxAllocator, type, ptr, new_size) \
    ((fxAllocator) ? (type*)(fxAllocator)->m_Realloc((fxAllocator), (ptr), (new_size) * sizeof(type)) : (FX_Realloc(type, ptr, new_size)))
#endif
/** @brief Free memory block on an allocator. */
#define FX_Allocator_Free(fxAllocator, ptr) \
    ((fxAllocator) ? (fxAllocator)->m_Free((fxAllocator), (ptr)) : (FX_Free(ptr)))
//<<<+++OPENSOURCE_MUST_END

#ifdef __cplusplus

/** @brief Placement new override with ::IFX_Allocator. */
inline void* operator new(size_t size, IFX_Allocator* fxAllocator)
{
  return (void*)FX_Allocator_Alloc(fxAllocator, FX_BYTE, size);
}

inline void operator delete(void* ptr, IFX_Allocator* fxAllocator)
{
  FX_Allocator_Free(fxAllocator, ptr);
}

/** @brief Macro for new operator on an allocator. */
#define FX_NewAtAllocator(fxAllocator) \
  ::new(static_cast<IFX_Allocator*>(fxAllocator))
/** @brief Macro for delete operator on an allocator. */
#define FX_DeleteAtAllocator(pointer, fxAllocator, __class__) \
  do { (pointer)->~__class__(); ::operator delete(static_cast<void*>(pointer), static_cast<IFX_Allocator*>(fxAllocator)); } while(false)

/**
 * @brief CFX_AllocObject class uses specific memory allocator to allocate and free memory.
 * All pAllocator parameter can be NULL, in this case the system default allocator is used
 * (then it will be same as CFX_Object).
 */
class CFX_AllocObject
{
 public:
  /**
   * @brief new operator for debug mode.
   *
   * @param[in] size        The size in bytes to allocate.
   * @param[in] pAllocator  The Allocator used to allocate memory.
   * @param[in] file        The name of the current source file.
   * @param[in] line        The line number in the current source file.
   *
   * @return Address of a new memory block.
   */
  void*      operator new (size_t size, IFX_Allocator* pAllocator, FX_LPCSTR file, int line);
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief delete operator for debug mode.
   *
   * @param[in] p           The Address of a memory block to be deleted.
   * @param[in] pAllocator  The Allocator used to free memory.
   * @param[in] file        The name of the current source file.
   * @param[in] line        The line number in the current source file.
   *
   * @return None.
   */
  void      operator delete (void* p, IFX_Allocator* pAllocator, FX_LPCSTR file, int line);
#endif

  /**
   * @brief new operator for release mode.
   *
   * @param[in] size        The size in bytes to allocate.
   * @param[in] pAllocator  The Allocator used to allocate memory.
   *
   * @return Address of a new memory block.
   */
  void*      operator new (size_t size, IFX_Allocator* pAllocator);
  /**
   * @brief delete operator for release mode.
   *
   * @param[in] p  The Address of a memory block to be deleted.
   *
   * @return None.
   */
  void      operator delete (void* p);
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief delete operator for release mode.
   *
   * @param[in] p           The Address of a memory block to be deleted.
   * @param[in] pAllocator  The Allocator used to free memory.
   *
   * @return None.
   */
  void      operator delete (void* p, IFX_Allocator* pAllocator);
#endif

  /**
   * @brief placement new operator.
   */
  void*      operator new (size_t, void* buf) { return buf; }
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief placement delete operator.
   */
  void      operator delete (void*, void*) {}
#endif

  /**
   * @brief Gets the Allocator pointer.
   *
   * @return A pointer to a IFX_Allocator object.
   */
  IFX_Allocator*  GetAllocator() const { return m_pAllocator; }

private:  /* all vector operators are disabled */
  /**
   * @brief new operator of vector for debug mode.
   *
   * @param[in] size        The size in bytes to allocate.
   * @param[in] pAllocator  The Allocator used to allocate memory.
   * @param[in] file        The name of the current source file.
   * @param[in] line        The line number in the current source file.
   *
   * @return Address of a new memory block.
   */
  void*      operator new[] (size_t size, IFX_Allocator* pAllocator, FX_LPCSTR file, int line) { return operator new(size, pAllocator, file, line); }
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief delete operator of vector for debug mode.
   *
   * @param[in] p           The Address of a memory block to be deleted.
   * @param[in] pAllocator  The Allocator used to free memory.
   * @param[in] file        The name of the current source file.
   * @param[in] line        The line number in the current source file.
   *
   * @return None.
   */
  void      operator delete[] (void* p, IFX_Allocator* pAllocator, FX_LPCSTR file, int line) {}
#endif

  /**
   * @brief new operator of vector for non-debug mode.
   *
   * @param[in] size        The size in bytes to allocate.
   * @param[in] pAllocator  The Allocator used to allocate memory.
   *
   * @return Address of a new memory block.
   */
  void*      operator new[] (size_t size, IFX_Allocator* pAllocator) { return operator new(size, pAllocator); }
  /**
   * @brief delete operator of vector for non-debug mode.
   *
   * @param[in] p  The Address of a memory block to be deleted.
   *
   * @return None.
   */
  void      operator delete[] (void* p) {}
#ifndef _FX_NO_EXCEPTION_
  /**
   * @brief delete operator of vector for non-debug mode.
   *
   * @param[in] p           The Address of a memory block to be deleted.
   * @param[in] pAllocator  The Allocator used to free memory.
   *
   * @return None.
   */
  void      operator delete[] (void* p, IFX_Allocator* pAllocator) {}
#endif

 protected:
  /*
   * The memory allocator.
   */
  IFX_Allocator*  m_pAllocator;
};

#if defined(_DEBUG)
  #define FX_NEWAT(pAllocator) new(pAllocator, __FILE__, __LINE__)
#else
  /**
   * @brief Foxit application should use FX_NEWAT macro when new a CFX_AllocObject derived object.
   * @hideinitializer
   */
  #define FX_NEWAT(pAllocator) new(pAllocator)
#endif

//////////////////////////////////////////////////////////////////////
//Cocurrency controls
//////////////////////////////////////////////////////////////////////

#if !defined(_FPDFAPI_MT_NONE_) && !defined(_FPDFAPI_MT_)
  // We enable multi-threading by default on all systems. However, MT can be disabled by compilation macro
  #define _FPDFAPI_MT_
#endif

#ifdef _FPDFAPI_MT_
  /**
   * @brief Lock object class.
   */
  class CFX_LockObject : public CFX_Object
  {
 public:
    /** @brief Construct a lock object. */
    CFX_LockObject() {FX_InitializeCriticalSection(&m_Lock);}
    /** @brief Destruct a lock object. */
    ~CFX_LockObject() {FX_DeleteCriticalSection(&m_Lock);}

    /** @brief Try to lock. For separating control. */
    FX_BOOL    TryLock()  {return FX_TryEnterCriticalSection(&m_Lock);}
    /** @brief Lock. For separating control. */
    void    Lock()    {FX_EnterCriticalSection(&m_Lock);}
    /** @brief Unlock. For separating control. */
    void    Unlock()  {FX_LeaveCriticalSection(&m_Lock);}

 protected:
    /* Critical section. */
    FX_CRITICAL_SECTION    m_Lock;
    friend class CFX_CSLock;
  };

  /**
   * @brief Lock operation class.
   */
  class CFX_CSLock
  {
 public:
    /** @brief Default constructor. */
    CFX_CSLock() : m_pCS(NULL) {}
    /** @brief Construct a lock operation with a critical section. */
    CFX_CSLock(FX_CRITICAL_SECTION* pCS) : m_pCS(pCS) {if (m_pCS) FX_EnterCriticalSection(m_pCS);}
    /** @brief Construct a Lock operation. */
    CFX_CSLock(CFX_LockObject* pObj) {m_pCS = &pObj->m_Lock; FX_EnterCriticalSection(m_pCS);}
    /** @brief Destruct a lock operation. */
    ~CFX_CSLock() {if (m_pCS) FX_LeaveCriticalSection(m_pCS);}

    /** @brief Critical Section. */
    FX_CRITICAL_SECTION*  m_pCS;
  };

  /** @brief A macro defines a lock operation with this pointer. */
  #define FXMT_CSLOCK_THIS          CFX_CSLock _fx_lock((CFX_LockObject*)this)
  /** @brief A macro defines a lock operation with a lock object. */
  #define FXMT_CSLOCK_OBJ(lock)        CFX_CSLock _fx_lock((CFX_LockObject*)lock)
  /** @brief A macro defines a named lock operation with a lock object. */
  #define FXMT_CSLOCK_DEFINEOBJ(csLock, lock) CFX_CSLock csLock((CFX_LockObject*)lock)

  /** @brief A macro defines a lock object. */
  #define FXMT_LOCKOBJECT_DEFINE(lockObj)    CFX_LockObject lockObj
  /** @brief A macro tries to lock. */
  #define FXMT_LOCKOBJECT_TRYLOCK(lockObj)  (lockObj)->TryLock()
  /** @brief A macro tries to lock with if. */
  #define FXMT_LOCKOBJECT_TRYLOCK_IF(lockObj)  if ((lockObj)->TryLock())
  /** @brief A macro locks. */
  #define FXMT_LOCKOBJECT_LOCK(lockObj)    (lockObj)->Lock()
  /** @brief A macro unlocks. */
  #define FXMT_LOCKOBJECT_UNLOCK(lockObj)    (lockObj)->Unlock()
#else //!_FPDFAPI_MT_
  class CFX_LockObject : public CFX_Object {};
  #define FXMT_CSLOCK_THIS
  #define FXMT_CSLOCK_OBJ(lock)
  #define FXMT_CSLOCK_DEFINEOBJ(csLock, lock)

  #define FXMT_LOCKOBJECT_DEFINE(lockObj)
  #define FXMT_LOCKOBJECT_TRYLOCK(lockObj)
  #define FXMT_LOCKOBJECT_TRYLOCK_IF(lockObj)  if (1)
  #define FXMT_LOCKOBJECT_LOCK(lockObj)
  #define FXMT_LOCKOBJECT_UNLOCK(lockObj)
#endif
//<<<+++OPENSOURCE_MUST_END

/**
 * @brief Memory Allocator for Build-Readonly applications, which only grow the memory consumption,
 * then free them all at once. This can be very useful when consolidating small memory pieces
 * together especially on embedded platforms. Also because there is no need to keep track of
 * block availability, there is no allocation overhead.
 */

class CFX_GrowOnlyPool : public IFX_Allocator, public CFX_Object

{
 public:
  /**
   * @brief A Constructor.
   *
   * @param[in] pAllocator  The memory allocator pointer. This can be <b>NULL</b> and
   *                        means to use FXCRT default allocator. Default value: <b>NULL</b>.
   * @param[in] trunk_size  The size of the memory consumption. default trunk size is 16K. Default value: 16384
   */

  CFX_GrowOnlyPool(IFX_Allocator* pAllocator = NULL, size_t trunk_size = 16384);

  /**
   * @brief A Destructor.
   */
  ~CFX_GrowOnlyPool();

  /**
   * @brief Change the allocator. The underlying allocator can only be changed before anything allocated from the pool.
   *
   * @param[in] pAllocator  An IFX_Allocator pointer.
   *
   * @return None.
   */
  void  SetAllocator(IFX_Allocator* pAllocator);

  /**
   * @brief Change the trunk size.
   *
   * @param[in] trunk_size  New trunk size to change.
   *
   * @return None.
   */
  void  SetTrunkSize(size_t trunk_size) { m_TrunkSize = trunk_size; }

  /**
   * @brief The debug-mode allocation function.
   *
   * @param[in] size  The size in bytes to allocate.
   * @param[in] file  The name of the current source file.
   * @param[in] line  The line number in the current source file.
   *
   * @return Address of new memory block.
 */
  void*  AllocDebug(size_t size, FX_LPCSTR file, int line) { return Alloc(size); }
  /**
   * @brief The allocation function.
   *
   * @param[in] size  The size in bytes to allocate.
   *
   * @return Address of new memory block.
   */
  void*  Alloc(size_t size);
  /**
   * The debug-mode re-allocation function.
   *
   * @return None.
   *
   * @note Do not call this function.
   */
  void*  ReallocDebug(void* p, size_t new_size, FX_LPCSTR file, int line) { return NULL; }
  /**
   * The re-allocation function.
   *
   * @return None.
   *
   * @note Do not call this function.
   */
  void*  Realloc(void* p, size_t new_size) { return NULL; }
  /**
   * @brief Free the memory.
   *
   * @return None.
   */
  void Free(void* mem) {}

  /**
   * @brief Free all the memory.
   *
   * @return None.
   */
  void  FreeAll();

 private:
  /* Trunk size. */
  size_t  m_TrunkSize;
  /* Pointer to the first trunk. */
  void*  m_pFirstTrunk;

  /* Memory allocator. */
  IFX_Allocator*  m_pAllocator;
    /* Critical section used for synchronization. */
    FX_CRITICAL_SECTION  m_Lock;

};

// A Proxy class for allocate memory.

template <class T> class AllocProxy : public CFX_Object {
 public:
  AllocProxy(size_t size) { buffer = (T *)FX_Alloc(T, size); }
  ~AllocProxy() { if (buffer) FX_Free(buffer); }
  T &operator[](int index) { return buffer[index]; }
  operator T *() { return buffer; }
  T *operator +(int offset) { return buffer + offset; }
  operator bool() const { return !!buffer; }
  T *operator->() const { return buffer; }

 private:
  AllocProxy(const AllocProxy &) {}
  AllocProxy &operator=(const AllocProxy &) {}
  T* buffer;
};

// Used with std::unique_ptr to Release() objects that can't be deleted.
template <class T>
struct CFX_ReleaseDeleter {
  inline void operator()(T* ptr) const { ptr->Release(); }
};

//<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#endif //__cplusplus
//<<<+++OPENSOURCE_MUST_END

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//* Fixed memory management
//*****************************************************************************
#define _FXMEM_NO64_
//#define  _FXMEM_LIT_

/** @brief Size of memory page, 64KB. */
#define FX_FIXEDMEM_PAGESIZE    (4096 * 16)
/** @brief Size of middle data block, 4KB. */
#define FX_FIXEDMEM_MIDBLOCKSIZE  (4096)

/** @brief Structure of fixed memory configuration. */
typedef struct _FX_MEMCONFIG
{
  /** @brief Initial number of memory pages for 8-bytes fixed data size. 1 for desktop platforms, 1 for limited memory environments. */
  size_t  nPageNum_Init8;
  /** @brief Initial number of memory pages for 16-bytes fixed data size. 8 for desktop platforms, 5 for limited memory environments. */
  size_t  nPageNum_Init16;
  /** @brief Initial number of memory pages for 32-bytes fixed data size. 24 for desktop platforms, 8 for limited memory environments. */
  size_t  nPageNum_Init32;
  #if !defined(_FXMEM_NO64_)
    size_t  nPageNum_Init64;
  #endif
  /** @brief More number of memory pages for 16-bytes fixed data size. 8 for desktop platforms, 4 for limited memory environments. */
  size_t  nPageNum_More16;
  /** @brief More number of memry pages for 32-bytes fixed data size. 24 for desktop platforms, 12 for limited memory environments. */
  size_t  nPageNum_More32;
  #if !defined(_FXMEM_NO64_)
    size_t  nPageNum_More64;
  #endif
  #if defined(_FXMEM_LIT_)
    size_t  nPageSize_Lit;
    size_t  nPageNum_InitLit;
    size_t  nPageNum_MoreLit;
    size_t  nPageNum_ReservedLit;
  #endif
  /** @brief Size of memory pages for middle data range (> 32-bytes & <= FX_FIXEDMEM_MIDBLOCKSIZE). 32 for desktop platforms, 8 for limited memory environments. */
  size_t  nPageSize_Mid;
  /** @brief Initial number of memory pages for middle data range. 2 for desktop platforms, 2 for limited memory environments. */
  size_t  nPageNum_InitMid;
  /** @brief More number of memory pages for middle data range. 4 for desktop platforms, 4 for limited memory environments. */
  size_t  nPageNum_MoreMid;
  /** @brief Minimum size of memory page for large data (> FX_FIXEDMEM_MIDBLOCKSIZE). 128 for desktop platforms, 32 for limited memory environments. */
  size_t  nPageSize_Large;
  /** @brief Minimum size of alone memory page for large data. 64 for desktop platforms, 64 for limited memory environments. */
  size_t  nPageSize_Alone;
}FX_MEMCONFIG;

/**
 * @brief Set configuration of fixed memory.
 *
 * @details This function is optional for desktop platforms, and should be called at first to change default configuration
 *          when start application before initialize fixed memory manager.
 *
 * @param[in] memConfig  A pointer to memory configuration.
 *
 * @return None.
 */
void  FXMEM_SetConfig(const FX_MEMCONFIG* memConfig);

/** @brief Fixed memory state. */
//#define _FX_MEMSTATE_
#if defined(_FX_MEMSTATE_)

  typedef struct _FX_MEMPAGESTATE_
  {
    size_t  nCurMemSize;
    size_t  nMinMemSize;
    size_t  nMaxMemSize;
    size_t  nCurAvailSize;
    size_t  nMinAvailSize;
    size_t  nMaxAvailSize;
    size_t  nCurUsedSize;
    size_t  nMinUsedSize;
    size_t  nMaxUsedSize;
    size_t  nCurUsedRate;
    size_t  nMinUsedRate;
    size_t  nMaxUsedRate;
    size_t  bValid;
  }FX_MEMPAGESTATE;
  typedef struct _FX_MEMINFO_
  {
    size_t      memBlockCount[64];
    FX_MEMPAGESTATE  pageState8;
    FX_MEMPAGESTATE  pageState16;
    FX_MEMPAGESTATE  pageState32;
    FX_MEMPAGESTATE  pageStateMid;
    FX_MEMPAGESTATE  pageStateLarge;
    FX_MEMPAGESTATE  totalState;
  }FX_MEMINFO;

  #define FX_MEMSTATE_RATEFRACTION  100000

  void      FX_MemState_MergeInfo(FX_MEMINFO *mi1, const FX_MEMINFO *mi2);
  FX_MEMINFO*    FX_MemState_GetInfo();
  void      FX_MemState_ResetInfo();

#endif //_FX_MEMSTATE_

#ifdef __cplusplus
}
#endif

//<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#endif //_FX_MEMORY_H_
//<<<+++OPENSOURCE_MUST_END

/** @} */

//<<<+++OPENSOURCE_END
