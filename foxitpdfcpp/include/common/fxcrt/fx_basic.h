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
 * @file fx_basic.h
 * @brief Header file for basic data class.
 */

//<<<+++OPENSOURCE
//<<<+++OPENSOURCE_LICENSE
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT||LIC==GOOGLE

/**
 * @addtogroup FXCRT
 * @{
 */
//<<<+++OPENSOURCE_MUST_BEGIN
#ifndef _FX_BASIC_H_
#define _FX_BASIC_H_

/* System dependant definitions */
#ifndef _FX_SYSTEM_H_
  #include "fx_system.h"
#endif
#ifndef _FX_MEMORY_H_
  #include "fx_memory.h"
#endif
#ifndef _FX_STRING_H_
  #include "fx_string.h"
#endif
#ifndef _FX_STREAM_H_
  #include "fx_stream.h"
#endif
//<<<+++OPENSOURCE_MUST_END

#ifndef _FX_EXCEPTION_H_
  #include "fx_exception.h"
#endif

//*****************************************************************************
//* Buffer
//*****************************************************************************
/**
 * @brief Dynamic binary buffers designed for more efficient appending.
 */
class CFX_BinaryBuf : public CFX_Object
{
 public:
  /** 
   * @brief A default constructor creating an empty buffer. 
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_BinaryBuf(IFX_Allocator* pAllocator = NULL);

  /** 
   * @brief A default constructor creating an empty buffer. 
   *
   * @param[in] size        The size of buffer.
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_BinaryBuf(FX_STRSIZE size, IFX_Allocator* pAllocator = NULL);
  //<<<+++OPENSOURCE_END

  /** @brief The destructor. */
  ~CFX_BinaryBuf();

  /**
   * @brief Set the binary buffer to be empty. 
   *
   * @return None.
   */
  void          Clear();

  /**
   * @brief Change the allocated buffer size, and set the allocation step if alloc_step is non-zero.
   *
   * @param[in] size        The new size expected.
   * @param[in] alloc_step  The new allocation step. If alloc_step is 0, then the allocation step will not change.
   *                        Default value: 0.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          EstimateSize(FX_STRSIZE size, FX_STRSIZE alloc_step = 0);

  /**
   * @brief Append a binary buffer block.
   *
   * @param[in] pBuf  A pointer to a binary buffer block.
   * @param[in] size  The size in bytes of the buffer block.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          AppendBlock(const void* pBuf, FX_STRSIZE size);

  /**
   * @brief Append a byte for specified number times. Not a byte-by-byte processing, but a byte filling processing internally.
   *
   * @param[in] byte   The input byte.
   * @param[in] count  Number of times.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          AppendFill(FX_BYTE byte, FX_STRSIZE count);

  /**
   * @brief Append a non-buffered byte string.
   *
   * @param[in] str  A no-buffered byte string.
   *
   * @return None.
   */
  void          AppendString(FX_BSTR str) { AppendBlock(str.GetPtr(), str.GetLength()); }

  /**
   * @brief Append a single byte.
   *
   * @param[in] byte  A single byte.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  inline FX_BOOL        AppendByte(FX_BYTE byte)
  {
    if (m_AllocSize <= m_DataSize)
    {
      if (!ExpandBuf(100))
        return false;
    }
    m_pBuffer[m_DataSize++] = byte;
    return true;
  }

  /**
   * @brief Insert a binary buffer block at the specified position.
   *
   * @param[in] pos   Specifies the zero-based index of the position in the binary buffer.
   * @param[in] pBuf  A pointer to a binary buffer block.
   * @param[in] size  The size in bytes of the buffer block.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          InsertBlock(FX_STRSIZE pos, const void* pBuf, FX_STRSIZE size);

  /**
   * @brief Attach to a buffer (this buffer will belong to this object). The buffer must be allocated by FX_Alloc.
   *
   * @param[in] pBuf  A pointer to a binary buffer.
   * @param[in] size  The size in bytes of the buffer.
   *
   * @return None.
   */
  void          AttachData(void* pBuf, FX_STRSIZE size);

  /**
   * @brief Copy from another buffer.
   *
   * @param[in] pBuf  A pointer to a binary buffer.
   * @param[in] size  The size in bytes of the input buffer.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          CopyData(const void* pBuf, FX_STRSIZE size);
  /**
   * @brief Takeover another buffer.
   *
   * @details This function attaches to the source CFX_BinaryBuf object's buffer. The source CFX_BinaryBuf object
   *          has detached the buffer.
   *
   * @param[in] other  A ref to CFX_BinaryBuf object.
   *
   * @return None.
   */
  void          TakeOver(CFX_BinaryBuf& other);

  /**
   * @brief Delete a inter-zone buffer defining by parameters start_index and count in the binary buffer.
   *
   * @param[in] start_index  Specifies the zero-based index of the start position to be deleted in the binary buffer.
   * @param[in] count        Specifies the length in bytes to be deleted.
   *
   * @return None.
   */
  void          Delete(int start_index, int count);

  /**
   * @brief Get a byte pointer to the binary buffer.
   *
   * @return A byte pointer to the binary buffer.
   */
  FX_LPBYTE        GetBuffer() const { return m_pBuffer; }

  /**
   * @brief Get the length of the binary buffer.
   *
   * @return The length in bytes of the binary buffer.
   */
  FX_STRSIZE        GetSize() const { return m_DataSize; }

  /**
   * @brief Get a byte string from the buffer.
   *
   * @return A byte string.
   */
  CFX_ByteStringC      GetByteString() const;

  /**
   * @brief Get a byte string from current buffer object.
   *
   * @param[out] str  Receives the byte string from current buffer object.
   *
   * @return None,
   */
  void          GetByteStringL(CFX_ByteStringL &str) const;

  /**
   * @brief Detach the buffer. Just set buffer pointer to <b>NULL</b>, and set the binary buffer size to zero.
   *
   * @return None.
   */
  void          DetachBuffer();

  /** @brief Special allocator pointer. <b>NULL</b> means to use default allocator. */
  IFX_Allocator*      m_pAllocator;

 protected:
  /* Allocation step. */
  FX_STRSIZE        m_AllocStep;
  /* The buffer pointer. */
  FX_LPBYTE        m_pBuffer;
  /* The length in bytes of the buffer. */
  FX_STRSIZE        m_DataSize;
  /* Allocation size in bytes of the buffer. */
  FX_STRSIZE        m_AllocSize;
  /*
   * Increase allocated buffer, not data size.
   *
   * @param[in] size    The size in bytes to increase.
   */
  FX_BOOL          ExpandBuf(FX_STRSIZE size);
};

/**
 * Dynamic byte text buffers designed for more efficient appending.
 */
class CFX_ByteTextBuf : public CFX_BinaryBuf
{
 public:
  /**
    * @brief Construct with allocator.
    *
    * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> means to use default allocator.
    *                        Default value: <b>NULL</b>
    */
  CFX_ByteTextBuf(IFX_Allocator* pAllocator = NULL) : CFX_BinaryBuf(pAllocator) {}

  /**
   * @brief Assignment(=) operator overload. From a non-buffered byte string.
   *
   * @param[in] str  A non-buffered byte string.
   *
   * @return None.
   */
  void          operator = (FX_BSTR str);

  /**
   * @brief Append a single character or byte.
   *
   * @param[in] ch  A single character or byte.
   *
   * @return None.
   */
  void          AppendChar(int ch) { AppendByte((FX_BYTE)ch); }

  /**
   * @brief Left shifts(<<) operator overload. Output an integer to the byte text buffer.
   *
   * @param[in] i  The input integer.
   *
   * @return A reference to the byte text buffer.
   */
  CFX_ByteTextBuf&    operator << (int i);

  /**
   * @brief Left shifts(<<) operator overload. Output a FX_DWORD to the byte text buffer.
   *
   * @param[in] i  The input value of FX_DWORD type.
   *
   * @return A reference to the byte text buffer.
   */
  CFX_ByteTextBuf&    operator << (FX_DWORD i);

  /**
   * @brief Left shifts(<<) operator overload. Output a double value to the byte text buffer.
   *
   * @param[in] f  The input double value.
   *
   * @return A reference to the byte text buffer.
   */
  CFX_ByteTextBuf&    operator << (double f);

  /**
   * @brief Left shifts(<<) operator overload. Output a non-buffered byte string to the byte text buffer.
   *
   * @param[in] lpsz  The input non-buffered byte string.
   *
   * @return A reference to the byte text buffer.
   */
  CFX_ByteTextBuf&    operator << (FX_BSTR lpsz);

  /**
   * @brief Left shifts(<<) operator overload. Output a byte text buffer to the byte text buffer.
   *
   * @param[in] buf  The input byte text buffer.
   *
   * @return A reference to the byte text buffer.
   */
  CFX_ByteTextBuf&    operator << (const CFX_ByteTextBuf& buf);

  /**
   * @brief Get the length of the byte text buffer.
   *
   * @return The length of the byte text buffer.
   */
  FX_STRSIZE        GetLength() const { return m_DataSize; }
};

/**
 * Dynamic wide text buffers designed for more efficient appending.
 */
class CFX_WideTextBuf : public CFX_BinaryBuf
{
 public:
  /**
    * @brief Construct with allocator.
    *
    * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> to use default allocator.
    *                        Default value: <b>NULL</b>.
    */
  CFX_WideTextBuf(IFX_Allocator* pAllocator = NULL) : CFX_BinaryBuf(pAllocator) {}

  /**
   * @brief Assignment(=) operator overload. From a zero terminated wide character string.
   *
   * @param[in] lpsz  A zero terminated wide character string.
   *
   * @return None.
   */
  void          operator = (FX_LPCWSTR lpsz);

  /**
   * @brief Assignment(=) operator overload. From a wide string.
   *
   * @param[in] str  A wide string.
   *
   * @return None.
   */
  void          operator = (FX_WSTR str);

  /**
   * @brief Append a single wide character.
   *
   * @param[in] wch  A single wide character.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          AppendChar(FX_WCHAR wch);

  /**
   * @brief Left shifts(<<) operator overload. Output a integer to the wide text buffer.
   *
   * @param[in] i  The input integer.
   *
   * @return A reference to the wide text buffer.
   */
  CFX_WideTextBuf&    operator << (int i);

  /**
   * @brief Left shifts(<<) operator overload. Output a double value to the wide text buffer.
   *
   * @param[in] f  The input double value.
   *
   * @return A reference to the wide text buffer.
   */
  CFX_WideTextBuf&    operator << (double f);

  /**
   * @brief Left shifts(<<) operator overload. Output a zero-terminated wide character string to the wide text buffer.
   *
   * @param[in] lpsz  The input zero-terminated wide character string.
   *
   * @return A reference to the wide text buffer.
   */
  CFX_WideTextBuf&    operator << (FX_LPCWSTR lpsz);

  /**
   * @brief Left shifts(<<) operator overload. Output a wide string to the wide text buffer.
   *
   * @param[in] str  The input wide string.
   *
   * @return A reference to the wide text buffer.
   */
  CFX_WideTextBuf&    operator << (FX_WSTR str);

  /**
   * @brief Left shifts(<<) operator overload. Output a wide string to the wide text buffer.
   *
   * @param[in] str    The input wide string.
   *
   * @return A reference to the wide text buffer.
   */
  CFX_WideTextBuf&    operator << (const CFX_WideString &str);

  /**
   * @brief Left shifts(<<) operator overload. Output a wide text buffer to the wide text buffer.
   *
   * @param[in] buf  The input wide text buffer.
   *
   * @return A reference to the wide text buffer.
   */
  CFX_WideTextBuf&    operator << (const CFX_WideTextBuf& buf);

  /**
   * @brief Get the length of the wide text buffer.
   *
   * @return The count of wide characters in the wide text buffer.
   */
  FX_STRSIZE        GetLength() const { return m_DataSize/sizeof(FX_WCHAR); }

  /**
   * @brief Get a wide character pointer.
   *
   * @return A wide character pointer to the wide text buffer.
   */
  FX_LPWSTR        GetBuffer() const { return (FX_LPWSTR)m_pBuffer; }

  /**
   * @brief Delete a inter-zone buffer defining by parameters <i>start_index</i> and <i>count</i> in the wide text buffer.
   *
   * @param[in] start_index  Specifies the zero-based index of the start position to be deleted in the wide text buffer buffer.
   * @param[in] count        Specifies the count of wide characters to be deleted.
   *
   * @return None.
   */
  void          Delete(int start_index, int count)
  {
    CFX_BinaryBuf::Delete(start_index * sizeof(FX_WCHAR), count * sizeof(FX_WCHAR));
  }

  /**
   * @brief Get a wide string from the wide text buffer.
   *
   * @return A wide string.
   */
  CFX_WideStringC      GetWideString() const;

  void          GetWideStringL(CFX_WideStringL& wideText) const;

};

//*****************************************************************************
//* Archive
//*****************************************************************************
/**
 * Binary archive using memory based buffer or stream.
 *
 * Providing cross-platform data serialization and de-serialization service.
 * Data structure is NOT stored in the archive, so the de-serialization must use exactly same
 * structure in when serialization.
 */
class CFX_ArchiveSaver : public CFX_Object
{
 public:
  /**
   * @brief Construct with allocator.
   *
   * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> to use default allocator.
   *                        Default value: <b>NULL</b>.
   */
  CFX_ArchiveSaver(IFX_Allocator* pAllocator = NULL) : m_SavingBuf(pAllocator), m_pStream(NULL) {}

  /**
   * @brief Left shifts(<<) operator overload. Serialize a single byte.
   *
   * @param[in] i  The input byte.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_BYTE i);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a bool.
   *
   * @param[in] i  The input bool.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_BOOL i);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a integer.
   *
   * @param[in] i  The input integer.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (int i);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a FX_DWORD value.
   *
   * @param[in] i  The input FX_DWORD value.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_DWORD i);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a FX_INT64 value.
   *
   * @param[in] i  The input FX_INT64 value.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_INT64 i);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a floating-point.
   *
   * @param[in] i  The input floating-point.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_FLOAT i);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a double value.
   *
   * @param[in] i  The input double value.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (double i);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a non-buffered byte string.
   *
   * @param[in] bstr  The input non-buffered byte string.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_BSTR bstr);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a zero-terminated string.
   *
   * @param[in] bstr  The input string.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_LPCSTR bstr);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a byte string.
   *
   * @param[in] bstr  The input byte string.
   *
   * @return A reference to the archive saver.
   */
   CFX_ArchiveSaver&    operator << (const CFX_ByteString& bstr);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a zero-terminated wide character string.
   *
   * @details Wide strings are stored in UTF-16LE encoding.
   *
   * @param[in] bstr  The input zero-terminated wide character string.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (FX_LPCWSTR bstr);

  /**
   * @brief Left shifts(<<) operator overload. Serialize a wide string.
   *
   * @details Wide strings are stored in UTF-16LE encoding.
   *
   * @param[in] wstr  The input wide string.
   *
   * @return A reference to the archive saver.
   */
  CFX_ArchiveSaver&    operator << (const CFX_WideString& wstr);

  /**
   * @brief Serialize a memory block.
   *
   * @param[in] pData   The pointer to a memory block.
   * @param[in] dwSize  The size in bytes of the memory block.
   *
   * @return None.
   */
  void          Write(const void* pData, FX_STRSIZE dwSize);

  /**
   * @brief Get the length of saved data.
   *
   * @return The length in bytes of the saved data.
   */
  FX_INTPTR        GetLength() const { return m_SavingBuf.GetSize(); }

  /**
   * @brief Get the constant byte pointer to the saved data.
   *
   * @return The constant byte pointer to the saved data.
   */
  FX_LPCBYTE        GetBuffer() const { return m_SavingBuf.GetBuffer(); }

  /**
   * @brief Set the attached stream.
   *
   * @param[in] pStream  The stream to the saved data.
   *
   * @return None.
   */
  void          SetStream(IFX_FileStream* pStream) { m_pStream = pStream; }

 protected:
  /* Saving data. */
  CFX_BinaryBuf      m_SavingBuf;
  /* Stream data. */
  IFX_FileStream*      m_pStream;
};

/**
 * Archive loader.
 */
class CFX_ArchiveLoader : public CFX_Object
{
 public:
  /**
   * @brief Construct a loading archive.
   *
   * @details The source data buffer must be valid during de-serialization.
   *
   * @param[in] pData   The source data buffer to be de-serialized.
   * @param[in] dwSize  The length in bytes of the source data buffer.
   */
  CFX_ArchiveLoader(FX_LPCBYTE pData, FX_DWORD dwSize);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a byte.
   *
   * @param[out] i  A reference to an byte to receive the byte value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (FX_BYTE& i);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a bool.
   *
   * @param[out] i  A reference to an bool to receive the bool value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (FX_BOOL& i);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a integer.
   *
   * @param[out] i  A reference to an integer to receive the integer value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (int& i);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a integer.
   *
   * @param[out] i  A reference to an integer to receive the integer value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (FX_INT64& i);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a FX_DWORD.
   *
   * @param[out] i  A reference to an FX_DWORD to receive the FX_DWORD value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (FX_DWORD& i);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a floating-point.
   *
   * @param[out] i  A reference to an floating-point to receive the floating-point value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (FX_FLOAT& i);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a double.
   *
   * @param[out] i  A reference to an double to receive the double value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (double& i);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a byte string.
   *
   * @param[out] bstr  A reference to an byte string to receive the byte string value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (CFX_ByteString& bstr);

  /**
   * @brief Right shifts(>>) operator overload. De-serialize a wide string.
   *
   * @param[out] wstr  A reference to an wide string to receive the wide string value.
   *
   * @return A reference to the archive loader.
   */
  CFX_ArchiveLoader&    operator >> (CFX_WideString& wstr);

  /**
   * @brief Check whether de-serializing is to the end of the loading buffer.
   *
   * @return <b>true</b> means to the end, and <b>false</b> means not yet.
   */
  FX_BOOL          IsEOF();

  /**
   * @brief De-serialize a memory block.
   *
   * @param[in,out] pBuf  A memory block pointer to receive the data.
   * @param[in] dwSize    The size in bytes of the memory block.
   *
   * @return <b>TRUE</b> means success, while <b>FALSE</b> means failure.
   */
  FX_BOOL          Read(void* pBuf, FX_DWORD dwSize);

 protected:
  /* Current loading position. */
  FX_DWORD        m_LoadingPos;
  /* Loading buffer. */
  FX_LPCBYTE        m_pLoadingBuf;
  /* The size in bytes of the loading buffer. */
  FX_DWORD        m_LoadingSize;
};

/**
 * Buffer Archive
 */
class IFX_BufferArchive
{
 public:
  /**
   * @brief Construct with buffer size and special allocator.
   *
   * @param[in] size        Initial buffer size.
   * @param[in] pAllocator  Allocator used in this class.
   *                        <b>NULL</b> to use default allocator. Default value: <b>NULL</b>.
   */
  IFX_BufferArchive(FX_STRSIZE size, IFX_Allocator* pAllocator = NULL);
  //<<<+++OPENSOURCE_END

  /**
   * @brief The destructor.
   */
  virtual ~IFX_BufferArchive() {}

  /**
   * @brief Clear the text buffer.
   *
   * @return None.
   */
  virtual void      Clear();

  /**
   * @brief Flush internal buffer of the file.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          Flush();

  /**
   * @brief Append a binary buffer block.
   *
   * @param[in] pBuf  A pointer to a binary buffer block.
   * @param[in] size  The size in bytes of the buffer block.
   *
   * @return Buffer size. -1 means error.
   */
  FX_INT32        AppendBlock(const void* pBuf, size_t size);

  /**
   * @brief Append a single byte.
   *
   * @param[in] byte  A single byte.
   *
   * @return Buffer size. -1 means error.
   */
  FX_INT32        AppendByte(FX_BYTE byte);

  /**
   * @brief Append a FX_DWORD value.
   *
   * @param[in] i  A FX_DWORD value.
   *
   * @return Buffer size. -1 means error.
   */
  FX_INT32        AppendDWord(FX_DWORD i);

  /**
   * @brief Append a FX_INT64 value.
   *
   * @param[in] i  A FX_INT64 value.
   *
   * @return Buffer size. -1 means error.
   */
  FX_INT32        AppendInt64(FX_INT64 i);

  /**
   * @brief Append a byte string value.
   *
   * @param[in] lpsz  A byte string value.
   *
   * @return Buffer size. -1 means error.
   */
  FX_INT32        AppendString(FX_BSTR lpsz);

 protected:
  /*
   * @brief Do work, it will be called when the text buffer is full.
   *
   * @param[in] pBuf  A pointer to a binary buffer block.
   * @param[in] size  The size in bytes of the buffer block.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual  FX_BOOL      DoWork(const void* pBuf, size_t size) = 0;

  /* Special allocator pointer. NULL to use default allocator. */
  IFX_Allocator*      m_pAllocator;

  /* The buffer size*/
  FX_STRSIZE        m_BufSize;
  /* Buffer. */
  FX_LPBYTE        m_pBuffer;
  /* Current buffer length. */
  FX_STRSIZE        m_Length;
};

/**
 * The class represents file buffer archive.
 */
class CFX_FileBufferArchive : public IFX_BufferArchive, public CFX_Object
{
 public:
  /**
   * @brief A constructor with size and allocator.
   *
   * @param[in] size        The size buffer. Default value: 32768
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_FileBufferArchive(FX_STRSIZE size = 32768, IFX_Allocator* pAllocator = NULL);

  /**
   * @brief The destructor.
   */
  ~CFX_FileBufferArchive();

  /**
   * @brief Clear buffer.
   *
   * @return None.
   */
  virtual void      Clear();

  /**
   * @brief Flush internal buffer.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          Flush();

  /**
   * @brief Attach file
   *
   * @param[in] pFile      A pointer to file stream.
   * @param[in] bTakeover  A boolean value to decide whether take over the file. Default value: <b>NULL</b>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          AttachFile(IFX_StreamWrite *pFile, FX_BOOL bTakeover = false);

  /**
   * @brief Attach file
   *
   * @param[in] filename  unicode file name. Available only for platforms supporting CRT file access (fopen, ...).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          AttachFile(FX_LPCWSTR filename);

  /**
   * @brief Attach file
   *
   * @param[in] filename  unicode file name. Available only for platforms supporting CRT file access (fopen, ...).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL          AttachFile(FX_LPCSTR filename);

 private:
  /*
   * Do work, it will be called when the text buffer is full.
   *
   * @param[in] pBuf  A pointer to a binary buffer block.
   * @param[in] size  The size in bytes of the buffer block.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual FX_BOOL      DoWork(const void* pBuf, size_t size);

  /* The file stream. */
  IFX_StreamWrite      *m_pFile;
  /* whether take over the file. */
  FX_BOOL          m_bTakeover;
};

/**
 * Abstract class for character mappings (encodings).
 * All character maps should have the ability to convert between internal encoding and Unicode.
 */
struct CFX_CharMap
{
  /**
   * @brief Get a character mapper according to Windows code page or other encoding system.
   *        This char maps are managed by FXAPI, don't destroy them.
   *
   * @details This is system default mapper according to locale settings.
   *
   * @param[in] codepage  The code page.
   *
   * @return A character mapper.
   */
  static CFX_CharMap*    GetDefaultMapper(FX_INT32 codepage = 0);

  /**
   * @brief A pointer type to GetWideString function.
   *
   * @details The function converts a byte string to a wide string according a  character mapper.<br>
   *          The function prototype is:
   *          CFX_WideString GetWideString(CFX_CharMap* pMap, const CFX_ByteString& bstr);
   *
   * @param[in] pMap  A character mapper.
   * @param[in] bstr  A byte string.
   *
   * @return A wide string.
   */
  CFX_WideString  (*m_GetWideString)(CFX_CharMap* pMap, const CFX_ByteString& bstr);

  /**
   * @brief A pointer type to GetByteString function.
   *
   * @details The function converts a wide string to a byte string according a  character mapper.<br>
   *          The function prototype is: CFX_ByteString GetByteString(CFX_CharMap* pMap, const CFX_WideString& wstr);
   *
   * @param[in] pMap  A character mapper.
   * @param[in] wstr  A wide string.
   *
   * @return A byte string.
   */
  CFX_ByteString  (*m_GetByteString)(CFX_CharMap* pMap, const CFX_WideString& wstr);

  /**
   * @brief A pointer type to GetCodePage function. The function return a code page of the platform.
   *
   * @return The function return a code page of the platform.
   */
  FX_INT32    (*m_GetCodePage)();
};

//*****************************************************************************
//* UTF-8
//*****************************************************************************
/**
 * The class represents a simple UTF-8 decoder.
 */
class CFX_UTF8Decoder
{
 public:
  /**
   * @brief A constructor. Set the decoder to initial.
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   *
   * @return None.
   */
  CFX_UTF8Decoder(IFX_Allocator* pAllocator = NULL) : m_PendingBytes(0),m_PendingChar(0),m_Buffer(pAllocator) { }

  /**
   * @brief Clear the decoding status and set the output wide text buffer to be empty.
   *
   * @return None.
   */
  void      Clear();

  /**
   * @brief Input a byte.
   *
   * @param[in] byte  The input byte.
   *
   * @return None.
   */
  void      Input(FX_BYTE byte);

  /**
   * @brief Append characters to wide text buffer.
   *
   * @param[in] ch  The input character.
   *
   * @return None.
   */
  void      AppendChar(FX_DWORD ch);

  /**
   * @brief Clear the decoding status.
   *
   * @return None.
   */
  void      ClearStatus() { m_PendingBytes = 0; }

  /**
   * @brief Get the result.
   *
   * @return A wide string.
   */
  CFX_WideStringC  GetResult() const { return m_Buffer.GetWideString(); }

  /**
   * @brief Get the result.
   *
   * @param[out] result  A wide string to receive the result.
   *
   * @return None.
   */
  void      GetResult(CFX_WideStringL &result) const {m_Buffer.GetWideStringL(result);}

 protected:
  /* The decoding status. */
  int        m_PendingBytes;
  /* Cached value. */
  FX_DWORD    m_PendingChar;
  /* The output wide text buffer. */
  CFX_WideTextBuf  m_Buffer;
};

/**
 * The class represents a simple UTF-8 encoder.
 */
class CFX_UTF8Encoder
{
 public:
  /**
   * @brief A constructor. Set the encoder to initial.
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>
   */
  CFX_UTF8Encoder(IFX_Allocator* pAllocator = NULL) : m_Buffer(pAllocator) { m_UTF16First = 0; }

  /**
   * @brief Input a unicode.
   *
   * @param[in] unicode  The input unicode.
   *
   * @return None.
   */
  void      Input(FX_WCHAR unicode);

  /**
   * @brief Append a non-buffered byte string.
   *
   * @param[in] str  A non-buffered byte string.
   *
   * @return None.
   */
  void      AppendStr(FX_BSTR str) { m_UTF16First = 0; m_Buffer << str; }

  /**
   * @brief Get the result.
   *
   * @return A byte string.
   */
  CFX_ByteStringC  GetResult() const { return m_Buffer.GetByteString(); }

  /**
   * @brief Get the result.
   *
   * @param[out] result  Receives the result byte string.
   *
   * @return None.
   */
  void      GetResult(CFX_ByteStringL &result) const {m_Buffer.GetByteStringL(result);}

 protected:
  /* The output byte text buffer. */
  CFX_ByteTextBuf  m_Buffer;
  /* The encoding status. */
  FX_DWORD    m_UTF16First;
};

/**
 * @brief A simple URL encode.
 *
 * @param[in] wsUrl  A URL string to be encoded.
 *
 * @return The encoded URL string.
 */
CFX_ByteString FX_UrlEncode(const CFX_WideString& wsUrl);

/**
 * @brief A simple URL decode.
 *
 * @param[in] bsUrl  A URL string to be decoded.
 *
 * @return The decoded URL string.
 */
CFX_WideString FX_UrlDecode(const CFX_ByteString& bsUrl);

/**
 * @brief A simple URI encode.
 *
 * @param[in] wsURI  A URI string to be encoded.
 *
 * @return The encoded URI string.
 */
CFX_ByteString FX_EncodeURI(const CFX_WideString& wsURI);

/**
 * @brief A simple URI Decode.
 *
 * @param[in] bsURI  A URI string to be decoded.
 *
 * @return The decoded URI string.
 */
CFX_WideString FX_DecodeURI(const CFX_ByteString& bsURI);

//*****************************************************************************
//* Array
//*****************************************************************************
/**
 * The class represents basic array class. Total allocated size is limited to 2^28 bytes (256MB).
 */
class CFX_BasicArray : public CFX_Object
{
 public:
  /** @brief Special allocator pointer. NULL to use default allocator. */
  IFX_Allocator*  m_pAllocator;

 protected:
  /*
   * @brief Construct with specified unit size.
   *
   * @param[in] unit_size   The specified unit size. Must be greater than 0 and less than 2^28.
   * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> means to use default allocator.
   *                        Default value: <b>NULL</b>.
   */
  CFX_BasicArray(int unit_size, IFX_Allocator* pAllocator = NULL);
  //<<<+++OPENSOURCE_END

  /*
   * @brief The destructor.
   */
  ~CFX_BasicArray();

  /*
   * @brief The copy constructor.
   *
   * @param[in] other      The other CFX_BasicArray object.
   * @param[in] pAllocator An allocator.
   */
  CFX_BasicArray(const CFX_BasicArray& other, IFX_Allocator* pAllocator = NULL);

  /*
   * @brief The assignment operator.
   *
   * @param[in] other  The other CFX_BasicArray object.
   *
   * @return Reference to current object itself.
   */
  CFX_BasicArray& operator=(const CFX_BasicArray& other);

  /*
   * @brief Change the allocated size and the grow amount.
   *
   * @param[in] nNewSize  The new size in elements expected.
   * @param[in] nGrowBy   The grow amount in elements expected, nGrowBy can be -1 for the grow amount unchanged.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure (such as parameter or memory error).
   */
  FX_BOOL      SetSize(int nNewSize, int nGrowBy);

  /*
   * @brief Append a basic array.
   *
   * @param[in] src  The input basic array. It must have the save unit size as the current array.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure (such as memory error).
   */
  FX_BOOL      Append(const CFX_BasicArray& src);

  /*
   * @brief Copy from a basic array.
   *
   * @param[in] src  The input basic array. It must have the save unit size as the current array.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure (such as memory error).
   */
  FX_BOOL      Copy(const CFX_BasicArray& src);

  /*
   * @brief Insert spaces at specified position.
   *
   * @param[in] nIndex  Specifies the zero-based index of element in the basic array.
   * @param[in] nCount  Specifies the count of element to insert.
   *
   * @return A byte pointer to the inserted space. <b>NULL</b> means error.
   */
  FX_LPBYTE    InsertSpaceAt(int nIndex, int nCount);

  /*
   * @brief Remove a number of elements.
   *
   * @param[in] nIndex  Specifies the zero-based index of start element in the basic array to be removed.
   * @param[in] nCount  Specifies the count of element to remove.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure (such as parameter error).
   */
  FX_BOOL      RemoveAt(int nIndex, int nCount);

  /*
   * @brief Insert a basic array at specified position.
   *
   * @param[in] nStartIndex  Specifies the zero-based index of start element to insert at.
   * @param[in] pNewArray    The input basic array. It must have the save unit size as the current array.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure (such as parameter or memory error).
   */
  FX_BOOL      InsertAt(int nStartIndex, const CFX_BasicArray* pNewArray);

  /*
   * @brief Get a typeless pointer to an element data.
   *
   * @param[in] index  Specifies the zero-based index of element.
   *
   * @return A typeless pointer to the element data. <b>NULL</b> means error.
   */
  const void*    GetDataPtr(int index) const;

 protected:
  /* The actual array of data */
  FX_LPBYTE    m_pData;
  /*  # of elements (upperBound - 1) */
  int        m_nSize;
  /* Max allocated */
  int        m_nMaxSize;
  /* Grow amount. */
  int        m_nGrowBy;
  /* Number of bytes in one unit. */
  int        m_nUnitSize;
};

/** The class represents array template. Total allocated size is limited to 2^28 bytes (256MB).*/
template<class TYPE>
class CFX_ArrayTemplate : public CFX_BasicArray
{
 public:
  /**
   * @brief Enumeration for error type.
   *
   * @details Values of this enumeration should be used alone.
   */
  enum ErrorType{
    /** @brief Invalid array size. */
    invalidArraySize,

    /** @brief Memory allocation error.*/
    memoryAllocationError,

    /** @brief Index out of range.*/
    indexOutOfRange
  };

  /**
   * @brief Constructor, from an allocator.
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_ArrayTemplate(IFX_Allocator* pAllocator = NULL) : CFX_BasicArray(sizeof(TYPE), pAllocator) {}
  //<<<+++OPENSOURCE_END

  /**
   * @brief The copy constructor.
   *
   * @param[in] other       The other array template object.
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_ArrayTemplate(const CFX_ArrayTemplate& other, IFX_Allocator* pAllocator = NULL) : CFX_BasicArray(other, pAllocator) {}

  /**
   * @brief The function is called when raise a fatal error.Print error info an exit(1).
   *
   * @param[in] error      The error type. It should be one of following values: <br>
   *                       {@link CFX_ArrayTemplate::invalidArraySize}, {@link CFX_ArrayTemplate::memoryAllocationError}.
   * @param[in] badIndex   The bad index. Default value: 0
   *
   * @return None.
   */
  void FX_Error(ErrorType error,FX_INT32 badIndex=0) const
  {
    const char *errorMsg[] = {
      "Invalid array size",
      "Memory allocation error",
      "Invalid index:"
    };

    fprintf(stderr, "%s\n", errorMsg[error]);
    if(error == indexOutOfRange)
      fprintf(stderr, "%i\n", badIndex);
    abort();
  }

    /**
     * @brief Get the number of elements in the array.
     *
     * @return The number of elements in the array.
     */
    int GetSize() const { return m_nSize; }

    /**
     * @brief Get the upper bound in the array, actually the maximum valid index.
     *
     * @return The upper bound.
     */
    int GetUpperBound() const { return m_nSize-1; }

    /**
     * @brief Change the allocated size and the grow amount.
     *
     * @param[in] nNewSize  The new size in elements expected.
     * @param[in] nGrowBy   The grow amount in elements expected. This can be -1 for the grow amount unchanged.
     *
   * @return <b>true</b>  means success, while <b>false</b> means failure (such as parameter or memory error).
     */
    FX_BOOL SetSize(int nNewSize, int nGrowBy = -1)
  {
    return CFX_BasicArray::SetSize(nNewSize, nGrowBy);
  }

    /**
     * @brief Clean up the array.
     *
     * @return None.
     */
     void RemoveAll() { SetSize(0, -1); }

    /**
     * @brief This method retrieves an element specified by an index number.
     *
     * @param[in] nIndex  Specifies the zero-based index of the element.
     *
     * @return An element.
     */
     const TYPE  GetAt(int nIndex) const {
        if (nIndex < 0 || nIndex >= m_nSize)
        //return (const TYPE&)(*(volatile const TYPE*)NULL);
        //In order to avoid crash, we input the index.(For reasons unknown)
          FX_Error(indexOutOfRange, nIndex);
        return ((const TYPE*)m_pData)[nIndex];
     }

    /**
     * @brief This method overwrites an element specified by an index number.
     *
     * @param[in] nIndex      Specifies the zero-based index of the element.
     * @param[in] newElement  An element.
     *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL    SetAt(int nIndex, TYPE newElement) {
    if (nIndex < 0 || nIndex >= m_nSize) return false;
    ((TYPE*)m_pData)[nIndex] = newElement;
    return true;
  }

  /**
   * @brief This method retrieves a ref to an element specified by an index number.
   *
   * @param[in] nIndex  Specifies the zero-based index of the element.
   *
   * @return A reference to the specified element.
   */
  TYPE&    ElementAt(int nIndex)
  {
    if (nIndex < 0 || nIndex >= m_nSize)
      //return *(TYPE*)NULL;
      //In order to avoid crash, we input the index.(For reasons unknown)
      FX_Error(indexOutOfRange, nIndex);
    return ((TYPE*)m_pData)[nIndex];
  }

  /**
   * @brief Direct Access to the element data (may return <b>NULL</b>).
   *
   * @return A constant element type pointer.
   */
  const TYPE*  GetData() const { return (const TYPE*)m_pData; }

  /**
   * @brief Direct Access to the element data (may return <b>NULL</b>).
   *
   * @return An element type pointer.
   */
  TYPE*    GetData() { return (TYPE*)m_pData; }

  /**
   * @brief Set an element value at specified position. Potentially growing the array.
   *
   * @param[in] nIndex      Specifies the zero-based index of element in the array.
   * @param[in] newElement  The input element.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL    SetAtGrow(int nIndex, TYPE newElement)
  {
    if (nIndex < 0) return false;
    if (nIndex >= m_nSize)
      if (!SetSize(nIndex+1, -1)) return false;
    ((TYPE*)m_pData)[nIndex] = newElement;
    return true;
  }

  /**
   * @brief Add an element at the tail. Potentially growing the array.
   *
   * @param[in] newElement  The input element.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure (such as memory error).
   */
  FX_BOOL    Add(TYPE newElement)
  {
    if (m_nSize < m_nMaxSize)
      m_nSize ++;
    else
      if (!SetSize(m_nSize+1, -1)) return false;
    ((TYPE*)m_pData)[m_nSize-1] = newElement;
    return true;
  }
    
  /**
   * @brief Append an array.
   *
   * @param[in] src  The input array.
   *
   * @return <b>TRUE</b> means success, while <b>FALSE</b> means failure (such as memory error).
   */
  FX_BOOL    Append(const CFX_ArrayTemplate& src) { return CFX_BasicArray::Append(src); }

  /**
   * @brief Copy from an array.
   *
   * @param[in] src  The input array.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure (such as memory error).
   */
  FX_BOOL    Copy(const CFX_ArrayTemplate& src) { return CFX_BasicArray::Copy(src); }

  /**
   * @brief Get a pointer to the specified element in the array. Direct pointer access.
   *
   * @param[in] index  Specifies the zero-based index of element in the array.
   *
   * @return A pointer to the specified element.
   */
  TYPE*    GetDataPtr(int index) { return (TYPE*)CFX_BasicArray::GetDataPtr(index); }

  /**
   * @brief Add an element's space.
   *
   * @return A pointer to the added space for the new element.
   */
  TYPE*    AddSpace() { return (TYPE*)CFX_BasicArray::InsertSpaceAt(m_nSize, 1); }

  /**
   * @brief Insert a number of elements.
   *
   * @param[in] nIndex  Specifies the zero-based index of start element in the array.
   * @param[in] nCount  Specifies the count of elements to insert.
   * 
   * @return A pointer to the inserted space for the new element.
   */
  TYPE*    InsertSpaceAt(int nIndex, int nCount) { return (TYPE*)CFX_BasicArray::InsertSpaceAt(nIndex, nCount); }
    
  /**
   * @brief Assignment operator overload.
   *
   * @param[in] src  The input array.
   *
   * @return A reference to current array object.
   */
  CFX_ArrayTemplate& operator=(const CFX_ArrayTemplate& src) { CFX_BasicArray::operator=(src); return *this; }

  /**
   * @brief Subscript([]) operator overload. It retrieves a element specified by the zero-based index in nIndex.
   *
   * @param[in] nIndex  Specifies the zero-based index in the array.
   *
   * @return An element value.
   */
  const TYPE  operator[](int nIndex) const
  {
    if (nIndex < 0 || nIndex >= m_nSize)
      //Merge from google trunk r2049, author: Johnson, date:2012.12.07
      *(volatile char*)0 = '\0';
    return ((const TYPE*)m_pData)[nIndex];
  }

  /**
   * @brief Subscript([]) operator overload. This function returns a reference to the specified element specified
   *        by the zero-based index in nIndex.
   *
   * @param[in] nIndex  Specifies the zero-based index in the array.
   *
   * @return A reference to the specified element.
   */
  TYPE&    operator[](int nIndex)
  {
    if (nIndex < 0 || nIndex >= m_nSize)
      //Merge from google trunk r2049, author: Johnson, date:2012.12.07
      *(volatile char*)0 = '\0';
    return ((TYPE*)m_pData)[nIndex];
  }

  /**
   * @brief Inset one or more continuous element at specified position.
   *
   * @param[in] nIndex      Specifies the zero-based index in the array.
   * @param[in] newElement  Specifies the element value to insert.
   * @param[in] nCount      Specifies the count of the element to insert.
   *
   * @return <b>TRUE</b> means success, while <b>FALSE</b> means failure (such as parameter or memory error).
   */
  FX_BOOL    InsertAt(int nIndex, TYPE newElement, int nCount = 1)
  {
    if (!InsertSpaceAt(nIndex, nCount)) return false;
    while (nCount--)
      ((TYPE*)m_pData)[nIndex++] = newElement;
    return true;
  }

  /**
   * @brief Remove a number of elements at specified position.
   *
   * @param[in] nIndex  Specifies the zero-based index in the array.
   * @param[in] nCount  Specifies the count of element to remove.
   *
   * @return <b>TRUE</b> means success, while <b>FALSE</b> means failure (such as parameter or memory error).
   */
  FX_BOOL    RemoveAt(int nIndex, int nCount = 1) { return CFX_BasicArray::RemoveAt(nIndex, nCount); }
  
  /**
   * @brief Inset an array at specified position.
   *
   * @param[in] nStartIndex  Specifies the zero-based index of start element to insert at.
   * @param[in] pNewArray    The input array.
   *
   * @return <b>TRUE</b> means success, while <b>FALSE</b> means failure (such as parameter or memory error).
   */
  FX_BOOL    InsertAt(int nStartIndex, const CFX_BasicArray* pNewArray) { return CFX_BasicArray::InsertAt(nStartIndex, pNewArray); }
  /**
   * @brief Find an element from specified position to last.
   *
   * @param[in] data    The input element.
   * @param[in] iStart  Specifies the zero-based index of start element to find.
   *
   * @return An index of the found element. -1 means found none.
   */
  int      Find(const TYPE& data, int iStart = 0) const
  {
    if (iStart < 0) return -1;
    for (; iStart < (int)m_nSize; iStart ++)
      if (((TYPE*)m_pData)[iStart] == data) return iStart;
    return -1;
  }
};

/** @brief Type definition for a byte array type */
typedef CFX_ArrayTemplate<FX_BYTE>    CFX_ByteArray;
/** @brief Type definition for a word array type. */
typedef CFX_ArrayTemplate<FX_WORD>    CFX_WordArray;
/** @brief Type definition for a double-word array type. */
typedef CFX_ArrayTemplate<FX_DWORD>    CFX_DWordArray;
/** @brief Type definition for: a typeless pointer array type. */
typedef CFX_ArrayTemplate<void*>    CFX_PtrArray;
/** @brief Type definition for file size array type. */
typedef CFX_ArrayTemplate<FX_FILESIZE>  CFX_FileSizeArray;
/** @brief Type definition for float array. */
typedef CFX_ArrayTemplate<FX_FLOAT>    CFX_FloatArray;
/** @brief Type definition for INT32 array. */
typedef CFX_ArrayTemplate<FX_INT32>    CFX_Int32Array;
/** @brief Type definition for FX_WHAR array. */
typedef CFX_ArrayTemplate<FX_WCHAR>    CFX_WCHARArray;

/**
 * The class represents Object array template.
 * Each object in the array is "owned" by the array, so when this array is destructed,
 * or an object is removed from the array, the object(s) will be destructed.
 *
 * The template parameter \<class T\> must support "placement new".
 * (any class derived from CFX_Object supports placement new).
 */
template <class ObjectClass>
class CFX_ObjectArray : public CFX_BasicArray
{
 public:
  /**
   * @brief The constructor.
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_ObjectArray(IFX_Allocator* pAllocator = NULL) : CFX_BasicArray(sizeof(ObjectClass), pAllocator) {}

  /**
   * @brief The destructor.
   */
  ~CFX_ObjectArray() { RemoveAll(); }

  /**
   * @brief The copy constructor.
   *
   * @param[in] other       The other object array.
   * @param[in] pAllocator  An allocator.  Default value: <b>NULL</b>.
   */
  CFX_ObjectArray(const CFX_ObjectArray& other, IFX_Allocator* pAllocator = NULL)
    : CFX_BasicArray(sizeof(ObjectClass), pAllocator)
  {
    Copy(other);
  }

  /**
   * @brief The assignment operator.
   * 
   * @param[in] other  The other object array.
   *
   * @return A reference to current object itself.
   */
  CFX_ObjectArray& operator=(const CFX_ObjectArray& other)
  {
    Copy(other);
    return *this;
  }

  /**
   * @brief Add a copy of an existing object to the array.
   *
   * @details To call this function, the template parameter class must support copy constructor.
   *
   * @param[in] data  The input object.
   *
   * @return None.
   */
  void      Add(const ObjectClass& data)
  {
      #ifndef _FX_NOPLACEMENTNEW_
        new ((void*)InsertSpaceAt(m_nSize, 1)) ObjectClass(data);
      #else
        ::new ((void*)InsertSpaceAt(m_nSize, 1)) ObjectClass(data);
      #endif

  }

  /**
   * @brief Add an empty object to the array.
   * 
   * @details To call this function, the template parameter class must support default constructor.
   *
   * @return A reference to the newly added object.
   */
  ObjectClass&  Add()
  {
      #ifndef _FX_NOPLACEMENTNEW_
        return *(ObjectClass*) new ((void*)InsertSpaceAt(m_nSize, 1)) ObjectClass();
      #else
        return *(ObjectClass*) ::new ((void*)InsertSpaceAt(m_nSize, 1)) ObjectClass();
      #endif
  }

  /**
   * @brief Add an empty space to the array.
   * 
   * @details Caller should initialize object at once to make sure object is available.
   *
   * @return Pointer to allocated space.
   */
  void*      AddSpace()
  {
    return InsertSpaceAt(m_nSize, 1);
  }

  /**
   * @brief Append an array.
   *
   * @param[in] src     The source array.
   * @param[in] nStart  The starting position to be appended in source array. Default value: 0.
   * @param[in] nCount  The total count of source elements to be appended. -1 means all elements from nStart position.
   *                    Default value: -1.
   *
   * @return The number of appended elements from source array.
   */
  FX_INT32    Append(const CFX_ObjectArray& src, FX_INT32 nStart = 0, FX_INT32 nCount = -1)
  {
    if (nCount == 0) return 0;
    FX_INT32 nSize = src.GetSize();
    if (!nSize) return 0;
    FXSYS_assert(nStart > -1 && nStart < nSize);
    if (nCount < 0) nCount = nSize;
    if (nStart + nCount > nSize) nCount = nSize - nStart;
    if (nCount < 1) return 0;
    nSize = m_nSize;
    InsertSpaceAt(m_nSize, nCount);
    ObjectClass* pStartObj = (ObjectClass*)GetDataPtr(nSize);
    nSize = nStart + nCount;
    for (FX_INT32 i = nStart; i < nSize; i ++, pStartObj++)
    {
      #ifndef _FX_NOPLACEMENTNEW_
        new ((void*)pStartObj) ObjectClass(src[i]);
      #else
        ::new ((void*)pStartObj) ObjectClass(src[i]);
      #endif

    }
    return nCount;
  }

  /**
   * @brief Copy from an array.
   *
   * @param[in] src     The source array.
   * @param[in] nStart  The starting position to be copied in source array. Default value: 0
   * @param[in] nCount  The total count of source elements to be copied, -1 means all elements from nStart position.
   *                    Default value: -1.
   *
   * @return The number of copied elements from source array.
   */
  FX_INT32    Copy(const CFX_ObjectArray& src, FX_INT32 nStart = 0, FX_INT32 nCount = -1)
  {
    if (this == &src) return 0;
    RemoveAll();
    if (nCount == 0) return 0;
    FX_INT32 nSize = src.GetSize();
    if (!nSize) return 0;
    FXSYS_assert(nStart > -1 && nStart < nSize);
    if (nCount < 0) nCount = nSize;
    if (nStart + nCount > nSize) nCount = nSize - nStart;
    if (nCount < 1) return 0;
    nSize = nStart + nCount;
    SetSize(nCount, -1);
    ObjectClass* pStartObj = (ObjectClass*)m_pData;
    for (FX_INT32 i = nStart; i < nSize; i ++, pStartObj++)
    {
      #ifndef _FX_NOPLACEMENTNEW_
        new ((void*)pStartObj) ObjectClass(src[i]);
      #else
        ::new ((void*)pStartObj) ObjectClass(src[i]);
      #endif

    }
    return nCount;
  }

  /**
   * @brief Get the size of the array.
   *
   * @return The size in objects in the array.
   */
  int        GetSize() const {return m_nSize;}

  /**
   * @brief Subscript([]) operator overload. This function returns a reference to the specified object specified
   *        by the zero-based index in nIndex.
   *
   * @param[in] index  Specifies the zero-based index in the array.
   *
   * @return A reference to the specified object.
   */
  ObjectClass&  operator[] (int index) const
  {
    FXSYS_assert(index < m_nSize);
    return *(ObjectClass*)CFX_BasicArray::GetDataPtr(index);
  }

  /**
   * @brief Get a pointer to the specified element in the array. Direct pointer access.
   *
   * @param[in] index  Specifies the zero-based index of element in the array.
   *
   * @return A pointer to the specified element.
   */
  ObjectClass*  GetDataPtr(int index) const {return (ObjectClass*)CFX_BasicArray::GetDataPtr(index);}

  /**
   * @brief Remove an object at specified position.
   *
   * @param[in] index  Specifies the zero-based index of object in the array.
   *
   * @return None.
   */
  void      RemoveAt(int index)
  {
    FXSYS_assert(index < m_nSize);
    ((ObjectClass*)GetDataPtr(index))->~ObjectClass();
    CFX_BasicArray::RemoveAt(index, 1);
  }

  /**
   * @brief Remove all objects in the array.
   *
   * @return None.
   */
  void      RemoveAll()
  {
    for (int i = 0; i < m_nSize; i ++)
      ((ObjectClass*)GetDataPtr(i))->~ObjectClass();
    CFX_BasicArray::SetSize(0, -1);
  }
};

/** @brief Type definition for a CFX_ByteString array type. */
typedef CFX_ObjectArray<CFX_ByteString> CFX_ByteStringArray;
/** @brief Type definition for a CFX_WideString array type. */
typedef CFX_ObjectArray<CFX_WideString> CFX_WideStringArray;

/**
 * The class represents stack template.
 */
template <class TYPE>
class CFX_Stack : CFX_Object
{
 public:
  /** @brief Construct. */
  CFX_Stack() {}

  /**
   * @brief Empty the container.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL      Empty() const
  {
    return m_Container.GetSize() == 0;
  }

  /**
   * @brief Get size of the container.
   *
   * @return The size of the container.
   */
  int        Size() const
  {
    return m_Container.GetSize();
  }

  /**
   * @brief Get the top byte data.
   *
   * @return The top byte data.
   */
  TYPE&      Top()
  {
    return m_Container[Size() - 1];
  }

  /**
   * @brief Pop the data from stack.
   *
   * @return None.
   */
  void      Pop()
  {
    m_Container.RemoveAt(Size() - 1);
  }

  /**
   * @brief Push the data to stack.
   *
   * @param[in] val  An element to be pushed to the stack.
   *
   * @return None.
   */
  void      Push(const TYPE& val)
  {
    m_Container.Add(val);
  }

  /**
   * @brief Remove all remaining data from stack.
   *
   *  @return None.
   */
  void	Clear()
  {
    m_Container.RemoveAll();
  }
 private:
  CFX_ArrayTemplate<TYPE>    m_Container;
};

/**
 * The class represents objects stack template.
 */
template <class TYPE>
class CFX_ObjectStack : CFX_Object
{
 public:
  /** @brief Construct. */
  CFX_ObjectStack() {}

  /**
   * @brief Empty the container.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL      Empty() const
  {
    return m_Container.GetSize() == 0;
  }

  /**
   * @brief Get size of the container.
   *
   * @return The size of the container.
   */
  int        Size() const
  {
    return m_Container.GetSize();
  }

  /**
   * @brief Get the top byte string.
   *
   * @return The top byte string.
   */
  TYPE&      Top()
  {
    return m_Container[Size() - 1];
  }

  /**
   * @brief Pop the byte string from stack.
   *
   * @return None.
   */
  void      Pop()
  {
    m_Container.RemoveAt(Size() - 1);
  }

  /**
   * @brief Push the byte string to stack.
   *
   * @param[in] val  A byte string to be pushed to the stack.
   *
   * @return None.
   */
  void      Push(const TYPE& val)
  {
    m_Container.Add(val);
  }

 private:
  CFX_ObjectArray<TYPE>    m_Container;
};

/**
 * The class represents CFX_ByteString stack template.
 */
template <>
class CFX_Stack<CFX_ByteString> : CFX_Object
{
 public:
  /** @brief Construct. */
  CFX_Stack() {}

  /**
   * @brief Empty the container.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL      Empty() const
  {
    return m_Container.GetSize() == 0;
  }

  /**
   * @brief Get size of the container.
   *
   * @return The size of the container.
   */
  int        Size() const
  {
    return m_Container.GetSize();
  }

  /**
   * @brief Get the top byte string.
   *
   * @return The top byte string.
   */
  CFX_ByteString&      Top()
  {
    return m_Container[Size() - 1];
  }

  /**
   * @brief Pop the byte string from stack.
   *
   * @return None.
   */
  void      Pop()
  {
    m_Container.RemoveAt(Size() - 1);
  }

  /**
   * @brief Push the byte string to stack.
   *
   * @param[in] val  A byte string to be pushed to the stack.
   *
   * @return None.
   */
  void Push(const CFX_ByteString& val)
  {
    m_Container.Add(val);
  }

 private:
  CFX_ObjectArray<CFX_ByteString>    m_Container;
};

/**
 * The class represents grow-able array with allocation in segments.
 */
class CFX_BaseSegmentedArray : public CFX_Object
{
 public:
  /**
   * @brief Construct with specified unit size, segment units, and number of index levels.
   *
   * @param[in] unit_size      The specified unit size.
   * @param[in] segment_units  The count of units in each segment, must be less than 32768.
   * @param[in] index_size     The number of segments(index levels) in the array, it must be larger than 1 and less than 256.
   * @param[in] pAllocator     Allocator used in this class. NULL to use default allocator.
   */
  CFX_BaseSegmentedArray(int unit_size = 1, int segment_units = 512, int index_size = 8, IFX_Allocator* pAllocator = NULL);

  /**
   * @brief The destructor.
   */
  ~CFX_BaseSegmentedArray();

  /**
   * @brief Change the unit size and the segment units. This can only be called when array is empty.
   *
   * @param[in] unit_size      The new unit size.
   * @param[in] segment_units  The new count of units in each segment.
   * @param[in] index_size     The new number of index levels.
   *
   * @return None.
   */
  void  SetUnitSize(int unit_size, int segment_units, int index_size = 8);

  /**
   * @brief Add an element.
   *
   * @return The typeless pointer to the added element.
   */
  void*  Add();

  /**
   * @brief Get a typeless pointer to an element data.
   *
   * @param[in] index  Specifies the zero-based index of element.
   *
   * @return A typeless pointer to the element data.
   */
  void*  GetAt(int index) const;

  /**
   * @brief Remove all elements in the array.
   *
   * @return None.
   */
  void  RemoveAll();

  /**
   * @brief Delete a number of elements.
   *
   * @param[in] index  Specifies the zero-based index of start element in the array to be deleted.
   * @param[in] count  Specifies the count of element to delete.
   *
   * @return None.
   */
  void  Delete(int index, int count = 1);

  /**
   * @brief Get number of elements in the array.
   *
   * @return The number of elements in the array.
   */
  int    GetSize() const { return m_DataSize; }

  /**
   * @brief Get number of elements in each segment.
   *
   * @return The number of elements in each segment.
   */
  int    GetSegmentSize() const { return m_SegmentSize; }

  /**
   * @brief Get number of bytes for each element.
   *
   * @return The number of bytes for each element.
   */
  int    GetUnitSize() const { return m_UnitSize; }

  /**
   * @brief Iterate all units, with a callback function for each unit.
   *
   * @param[in] callback  
   * @param[in] param     
   *
   * @return The current unit when stopped, or NULL when all units iterated.
   */
  void*  Iterate(FX_BOOL (*callback)(void* param, void* pData), void* param) const;

  /** @brief Special allocator pointer. <b>NULL</b> means to use default allocator. */
  IFX_Allocator*  m_pAllocator;
 private:
  /* Unit size */
  int        m_UnitSize;
  /* Count of units in each segment. */
  short      m_SegmentSize;
  /* Number of index level in the array. */
  FX_BYTE      m_IndexSize;
  /* The current level in the index tree. */
  FX_BYTE      m_IndexDepth;
  /* The current number of units in the array. */
  int        m_DataSize;
  /* index to segments or indices, or directly pointing to the segment if only one segment. */
  void*      m_pIndex;

  void**  GetIndex(int seg_index) const;
  void*  IterateIndex(int level, int& start, void** pIndex, FX_BOOL (*callback)(void* param, void* pData), void* param) const;
  void*  IterateSegment(FX_LPCBYTE pSegment, int count, FX_BOOL (*callback)(void* param, void* pData), void* param) const;
};

/**
 * The class represents grow-able array template with allocation in segments.
 */
template <class ElementType>
class CFX_SegmentedArray : public CFX_BaseSegmentedArray
{
 public:
  /**
    * @brief Construct with specified segment units.
    *
    * @param[in] segment_units  The count of units in each segment.
    * @param[in] index_size     The number of segments in the array. Default value: 8.
    * @param[in] pAllocator     An allocator. Default value: <b>NULL</b>.
    */
  CFX_SegmentedArray(int segment_units, int index_size = 8, IFX_Allocator* pAllocator = NULL)
    : CFX_BaseSegmentedArray(sizeof(ElementType), segment_units, index_size, pAllocator)
  {}
  //<<<+++OPENSOURCE_END

  /**
   * @brief Add an element.
   *
   * @param[in] data  The input element.
   *
   * @return None.
   */
  void  Add(ElementType data)
  {
    *(ElementType*)CFX_BaseSegmentedArray::Add() = data;
  }

  /**
   * @brief Subscript([]) operator overload. This function returns a ref to the specified element specified by the zero-based index.
   *
   * @param[in] index  Specifies the zero-based index in the array.
   *
   * @return A reference to the specified element.
   */
  ElementType& operator [] (int index)
  {
    return *(ElementType*)CFX_BaseSegmentedArray::GetAt(index);
  }
};

/**
  * The class represents fixed buffer but can be bigger if needed.
  */
template <class DataType, int FixedSize>
class CFX_FixedBufGrow : public CFX_Object
{
 public:
  /**
   * @brief Construct with allocator.
   *
   * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> means to use default allocator.
   *                        Default value: <b>NULL</b>.
   */
  CFX_FixedBufGrow(IFX_Allocator* pAllocator = NULL)
    : m_pAllocator(pAllocator)
    , m_pData(NULL)
  {
    FXSYS_memset32(m_Data, 0, sizeof(DataType)*FixedSize);
  }

  /**
   * @brief Construct with allocator.
   *
   * @param[in] data_size   The data size.
   * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> means to use default allocator.
   *                        Default value: <b>NULL</b>.
   */
  CFX_FixedBufGrow(int data_size, IFX_Allocator* pAllocator = NULL)
    : m_pAllocator(pAllocator)
    , m_pData(NULL)
  {
    if (data_size > FixedSize)
      m_pData = FX_Allocator_Alloc(m_pAllocator, DataType, data_size);
    else
      FXSYS_memset32(m_Data, 0, sizeof(DataType)*FixedSize);
  }
  //<<<+++OPENSOURCE_END

  /**
   * @brief Construct with allocator.
   *
   * @param[in] data_size  The data size.
   *
   * @return None.
   */
  void SetDataSize(int data_size) {
    if (m_pData)
      FX_Allocator_Free(m_pAllocator, m_pData);
    m_pData = NULL;
    if (data_size > FixedSize)
      m_pData = FX_Allocator_Alloc(m_pAllocator, DataType, data_size);
    else {
      FXSYS_memset32(m_Data, 0, sizeof(DataType)*FixedSize);
    }
  }

  /**
   * @brief The Destructor.
   */
  ~CFX_FixedBufGrow() { if (m_pData) FX_Allocator_Free(m_pAllocator, m_pData); }

  operator DataType*() { return m_pData ? m_pData : m_Data; }

 private:
  IFX_Allocator*  m_pAllocator;

  DataType    m_Data[FixedSize];
  DataType*    m_pData;
};

/**
 * The class represents a temporarily allocated buffer.
 */
template <class DataType>
class CFX_TempBuf
{
 public:
  /**
   * @brief Construct with allocator.
   *
   * @param[in] size        The temporarily buffer size. This parameter must be > 0.
   * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> means to use default allocator.
   *                        Default value: <b>NULL</b>.
   */
  CFX_TempBuf(int size, IFX_Allocator* pAllocator = NULL) : m_pAllocator(pAllocator)
  {
    m_pData = FX_Allocator_Alloc(m_pAllocator, DataType, size);
  }

  /**
   * @brief The Destructor.
   */
  ~CFX_TempBuf()
   {
      if (m_pData) FX_Allocator_Free(m_pAllocator, m_pData);
   }
  //<<<+++OPENSOURCE_END

  DataType&  operator[](int i) { FXSYS_assert(m_pData != NULL); return m_pData[i]; }
  operator DataType*() const { return m_pData; }

 private:
  IFX_Allocator*  m_pAllocator;

  DataType*    m_pData;
};

//*****************************************************************************
//* Map
//*****************************************************************************

/**
 * The class represents POINTER/DWORD TO POINTER/DWORD MAP.
 */
class CFX_MapPtrToPtr : public CFX_Object
{
 protected:
  /**
   * @brief Association in CFX_MapPtrToPtr.
   */
  struct CAssoc
  {
    /** @brief Pointer to next association. */
    CAssoc* pNext;
    /** @brief Key data. */
    void* key;
    /** @brief Value data. */
    void* value;
  };

 public:
  /**
   * @brief Construct with specified block size.
   *
   * @param[in] nBlockSize  The internal block. This parameter must be > 0.
   * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> means to use default allocator.
   *                        Default value: <b>NULL</b>.
   */
  CFX_MapPtrToPtr(int nBlockSize = 10, IFX_Allocator* pAllocator = NULL);
  //<<<+++OPENSOURCE_END

  /**
   * @brief The Destructor.
   */
  ~CFX_MapPtrToPtr();

  /**
   * @brief Get the number of elements.
   *
   * @return The number of elements in the map.
   */
  int GetCount() const { return m_nCount; }

  /**
   * @brief Verify whether the map is empty.
   *
   * @return <b>true</b> means current map is empty, while <b>false</b> means current map is not empty.
   */
  FX_BOOL IsEmpty() const { return m_nCount == 0; }

  /**
   * @brief Lookup by a key.
   *
   * @param[in]  key     The key to lookup.
   * @param[out] rValue  A reference of a typeless pointer to receive the found value.
   *
   * @return <b>true</b> means the key is found, while <b>false</b> means the key is not found.
   */
  FX_BOOL Lookup(void* key, void*& rValue) const;

  /**
   * @brief Get a value pointer by a key.
   *
   * @param[in] key  The key, whose mapping value is to be retrieved.
   *
   * @return A value. <b>NULL</b> means the key is not found.
   */
  void* GetValueAt(void* key) const;

  /**
   * @brief Subscript([]) operator overload. Lookup and add if not there.
   *
   * @param[in] key  The key to lookup.
   *
   * @return A reference to the found value.
   */
  void*& operator[](void* key);

  /**
   * @brief Add a new (key, value) pair. Add if not exist, otherwise modify.
   *
   * @param[in] key       The key to specify a position.
   * @param[in] newValue  The new value.
   *
   * @return None.
   */
  void SetAt(void* key, void* newValue) { (*this)[key] = newValue; }

  /**
   * @brief Removing existing (key, ?) pair.
   *
   * @param[in] key The key to be removed.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL RemoveKey(void* key);

  /**
   * @brief Remove all the (key, value) pairs in the map.
   *
   * @return None.
   */
  void RemoveAll();

  /**
   * @brief Get the first key-value pair position. iterating all (key, value) pairs.
   *
   * @return The first key-value pair position in the map.
   */
  FX_POSITION GetStartPosition() const { return (m_nCount == 0) ? NULL : (FX_POSITION)-1; }

  /**
   * @brief Get the current association and set the position to next association.
   *
   * @details Never call this function on an empty map.
   *
   * @param[in, out] rNextPosition  Input a position, and receive the next association position as result.
   *                                This parameter will be <b>NULL</b> when reaching the end of the map.
   * @param[out] rKey               Receive a key.
   * @param[out] rValue             Receive a value.
   *
   * @return None.
   */
  void GetNextAssoc(FX_POSITION& rNextPosition, void*& rKey, void*& rValue) const;

  /**
   * @brief Get the internal hash table size. Advanced features for derived classes.
   *
   * @return The hash table size.
   */
  FX_DWORD GetHashTableSize() const { return m_nHashTableSize; }

  /**
   * @brief Initialize the hash table.
   *
   * @param[in] hashSize   Initialize the hash table size.
   * @param[in] bAllocNow  A boolean value to decide whether to allocate the hash table now.
   *                       <b>true</b> means to allocate the hash table now, while <b>false</b> means not.
   *
   * @return None.
   */
  void InitHashTable(FX_DWORD hashSize, FX_BOOL bAllocNow = true);

 protected:
  /* Special allocator pointer. NULL to use default allocator. */
  IFX_Allocator*  m_pAllocator;

  /* The hash table. */
  CAssoc** m_pHashTable;
  /* The size of hash table. */
  FX_DWORD m_nHashTableSize;
  /* The number of key-value pair in the map. */
  int m_nCount;
  /* The freed association list internal. */
  CAssoc* m_pFreeList;
  /* The block list internal. */
  struct CFX_Plex* m_pBlocks;
  /* The size in associations of each block. */
  int m_nBlockSize;

  /*
   * Routine used to user-provided hash keys.
   *
   * @note Overwrite-able: special non-virtual (see map implementation for details).
   *
   * @param[in] key    The key used to produce hash key.
   * @return A hash value.
   */
  FX_DWORD HashKey(void* key) const;

  /*
   * Allocate a new association.
   *
   * @return The pointer to the new allocated association.
   */
  CAssoc* NewAssoc();
  /*
   * Free an association.
   *
   * @param[in] pAssoc  A pointer to an association.
   */
  void FreeAssoc(CAssoc* pAssoc);
  /*
   * @brief Retrieve an association by a key.
   *
   * @param[in] key    The input key.
   * @param[out] hash  The hash value computed.
   *
   * @return Current association object.
   */
  CAssoc* GetAssocAt(void* key, FX_DWORD& hash) const;
  /*
   * @brief Retrieve current association by position.
   *
   * @param[in, out] rNextPosition  Input a position, and receive the next association position.
   *
   * @return Current association object.
   */
  CAssoc* GetCurrentAssoc(FX_POSITION& rNextPosition) const;
  /*
   * @brief Expand 2 times HashTable Size than before.
   *
   * @details The MaxHashTableSize is 10000.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL ExpandHashTable();
 private:
	CFX_MapPtrToPtr(const CFX_MapPtrToPtr &) FX_EQDELETE;
	CFX_MapPtrToPtr &operator=(const CFX_MapPtrToPtr &) FX_EQDELETE;
};

/**
 * The class represents POINTER/DWORD TO POINTER/DWORD MAP template.
 */
template <class KeyType, class ValueType>
class CFX_MapPtrTemplate : public CFX_MapPtrToPtr
{
 public:
  /**
   * @brief Default constructor. 
   *
   * @param[in] pAllocator  An allocator. Defautl value: <b>NULL</b>.
   */
  CFX_MapPtrTemplate(IFX_Allocator* pAllocator = NULL) : CFX_MapPtrToPtr(10, pAllocator) {}

  /**
   * @brief Lookup by a key.
   *
   * @param[in] key      The key to lookup.
   * @param[out] rValue  A reference of a value to receive the found value.
   *
   * @return <b>true</b> means the key is found, while <b>false</b> means the key is not found.
   */
  FX_BOOL  Lookup(KeyType key, ValueType& rValue) const
  {
    FX_LPVOID pValue = NULL;
    if (!CFX_MapPtrToPtr::Lookup((void*)(FX_UINTPTR)key, pValue))
      return false;
    rValue = (ValueType)(FX_UINTPTR)pValue;
    return true;
  }

  /**
   * @brief Subscript([]) operator overload. Lookup and add if not there.
   *
   * @param[in] key  The key to lookup.
   *
   * @return A reference to the found value.
   */
  ValueType& operator[](KeyType key) { return (ValueType&)CFX_MapPtrToPtr::operator []((void*)(FX_UINTPTR)key); }

  /**
   * @brief Add a new (key, value) pair. Add if not exist, otherwise modify.
   *
   * @param[in] key       The key to specify a position.
   * @param[in] newValue  The new value.
   *
   * @return None.
   */
  void SetAt(KeyType key, ValueType newValue) { CFX_MapPtrToPtr::SetAt((void*)(FX_UINTPTR)key, (void*)(FX_UINTPTR)newValue); }

  /**
   * @brief Remove existing (key, ?) pair.
   *
   * @param[in] key  The key to be removed.
   *
   * @return <b>true</b> means the removing is successfully, while <b>false</b> means the key does not exist.
   */
  FX_BOOL  RemoveKey(KeyType key) { return CFX_MapPtrToPtr::RemoveKey((void*)(FX_UINTPTR)key); }

  /**
   * @brief Get the current association and set the position to next association.
   *
   * @param[in, out] rNextPosition  Input a position, and receive the next association position as result.
   * @param[out]     rKey           Receive a key.
   * @param[out]     rValue         Receive a value.
   *
   * @return None.
   */
  void GetNextAssoc(FX_POSITION& rNextPosition, KeyType& rKey, ValueType& rValue) const
  {
    void* pKey = NULL; void* pValue = NULL;
    CFX_MapPtrToPtr::GetNextAssoc(rNextPosition, pKey, pValue);
    rKey = (KeyType)(FX_UINTPTR)pKey; rValue = (ValueType)(FX_UINTPTR)pValue;
  }
 private:
	CFX_MapPtrTemplate(const CFX_MapPtrTemplate &) FX_EQDELETE;
	CFX_MapPtrTemplate &operator=(const CFX_MapPtrTemplate &) FX_EQDELETE;
};

/**
 * The class represents a compact map class that simply put all mapping into one single buffer
 * The map is kept sorted so lookup can be pretty fast.
 */
class CFX_CMapDWordToDWord : public CFX_Object
{
 public:
  /** 
   * @brief Constructor with allocator. 
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_CMapDWordToDWord(IFX_Allocator* pAllocator = NULL) : m_Buffer(pAllocator) {}

  /**
   * @brief Lookup by a key.
   *
   * @param[in] key     The key to lookup.
   * @param[out] value  A reference of a FX_DWORD value to receive the found value.
   *
   * @return <b>true</b> means the key is found, while <b>false</b> means the key is not found.
   */
  FX_BOOL      Lookup(FX_DWORD key, FX_DWORD& value) const;

  /**
   * @brief Add a new (key, value) pair. Add if not exist, otherwise modify.
   *
   * @param[in] key    The key to specify a position.
   * @param[in] value  The new FX_DWORD value.
   *
   * @return None.
   */
  void      SetAt(FX_DWORD key, FX_DWORD value);

  /**
   * @brief Change internal allocation size and grow amount.
   *
   * @param[in] size     The new allocation size.
   * @param[in] grow_by  The new grow amount.
   *
   * @return None.
   */
  void      EstimateSize(FX_DWORD size, FX_DWORD grow_by);

  /**
   * @brief Get the first key-value pair position. iterating all (key, value) pairs.
   *
   * @return The first key-value pair position in the map.
   */
  FX_POSITION    GetStartPosition() const;

  /**
   * @brief Get the next association.
   *
   * @param[in, out] pos  Input a position, and receive the next (key, value) pair position as result.
   * @param[out] key      Receive a key.
   * @param[out] value    Receive a value.
   *
   * @return None.
   */
  void      GetNextAssoc(FX_POSITION& pos, FX_DWORD& key, FX_DWORD& value) const;

  /**
   * @brief Remove all (key, value) pair.
   *
   * @return None.
   */
  void      RemoveAll() { m_Buffer.Clear(); }

 protected:
  /** (key, value) pair buffer. */
  CFX_BinaryBuf  m_Buffer;
 private:
  CFX_CMapDWordToDWord(const CFX_CMapDWordToDWord &) FX_EQDELETE;
  CFX_CMapDWordToDWord &operator=(const CFX_CMapDWordToDWord &) FX_EQDELETE;
};

/** The class represents BYTE STRING MAP. */
class CFX_MapByteStringToPtr : public CFX_Object
{
 protected:
  /**
   * @brief Association in CFX_MapByteStringToPtr.
   */
  struct CAssoc
  {
    /** @brief Pointer to next association. */
    CAssoc* pNext;

    /** @brief Cached hash value, needed for efficient iteration. */
    FX_DWORD nHashValue;
    /** @brief Key data. */
    CFX_ByteString key;
    /** @brief Value data. */
    void* value;
  };

 public:
  /**
    * @brief Construct with specified block size.
    *
    * @param[in] nBlockSize  The internal block. Default value: 10.
    * @param[in] pAllocator  Allocator used in this class. <b>NULL</b> means to use default allocator.
    *                        Default value: <b>NULL</b>.
    */
  CFX_MapByteStringToPtr(int nBlockSize = 10, IFX_Allocator* pAllocator = NULL);

  /**
   * @brief Get the number of elements.
   *
   * @return The number of elements in the map.
   */
  int GetCount() const { return m_nCount; }

  /**
   * @brief Verify whether the map is empty.
   *
   * @return <b>true</b> means current map is empty, while <b>false</b> means current map is not empty.
   */
  FX_BOOL IsEmpty() const { return m_nCount == 0; }

  /**
   * @brief Lookup by a key.
   *
   * @param[in] key      The key to lookup.
   * @param[out] rValue  A reference of a typeless pointer to receive the found value.
   *
   * @return <b>true</b> means the key is found, while <b>false</b> means the key is not found.
   */
  FX_BOOL Lookup(FX_BSTR key, void*& rValue) const;

  /**
   * @brief Subscript([]) operator overload. Lookup and add if not there.
   *
   * @param[in] key  The key to lookup.
   *
   * @return A reference to the found value.
   */
  void*& operator[](FX_BSTR key);

  /**
   * @brief Add a new (key, value) pair. Add if not exist, otherwise modify.
   *
   * @param[in] key       The key to specify a position.
   * @param[in] newValue  The new value.
   *
   * @return None.
   */
  void SetAt(FX_BSTR key, void* newValue) { (*this)[key] = newValue; }

  /**
   * @brief Remove existing key.
   *
   * @param[in] key  The key to be removed.
   *
   * @return <b>true</b> means removing is successfully, while <b>false</b> means the key does not exist.
   */
  FX_BOOL RemoveKey(FX_BSTR key);

  /**
   * @brief Remove all the (key, value) pairs in the map.
   *
   * @return None.
   */
  void RemoveAll();

  /**
   * @brief Get the first key-value pair position. iterating all (key, value) pairs.
   *
   * @return The first key-value pair position in the map.
   */
  FX_POSITION GetStartPosition() const { return (m_nCount == 0) ? NULL : (FX_POSITION)-1; }

  /**
   * @brief Get the current association and set the position to next association.
   *
   * @param[in, out] rNextPosition  Input a position, and receive the next association position as result.
   * @param[out]     rKey           Receive a key.
   * @param[out]     rValue         Receive a value.
   *
   * @return None.
   */
  void GetNextAssoc(FX_POSITION& rNextPosition, CFX_ByteString& rKey, void*& rValue) const;

  /**
   * @brief Get the the current value and set the position to next association.
   *
   * @param[in, out] rNextPosition  Input a position, and receive the next association position as result.
   *
   * @return Current value.
   */
  FX_LPVOID    GetNextValue(FX_POSITION& rNextPosition) const;

  /**
   * @brief Get the internal hash table size. Advanced features for derived classes.
   *
   * @return The hash table size.
   */
  FX_DWORD GetHashTableSize() const { return m_nHashTableSize; }

  /**
   * @brief Initialize the hash table.
   *
   * @param[in] hashSize   Initialize the hash table size.
   * @param[in] bAllocNow  A boolean value to decide whether to allocate the hash table now.
   *                       <b>true</b> means to allocate hash table now, while <b>false</b> means not.
   *
   * @return None.
   */
  void InitHashTable(FX_DWORD hashSize, FX_BOOL bAllocNow = true);

  /**
   * @brief Routine used to user-provided hash keys.
   *
   * @details Overwrite-able: special non-virtual (see map implementation for details).
   *
   * @param[in] key The key used to produce hash key.
   *
   * @return A hash value.
   */
  FX_DWORD HashKey(FX_BSTR key) const;

 protected:
  /* Special allocator pointer. NULL to use default allocator. */
  IFX_Allocator*  m_pAllocator;

  /* The hash table. */
  CAssoc** m_pHashTable;
  /* The size of hash table. */
  FX_DWORD m_nHashTableSize;
  /* The number of key-value pair in the map. */
  int m_nCount;
  /* The freed association list internal. */
  CAssoc* m_pFreeList;
  /* The block list internal. */
  struct CFX_Plex* m_pBlocks;
  /* The size in associations of each block. */
  int m_nBlockSize;

  /*
   * @brief Allocate a new association.
   *
   * @return The pointer to the new allocated association.
   */
  CAssoc* NewAssoc();
  /*
   * @brief Free an association.
   *
   * @param[in] pAssoc  A pointer to an association.
   *
   * @return None.
   */
  void FreeAssoc(CAssoc* pAssoc);
  /*
   * @brief Retrieve an association by a key.
   *
   * @param[in] key    The input key.
   * @param[out] hash  The hash value computed.
   *
   * @return An association object.
   */
  CAssoc* GetAssocAt(FX_BSTR key, FX_DWORD& hash) const;
  /*
   * @brief Retrieve current association by position.
   *
   * @param[in] rNextPosition  The current position.
   *
   * @return An association object.
   */
  CAssoc* GetCurrentAssoc(FX_POSITION& rNextPosition) const;
  /*
   * @brief Expand 2 times HashTable Size than before.
   *
   * @details The MaxHashTableSize is 10000.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL ExpendHashTable();

 public:
  /** @brief The destructor. */
  ~CFX_MapByteStringToPtr();
};

/**
 * A compact mapping from byte strings to pointers.<br>
 * Use this class instead of CFX_MapByteStringToPtr when:
 * <ul>
 * <li>The number of mappings is mostly limited, for example, tens of mappings;</li>
 * <li>The length of mapping keys is mostly limited, for example, often less than 8 characters.</li>
 * </ul>
 */
class CFX_CMapByteStringToPtr : public CFX_Object
{
 public:
  /**
   * @brief The constructor.
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_CMapByteStringToPtr(IFX_Allocator* pAllocator = NULL);
  //<<<+++OPENSOURCE_END

  /** @brief The destructor. */
  ~CFX_CMapByteStringToPtr();

  /**
   * @brief Remove all key-value pairs in the map.
   *
   * @return None.
   */
  void      RemoveAll();

  /**
   * @brief Get the first key-value pair position. iterating all (key, value) pairs.
   *
   * @return The first key-value pair position in the map.
   */
  FX_POSITION    GetStartPosition() const;

  /**
   * @brief Get the current association and set the position to next association.
   *
   * @param[in, out] rNextPosition  Input a position, and receive the next association position as result.
   * @param[out] rKey               Receive a key.
   * @param[out] rValue             Receive a value.
   *
   * @return None.
   */
  void      GetNextAssoc(FX_POSITION& rNextPosition, CFX_ByteString& rKey, void*& rValue) const;

  /**
   * @brief Get the the current value and set the position to next association.
   *
   * @param[in, out] rNextPosition  Input a position, and receive the next association position as result.
   *
   * @return Current value.
   */
  FX_LPVOID    GetNextValue(FX_POSITION& rNextPosition) const;

  /**
   * @brief Lookup by a key.
   *
   * @param[in] key      The key to lookup.
   * @param[out] rValue  A reference of a typeless pointer to receive the found value.
   *
   * @return <b>true</b> means the key is found, while <b>false</b> means the key is not found.
   */
  FX_BOOL      Lookup(FX_BSTR key, void*& rValue) const;

  /**
   * @brief Add a new (key, value) pair. Add if not exist, otherwise modify.
   *
   * @param[in] key    The key to specify a position.
   * @param[in] value  The new value.
   *
   * @return None.
   */
  void      SetAt(FX_BSTR key, void* value);

  /**
   * @brief Removing existing (key, ?) pair.
   *
   * @param[in] key The key to be removed.
   *
   * @return None.
   */
  void      RemoveKey(FX_BSTR key);

  /**
   * @brief Get the number of key-value pairs.
   *
   * @return The number of key-value pairs in the map.
   */
  int        GetCount() const;

  /** 
   * @brief Add a key-value pair to the dictionary, assuming there is no duplicated key existing.
   *
   * @details This is a function for quickly building up the whole dictionary, but should be used with care.
   *          If duplicate key happens, only the first value will prevail.
   *
   * @param[in] key     The key to be added.
   * @param[in] pValue  The value to be added.
   *
   * @return None.
   */
  void      AddValue(FX_BSTR key, void* pValue);

 protected:
  /* A chained buffer storing keys and values. */
  CFX_BaseSegmentedArray      m_Buffer;
};

//////////////////////////////////////////////////////////////////////
//              Lists
//////////////////////////////////////////////////////////////////////

/** The class represents pointer list. */
class CFX_PtrList : public CFX_Object
{
 protected:
  /** @brief Bidirectional node in CFX_PtrList. */
  struct CNode
  {
    /** @brief Pointer to next node. */
    CNode* pNext;
    /** @brief Pointer to previous node. */
    CNode* pPrev;
    /** @brief Node data. */
    void* data;
  };

 public:
  /**
   * @brief Construct with block size and allocator.
   *
   * @param[in] nBlockSize  The block size. Default value: 10.
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_PtrList(int nBlockSize = 10, IFX_Allocator* pAllocator = NULL);
  //<<<+++OPENSOURCE_END

  /**
   * @brief Get the header position.
   *
   * @return The header position.
   */
  FX_POSITION GetHeadPosition() const { return (FX_POSITION)m_pNodeHead; }

  /**
   * @brief Get the tail position.
   *
   * @return The tail position.
   */
  FX_POSITION GetTailPosition() const { return (FX_POSITION)m_pNodeTail; }

  /**
   * @brief Get the the current value and set the position to next node.
   *
   * @param[in, out] rPosition  Input a position, and receive the next node position as result.
   *
   * @return Current value.
   */
  void*  GetNext(FX_POSITION& rPosition) const
  {
    CNode* pNode = (CNode*)rPosition; rPosition = (FX_POSITION)pNode->pNext; return pNode->data;
  }

  /**
   * @brief Get the the current value and set the position to previous node.
   *
   * @param[in, out] rPosition  Input a position, and receive the previous node position as result.
   *
   * @return Current value.
   */
  void*  GetPrev(FX_POSITION& rPosition) const
  {
    CNode* pNode = (CNode*)rPosition; rPosition = (FX_POSITION)pNode->pPrev; return pNode->data;
  }

  /**
   * @brief Get the next position.
   *
   * @param[in] pos  The input position.
   *
   * @return The next position.
   */
  FX_POSITION  GetNextPosition(FX_POSITION pos) const { return ((CNode*)pos)->pNext; }

  /**
   * @brief Get the previous position.
   *
   * @param[in] pos  The input position.
   *
   * @return The previous position.
   */
  FX_POSITION  GetPrevPosition(FX_POSITION pos) const { return ((CNode*)pos)->pPrev; }

  /**
   * @brief Get an value at specified position.
   *
   * @param[in] rPosition  The input position.
   *
   * @return Value at specified position.
   */
  void*  GetAt(FX_POSITION rPosition) const
  {
    CNode* pNode = (CNode*)rPosition; return pNode ? pNode->data : NULL;
  }

  /**
   * @brief Get the number of nodes.
   *
   * @return The number of nodes in the list.
   */
  int    GetCount() const { return m_nCount; }

  /**
   * @brief Add a value to the tail.
   *
   * @param[in] newElement  The value to be added to tail.
   *
   * @return The new tail position.
   */
  FX_POSITION  AddTail(void* newElement);

  /**
   * @brief Add a value to the head.
   *
   * @param[in] newElement  The value to be added to head.
   *
   * @return The new head position.
   */
  FX_POSITION AddHead(void* newElement);

  /**
   * @brief Change the value at specified position.
   *
   * @param[in] pos         The position to change.
   * @param[in] newElement  The new value.
   *
   * @return None.
   */
  void  SetAt(FX_POSITION pos, void* newElement)
  {
    CNode* pNode = (CNode*)pos; pNode->data = newElement;
  }

  /**
   * @brief Insert a value after specified position.
   *
   * @param[in] pos         Specify the position.
   * @param[in] newElement  The new value.
   *
   * @return The new element position.
   */
  FX_POSITION InsertAfter(FX_POSITION pos, void* newElement);

  /**
   * @brief Find a value starting after specified position.
   *
   * @param[in] searchValue  The value to be searched.
   * @param[in] startAfter   The position to start after.
   *
   * @return The found position. <b>NULL</b> means find none.
   */
  FX_POSITION Find(void* searchValue, FX_POSITION startAfter = NULL ) const;

  /**
   * @brief Find a value by index number.
   *
   * @param[in] index  The zero-based index number of the element.
   *
   * @return The found position of the element.
   */
  FX_POSITION FindIndex(int index) const;

  /**
   * @brief Remove a node at specified position.
   *
   * @param[in] pos  The position to remove.
   *
   * @return None.
   */
  void  RemoveAt(FX_POSITION pos);

  /**
   * @brief Remove all nodes in the list.
   *
   * @return None.
   */
  void  RemoveAll();

 protected:
  /* Special allocator pointer. <b>NULL</b> means to use default allocator. */
  IFX_Allocator*  m_pAllocator;

  /* Pointer to the head. */
  CNode* m_pNodeHead;
  /* Pointer to the tail. */
  CNode* m_pNodeTail;
  /* The count of nodes in the list. */
  int m_nCount;
  /* The freed node list internal. */
  CNode* m_pNodeFree;
  /* The block list internal. */
  struct CFX_Plex* m_pBlocks;
  /* The size in nodes of each block. */
  int m_nBlockSize;

  /*
   * Allocate a new node.
   *
   * @param[in] pPrev    The pointer to the previous node.
   * @param[in] pNext    The pointer to the next node.
   *
   * @return The pointer to the new node.
   */
  CNode* NewNode(CNode* pPrev, CNode* pNext);
  /*
   * Free a node.
   *
   * @param[in] pNode    The node pointer.
   */
  void FreeNode(CNode* pNode);

 public:
  /** The destructor. */
  ~CFX_PtrList();
};

//*****************************************************************************
//* Utilities
//*****************************************************************************

/**
 * Prototype of callback function provided by custom module for deallocating private data.
 */
typedef void (*PD_CALLBACK_FREEDATA)(FX_LPVOID pData);

/**
 * The struct for private data structure.
 */
struct FX_PRIVATEDATA
{
  /**
   * @brief Free the private data pointed by m_pData.
   *
   * @return None.
   */
  void          FreeData();

  /** @brief Module ID */
  FX_LPVOID        m_pModuleId;

  /** @brief Private data. */
  FX_LPVOID        m_pData;

  /** @brief Pointer of a callback function provided by custom module for deallocating private data. */
  PD_CALLBACK_FREEDATA  m_pCallback;

  /**
   * @brief A boolean value to decide whether it is using self destruct for private data.
   *        If this is <b>true</b>, <i>m_pData</i> must point to a CFX_DestructObject derived object actually.
   */
  FX_BOOL          m_bSelfDestruct;
};

/**
 * The class represents the private data storage.
 */
class CFX_PrivateData
{
 public:
  /** 
   * @brief Construct with allocator.
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_PrivateData(IFX_Allocator* pAllocator = NULL) : m_DataList(pAllocator) {}

  /** @brief The destructor. */
  ~CFX_PrivateData();

  /**
   * @brief Release all remaining data 
   *
   *  @return None.
   */
  void          ClearAll();

  /**
   * @brief Set private data.
   * 
   * @details If the data points to an object that will belong to the attached object (which means
   *          when the attached object is destroyed, the private data should be destroyed too), then the caller
   *          must provide a callback for freeing the data.
   *          If the private data is just a number, or some external pointer, then the callback can be NULL.
   *          This function will free any previously stored data for with same module ID. The caller can not
   *          set same data twice(this will cause a crash).
   *
   * @param[in] module_id  The module id.
   * @param[in] pData      The private data.
   * @param[in] callback   The callback function for deallocating provided private data.
   *
   * @return None.
   */
  void          SetPrivateData(FX_LPVOID module_id, FX_LPVOID pData, PD_CALLBACK_FREEDATA callback);

  /**
   * @brief Set private object.
   * 
   * @details The private object will become a part of the attached object, so when the attached object is destroyed, 
   *          the private object will be destroyed too. This function will free any previously stored data
   *          for with same module ID.The caller can not set same object twice(this will cause a crash).
   *
   * @param[in] module_id  The module id.
   * @param[in] pObj       The private data in fact a CFX_DestructObject derived object.
   *
   * @return None.
   */
  void          SetPrivateObj(FX_LPVOID module_id, CFX_DestructObject* pObj);

  /**
   * @brief Get previously stored private data. Returns NULL for not stored.
   * 
   * @details This function works for private data set by function {@link CFX_PrivateData::SetPrivateData}
   *          {@link CFX_PrivateData::SetPrivateObj}.
   *
   * @param[in] module_id  The module id.
   *
   * @return The private data identified by provided module id.
   */
  FX_LPVOID        GetPrivateData(FX_LPVOID module_id);

  /**
   * @brief Lookup a private data.
   *
   * @param[in] module_id  The module id.
   * @param[out] pData     Private data.
   *
   * @return <b>true</b> means the private data exists, while <b>false</b> means not found.
   */
  FX_BOOL          LookupPrivateData(FX_LPVOID module_id, FX_LPVOID &pData) const
  {
    if (!module_id) return false;
    FX_DWORD nCount = m_DataList.GetSize();
    for (FX_DWORD n = 0; n < nCount; n++) {
      if (m_DataList[n].m_pModuleId == module_id) {
        pData = m_DataList[n].m_pData;
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Remove previously stored private data. FPDFAPI assumes the module has deallocated the data,
   *        so the free data callback will NOT be called.
   *
   * @param[in] module_id      The module id.
   *
   * @return <b>true</b> means the private data exists and has been removed successfully,
   *         while <b>false</b> means not found.
   */
  FX_BOOL          RemovePrivateData(FX_LPVOID module_id);

 protected:
  /* Private data array. */
  CFX_ArrayTemplate<FX_PRIVATEDATA>  m_DataList;
  /*
   * Add a private data. Add if not exist, otherwise modify.
   *
   * @param[in] module_id      The module id.
   * @param[in] pData          The private data.
   * @param[in] callback       The callback function for deallocating provided private data.
   * @param[in] bSelfDestruct  Whether the private data is a CFX_DestructObject derived object actually.
   *
   * @return None.
   */
  void          AddData(FX_LPVOID module_id, FX_LPVOID pData, PD_CALLBACK_FREEDATA callback, FX_BOOL bSelfDestruct);
};

/**
 * The class represents Bit stream, reading from a continuous bit stream (starting at byte boundary).
 * Assuming number of bits in each unit is not larger than 32.
 */
class CFX_BitStream : public CFX_Object
{
 public:
  /**
   * @brief Initialize the bit-stream with a memory block. Must call Init() first.
   *
   * @param[in] pData   Pointer to a memory block.
   * @param[in] dwSize  The size in bytes of the memory block.
   *
   * @return None.
   */
  void        Init(FX_LPCBYTE pData, FX_DWORD dwSize);

  /**
   * @brief Get specified number of bits (maximum 32 bits).
   *
   * @param[in] nBits  Specify the number of bits (maximum 32 bits).
   *
   * @return A FX_DWORD value.
   */
  FX_DWORD      GetBits(FX_DWORD nBits);

  /**
   * @brief Get to byte boundary. If current bit position is not multiplication of 8, the rest of the current byte will be skipped.
   *
   * @return None.
   */
  void        ByteAlign();

  /**
   * @brief Check if reached end of the stream.
   *
   * @return <b>true</b> means it reached end of the stream, while <b>false</b> means not.
   */
  FX_BOOL        IsEOF() const { return m_BitPos >= m_BitSize; }

  /**
   * @brief Skip a number of bits.
   *
   * @param[in] nBits  The number of bits to be skipped.
   *
   * @return None.
   */
  void        SkipBits(FX_DWORD nBits) { m_BitPos += nBits; }

  /**
   * @brief Rewind a bit-stream. Simply set the current bit position to be zero.
   *
   * @return None.
   */
  void        Rewind() { m_BitPos = 0; }

 protected:
  /* Bit position (zero-based). */
  FX_DWORD      m_BitPos;
  /* Total bit counts in the memory block. */
  FX_DWORD      m_BitSize;
  /* bit-stream stream buffer. */
  FX_LPCBYTE      m_pData;
};

/**
 * The class represents Bit Writer, writting a value to a continuous bit stream (starting at byte boundary).
 */
class CFX_BitWriter : public CFX_Object
{
 public:
  /**
   * @brief A constructor with bits write.
   *
   * @param[in] pBinBuf        The dynamic binary buffer.
   */
  CFX_BitWriter(CFX_BinaryBuf* pBinBuf) :m_pBinBuf(pBinBuf), m_BitPos(0), m_BytePos(0) {}

  /**
   * @brief Write a value of bits.
   *
   * @param[in] value  The value to be written.
   * @param[in] nBits  The number of bits to be written.
   *
   * @return None.
   */
  void WriteBits(FX_INT64 value, FX_INT32 nBits);

  /**
   * @brief Get to byte boundary. If current bit position is not multiplication of 8, the rest of the current byte will be skipped.
   *
   * @return None.
   */
  void ByteAlign();

  /**
   * @brief Get current byte position.
   *
   * @return Return the current byte position.
   */
  int GetCurBytePos() { return m_BytePos; }

 protected:
  /* Dynamic binary buffer. */
  CFX_BinaryBuf * m_pBinBuf;
  /* Bit position (zero-based). */
  int m_BitPos;
  /* Byte position (zero-based). */
  int m_BytePos;
};

/**
 * The class represents accessor of reference counted object.
 * To use reference counted objects, application can use this template with particular object class.
 */
template <class ObjClass> class CFX_CountRef : public CFX_Object
{
 public:
  /** @brief Type definition: it is used short for CFX_CountRef<ObjClass>. */
  typedef CFX_CountRef<ObjClass> Ref;

  /**
   * @brief Define a class here derived from user data class, with an additional reference count member.
   */
  class CountedObj : public ObjClass
  {
 public:
    /** @brief The constructor. */
    CountedObj():m_RefCount(0) {}

    /**
     * @brief The copy constructor.
     *
     * @param[in] src The other counted object. 
     */
    CountedObj(const CountedObj& src) : ObjClass(src) ,m_RefCount(0){}

    /** @brief The reference count. */
    int      m_RefCount;
  };

  /**
   * @brief Construct a null reference.
   */
  CFX_CountRef()
  {
    m_pObject = NULL;
  }

  /**
   * @brief Copy constructor from another reference.
   *
   * @param[in] ref  The input reference.
   */
  CFX_CountRef(const Ref& ref)
  {
    m_pObject = ref.m_pObject;
    if (m_pObject) m_pObject->m_RefCount ++;
  }

  /**
   * @brief Destruct a reference and release the object it refers to.
   */
  ~CFX_CountRef()
  {
    if (!m_pObject) return;
    m_pObject->m_RefCount --;
    if (m_pObject->m_RefCount <= 0) {
      delete m_pObject;
      m_pObject = NULL;
    }
  }

  /**
   * @brief Create a new object and refer to it.
   *        The returned pointer to the object can be used to modify the content of objects.
   *
   * @return A modifiable object pointer.
   */
  ObjClass*      New()
  {
    if (m_pObject) {
      m_pObject->m_RefCount --;
      if (m_pObject->m_RefCount <= 0)
        delete m_pObject;
      m_pObject = NULL;
    }
    m_pObject = FX_NEW CountedObj;
    if (!m_pObject) return NULL;
    m_pObject->m_RefCount = 1;
    return m_pObject;
  }

  /**
   * @brief Assignment(=) operator overload. Assign from another reference.
   *
   * @param[in] ref  The input reference.
   *
   * @return None.
   */
  void        operator = (const Ref& ref)
  {
    if (ref.m_pObject)
      ref.m_pObject->m_RefCount ++;
    if (m_pObject) {
      m_pObject->m_RefCount --;
      if (m_pObject->m_RefCount <= 0)
        delete m_pObject;
    }
    m_pObject = ref.m_pObject;
  }

  /**
   * @brief assignment(=) operator overload. Assign from a typeless pointer.
   *
   * @param[in] p  It must be zero. Other value is not valid.
   *
   * @return None.
   */
  void        operator = (void* p)
  {
    FXSYS_assert(p == 0);
    if (m_pObject == NULL) return;
    m_pObject->m_RefCount --;
    if (m_pObject->m_RefCount <= 0)
      delete m_pObject;
    m_pObject = NULL;
  }

#if defined(_FX_MANAGED_CODE_) && defined(GetObject)
  #undef GetObject
#endif
  /**
   * @brief Get a pointer of constant object. This pointer can't be used to alter the object content.
   *
   * @return A pointer to the constant object.
   */
  const ObjClass*    GetObject() const
  {
    return m_pObject;
  }
  /**
   * @brief This casting operator get a pointer of the constant object.
   *
   * @return A pointer to the constant object.
   */
  operator      const ObjClass*() const
  {
    return m_pObject;
  }

  /**
   * @brief Check if the pointer of the object is <b>NULL</b>.
   *
   * @return <b>true</b> means the pointer of object is <b>NULL</b>, while <b>false</b> means not.
   */
  FX_BOOL        IsNull() const
  {
    return m_pObject == NULL;
  }
  /**
   * @brief Check if the pointer of the object is not <b>NULL</b>.
   *
   * @return <b>true</b> means the pointer of object is not <b>NULL</b>, while <b>false</b> means <b>NULL</b>.
   */
  FX_BOOL        NotNull() const
  {
    return m_pObject != NULL;
  }

  /**
   * @brief Get a modifiable copy of the object.
   *
   * @details If the reference was refer to null, then a new object will be created.
   *          The returned pointer can be used to alter the object content.
   *
   * @return A pointer to the object.
   */
  ObjClass*      GetModify()
  {
    if (m_pObject == NULL) {
      m_pObject = FX_NEW CountedObj;
      if (m_pObject)
        m_pObject->m_RefCount = 1;
    } else if (m_pObject->m_RefCount > 1) {
      m_pObject->m_RefCount --;
      CountedObj* pOldObject = m_pObject;
      m_pObject = NULL;
      m_pObject = FX_NEW CountedObj(*pOldObject);
      if (m_pObject)
        m_pObject->m_RefCount = 1;
    }
    return m_pObject;
  }

  /**
   * @brief Set the pointer of the object to be null.
   *
   * @return None.
   */
  void        SetNull()
  {
    if (m_pObject == NULL) return;
    m_pObject->m_RefCount --;
    if (m_pObject->m_RefCount <= 0)
      delete m_pObject;
    m_pObject = NULL;
  }

  /**
   * @brief Comparison(==) operator overload. Compare with another reference.
   *
   * @param[in] ref  Another Ref object.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  FX_BOOL        operator == (const Ref& ref) const
  {
    return m_pObject == ref.m_pObject;
  }

  /**
   * @brief Get the reference count.
   *
   * @return The count of reference.
   */
  int          RefCount() const
  {
    return m_pObject ? m_pObject->m_RefCount : 0;
  }

  /**
   * @brief Increase the reference. 
   *
   * @return None.
   */
  void        Incref()
  {
    if (m_pObject == NULL) return;
    m_pObject->m_RefCount++;
  }

  /**
   * @brief Decrease the reference. 
   *
   * @return None.
   */
  void        Decref()
  {
    if (m_pObject == NULL) return;
    m_pObject->m_RefCount--;
    if (m_pObject->m_RefCount <= 0) {
      delete m_pObject;
      m_pObject = NULL;
    }
  }

 protected:
  /* Reference counted object internal. */
  CountedObj*      m_pObject;
};

/**The class represents the callback for pause interface.*/
class IFX_Pause
{
 public:
  /** @brief Destructor. */
  virtual ~IFX_Pause() {}

  /**
   * @brief Check whether callers need to pause now.
   *
   * @return <b>true</b> means to pause now, while <b>false</b> means not to pause now.
   */
  virtual FX_BOOL  NeedToPauseNow() = 0;
};

/** Base class for data filters. A data filter takes some input data and outputs to another filter, or the final destination buffer.*/
class CFX_DataFilter : public CFX_Object
{
 public:
  /**
   * @brief The destructor. Destroy this filter and all its chain.
   */
  virtual ~CFX_DataFilter();

  /**
   * @brief Set destination filter. Note the filter will be appended to the end of current filter chain.
   *
   * @param[in] pFilter  The input data filter.
   *
   * @return None.
   */
  void      SetDestFilter(CFX_DataFilter* pFilter);

  /**
   * @brief Detect EOF.
   *
   * @return <b>true</b> means it met EOF, while <b>false</b> means not yet.
   */
  FX_BOOL      IsEOF() const { return m_bEOF; }

  /**
   * @brief Get current position in the source stream (byte offset from the beginning of all input data).
   *
   * @return The current position in the source stream.
   */
  FX_FILESIZE    GetSrcPos() const { return m_SrcPos; }

  /**
   * @brief Input a data block to the filter (and its filter chain), and receive the final output.
   *
   * @param[in] src_buf    The input data block.
   * @param[in] src_size   The size in bytes of the input data block.
   * @param[out] dest_buf  It receives the output data.
   *
   * @return None.
   */
  void      FilterIn(FX_LPCBYTE src_buf, size_t src_size, CFX_BinaryBuf& dest_buf);

  /**
   * @brief Indicate the input finished.
   *        For some filters, there might be some last output generated.
   *
   * @param[out] dest_buf  It receives the output data.
   *
   * @return None.
   */
  void      FilterFinish(CFX_BinaryBuf& dest_buf);

  /**
   * @brief Indicate whether this filter exhausts the input buffer.
   *
   * @return <b>true</b> means input buffer is exhausted., while <b>false</b> means not.
   */
  FX_BOOL      IsExhaustBuffer() const { return m_bExhaustBuffer; }

  /**
   * @brief Indicate whether this filter needs to input new src data.
   *
   * @return <b>true</b> means all filters exhaust the input buffer, while <b>false</b> means not.
   */
  FX_BOOL      NeedNewSrc();

  /**
   * @brief Indicate whether to abort the filter process.
   *
   * @return <b>true</b> means to abort, while <b>false</b> means not.
   */
  FX_BOOL      Abort() const { return m_bAbort; }

  /**
   * @brief Indicate whether to abort the filter process, including all dest filter.
   *
   * @return <b>true</b> means to abort, while <b>false</b> means not.
   */
  FX_BOOL      AbortAll();

  /**
   * @brief Reset statistics.
   *
   * @return None.
   */
  void      ResetStatistics();

 protected:
  /* The constructor. */
  CFX_DataFilter();

  virtual void  v_FilterIn(FX_LPCBYTE src_buf, size_t src_size, CFX_BinaryBuf& dest_buf) = 0;
  virtual void  v_FilterFinish(CFX_BinaryBuf& dest_buf) = 0;
  virtual void  v_ResetStatistics() {};
  void      ReportEOF(FX_FILESIZE left_input);

  /* Indicate whether we met the EOF. */
  FX_BOOL      m_bEOF;
  /* Current position in the source stream. */
  FX_FILESIZE    m_SrcPos;
  /* Filter chain. */
  CFX_DataFilter*  m_pDestFilter;

  /* Indicate whether this filter exhausts the input buffer. */
  FX_BOOL      m_bExhaustBuffer;
  /* Store the output data of the FilterIn function.*/
  CFX_BinaryBuf  m_FilterInBuffer;

  /* Indicate whether this filter aborts the filter process. For instance, RunLenFilter meets bad input data */
  FX_BOOL      m_bAbort;
};

/** The class represents the auto restorer.*/
template<typename T>
class CFX_AutoRestorer {
 public:
  /**
   * @brief The constructor. 
   *
   * @param[in] location  The location. 
   */
  explicit CFX_AutoRestorer(T* location) {
    m_Location = location;
    m_OldValue = *location;
  }

  /** @brief The destructor. */
  ~CFX_AutoRestorer() { *m_Location = m_OldValue; }
 private:
  T* m_Location;
  T m_OldValue;
};

/**The class represents the smart pointer.*/
template <class T>
class CFX_SmartPointer
{
 public:
  /**
   * @brief The constructor. 
   *
   * @param[in] pObj  The kernel object. 
   */
  CFX_SmartPointer(T *pObj) : m_pObj(pObj) {}

  /** @brief The destructor. */
  ~CFX_SmartPointer() {m_pObj->Release();}

  /**
   * @brief Get the object pointer.
   *
   * @return The object pointer.
   */
  T*    Get(void)  {return m_pObj;}

  /**
   * @brief Get the object reference operator.
   *
   * @return The object reference.
   */
  T&    operator *(void)  {return *m_pObj;}

  /**
   * @brief Get the object pointer operator.
   *
   * @return The object pointer.
   */
  T*    operator ->(void)  {return m_pObj;}

 protected:
  T *m_pObj;
};

#define FX_DATALIST_LENGTH  1024

/** The class represents sorted list array template.*/
template<size_t unit>
class CFX_SortListArray : public CFX_Object
{
 protected:
  /** @brief The data list. */
  struct DataList {
    /** @brief The start index. */
    FX_INT32  start;
    /** @brief The data count. */
    FX_INT32  count;
    FX_LPBYTE  data;
    DataList()
    {
      start = count = 0;
      data = NULL;
    }
  };

 public:
  /**
   * @brief The constructor. 
   *
   * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
   */
  CFX_SortListArray(IFX_Allocator* pAllocator = NULL) : m_CurList(0), m_DataLists(pAllocator) {}

  /** @brief The destructor. */
  ~CFX_SortListArray()
  {
    Clear();
  }

  /**
   * @brief Clear the data list.
   *
   * @return None.
   */
  void      Clear()
  {
    IFX_Allocator* pAllocator = m_DataLists.m_pAllocator;

    for (FX_INT32 i = m_DataLists.GetUpperBound(); i >= 0; i--){
      DataList list = m_DataLists.ElementAt(i);
      if (list.data) FX_Allocator_Free(pAllocator, list.data);
    }
    m_DataLists.RemoveAll();
    m_CurList = 0;
  }

  /**
   * @brief Append a list data
   *
   * @param[in] nStart  The start index of data
   * @param[in] nCount  The count of data
   * 
   * @return None.
   */
  void      Append(FX_INT32 nStart, FX_INT32 nCount)
  {
    if (nStart < 0) return;

    IFX_Allocator* pAllocator = m_DataLists.m_pAllocator;

    while (nCount > 0){
      FX_INT32 temp_count = FX_MIN(nCount, FX_DATALIST_LENGTH);
      DataList list;

      list.data = FX_Allocator_Alloc(pAllocator, FX_BYTE, temp_count * unit);
      if (!list.data) break;
      FXSYS_memset32(list.data, 0, temp_count * unit);
      list.start = nStart;
      list.count = temp_count;

      FX_BOOL ret = Append(list);
      if(ret)
      {
        nCount -= temp_count;
        nStart += temp_count;
      }
      else
      {
        if (list.data) FX_Allocator_Free(pAllocator, list.data);
        return;
      }
    }
  }

  /**
   * @brief Get the data.
   *
   * @param[in] nIndex  The data index.
   *
   * @return The data.
   */
  FX_LPBYTE    GetAt(FX_INT32 nIndex)
  {
    if (nIndex < 0) return NULL;
    if (m_CurList < 0 || m_CurList >= m_DataLists.GetSize()) return NULL;
    DataList *pCurList = m_DataLists.GetDataPtr(m_CurList);
    if (!pCurList || nIndex < pCurList->start || nIndex >= pCurList->start + pCurList->count){
      pCurList = NULL;
      FX_INT32 iStart = 0;
      FX_INT32 iEnd = m_DataLists.GetUpperBound();
      while (iStart <= iEnd){
        FX_INT32 iMid = (iStart + iEnd) / 2;
        DataList* list = m_DataLists.GetDataPtr(iMid);
        if (nIndex < list->start)
          iEnd = iMid - 1;
        else if (nIndex >= list->start + list->count)
          iStart = iMid + 1;
        else {
          pCurList = list;
          m_CurList = iMid;
          break;
        }
      }
    }
    return pCurList ? pCurList->data + (nIndex - pCurList->start) * unit : NULL;
  }

 protected:
  FX_BOOL      Append(const DataList& list)
  {
    FX_INT32 iStart = 0;
    FX_INT32 iEnd = m_DataLists.GetUpperBound();
    FX_INT32 iFind = 0;
    while (iStart <= iEnd) {
      FX_INT32 iMid = (iStart + iEnd) / 2;
      DataList* cur_list = m_DataLists.GetDataPtr(iMid);
      if (list.start == cur_list->start){
        return false; // lists overlap, no op
      } else if (list.start < cur_list->start + cur_list->count)
        iEnd = iMid - 1;
      else{
        if (iMid == iEnd){
          iFind = iMid + 1;
          break;
        }
        DataList* next_list = m_DataLists.GetDataPtr(iMid + 1);
        if (list.start == next_list->start){
          return false; // lists overlap, no op
        } else if (list.start < next_list->start){
          iFind = iMid + 1;
          break;
        } else {
          iStart = iMid + 1;
        }
      }
    }
    m_DataLists.InsertAt(iFind, list);
    return true;
  }

  FX_INT32    m_CurList;
  CFX_ArrayTemplate<DataList>  m_DataLists;
};

/** The class represents the list array template.*/
template<typename T1, typename T2>
class CFX_ListArrayTemplate : public CFX_Object
{
 public:
  /**
   * @brief Clear data.
   *
   * @return None.
   */
  void      Clear()
  {
    m_Data.Clear();
  }

  /**
   * @brief Add a list data.
   *
   * @param[in] nStart  The start index of data
   * @param[in] nCount  The count of data
   *
   * @return None.
   */
  void      Add(FX_INT32 nStart, FX_INT32 nCount)
  {
    m_Data.Append(nStart, nCount);
  }

  /**
   * @brief Subscript([]) operator overload.
   *
   * @param[in] nIndex  The data index.
   *
   * @return The retrieved element.
   */
  T2& operator [] (FX_INT32 nIndex)
  {
    FX_LPBYTE data = m_Data.GetAt(nIndex);
    FXSYS_assert(data != NULL);

    return (T2&)(*(volatile T2*)data);
  }

  /**
   * @brief Get a point to data.
   *
   * @param[in] nIndex  The data index.
   *
   * @return Pointer to the element specified by index.
   */
  T2* GetPtrAt(FX_INT32 nIndex)
  {
    return (T2*)m_Data.GetAt(nIndex);
  }
 protected:
  T1      m_Data;
};

/** @brief Type definition for file size list array. */
typedef CFX_ListArrayTemplate<CFX_SortListArray<sizeof(FX_FILESIZE)>, FX_FILESIZE>  CFX_FileSizeListArray;
/** @brief Type definition for FX_DWORD list array. */
typedef CFX_ListArrayTemplate<CFX_SortListArray<sizeof(FX_DWORD)>, FX_DWORD>    CFX_DWordListArray;

/**
 * @brief Enumeration for progressive status
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum {
    /** @brief Ready. */
    Ready,
    /** @brief To be continued. */
    ToBeContinued,
    /** @brief Found. */
    Found,
    /** @brief Not Found. */
    NotFound,
    /** @brief Failed. */
    Failed,
    /** @brief Done. */
    Done
} FX_ProgressiveStatus;

#define ProgressiveStatus  FX_ProgressiveStatus

#ifdef _FX_NO_NAMESPACE_
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT
#define FX_NAMESPACE_DECLARE(namespace, type)       type
//<<<+++OPENSOURCE_END
#else
//<<<+++OPENSOURCE_BEGIN LIC==GOOGLE
#define FX_NAMESPACE_DECLARE(namespace, type)       namespace::type
//<<<+++OPENSOURCE_END
#endif

/** This class represents a unknown object.*/
class IFX_Unknown
{
 public:
  /** 
   * @brief Decrements reference count and release the current object.
   *  
   * @return The reference count.
   */
  virtual FX_DWORD  Release() = 0;

  /** 
   * @brief Increments reference count.
   *  
   * @return The reference count.
   */
  virtual FX_DWORD  AddRef() = 0;

 protected:
  virtual ~IFX_Unknown() {}
};

/** @brief Judge whether an integer is odd or even*/
#define FX_IsOdd(a)  ((a) & 1)

//<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#endif // _FX_BASIC_H_
//<<<+++OPENSOURCE_MUST_END

/** @} */

//<<<+++OPENSOURCE_END
